/* File: $Id$
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
void cktuple( const_tmstring nm, const_Field_list fields, const_tmstring_list inherits )
{
    unsigned int ix;	/* index of currently checked field */

    for( ix=0; ix<fields->sz; ix++ ){
	Field fx = fields->arr[ix];
	tmstring fnm = fx->name;
	unsigned int iy;	/* index of searched subsequent fields */

	for( iy=ix+1; iy<fields->sz; iy++ ){
	    Field fy = fields->arr[iy];

	    if( strcmp( fy->name, fnm ) == 0 ){
		sprintf( errpos, "in type '%s'", nm );
		sprintf( errarg, "'%s'", fnm );
		error( "double use of field name" );
		return;
	    }
	}
    }
    if( member_tmstring_list( nm, inherits ) ){
	sprintf( errpos, "in type '%s'", nm );
	error( "Type inherits itself" );
	return;
    }
    return;
}

/* Given a list of datastructure definitions, an index in the list,
 * a list of visited flags and a list of accepted flags, check the
 * data structure with the given index for circular inheritances.
 */
static bool check_ds_inheritance(
 const_ds_list dl,
 unsigned int theds,
 bool *visited,
 bool *accepted
)
{
    tmstring_list supers;	/* The list of superclasses. */
    unsigned int ix;
    ds me = dl->arr[theds];
    bool ok = TRUE;

    assert( theds<dl->sz );
    if( accepted[theds] ){
        return ok;
    }
    if( visited[theds] ){
	sprintf( errpos, "type '%s'", me->name );
	error( "circular inheritance/alias hierarchy" );
	accepted[theds] = TRUE;		/* Break the circle to allow further checks. */
	return FALSE;
    }
    visited[theds] = TRUE;
    supers = rdup_tmstring_list( me->inherits );
    for( ix=0; ix<supers->sz; ix++ ){
        tmstring super = supers->arr[ix];
        unsigned int superix = find_type_ix( dl, super );

        if( superix<dl->sz ){
	    ok &= check_ds_inheritance( dl, superix, visited, accepted );
        }
    }
    rfre_tmstring_list( supers );
    visited[theds] = FALSE;
    accepted[theds] = TRUE;
    return ok;
}

/* Given a list of datastructure definitions, ensure that it does not
 * contain circular inheritances.
 */
bool check_ds_list( const_ds_list dl )
{
    bool *visited;	/* The data structures currently under examination */
    bool *accepted;	/* The data structures that already passed the test. */
    unsigned int ix;
    unsigned int sz;
    bool ok;

    ok = TRUE;
    /* First check on double definition of a type. */
    for( ix=0; ix<dl->sz; ix++ ){
	unsigned int iy;
	const_tmstring nmx = dl->arr[ix]->name;

	for( iy=ix+1; iy<dl->sz; iy++ ){
	    const_tmstring nmy = dl->arr[iy]->name;

	    if( strcmp( nmx, nmy ) == 0 ){
		sprintf( errarg, "type '%s'", nmx );
		error( "Double definition" );
		ok = FALSE;
		break;
	    }
	}
    }
    if( !ok ){
	/* Double definitions. Don't even try the next tests. */
	return ok;
    }
    sz = dl->sz;
    visited = TM_MALLOC( bool *, sizeof(bool)*sz );
    if( visited == NULL ){
        /* No room. Don't report it; the check is not that important anyway.  */
        return ok;
    }
    accepted = TM_MALLOC( bool *, sizeof(bool)*sz );
    if( accepted == NULL ){
        /* No room. Don't report it; the check is not that important anyway. */
        TM_FREE( visited );
        return ok;
    }
    for( ix=0; ix<sz; ix++ ){
        visited[ix] = accepted[ix] = FALSE;
    }
    for( ix=0; ix<sz; ix++ ){
        ok &= check_ds_inheritance( dl, ix, visited, accepted );
    }
    TM_FREE( accepted );
    TM_FREE( visited );
    if( !ok ){
	/* Circular inheritance. Don't even try the next tests. */
	return ok;
    }
    for( ix=0; ix<dl->sz; ix++ ){
	const_tmstring nmx = dl->arr[ix]->name;
	char msg[200];
	tmstring_list tl = new_tmstring_list();

	collect_superclasses( &tl, dl, nmx );
	sprintf( msg, "Duplicate superclass in type '%s'", nmx );
	ok &= check_double_strings( msg, tl );
	rfre_tmstring_list( tl );
	if( ok ){
	    tmstring_list fields = new_tmstring_list();

	    collect_all_fields( &fields, dl, nmx );
	    sprintf( msg, "Duplicate field in type '%s'", nmx );
	    ok &= check_double_strings( msg, fields );
	    rfre_tmstring_list( fields );
	}
    }
    return ok;
}
