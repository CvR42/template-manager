/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: dsparser.c
 * A recursive descend parser for Tm datastructure definitions.
 */

#include "config.h"
#include "tmdefs.h"
#include <assert.h>
#include <ctype.h>
#include <tmc.h>

#include "tmcode.h"
#include "tmstring.h"
#include "error.h"
#include "global.h"
#include "lex.h"
#include "misc.h"
#include "dsparser.h"
#include "checkds.h"
#include "srchfile.h"

lextok curr_token;

/* Forward declarations. */
static bool parse_class_components( classComponent_list *clp );
static void update_class_info( tmstring nm, tmstring_list *inherits, field_list *fields, ds_list *types, const classComponent cc );

static void yyerror( const char *s )
{
    show_parse_context( stderr );
    if( noerrorline ){
	(void) sprintf( errpos, "%s", dsfilename );
    }
    else {
	(void) sprintf( errpos, "%s(%d)", dsfilename, dslineno );
    }
    error( s );
    fputc( '\n', stderr );
}

/* Check a name on underscores and give an error message if one is found */
static void ckunderscore( const char *s )
{
    if( strchr( s, '_' ) != NULL ){
	strcpy( errarg, s );
	yyerror( "No '_' allowed in name" );
    }
}

/* Ensure that name 's' is a proper constructor name. */
static void ckconsname( const char *s )
{
    if( s[0] == '\0' ) return;
    ckunderscore( s );
    if( !isupper( s[0] ) ){
	strcpy( errarg, s );
	yyerror( "a constructor name should start with an uppercase character" );
    }
}

/* Ensure that name 's' is a proper type name. */
static void cktypename( const char *s )
{
    if( s[0] == '\0' ){
	return;
    }
    ckunderscore( s );
    if( !islower( s[0] ) ){
	(void) strcpy( errarg, s );
	yyerror( "a type name should start with a lowercase character" );
    }
}

/* Ensure that name 's' is a proper element name. */
static void ckelmname( const char *s )
{
    if( s[0] == '\0' ){
	return;
    }
    ckunderscore( s );
}


/* Given a tmstring list 'l' and a tmstring 's', add 's' to the
 * list 'l' and return the newly constructed list. Reject strings
 * that are already defined.
 */
static tmstring_list add_inherit_list( tmstring_list l, tmstring s )
{
    cktypename( s );
    if( member_tmstring_list( s, l ) ){
	(void) sprintf( errarg, "'%s'", s );
	yyerror( "duplicate inheritance" );
    }
    else {
	l = append_tmstring_list( l, rdup_tmstring( s ) );
    }
    return l;
}

/* Given a constructor list 'l' and a constructor 'c', add c to the
 * list l and return the newly constructed list. Reject constructors
 * that are already defined.
 */
static constructor_list add_constructor_list( constructor_list l, constructor c )
{
    unsigned int ix;
    char *nm;

    nm = c->name;
    ix = find_constructor_ix( l, nm );
    if( ix<l->sz ){
	(void) sprintf( errarg, "'%s'", nm );
	yyerror( "double use of constructor name" );
    }
    else {
	l = append_constructor_list( l, rdup_constructor( c ) );
    }
    return l;
}

/* Given two constructor types 'a' and 'b', return a new constructor
 * type that has the constructors of both.
 * It *must* be certain that 'a' and 'b' are both constructor types.
 */
static ds merge_cons_types( ds a, ds b )
{
    constructor_list la;
    constructor_list lb;
    tmstring_list ila;
    tmstring_list ilb;
    unsigned int ix;

    la = rdup_constructor_list( a->DsCons.constructors );
    lb = b->DsCons.constructors;
    for( ix=0; ix<lb->sz; ix++ ){
	la = add_constructor_list( la, lb->arr[ix] );
    }
    ila = rdup_tmstring_list( a->DsCons.inherits );
    ilb = b->DsCons.inherits;
    for( ix=0; ix<ilb->sz; ix++ ){
	ila = add_inherit_list( ila, ilb->arr[ix] );
    }
    return new_DsCons(
	rdup_tmstring( a->DsCons.name ),
	ila,
	la
    );
}

/* Given a type 't', a constructor name 'cnm' and a type name
 * 'tnm' to which the constructor belongs, ensure that if 't' is a constructor
 * type, 'cnm' does not occur in it.
 */
static void ckcname_type( const ds t, const tmstring cnm, const tmstring tnm )
{
    constructor_list cl;
    unsigned int ix;

    if( t->tag != TAGDsCons ){
	return;
    }
    cl = t->DsCons.constructors;
    for( ix=0; ix<cl->sz; ix++ ){
	if( strcmp( cl->arr[ix]->name, cnm) == 0 ){
	    (void) sprintf( errpos, "type %s", tnm );
	    (void) sprintf( errarg, "'%s' (in type %s)", cnm, get_type_name( t ) );
	    error( "constructor already defined" );
	}
    }
}

/* Given a list of types 'l', a constructor name 'cnm' and a type name
 * 'tnm' to which the constructor belongs, ensure that 'cnm' does not
 * occur in any of the constructor types of 'l'.
 */
static void ckcname( const ds_list l, const tmstring cnm, const tmstring tnm )
{
    unsigned int ix;

    for( ix=0; ix<l->sz; ix++ ){
	ckcname_type( l->arr[ix], cnm, tnm );
    }
}

/* Given a list of types 'l' and a type 't', ensure that if 't' is a
 * constructor type, it does not contain the same constructor names
 * as in previous constructor types.
 */
static void ckcnames( ds_list l, ds t )
{
    constructor_list cl;
    unsigned int ix;
    tmstring tnm;

    if( t->tag != TAGDsCons ){
	return;
    }
    cl = t->DsCons.constructors;
    tnm = get_type_name( t );
    for( ix=0; ix<cl->sz; ix++ ){
	ckcname( l, cl->arr[ix]->name, tnm );
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
    tmstring nm;		/* Name of the nw type. */
    unsigned int ix;	/* Index of any previous def'n of it. */
    ds old;		/* The old type definition. */
    ds nw;		/* The type constructed from two constr. def'ns. */

    nm = get_type_name( t );
    ix = find_type_ix( l, nm );
    if( ix<l->sz ){
	old = l->arr[ix];
	if( old->tag == TAGDsCons && t->tag == TAGDsCons ){
	    nw = merge_cons_types( old, t );
	    l = delete_ds_list( l, ix );
	    l = append_ds_list( l, nw );
	}
	else {
	    (void) sprintf( errarg, "'%s'", nm );
	    yyerror( "redefinition of type" );
	}
    }
    else {
	ckcnames( l, t );
	l = append_ds_list( l, rdup_ds( t ) );
    }
    return l;
}

/* Unconditionally get the next token from the lexical analyzer. */
static void next_token( void )
{
    curr_token = yylex();
}

/* Given a field name 'nm', try to parse a field type, and set
 * '*fp' to the constructed field. Return TRUE if you have constructed
 * a valid field.
 */
static bool parse_field_type( const tmstring nm, field *fp )
{
    bool ok;

    if( curr_token==LSBRAC ){
	next_token();
	ok = parse_field_type( nm, fp );
	if( !ok ){
	    return FALSE;
	}
	(*fp)->level++;
	if( curr_token==RSBRAC ){
	    next_token();
	}
	else {
	    yyerror( "']' expected" );
	}
	return TRUE;
    }
    if( curr_token==NAME ){
	*fp = new_field( 0, nm, yylval.parstring );
	next_token();
	return TRUE;
    }
    yyerror( "type specification expected" );
    return FALSE;
}

/* Try to parse a field. Return TRUE if you have a valid field. */
static bool parse_field( field *fp )
{
    tmstring elmname;

    if( curr_token!=NAME ){
	return FALSE;
    }
    elmname = yylval.parstring;
    ckelmname( elmname );
    next_token();
    if( curr_token!=COLON ){
	yyerror( "':' expected" );
	return FALSE;
    }
    next_token();
    return parse_field_type( elmname, fp );
}

/* Try to parse a list of fields for a tuple body. 
 * keep parsing field definitions until you encounter
 * a '|' or a ')'. 
 *
 * Return TRUE if you have a valid tuple body.
 */
static bool parse_field_list( field_list *flp )
{
    bool ok;
    field nw;

    *flp = new_field_list();
    for(;;){
	ok = parse_field( &nw );
	if( ok ){
	    *flp = append_field_list( *flp, nw );
	}
	else {
	    break;
	}
    }
    return TRUE;
}

/* Trye to parse a constructor. Return TRUE if this succeeded. */
static bool parse_constructor( constructor *cp )
{
    tmstring nm;
    bool ok;
    field_list fl;

    if( curr_token!=NAME ){
	return FALSE;
    }
    nm = yylval.parstring;
    ckconsname( nm );
    next_token();
    ok = parse_field_list( &fl );
    if( !ok ){
	yyerror( "invalid field list" );
	rfre_tmstring( nm );
	return FALSE;
    }
    *cp = new_constructor( nm, fl );
    return TRUE;
}

/* Try to parse a list of constructors up to (but not including)
 * the final ';'. Return TRUE if you have a valid constructor list.
 */
static bool parse_constructor_list( constructor_list *clp )
{
    bool ok;
    constructor nw;

    *clp = new_constructor_list();
    if( curr_token==SEMI ){
	return TRUE;
    }
    for(;;){
	ok = parse_constructor( &nw );
	if( ok ){
	    *clp = add_constructor_list( *clp, nw );
	    rfre_constructor( nw );
	}
	else {
	    yyerror( "constructor expected" );
	    /* Try to recover by skipping tokens up to the next
	     * '|', ';' or LEXEOF. */
	    while( curr_token!=BAR && curr_token!=SEMI && curr_token!=LEXEOF ){
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
	    yyerror( "'|' expected" );
	}
    }
    return TRUE;
}

/* Given a type name 'nm', try to parse the remainder
 * of a constructor definition, up to (but not including) the final ';'.
 * Return TRUE if this succeeded, and set *tp to the parsed constructor.
 */
static bool parse_constructor_type( tmstring nm, ds *tp )
{
    bool ok;
    constructor_list cl;
    tmstring_list inherits;

    inherits = new_tmstring_list();
    /* This is a bit dirty: we assume that inherited type names
     * start with a lowercase character, and constructor names start
     * with an uppercase character.
     */
    while( curr_token == NAME && islower( yylval.parstring[0] ) ){
	inherits = add_inherit_list( inherits, yylval.parstring );
	next_token();
	if( curr_token != PLUS ){
	    yyerror( "'+' expected" );
	}
	else {
	    next_token();
	}
    }
    ok = parse_constructor_list( &cl );
    ckconstructor( nm, cl );
    *tp = new_DsCons( nm, inherits, cl );
    return ok;
}

/* Try to parse a list of fields for a tuple body.
 *
 * Return TRUE if you have a valid tuple body.
 */
static bool parse_tuplebody( field_list *flp )
{
    bool ok;
    field nw;

    *flp = new_field_list();
    if( curr_token == RRBRAC || curr_token == RCBRAC ){
	return TRUE;
    }
    for(;;){
	ok = parse_field( &nw );
	if( ok ){
	    *flp = append_field_list( *flp, nw );
	}
	else {
	    yyerror( "field expected" );
	    /* Try to recover by skipping tokens up to the next
	     * ',', ,}', ')', ';' or LEXEOF. */
	    while(
		   curr_token!=COMMA
		&& curr_token!=RRBRAC
		&& curr_token!=SEMI
		&& curr_token!=LEXEOF
		&& curr_token!=RCBRAC
	    ){
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
 * TRUE if you have a valid tuple.
 */
static bool parse_tuple_type( tmstring nm, ds *tp )
{
    bool ok;
    field_list body;
    tmstring_list inherits;

    inherits = new_tmstring_list();
    while( curr_token == NAME ){
	inherits = add_inherit_list( inherits, yylval.parstring );
	next_token();
	if( curr_token != PLUS ){
	    yyerror( "'+' expected" );
	}
	else {
	    next_token();
	}
    }
    if( curr_token!=LRBRAC ){
	yyerror( "'(' expected" );
	return FALSE;
    }
    else {
	next_token();
    }
    ok = parse_tuplebody( &body );
    if( !ok ){
	return FALSE;
    }
    if( curr_token!=RRBRAC ){
	yyerror( "')' expected" );
    }
    else {
	next_token();
    }
    cktuple( nm, body );
    *tp = new_DsTuple( nm, inherits, body );
    return TRUE;
}

/* Given a pointer to a class component, try to parse
 * a class component. Return TRUE if you have a valid class component.
 *
 * Do not try to eat the '+' that separates components.
 */
static bool parse_class_component( classComponent *cp )
{
    bool ok;
    classComponent res;

    if( curr_token == LCBRAC ){
	field_list fields;

	next_token();
	/* We want a list of field definitions. */
	ok = parse_tuplebody( &fields );
	if( !ok ){
	    return FALSE;
	}
	res = new_CCFields( fields );
	if( curr_token != RCBRAC ){
	    /* '{' to balance bracket below */
	    yyerror( "'}' expected" );
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
	tmstring nm = yylval.parstring;

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
		    rfre_tmstring( nm );
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
		    yyerror( "label name expected, because a '|' must be followed by a label" );
		    rfre_alternative_list( alts );
		    return FALSE;
		}
		nm = yylval.parstring;
		next_token();
		if( curr_token != COLON ){
		    yyerror( "':' expected, because a '|' must be followed by a label" );
		}
	    }
	    res = new_CCAlternatives( alts );
	}
	else {
	    /* Presumably was an inherit. Fine. */
	    res = new_CCSuper( nm );
	}
	*cp = res;
	return TRUE;
    }
    if( curr_token == LRBRAC ){
	classComponent_list ccl;

	/* It is a bracketed sublist. */
	ok = parse_class_components( &ccl );
	if( !ok ){
	    return FALSE;
	}
	res = new_CCSublist( ccl );
	if( curr_token != RRBRAC ){
	    /* '(' to balance bracket below */
	    yyerror( "')' expected" );
	    rfre_classComponent( res );
	    return FALSE;
	}
	next_token();
	*cp = res;
	return TRUE;
    }
    yyerror( "class type component expected" );
    return FALSE;
}

/* Given a pointer to a list of class components, try to parse
 * a class type definition. Return TRUE if you have a valid class type.
 */
static bool parse_class_components( classComponent_list *clp )
{
    bool ok;
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

static ds_list create_subtype( const tmstring nm, const tmstring super, const classComponent comp )
{
    tmstring_list inherits;
    field_list fields;
    ds_list types;

    inherits = new_tmstring_list();
    fields = new_field_list();
    types = new_ds_list();
    inherits = append_tmstring_list( inherits, rdup_tmstring( super ) );
    update_class_info( nm, &inherits, &fields, &types, comp );
    types = append_ds_list(
	types,
	new_DsClass( rdup_tmstring( nm ), FALSE, inherits, fields )
    );
    return types;

}

static void update_class_info( tmstring nm, tmstring_list *inherits, field_list *fields, ds_list *types, const classComponent cc )
{
    switch( cc->tag ){
	case TAGCCSuper:
	    *inherits = append_tmstring_list( *inherits, rdup_tmstring( cc->CCSuper.super ) );
	    break;

	case TAGCCFields:
	    *fields = concat_field_list(
		*fields,
		rdup_field_list( cc->CCFields.fields )
	    );
	    break;

	case TAGCCSublist:
	{
	    unsigned int ix;
	    classComponent_list ccl;

	    ccl = cc->CCSublist.components;
	    for( ix=0; ix<ccl->sz; ix++ ){
		update_class_info( nm, inherits, fields, types, ccl->arr[ix] );
	    }
	    break;
	}

	case TAGCCAlternatives:
	{
	    unsigned int ix;
	    alternative_list alts;

	    alts = cc->CCAlternatives.alternatives;
	    for( ix=0; ix<alts->sz; ix++ ){
		alternative alt = alts->arr[ix];

		*types = concat_ds_list(
		    *types,
		    create_subtype( alt->label, nm, alt->component )
		);
	    }
	}
    }
}

static ds_list normalize_class( tmstring nm, const classComponent_list ccl, const tmbool virtual )
{
    tmstring_list inherits;
    field_list fields;
    unsigned int ix;
    ds_list types;

    inherits = new_tmstring_list();
    fields = new_field_list();
    types = new_ds_list();
    for( ix=0; ix<ccl->sz; ix++ ){
	update_class_info( nm, &inherits, &fields, &types, ccl->arr[ix] );
    }
    types = append_ds_list(
	types,
	new_DsClass( rdup_tmstring( nm ), virtual, inherits, fields )
    );
    return types;
}

/* Try to parse a data structure definition or an include. 
 * 'dl'. Return TRUE if you managed to do that.
 *
 * When an include is given, all the data structures encountered in
 * the included file are appended. That's why the ds list is passed.
 */
static bool parse_ds( ds_list *dl )
{
    tmstring nm;
    bool ok;

    if( curr_token==INCLUDE ){
	tmstring fnm;

	next_token();
	if( curr_token!=STRING ){
	    yyerror( "file name string expected" );
	    while( curr_token!=SEMI && curr_token!=LEXEOF ){
		next_token();
	    }
	    if( curr_token==SEMI ){
		next_token();
	    }
	    *dl = new_ds_list();
	    return TRUE;
	}
	fnm = yylval.parstring;
	/* parse_ds_file() eats the current token. */
	*dl = parse_ds_file( fnm );
	rfre_tmstring( fnm );
	if( curr_token==LEXEOF ){
	    /* The LEXEOF is from the included file. */
	    next_token();
	}
	if( curr_token!=SEMI ){
	    yyerror( "';' expected" );
	}
	else {
	    next_token();
	}
	return TRUE;
    }
    if( curr_token!=NAME ){
	return FALSE;
    }
    nm = yylval.parstring;
    cktypename( nm );
    next_token();
    switch( curr_token ){
	case COLCOLEQ:
	{
	    ds nw;

	    next_token();
	    ok = parse_constructor_type( nm, &nw );
	    if( ok ){
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
	    bool virtual = (curr_token == TILDEQ);

	    next_token();
	    ok = parse_class_components( &nw );
	    if( ok ){
		*dl = normalize_class( nm, nw, virtual );
		rfre_classComponent_list( nw );
		rfre_tmstring( nm );
	    }
	    break;
	}

	case LEXEOF:
	    yyerror( "unexpected end of file" );
	    ok = FALSE;
	    break;

	default:
	    yyerror( "'=', '~=', '::=' or '==' expected" );
	    ok = FALSE;
	    break;
    }
    if( !ok ){
	rfre_tmstring( nm );
	/* Try to recover from the parse error: eat everything until
	 * end of file or a semicolon.
	 */
	while( curr_token!=SEMI && curr_token!=LEXEOF ){
	    next_token();
	}
	if( curr_token==SEMI ){
	    next_token();
	}
	return ok;
    }
    if( curr_token!=SEMI ){
	yyerror( "';' expected" );
    }
    else {
	next_token();
    }
    return ok;
}

/* Parse datastructure definitions until you don't understand
 * it any more, or you have reached end of file.
 */
static ds_list parse_ds_list( void )
{
    ds_list dl;
    ds_list nw;
    bool ok;
    unsigned int ix;

    dl = new_ds_list();
    for(;;){
	if( curr_token==LEXEOF ){
	    break;
	}
	ok = parse_ds( &nw );
	if( !ok ){
	    yyerror( "datastructure definition expected" );
	    return dl;
	}
	for( ix=0; ix<nw->sz; ix++ ){
	    dl = add_ds_list( dl, nw->arr[ix] );
	}
	rfre_ds_list( nw );
    }
    return dl;
}

/* Top level of parser: given a file name 'fnm', open it, if necessary
 * after searching for it in searchpath, parse it, and return
 * a list of datastructures.
 */
ds_list parse_ds_file( const tmstring fnm )
{
    ds_list ans;
    FILE *oldf;
    tmstring oldfnm;
    int oldlineno;
    char oldlinebuf[LINESIZE];
    unsigned int oldlineix;

    if( fnm == tmstringNIL ){
	/* No file name specified. */
	return new_ds_list();
    }
    oldf = dsfile;
    oldfnm = dsfilename;
    oldlineno = dslineno;
    strcpy( oldlinebuf, linebuf );
    oldlineix = lineix;
    dsfilename = search_file( searchpath, fnm, PATHSEPSTR, "r" );
    if( dsfilename == tmstringNIL ){
	sprintf( errarg, "'%s'", fnm );
	fatal( "file not found" );
    }
    dsfile = ckfopen( dsfilename, "r" );
    dslineno = 1;
    linebuf[0] = '\0';
    lineix = 0;
    next_token();
    ans = parse_ds_list();
    if( curr_token!=LEXEOF ){
	yyerror( "extra tokens in included file ignored" );
	while( curr_token!=LEXEOF ){
	    next_token();
	}
    }
    fclose( dsfile );
    rfre_tmstring( dsfilename );
    dsfile = oldf;
    dsfilename = oldfnm;
    dslineno = oldlineno;
    strcpy( linebuf, oldlinebuf );
    lineix = oldlineix;
    return ans;
}
