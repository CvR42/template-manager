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
void cktuple( tmstring nm, field_list fields )
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
}

/* Ensure that there are no double names in each of the constructors of
 * constructor type with name 'nm' and constructors 'cons'.
 */
void ckconstructor( tmstring nm, constructor_list cons )
{
    constructor conx;
    field_list fields;
    unsigned int cix;	/* index in constructor list */
    unsigned int ix;	/* index of currently checked field */
    unsigned int six;	/* index for searching of fields/constr. */
    field fx;		/* checked field */
    field fy;		/* searched field */
    tmstring fnm;	/* name of currently checked field */
    tmstring connm;	/* name of current constructor */

    for( cix=0; cix<cons->sz; cix++ ){
	conx = cons->arr[cix];
	fields = conx->fields;
	connm = conx->name;
	for( ix=0; ix<fields->sz; ix++ ){
	    fx = fields->arr[ix];
	    fnm = fx->name;
	    for( six=ix+1; six<fields->sz; six++ ){
		fy = fields->arr[six];
		if( strcmp( fy->name, fnm ) == 0 ){
		    sprintf(
			errpos,
			"in type '%s', constructor '%s'",
			nm,
			connm
		    );
		    sprintf( errarg, "'%s'", fnm );
		    error( "double use of field name" );
		}
	    }
	}
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
    myname = tmstringNIL;
    supers = tmstring_listNIL;
    switch( me->tag ){
        case TAGDsCons:
            supers = rdup_tmstring_list( me->DsCons.inherits );
            myname = me->DsCons.name;
            break;

	case TAGDsTuple:
            supers = rdup_tmstring_list( me->DsTuple.inherits );
            myname = me->DsTuple.name;
            break;

	case TAGDsClass:
	    supers = rdup_tmstring_list( me->DsClass.inherits );
            myname = me->DsClass.name;
            break;

    }
    if( accepted[theds] ){
        return;
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
	else {
	    sprintf( errpos, "type '%s'", myname );
	    sprintf( errarg, "'%s'", super );
	    error( "Inheritance from unknown type" );
	}
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

    for( ix=0; ix<dl->sz; ix++ ){
	unsigned int iy;
	const tmstring nmx = get_type_name( dl->arr[ix] );

	for( iy=ix+1; iy<dl->sz; iy++ ){
	    const tmstring nmy = get_type_name( dl->arr[iy] );

	    if( strcmp( nmx, nmy ) == 0 ){
		sprintf( errarg, "type '%s'", nmx );
		error( "Double definition" );
	    }
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
