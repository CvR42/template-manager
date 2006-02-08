/* File: $Id$
 *
 * Check correctness of the ds file.
 */

#include <assert.h>
#include <tmc.h>

#include "config.h"
#include "tmdefs.h"
#include "tmcode.h"
#include "error.h"
#include "misc.h"
#include "checkds.h"

/* Ensure that there are no double names in tuple with name 'nm'
 * and fields 'fields'.
 */
void cktuple( const_tmsymbol nm, const_Field_list fields, const_tmsymbol_list inherits )
{
    unsigned int ix;	/* index of currently checked field */

    for( ix=0; ix<fields->sz; ix++ ){
	const_Field fx = fields->arr[ix];
	const_origsymbol fnm = fx->name;
	unsigned int iy;	/* index of searched subsequent fields */

	for( iy=ix+1; iy<fields->sz; iy++ ){
	    const_Field fy = fields->arr[iy];

	    if( fy->name->sym == fnm->sym ){
		origsymbol_error( fy->name, "double use of field name in type `%s'", nm->name );
		return;
	    }
	}
    }
    if( member_tmsymbol_list( nm, inherits ) ){
	error( "Type `%s' inherits itself", nm->name );
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
    tmsymbol_list supers;	/* The list of superclasses. */
    unsigned int ix;
    const_ds me = dl->arr[theds];
    bool ok = TRUE;

    assert( theds<dl->sz );
    if( accepted[theds] ){
        return ok;
    }
    if( visited[theds] ){
	origsymbol_error( me->name, "circular inheritance/alias hierarchy in type" );
	accepted[theds] = TRUE;		/* Break the circle to allow further checks. */
	return FALSE;
    }
    visited[theds] = TRUE;
    supers = rdup_tmsymbol_list( me->inherits );
    for( ix=0; ix<supers->sz; ix++ ){
        tmsymbol super = supers->arr[ix];
        unsigned int superix = find_type_ix( dl, super );

        if( superix<dl->sz ){
	    ok &= check_ds_inheritance( dl, superix, visited, accepted );
        }
    }
    rfre_tmsymbol_list( supers );
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
	const_origsymbol nmx = dl->arr[ix]->name;

	for( iy=ix+1; iy<dl->sz; iy++ ){
	    const_origsymbol nmy = dl->arr[iy]->name;

	    if( nmx->sym == nmy->sym ){
		origsymbol_error( nmy, "Double definition" );
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
	tmsymbol nmx = dl->arr[ix]->name->sym;
	char msg[200];
	tmsymbol_list tl = new_tmsymbol_list();

	collect_superclasses( &tl, dl, nmx );
	sprintf( msg, "Duplicate superclass in type '%s'", nmx->name );
	ok &= check_double_symbols( msg, tl );
	rfre_tmsymbol_list( tl );
	if( ok ){
	    tmsymbol_list fields = new_tmsymbol_list();

	    collect_all_fields( &fields, dl, nmx );
	    sprintf( msg, "Duplicate field in type '%s'", nmx->name );
	    ok &= check_double_symbols( msg, fields );
	    rfre_tmsymbol_list( fields );
	}
    }
    return ok;
}
