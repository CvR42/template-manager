/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: tmmisc.c
   Various low-level routines.
 */
#include "config.h"
#include <stdio.h>
#include <tmc.h>
#include "tmdefs.h"

#include "tmcode.h"
#include "misc.h"
#include "error.h"

/* Same as fopen, but give error message if file can't be opened */
FILE *ckfopen( const char *nm, const char *acc )
{
    FILE *hnd;

    hnd = fopen( nm, acc );
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

/* Given a type 't', return a pointer to its name tmstring. */
const tmstring get_type_name( const ds t )
{
    return t->name;
}

/* Given a list of types 'types', search for type with name 't'.
 * Return the index of that type in the list, or types->sz if not
 * found.
 */ 
unsigned int find_type_ix( const ds_list types, const char *t )
{
    ds d;
    unsigned int ix;

    for( ix = 0; ix < types->sz; ix++ ){
	d = types->arr[ix];
	if( strcmp( get_type_name( d ), t ) == 0 ){
	    return ix;
	}
    }
    return types->sz;
}

/* Given a list of fields 'fl', search for field with name 'nm'.
 * Return the index of that field in the list, or fl->sz if not
 * found.
 */ 
unsigned int find_field_ix( const field_list fl, const char *nm )
{
    unsigned int ix;

    for( ix = 0; ix < fl->sz; ix++ ){
	const field f = fl->arr[ix];

	if( strcmp( f->name, nm ) == 0 ){
	    return ix;
	}
    }
    return fl->sz;
}

/* Search for tmstring 's' in the list 'l' and return TRUE if
   found or FALSE otherwise.
 */
bool member_tmstring_list( const tmstring s, const tmstring_list l )
{
    unsigned int sno;

    for( sno=0; sno<l->sz; sno++ ){
	if( strcmp( l->arr[sno], s ) == 0 ){
	    return TRUE;
	}
    }
    return FALSE;
}

field find_field_super( const ds_list types, tmstring_list supers, const char *nm )
{
    unsigned int ix;

    for( ix=0; ix<supers->sz; ix++ ){
	field f;

	f = find_field( types, supers->arr[ix], nm );
	if( f != fieldNIL ){
	    return f;
	}
    }
    return fieldNIL;
}

field find_field( const ds_list types, const char *type, const char *nm )
{
    unsigned int pos;
    ds t;
    field_list fl = field_listNIL;
    tmstring_list inherits = tmstring_listNIL;

    pos = find_type_ix( types, type );
    if( pos >= types->sz ){
	return fieldNIL;
    }
    t = types->arr[pos];
    switch( t->tag ){
	case TAGDsConstructorBase:
	    fl = field_listNIL;
	    inherits = to_DsConstructorBase(t)->inherits;
	    break;

	case TAGDsTuple:
	    fl = to_DsTuple(t)->fields;
	    inherits = to_DsTuple(t)->inherits;
	    break;

	case TAGDsClass:
	    fl = to_DsClass(t)->fields;
	    inherits = to_DsClass(t)->inherits;
	    break;

	case TAGDsConstructor:
	    fl = to_DsConstructor(t)->fields;
	    inherits = to_DsConstructor(t)->inherits;
	    break;

    }
    if( fl != field_listNIL ){
	pos = find_field_ix( fl, nm );
	if( pos<fl->sz ){
	    return fl->arr[pos];
	}
    }
    return find_field_super( types, inherits, nm );
}

static const tmstring_list extract_inherits_type( const ds d )
{
    tmstring_list ans = tmstring_listNIL;

    switch( d->tag ){
	case TAGDsConstructorBase:
	    ans = to_DsConstructorBase(d)->inherits;
	    break;

	case TAGDsTuple:
	    ans = to_DsTuple(d)->inherits;
	    break;

	case TAGDsClass:
	    ans = to_DsClass(d)->inherits;
	    break;

	case TAGDsConstructor:
	    ans = to_DsConstructor(d)->inherits;
	    break;

    }
    return ans;
}

const tmstring_list extract_inherits( const ds_list types, const char *type )
{
    unsigned int ix;

    ix = find_type_ix( types, type );
    if( ix>=types->sz ){
	return tmstring_listNIL;
    }
    return extract_inherits_type( types->arr[ix] );
}

/* Given a pointer to a string list 'res', a list of types 'types'
 * and a type name 'type', collect into '*res' the transitive closure
 * of the types that inherit 'type'.
 */
void collect_subclasses( tmstring_list *res, const ds_list types, const tmstring type )
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
void collect_superclasses( tmstring_list *res, const ds_list types, const char *type )
{
    unsigned int ix;
    const tmstring_list inherits = extract_inherits( types, type );

    if( inherits == tmstring_listNIL ){
	return;
    }
    for( ix=0; ix<inherits->sz; ix++ ){
	const tmstring t = inherits->arr[ix];

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
void collect_inheritors( tmstring_list *res, const ds_list types, const tmstring type )
{
    unsigned int ix;

    for( ix=0; ix<types->sz; ix++ ){
	const ds d = types->arr[ix];
	const tmstring_list inherits = extract_inherits_type( d );

	if( inherits != tmstring_listNIL && member_tmstring_list( type, inherits ) ){
	    const char *nm = get_type_name( d );

	    *res = append_tmstring_list( *res, rdup_tmstring( nm ) );
	}
    }
}

/* Given a pointer to a string list 'fields', a list of types 'types'
 * and a type name 'type', collect into '*fields' the fields 
 * of this type (but not the fields it inherits).
 * Constructor types in the inherit tree are considered to have an
 * empty field list.
 */
void collect_fields( tmstring_list *fields, const ds_list types, const char *type )
{
    unsigned int ix;
    field_list el = field_listNIL;
    ds d;

    ix = find_type_ix( types, type );
    if( ix>=types->sz ){
	return;
    }
    d = types->arr[ix];
    switch( d->tag ){
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
    for( ix=0; ix<el->sz; ix++ ){
	field e = el->arr[ix];

	*fields = append_tmstring_list( *fields, new_tmstring( e->name ) );
    }
}

/* Given a pointer to a string list 'fields', a list of types 'types'
 * and a type name 'type', collect into '*fields' the fields that are
 * inherited by this type, and the fields of this type, in depth-first order.
 * Constructor types in the inherit tree are considered to have an
 * empty field list, but may of course inherit from other classes.
 */
void collect_all_fields( tmstring_list *fields, const ds_list types, const char *type )
{
    collect_inherited_fields( fields, types, type );
    collect_fields( fields, types, type );
}

/* Given a pointer to a string list 'fields', a list of types 'types'
 * and a type name 'type', collect into '*fields' the fields that are
 * inherited by this type, in depth-first order.
 * Constructor types in the inherit tree are considered to have an
 * empty field list, but may of course inherit from other classes.
 */
void collect_inherited_fields( tmstring_list *fields, const ds_list types, const char *type )
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

/* Given a description 'desc' and a list of tmstrings 'l', check
 * that the given list of tmstrings does not contain duplicate entries.
 */
bool check_double_strings( const char *msg, const tmstring_list l )
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
