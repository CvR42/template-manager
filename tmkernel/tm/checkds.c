/* File: checkds.c
 *
 * Check correctness of the ds file.
 */

#include <assert.h>
#include <tmc.h>

#include "config.h"
#include "tmdefs.h"
#include "error.h"
#include "tmcode.h"
#include "misc.h"
#include "checkds.h"

/* Ensure that there are no double names in tuple with name 'nm'
 * and fields 'fields'.
 */
void cktuple( tmstring nm, field_list fields, tmstring_list inherits )
{
    unsigned int ix;	/* index of currently checked field */
    unsigned int iy;	/* index of searched subsequent fields */
    field fx;		/* checked field */
    field fy;		/* searched field */
    tmstring fnm;	/* name of currently checked field */

    for( ix=0; ix<fields->sz; ix++ ){
	fx = fields->arr[ix];
	fnm = fx->name;
	for( iy=ix+1; iy<fields->sz; iy++ ){
	    fy = fields->arr[iy];
	    if( strcmp( fy->name, fnm ) == 0 ){
		sprintf( errpos, "in type '%s'", nm );
		sprintf( errarg, "'%s'", fnm );
		error( "double use of field name" );
	    }
	}
    }
    if( member_tmstring_list( nm, inherits ) ){
	sprintf( errpos, "in type '%s'", nm );
	error( "Type inherits itself" );
    }
}

/* Given a list of datastructure definitions, an index in the list,
 * a list of visited flags and a list of accepted flags, check the
 * data structure with the given index for circular inheritances.
 */
static void check_ds_inheritance(
 ds_list dl,
 unsigned int theds,
 bool *visited,
 bool *accepted
)
{
    tmstring_list supers;	/* The list of superclasses. */
    unsigned int ix;
    ds me = dl->arr[theds];
    tmstring myname;

    assert( theds<dl->sz );
    if( accepted[theds] ){
        return;
    }
    myname = tmstringNIL;
    supers = tmstring_listNIL;
    switch( me->tag ){
        case TAGDsConstructorBase:
            supers = rdup_tmstring_list( to_DsConstructorBase(me)->inherits );
            myname = to_DsConstructorBase(me)->name;
            break;

	case TAGDsTuple:
            supers = rdup_tmstring_list( to_DsTuple(me)->inherits );
            myname = to_DsTuple(me)->name;
            break;

	case TAGDsClass:
	    supers = rdup_tmstring_list( to_DsClass(me)->inherits );
            myname = to_DsClass(me)->name;
            break;

	case TAGDsConstructor:
	    supers = rdup_tmstring_list( to_DsConstructor(me)->inherits );
            myname = to_DsConstructor(me)->name;
            break;

    }
    if( visited[theds] ){
	sprintf( errpos, "type '%s'", myname );
	error( "circular inheritance" );
	accepted[theds] = TRUE;		/* Break the circle to allow further checks. */
	rfre_tmstring_list( supers );
	return;
    }
    visited[theds] = TRUE;
    for( ix=0; ix<supers->sz; ix++ ){
        tmstring super = supers->arr[ix];
        unsigned int superix = find_type_ix( dl, super );

        if( superix<dl->sz ){
	    check_ds_inheritance( dl, superix, visited, accepted );
        }
#if 0
	else {
	    sprintf( errpos, "type '%s'", myname );
	    sprintf( errarg, "'%s'", super );
	    error( "inheritance from unknown type" );
	}
#endif
    }
    rfre_tmstring_list( supers );
    visited[theds] = FALSE;
    accepted[theds] = TRUE;
}

/* Given a list of datastructure definitions, ensure that it does not
 * contain circular inheritances.
 */
void check_ds_list( const ds_list dl )
{
    bool *visited;	/* The data structures currently under examination */
    bool *accepted;	/* The data structures that already passed the test. */
    unsigned int ix;
    unsigned int sz;
    bool ok;

    for( ix=0; ix<dl->sz; ix++ ){
	unsigned int iy;
	const tmstring nmx = get_type_name( dl->arr[ix] );
	char msg[200];

	ok = TRUE;
	for( iy=ix+1; iy<dl->sz; iy++ ){
	    const tmstring nmy = get_type_name( dl->arr[iy] );

	    if( strcmp( nmx, nmy ) == 0 ){
		sprintf( errarg, "type '%s'", nmx );
		error( "Double definition" );
		ok = FALSE;
		break;
	    }
	}
	if( ok ){
	    tmstring_list tl = new_tmstring_list();

	    sprintf( msg, "Duplicate superclass in type '%s'", nmx );
	    collect_superclasses( &tl, dl, nmx );
	    ok = check_double_strings( msg, tl );
	    rfre_tmstring_list( tl );
	}
	if( ok ){
	    tmstring_list fields = new_tmstring_list();

	    sprintf( msg, "Duplicate field in type '%s'", nmx );
	    collect_all_fields( &fields, dl, nmx );
	    (void) check_double_strings( msg, fields );
	    rfre_tmstring_list( fields );
	}
    }
    sz = dl->sz;
    visited = TM_MALLOC( bool *, sizeof(bool)*sz );
    if( visited == NULL ){
        /* No room. Don't report it; the check is not that important anyway.  */
        return;
    }
    accepted = TM_MALLOC( bool *, sizeof(bool)*sz );
    if( accepted == NULL ){
        /* No room. Don't report it; the check is not that important anyway. */
        TM_FREE( visited );
        return;
    }
    for( ix=0; ix<sz; ix++ ){
        visited[ix] = accepted[ix] = FALSE;
    }
    for( ix=0; ix<sz; ix++ ){
        check_ds_inheritance( dl, ix, visited, accepted );
    }
    TM_FREE( accepted );
    TM_FREE( visited );
}
