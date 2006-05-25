/* file: $Id$
 *
 * A recursive descend parser for Tm datastructure definitions.
 */

#include <tmc.h>
#include "tmdefs.h"

#include "tmcode.h"
#include "error.h"
#include "global.h"
#include "lex.h"
#include "misc.h"
#include "dsparser.h"
#include "checkds.h"
#include "srchfile.h"

static lextok curr_token;

/* Forward declarations. */
static tmbool parse_class_components( classComponent_list *clp );
static void update_class_info(
    tmsymbol nm,
    tmsymbol_list *inherits,
    Field_list *fields,
    ds_list *types,
    const classComponent cc,
    tmbool *isvirtual
);

/* Given a tmstring list 'l' and a tmstring 's', add 's' to the
 * list 'l' and return the newly constructed list. Reject strings
 * that are already defined.
 */
static tmsymbol_list add_inherit_list( /*@returned@*/ tmsymbol_list l, tmsymbol s )
{
    if( member_tmsymbol_list( s, l ) ){
        /* FIXME: do something smarter. */
	/* (void) sprintf( errarg, "'%s'", s->name ); */
	parserror( "duplicate inheritance" );
    }
    else {
	l = append_tmsymbol_list( l, rdup_tmsymbol( s ) );
    }
    return l;
}

/* Given a (constructor) type list 'l' and a constructor type 'c', add c to the
 * list l and return the newly constructed list. Reject constructors
 * that are already defined.
 */
static ds_list add_constructor_list( ds_list l, const_ds c )
{
    unsigned int ix;
    const_origsymbol cnm = c->name;

    for( ix=0; ix<l->sz; ix++ ){
        const_origsymbol nm = l->arr[ix]->name;

	if( cnm->sym == nm->sym ){
#if 0
            /* FIXME: enable again. */
	    (void) sprintf( errarg, "'%s'", cnm->sym->name );
#endif
	    parserror( "double use of constructor name" );
            origin_error( nm->org, " ... previous definition" );
	    return l;
	}
    }
    l = append_ds_list( l, rdup_ds( c ) );
    return l;
}

/* Given two constructor types 'a' and 'b', return a new constructor
 * type that has the constructors of both.
 * It *must* be certain that 'a' and 'b' are both constructor types.
 */
static ds merge_cons_types( const_ds a, const_ds b )
{
    tmsymbol_list ila;
    tmsymbol_list ilb;
    unsigned int ix;

    tmsymbol_list la = rdup_tmsymbol_list( to_const_DsConstructorBase(a)->constructors );
    tmsymbol_list lb = rdup_tmsymbol_list( to_const_DsConstructorBase(b)->constructors );
    la = concat_tmsymbol_list( la, lb );
    ila = rdup_tmsymbol_list( a->inherits );
    ilb = b->inherits;
    for( ix=0; ix<ilb->sz; ix++ ){
	ila = add_inherit_list( ila, ilb->arr[ix] );
    }
    return to_ds( new_DsConstructorBase( rdup_origsymbol( a->name ), ila, tmsymbol_listNIL, la ) );
}

/* Given a type 't', a constructor name 'cnm' and a type name
 * 'tnm' to which the constructor belongs, ensure that if 't' is a constructor
 * type, 'cnm' does not occur in it.
 */
static void check_constructor_name_type( const_ds t, const_tmsymbol cnm, const_origsymbol tnm )
{
    tmsymbol_list cl;

    if( t->tag != TAGDsConstructorBase ){
	return;
    }
    cl = to_const_DsConstructorBase(t)->constructors;
    if( member_tmsymbol_list( cnm, cl ) ){
	origsymbol_error( tnm, "constructor '%s' already defined", cnm->name );
    }
}

/* Given a list of types 'l', a constructor name 'cnm' and a type name
 * 'tnm' to which the constructor belongs, ensure that 'cnm' does not
 * occur in any of the constructor types of 'l'.
 */
static void check_constructor_name( const_ds_list l, const_tmsymbol cnm, const_origsymbol tnm )
{
    unsigned int ix;

    for( ix=0; ix<l->sz; ix++ ){
	check_constructor_name_type( l->arr[ix], cnm, tnm );
    }
}

/* Given a list of types 'l' and a type 't', ensure that if 't' is a
 * constructor type, it does not contain the same constructor names
 * as in previous constructor types.
 */
static void check_constructor_names( const_ds_list l, const_ds t )
{
    tmsymbol_list cl;
    unsigned int ix;
    origsymbol tnm;

    if( t->tag != TAGDsConstructorBase ){
	return;
    }
    cl = to_const_DsConstructorBase(t)->constructors;
    tnm = t->name;
    for( ix=0; ix<cl->sz; ix++ ){
	check_constructor_name( l, cl->arr[ix], tnm );
    }
}

/* Add a new type 't' to the list of types 'l'. If it has the
 * same name as a previously defined one, reject it, unless both the
 * old one and the nw one are constructor types. In that case the constructors
 * of the nw type are added to the previous ones.
 *
 * Also, ensure that if the type is a constructor type it does not have
 * the same constructor names as previous ones.
 */
static ds_list add_ds_list( ds_list l, ds t )
{
    origsymbol nm;	/* Name of the new type. */
    unsigned int ix;	/* Index of any previous def'n of it. */
    ds old;		/* The old type definition. */
    ds nw;		/* The type constructed from two constr. def'ns. */

    if( t->tag == TAGDsInclude ){
        l = append_ds_list( l, rdup_ds( t ) );
        return l;
    }
    nm = t->name;
    ix = find_type_ix( l, nm->sym );
    if( ix<l->sz ){
	old = l->arr[ix];
	if( old->tag == TAGDsConstructorBase && t->tag == TAGDsConstructorBase ){
	    nw = merge_cons_types( old, t );
	    l = delete_ds_list( l, ix );
	    l = append_ds_list( l, nw );
	}
	else {
#if 0
	    (void) sprintf( errarg, "'%s'", nm->sym->name );
#endif
	    parserror( "redefinition of type" );
	}
    }
    else {
	check_constructor_names( l, t );
	l = append_ds_list( l, rdup_ds( t ) );
    }
    return l;
}

/* Unconditionally get the next token from the lexical analyzer. */
static void next_token( void )
{
    curr_token = yylex();
}

/* Try to parse a field type, and set
 * '*tp' to the constructed field. Return TRUE if you have constructed
 * a valid field.
 */
static tmbool parse_Type( Type *tp )
{
    tmbool ok;

    if( curr_token==LSBRAC ){
	next_token();
	ok = parse_Type( tp );
	if( !ok ){
	    return FALSE;
	}
	(*tp)->level++;
	if( curr_token==RSBRAC ){
	    next_token();
	}
	else {
	    parserror( "']' expected" );
	}
	return TRUE;
    }
    if( curr_token==NAME ){
	*tp = new_Type( 0, yylval.parsymbol );
	next_token();
	return TRUE;
    }
    parserror( "type specification expected" );
    return FALSE;
}

/* Try to parse a field. Return TRUE iff you have a valid field. */
static tmbool parse_field( Field *fp )
{
    tmsymbol elmname;
    tmbool ok = TRUE;
    Type t = TypeNIL;
    tmbool recovery = FALSE;

    if( curr_token!=NAME ){
	return FALSE;
    }
    elmname = yylval.parsymbol;
    next_token();
    if( curr_token!=COLON ){
	parserror( "':' expected" );
        recovery = TRUE;
    }
    else {
        next_token();
    }
    if( (!recovery) || curr_token == LSBRAC || curr_token == NAME ){
        ok = parse_Type( &t );
    }
    *fp = new_Field( new_origsymbol( elmname, make_origin() ), t );
    return ok;
}

/* Try to parse a list of fields for a constructor body. 
 * keep parsing field definitions until you encounter
 * a '|' or a ')'. 
 *
 * Return TRUE iff you have a valid constructor body.
 */
static tmbool parse_Field_list( Field_list *flp )
{
    tmbool ok;
    Field nw;

    *flp = new_Field_list();
    for(;;){
	ok = parse_field( &nw );
	if( ok ){
	    *flp = append_Field_list( *flp, nw );
	}
	else {
	    break;
	}
    }
    return TRUE;
}

/* Given the name of the constructor type these constructors are member
 * of, the name of the construcotr (if it isn't empty), try to parse a
 * constructor. Return TRUE iff this succeeded.
 */
static tmbool parse_constructor( tmsymbol super, tmsymbol p_nm, ds *cp )
{
    tmbool ok;
    Field_list fl;
    tmsymbol nm;

    if( p_nm == tmsymbolNIL ){
	if( curr_token!=NAME ){
	    return FALSE;
	}
	nm = yylval.parsymbol;
	next_token();
    }
    else {
	nm = p_nm;
    }
    ok = parse_Field_list( &fl );
    if( !ok ){
	parserror( "invalid field list" );
	return FALSE;
    }
    *cp = (ds) new_DsConstructor(
	new_origsymbol( nm, make_origin() ),
	append_tmsymbol_list( new_tmsymbol_list(), super ),
	tmsymbol_listNIL,
	fl
    );
    return TRUE;
}

/* Given the name of the constructor type these constructors are member
 * of, the name of the first constructor 'nm' (if it isn't empty),
 * try to parse a list of constructors up to (but not including)
 * the final ';'. Return TRUE if you have a valid constructor list.
 */
static tmbool parse_constructor_list( tmsymbol super, tmsymbol nm, ds_list *clp )
{
    tmbool ok;
    ds nw;

    *clp = new_ds_list();
    if( curr_token==SEMI ){
	if( nm != tmsymbolNIL ){
	    *clp = append_ds_list(
		*clp,
		(ds) new_DsConstructor(
                    new_origsymbol( nm, make_origin() ),
		    append_tmsymbol_list( new_tmsymbol_list(), super ),
		    tmsymbol_listNIL,
		    new_Field_list()
		)
	    );
	}
	return TRUE;
    }
    for(;;){
	ok = parse_constructor( super, nm, &nw );
	nm = tmsymbolNIL;
	if( ok ){
	    *clp = add_constructor_list( *clp, nw );
	    rfre_ds( nw );
	}
	else {
	    parserror( "constructor expected" );
	    /* Try to recover by skipping tokens up to the next
	     * '|', ';' or LEXEOF.
	     */
	    while( curr_token!=BAR && curr_token!=SEMI && curr_token!=LEXEOF ){
		if( curr_token == STRING ){
		    rfre_tmstring( yylval.parstring );
		}
		next_token();
	    }
	}
	if( curr_token==SEMI || curr_token==LEXEOF ){
	    break;
	}
	if( curr_token==BAR ){
	    next_token();
	}
	else {
	    parserror( "'|' expected" );
	}
    }
    return TRUE;
}

/* Try to parse the remainder
 * of a constructor definition, up to (but not including) the final ';'.
 * Return TRUE if this succeeded, and set *tp to the parsed constructor.
 */
static tmbool parse_constructor_type( tmsymbol nm, ds_list *tp )
{
    tmbool ok;
    ds_list cl;
    tmsymbol_list inherits;
    tmsymbol cnm = tmsymbolNIL;
    unsigned int ix;
    tmsymbol_list members;

    inherits = new_tmsymbol_list();
    /* First eat all names followed by a '+'. After that assume
     * that the first constructor has started.
     */
    while( curr_token == NAME ){
	cnm = yylval.parsymbol;
	next_token();
	if( curr_token != PLUS ){
	    /* Not a plus, so at least it isn't an inherit. */
	    break;
	}
	inherits = add_inherit_list( inherits, cnm );
	cnm = tmsymbolNIL;
	next_token();	/* Eat the PLUS */
    }
    ok = parse_constructor_list( nm, cnm, &cl );
    members = new_tmsymbol_list();
    for( ix=0; ix<cl->sz; ix++ ){
	tmsymbol mnm = cl->arr[ix]->name->sym;

	members = append_tmsymbol_list( members, mnm );
    }
    *tp = append_ds_list(
	new_ds_list(),
	(ds) new_DsConstructorBase( new_origsymbol( nm, make_origin() ), inherits, tmsymbol_listNIL, members )
    );
    *tp = concat_ds_list( *tp, cl );
    return ok;
}

/* Try to parse a list of fields for a tuple or class body.
 *
 * Return TRUE iff you have a valid tuple or class body.
 */
static tmbool parse_tuplebody( Field_list *flp )
{
    tmbool ok;
    Field nw;

    *flp = new_Field_list();
    if( curr_token == RRBRAC || curr_token == RCBRAC ){
	return TRUE;
    }
    for(;;){
	ok = parse_field( &nw );
	if( ok ){
	    *flp = append_Field_list( *flp, nw );
	}
	else {
	    parserror( "field expected" );
	    /* Try to recover by skipping tokens up to the next
	     * ',', ,}', ')', ';' or LEXEOF. */
	    while(
		   curr_token!=COMMA
		&& curr_token!=RRBRAC
		&& curr_token!=SEMI
		&& curr_token!=LEXEOF
		&& curr_token!=RCBRAC
	    ){
		if( curr_token == STRING ){
		    rfre_tmstring( yylval.parstring );
		}
		next_token();
	    }
	}
	if( curr_token==COMMA ){
	    next_token();
	}
	else {
	    break;
	}
    }
    return TRUE;
}

/* Given a type name 'nm', try to parse a tuple definition. Return
 * TRUE iff you have a valid tuple.
 */
static tmbool parse_tuple_type( tmsymbol nm, ds *tp )
{
    tmbool ok;
    Field_list body;
    tmsymbol_list inherits;

    inherits = new_tmsymbol_list();
    while( curr_token == NAME ){
	inherits = add_inherit_list( inherits, yylval.parsymbol );
	next_token();
	if( curr_token == PLUS ){
	    next_token();
	}
	else {
	    parserror( "'+' expected" );
	    rfre_tmsymbol_list( inherits );
	    return FALSE;
	}
    }
    if( curr_token==LRBRAC ){
	next_token();
    }
    else {
	parserror( "'(' expected" );
	rfre_tmsymbol_list( inherits );
	return FALSE;
    }
    ok = parse_tuplebody( &body );
    if( !ok ){
	rfre_tmsymbol_list( inherits );
	return FALSE;
    }
    if( curr_token==RRBRAC ){
	next_token();
    }
    else {
	parserror( "')' expected" );
    }
    cktuple( nm, body, inherits );
    *tp = to_ds( new_DsTuple( new_origsymbol( nm, make_origin() ), inherits, tmsymbol_listNIL, body ) );
    return TRUE;
}

/* Given a pointer to a class component, try to parse
 * a class component. Return TRUE if you have a valid class component.
 *
 * Do not try to eat the '+' that separates components.
 */
static tmbool parse_class_component( classComponent *cp )
{
    tmbool ok;
    classComponent res;

    if( curr_token == LCBRAC ){
	Field_list fields;

	next_token();
	/* We want a list of field definitions. */
	ok = parse_tuplebody( &fields );
	if( !ok ){
	    return FALSE;
	}
	res = (classComponent) new_CCFields( fields );
	if( curr_token != RCBRAC ){
	    /* '{' to balance bracket below */
	    parserror( "'}' expected" );
	    rfre_classComponent( res );
	    return FALSE;
	}
	next_token();
	*cp = res;
	return TRUE;
    }
    if( curr_token == NAME ){
	/* This can be either a inherit specification or a list of
	 * alternatives.
	 */
	tmsymbol nm = yylval.parsymbol;

	next_token();
	if( curr_token == COLON ){
	    alternative_list alts;
	    classComponent cc;

	    /* This is a labeled component, presumably part of a list
	     * of labeled components.
	     */
	    alts = new_alternative_list();
	    for(;;){
		next_token();
		if( !parse_class_component( &cc ) ){
		    rfre_alternative_list( alts );
		    return FALSE;
		}
		alts = append_alternative_list( alts, new_alternative( nm, cc ) );
		if( curr_token != BAR ){
		    break;
		}
		/* There was a bar, so there should be another labeled
		 * class component here.
		 */
		next_token();
		if( curr_token != NAME ){
		    parserror( "label name expected, because a '|' must be followed by a label" );
		    rfre_alternative_list( alts );
		    return FALSE;
		}
		nm = yylval.parsymbol;
		next_token();
		if( curr_token != COLON ){
		    parserror( "':' expected, because a '|' must be followed by a label" );
		}
	    }
	    res = (classComponent) new_CCAlternatives( alts );
	}
	else {
	    /* Presumably was an inherit. Fine. */
	    res = (classComponent) new_CCSuper( nm );
	}
	*cp = res;
	return TRUE;
    }
    if( curr_token == LRBRAC ){
	classComponent_list ccl;

	/* It is a bracketed sublist. */
	next_token();
	ok = parse_class_components( &ccl );
	if( !ok ){
	    return FALSE;
	}
	res = (classComponent) new_CCSublist( ccl );
	if( curr_token != RRBRAC ){
	    /* '(' to balance bracket below */
	    parserror( "')' expected" );
	    rfre_classComponent( res );
	    return FALSE;
	}
	next_token();
	*cp = res;
	return TRUE;
    }
    parserror( "class type component expected" );
    return FALSE;
}

/* Given a pointer to a list of class components, try to parse
 * a class type definition. Return TRUE if you have a valid class type.
 */
static tmbool parse_class_components( classComponent_list *clp )
{
    tmbool ok;
    classComponent_list cl;
    classComponent cc;

    cl = new_classComponent_list();
    if( curr_token == SEMI ){
	*clp = cl;
	return TRUE;
    }
    for(;;){
	ok = parse_class_component( &cc );
	if( !ok ){
	    rfre_classComponent_list( cl );
	    return FALSE;
	}
	cl = append_classComponent_list( cl, cc );
	if( curr_token != PLUS ){
	    break;
	}
	next_token();
    }
    *clp = cl;
    return TRUE;
}

static ds_list create_subtype( tmsymbol nm, tmsymbol super, const classComponent comp )
{
    tmsymbol_list inherits;
    Field_list fields;
    ds_list types;
    tmbool isvirtual = TMFALSE;

    inherits = new_tmsymbol_list();
    fields = new_Field_list();
    types = new_ds_list();
    inherits = append_tmsymbol_list( inherits, super );
    update_class_info( nm, &inherits, &fields, &types, comp, &isvirtual );
    types = append_ds_list(
	types,
	to_ds( new_DsClass( new_origsymbol( nm, make_origin() ), inherits, tmsymbol_listNIL, fields, isvirtual ) )
    );
    return types;

}

static void update_class_info(
    tmsymbol nm,
    tmsymbol_list *inherits,
    Field_list *fields,
    ds_list *types,
    const classComponent cc,
    tmbool *isvirtual
)
{
    switch( cc->tag ){
	case TAGCCSuper:
	    *inherits = append_tmsymbol_list( *inherits, to_CCSuper(cc)->super );
	    break;

	case TAGCCFields:
	    *fields = concat_Field_list(
		*fields,
		rdup_Field_list( to_CCFields(cc)->fields )
	    );
	    break;

	case TAGCCSublist:
	{
	    unsigned int ix;
	    classComponent_list ccl;

	    ccl = to_CCSublist(cc)->components;
	    for( ix=0; ix<ccl->sz; ix++ ){
		update_class_info( nm, inherits, fields, types, ccl->arr[ix], isvirtual );
	    }
	    break;
	}

	case TAGCCAlternatives:
	{
	    unsigned int ix;
	    alternative_list alts;

	    alts = to_CCAlternatives(cc)->alternatives;
	    for( ix=0; ix<alts->sz; ix++ ){
		alternative alt = alts->arr[ix];

		*types = concat_ds_list(
		    *types,
		    create_subtype( alt->label, nm, alt->component )
		);
		*isvirtual = TMTRUE;
	    }
	}
    }
}

static ds_list normalize_class( tmsymbol nm, const classComponent_list ccl, tmbool isvirtual )
{
    tmsymbol_list inherits;
    Field_list fields;
    unsigned int ix;
    ds_list types;

    inherits = new_tmsymbol_list();
    fields = new_Field_list();
    types = new_ds_list();
    for( ix=0; ix<ccl->sz; ix++ ){
	update_class_info( nm, &inherits, &fields, &types, ccl->arr[ix], &isvirtual );
    }
    types = append_ds_list(
	types,
	to_ds( new_DsClass( new_origsymbol( nm, make_origin() ), inherits, tmsymbol_listNIL, fields, isvirtual ) )
    );
    return types;
}

/* Try to parse a data structure definition or an include. 
 * Return TRUE if you managed to do that.
 *
 * When an include is given, all the data structures encountered in
 * the included file are appended. That's why the ds list is passed.
 */
static tmbool parse_ds( ds_list *dl )
{
    tmsymbol nm;
    tmbool ok;

    if( curr_token==INCLUDE ){
	tmstring fnm;

	next_token();
        *dl = new_ds_list();
	if( curr_token!=STRING ){
	    parserror( "file name string expected" );
	    while( curr_token!=SEMI && curr_token!=LEXEOF ){
		if( curr_token == STRING ){
		    rfre_tmstring( yylval.parstring );
		}
		next_token();
	    }
	    return TRUE;
	}
	fnm = yylval.parstring;
        *dl = append_ds_list(
            *dl,
            to_ds(
                new_DsInclude(
                    origsymbolNIL,
                    tmsymbol_listNIL,
                    tmsymbol_listNIL,
                    fnm
                )
            )
        );
        next_token();    /* Eat the filename string. */
	return TRUE;
    }
    if( curr_token!=NAME ){
	return FALSE;
    }
    nm = yylval.parsymbol;
    next_token();
    switch( curr_token ){
	case COLCOLEQ:
	{
	    ds_list nw;

	    next_token();
	    ok = parse_constructor_type( nm, &nw );
	    if( ok ){
		*dl = nw;
	    }
	    break;
	}

	case ARROW:
	{
	    Type t;

	    next_token();
	    ok = parse_Type( &t );
	    if( ok ){
		ds nw = to_ds( new_DsAlias( new_origsymbol( nm, make_origin() ), new_tmsymbol_list(), tmsymbol_listNIL, t ) );

		*dl = new_ds_list();
		*dl = append_ds_list( *dl, nw );
	    }
	    break;
	}

	case EQEQ:
	{
	    ds nw;

	    next_token();
	    ok = parse_tuple_type( nm, &nw );
	    if( ok ){
		*dl = new_ds_list();
		*dl = append_ds_list( *dl, nw );
	    }
	    break;
	}

	case EQ:
	case TILDEQ:
	{
	    classComponent_list nw;
	    tmbool isvirtual = (curr_token == TILDEQ);

	    next_token();
	    ok = parse_class_components( &nw );
	    if( ok ){
		*dl = normalize_class( nm, nw, isvirtual );
		rfre_classComponent_list( nw );
	    }
	    break;
	}

	case LEXEOF:
	    parserror( "unexpected end of file" );
	    ok = FALSE;
	    break;

	default:
	    parserror( "'=', '~=', '::=' or '==' expected" );
	    ok = FALSE;
	    break;
    }
    if( !ok ){
	/* Try to recover from the parse error: eat everything until
	 * end of file or a semicolon.
	 */
	while( curr_token!=SEMI && curr_token!=LEXEOF ){
	    if( curr_token == STRING ){
		rfre_tmstring( yylval.parstring );
	    }
	    next_token();
	}
        /* We've (hopefully) recovered from the error, so say everythink ok. */
        *dl = new_ds_list();
    }
    return TRUE;
}

/* Parse datastructure definitions until you don't understand
 * it any more, or you have reached end of file.
 */
static ds_list parse_ds_list( void )
{
    ds_list dl;
    ds_list nw;
    tmbool ok;
    unsigned int ix;

    dl = new_ds_list();
    for(;;){
	if( curr_token==LEXEOF ){
	    break;
	}
	ok = parse_ds( &nw );
	if( !ok ){
	    parserror( "datastructure definition expected" );
            next_token();
	    return dl;
	}
	for( ix=0; ix<nw->sz; ix++ ){
	    dl = add_ds_list( dl, nw->arr[ix] );
	}
	if( curr_token!=SEMI ){
	    parserror( "';' expected" );
	}
	else {
	    next_token();
	}
	rfre_ds_list( nw );
    }
    return dl;
}

/* Top level of parser: given a file name 'fnm', open it, if necessary
 * after searching for it in searchpath, parse it, and return
 * a list of datastructures.
 */
ds_list parse_ds_file( const char *fnm )
{
    ds_list ans;
    FILE *dsfile;
    unsigned int ix = 0;
    tmstring ds_filename;

    if( fnm == tmstringNIL ){
	/* No file name specified. */
	return new_ds_list();
    }
    ds_filename = search_file( searchpath, fnm, PATHSEPSTR, "r" );
    if( ds_filename == tmstringNIL ){
	error( "file `%s' not found", fnm );
        return new_ds_list();
    }
    dsfile = ckfopen( ds_filename, "r" );
    set_lexfile( dsfile, ds_filename );
    next_token();
    ans = parse_ds_list();
    if( curr_token!=LEXEOF ){
	while( curr_token!=LEXEOF ){
	    next_token();
	}
    }
    fclose( dsfile );
    rfre_tmstring( ds_filename );

    /* Now expand any includes. */
    while( ix<ans->sz ){
        ds d = ans->arr[ix];

        if( d->tag == TAGDsInclude ){
            /* Replace the include with the contents of the included file. */
            const_tmstring filenm = to_const_DsInclude( d )->fnm;
            ds_list dl = parse_ds_file( filenm );

            ans = delete_ds_list( ans, ix );
            if( dl != ds_listNIL ){
                ans = insertlist_ds_list( ans, ix, dl );
            }
        }
        else {
            ix++;
        }
    }
    return ans;
}
