/* File: $Id$
 *
 * Various low-level routines.
 */
#include "config.h"
#include <stdio.h>
#include <tmc.h>
#include <errno.h>
#include "tmdefs.h"

#include "tmcode.h"
#include "misc.h"
#include "error.h"

/* Same as fopen, but give error message if file can't be opened */
FILE *ckfopen( const char *nm, const char *acc )
{
    FILE *hnd = fopen( nm, acc );

    if( NULL == hnd ){
	(void) strcpy( errarg, nm );
	sys_error( errno );
	exit( 1 );
    }
    return hnd;
}

/* Similar to freopen, but give error message if file can't be opened.
 * Therefore, file handle need not be returned.
 */
void ckfreopen( const char *nm, const char *acc, FILE *f )
{
    if( freopen( nm, acc, f ) == NULL ){
	(void) strcpy( errarg, nm );
	sys_error( errno );
	exit( 1 );
    }
}

/******************************************************
 *         DATASTRUCTURE SEARCH ROUTINES              *
 ******************************************************/

/* NOTE: The remainder of the code assumes TYPES_HASHWIDTH is a power of 2. */
#define TYPES_HASHBITS 8
#define TYPES_HASHWIDTH (1<<TYPES_HASHBITS)
#define TYPES_HASHMASK (TYPES_HASHWIDTH-1)

static unsigned int types_hash[TYPES_HASHWIDTH] = { 0 };
static unsigned int prev_types_ix = 0;

/* Hash function: map a 'normal' distribution of tmstrings on a
   evenly distributed number between 0..TYPES_HASHWIDTH-1.
 */
static unsigned int types_hashval( const char *s )
{
    unsigned int v = 0;

    while( *s!= '\0' ){
	 v = (v ^ *s);
	 v<<=1;
	 if( v & TYPES_HASHWIDTH ) v++;
	 v &= TYPES_HASHMASK;
	 s++;
    }
    return v;
}

/* Given a list of types 'types', search for type with name 't'.
 * Return the index of that type in the list, or types->sz if not
 * found.
 *
 * Since this function is dominant in most Tm templates, it tries to
 * avoid a linear search through the list each time it is called.
 * This is done by hashing the type strings to an index in
 * types_hash[]. This may well match the type we're looking for.
 *
 * Also, the result of the last call is remembered in prev_types_ix, since
 * that may well be the right answer for this call as well.
 *
 * Note that these heuristics are insensitive to changes in the type list;
 * after the change they are more likely to fail, but the result is
 * still correct.
 */ 
unsigned int find_type_ix( const_ds_list types, const char *t )
{
    unsigned int ix;
    unsigned int hv;

    if( prev_types_ix<types->sz && ( strcmp( types->arr[prev_types_ix]->name, t ) == 0 ) ){
	return prev_types_ix;
    }
    if( t == NULL ){
	return types->sz;
    }
    hv = types_hashval( t );
    ix = types_hash[hv];
    if( ix<types->sz && ( strcmp( types->arr[ix]->name, t ) == 0 ) ){
	prev_types_ix = ix;
	return ix;
    }
    for( ix = 0; ix < types->sz; ix++ ){
	ds d = types->arr[ix];

	if( strcmp( d->name, t ) == 0 ){
	    prev_types_ix = ix;
	    types_hash[hv] = ix;
	    return ix;
	}
    }
    return types->sz;
}

/* Given a list of fields 'fl', search for field with name 'nm'.
 * Return the index of that field in the list, or fl->sz if not
 * found.
 */ 
unsigned int find_field_ix( const_Field_list fl, const char *nm )
{
    unsigned int ix;

    for( ix = 0; ix < fl->sz; ix++ ){
	const_Field f = fl->arr[ix];

	if( strcmp( f->name->name, nm ) == 0 ){
	    return ix;
	}
    }
    return fl->sz;
}

/* Search for tmstring 's' in the list 'l' and return TRUE if
   found or FALSE otherwise.
 */
bool member_tmstring_list( const_tmstring s, const_tmstring_list l )
{
    unsigned int sno;

    for( sno=0; sno<l->sz; sno++ ){
	if( strcmp( l->arr[sno], s ) == 0 ){
	    return TRUE;
	}
    }
    return FALSE;
}

/* Search for all strings 'sl' in the list 'l' and return TRUE if
 * any of them occurs in 'l', or FALSE otherwise.
 */
bool any_member_tmstring_list( const_tmstring_list sl, const_tmstring_list l )
{
    unsigned int ix;

    for( ix=0; ix<sl->sz; ix++ ){
	if( member_tmstring_list( sl->arr[ix], l ) ){
	    return TRUE;
	}
    }
    return FALSE;
}

Field find_field_super( const_ds_list types, tmstring_list supers, const char *nm )
{
    unsigned int ix;

    for( ix=0; ix<supers->sz; ix++ ){
	Field f = find_field( types, supers->arr[ix], nm );

	if( f != FieldNIL ){
	    return f;
	}
    }
    return FieldNIL;
}

Field find_field( const_ds_list types, const char *type, const char *nm )
{
    unsigned int pos;
    ds t;
    Field_list fl = Field_listNIL;
    tmstring_list inherits = tmstring_listNIL;

    pos = find_type_ix( types, type );
    if( pos >= types->sz ){
	return FieldNIL;
    }
    t = types->arr[pos];
    inherits = t->inherits;
    switch( t->tag ){
	case TAGDsAlias:
	    fl = Field_listNIL;
	    break;

	case TAGDsConstructorBase:
	    fl = Field_listNIL;
	    break;

	case TAGDsTuple:
	    fl = to_DsTuple(t)->fields;
	    break;

	case TAGDsClass:
	    fl = to_DsClass(t)->fields;
	    break;

	case TAGDsConstructor:
	    fl = to_DsConstructor(t)->fields;
	    break;

    }
    if( fl != Field_listNIL ){
	pos = find_field_ix( fl, nm );
	if( pos<fl->sz ){
	    return fl->arr[pos];
	}
    }
    return find_field_super( types, inherits, nm );
}

tmstring_list extract_inherits( const_ds_list types, const char *type )
{
    unsigned int ix;

    ix = find_type_ix( types, type );
    if( ix>=types->sz ){
	return tmstring_listNIL;
    }
    return types->arr[ix]->inherits;
}

/* Given a pointer to a string list 'res', a list of types 'types'
 * and a type name 'type', collect into '*res' the transitive closure
 * of the types that inherit 'type'.
 */
void collect_subclasses( tmstring_list *res, const_ds_list types, const_tmstring type )
{
    tmstring_list queue;

    queue = new_tmstring_list();
    collect_inheritors( &queue, types, type );
    while( queue->sz>0 ){
	tmstring nm;
	int valid;

	queue = extract_tmstring_list( queue, 0, &nm, &valid );
	if( valid ){
	    if( !member_tmstring_list( nm, *res ) ){
		collect_inheritors( &queue, types, nm );
		*res = append_tmstring_list( *res, nm );
	    }
	    else {
		rfre_tmstring( nm );
	    }
	}
    }
    rfre_tmstring_list( queue );
}

/* Given a pointer to a string list 'res', a list of types 'types'
 * and a type name 'type', collect into '*res' the transitive closure
 * of the types where 'type' inherits from.
 */
void collect_superclasses( tmstring_list *res, const_ds_list types, const char *type )
{
    unsigned int ix;
    const_tmstring_list inherits = extract_inherits( types, type );

    if( inherits == tmstring_listNIL ){
	return;
    }
    for( ix=0; ix<inherits->sz; ix++ ){
	const_tmstring t = inherits->arr[ix];

	if( !member_tmstring_list( t, *res ) ){
	    collect_superclasses( res, types, t );
	    *res = append_tmstring_list( *res, rdup_tmstring( t ) );
	}
    }
}

/* Given a pointer to a string list 'res', a list of types 'types'
 * and a type name 'type', collect into '*res' the types that inherit
 * 'type'.
 */
void collect_inheritors( tmstring_list *res, const_ds_list types, const_tmstring type )
{
    unsigned int tix;
    unsigned int ix;
    tmstring_list mine;

    tix = find_type_ix( types, type );
    if( tix<types->sz && types->arr[tix]->inheritors != tmstring_listNIL ){
	*res = concat_tmstring_list(
	    *res,
	    rdup_tmstring_list( types->arr[tix]->inheritors )
	);
	return;
    }
    mine = new_tmstring_list();
    for( ix=0; ix<types->sz; ix++ ){
	const_ds d = types->arr[ix];
	const_tmstring_list inherits = d->inherits;

	if( inherits != tmstring_listNIL && member_tmstring_list( type, inherits ) ){
	    const char *nm = d->name;

	    mine = append_tmstring_list( mine, rdup_tmstring( nm ) );
	}
    }
    if( tix<types->sz ){
	types->arr[tix]->inheritors = rdup_tmstring_list( mine );
    }
    *res = concat_tmstring_list( *res, mine );
}

/* Given a list of types, zap all memoized inheritors */
ds_list zap_memoized_inheritors( ds_list types )
{
    unsigned int ix;

    for( ix=0; ix<types->sz; ix++ ){
	ds d = types->arr[ix];

	if( d->inheritors != tmstring_listNIL ){
	    rfre_tmstring_list( d->inheritors );
	    d->inheritors = tmstring_listNIL;
	}
    }
    return types;
}


/* Given a pointer to a string list 'fields', a list of types 'types'
 * and a type name 'type', collect into '*fields' the fields 
 * of this type (but not the fields it inherits).
 * Constructor types in the inherit tree are considered to have an
 * empty field list.
 */
void collect_fields( tmsymbol_list *fields, const_ds_list types, const char *type )
{
    unsigned int ix;
    Field_list el = Field_listNIL;
    ds d;

    ix = find_type_ix( types, type );
    if( ix>=types->sz ){
	return;
    }
    d = types->arr[ix];
    switch( d->tag ){
	case TAGDsAlias:
	    break;

	case TAGDsTuple:
	    el = to_DsTuple(d)->fields;
	    break;

	case TAGDsClass:
	    el = to_DsClass(d)->fields;
	    break;

	case TAGDsConstructor:
	    el = to_DsConstructor(d)->fields;
	    break;

	case TAGDsConstructorBase:
	    return;
    }
    if( el != Field_listNIL ){
	for( ix=0; ix<el->sz; ix++ ){
	    const_Field e = el->arr[ix];

	    *fields = append_tmsymbol_list( *fields, e->name );
	}
    }
}

/* Given a pointer to a string list 'fields', a list of types 'types'
 * and a type name 'type', collect into '*fields' the fields that are
 * inherited by this type, in depth-first order.
 * Constructor types in the inherit tree are considered to have an
 * empty field list, but may of course inherit from other classes.
 */
void collect_inherited_fields( tmsymbol_list *fields, const_ds_list types, const char *type )
{
    tmstring_list inherits;
    unsigned int ix;

    inherits = extract_inherits( types, type );
    if( inherits == tmstring_listNIL ){
	return;
    }
    for( ix=0; ix<inherits->sz; ix++ ){
	collect_all_fields( fields, types, inherits->arr[ix] );
    }
}

/* Given a pointer to a string list 'fields', a list of types 'types'
 * and a type name 'type', collect into '*fields' the fields that are
 * inherited by this type, and the fields of this type, in depth-first order.
 * Constructor types in the inherit tree are considered to have an
 * empty field list, but may of course inherit from other classes.
 */
void collect_all_fields( tmsymbol_list *fields, const_ds_list types, const char *type )
{
    collect_inherited_fields( fields, types, type );
    collect_fields( fields, types, type );
}

/* Given a description 'desc' and a list of tmstrings 'l', check
 * that the given list of tmstrings does not contain duplicate entries.
 */
bool check_double_strings( const char *msg, const_tmstring_list l )
{
    unsigned int ixa;
    unsigned int ixb;
    bool ok = TRUE;

    for( ixa=0; ixa<l->sz; ixa++ ){
	tmstring sa = l->arr[ixa];

	for( ixb=ixa+1; ixb<l->sz; ixb++ ){
	    tmstring sb = l->arr[ixb];
	    if( strcmp( sa, sb ) == 0 ){
		sprintf( errarg, "'%s'", sa );
		error( msg );
		ok = FALSE;
	    }
	}
    }
    return ok;
}

/* Given a description 'desc' and a list of tmsymbols 'l', check
 * that the given list of tmsymbols does not contain duplicate entries.
 */
bool check_double_symbols( const char *msg, const_tmsymbol_list l )
{
    unsigned int ixa;
    unsigned int ixb;
    bool ok = TRUE;

    for( ixa=0; ixa<l->sz; ixa++ ){
	tmsymbol sa = l->arr[ixa];

	for( ixb=ixa+1; ixb<l->sz; ixb++ ){
	    tmsymbol sb = l->arr[ixb];

	    if( sa == sb ){
		sprintf( errarg, "'%s'", sa->name );
		error( msg );
		ok = FALSE;
	    }
	}
    }
    return ok;
}
