/* File: expand.c
 *
 * Expand inherits of the datastructure definitions.
 */

#include <tmc.h>

#include "tmdefs.h"
#include "config.h"

#include "tmcode.h"
#include "global.h"
#include "error.h"
#include "misc.h"
#include "expand.h"

/* Forward declarations. */
static field_list collect_fields_tmstring_list( tmstring_list ihl );

/* Given a string that presumably is a type name, collect the
 * fields that must be inherited from this type.
 */
static field_list collect_fields_tmstring( tmstring super )
{
    unsigned int superix;
    ds superds;
    field_list ans;

    superix = find_type_ix( allds, super );
    if( superix>=allds->sz ){
        sprintf( errarg, "'%s'", super );
        error( "since this is not a known type, I cannot use it as a superclass" );
        return new_field_list();
    }
    superds = allds->arr[superix];
    ans = field_listNIL;
    switch( superds->tag ){
        case TAGDsCons:
            sprintf( errarg, "'%s'", super );
            error( "Expansion does not allow inheritance from a constructor type" );
            return new_field_list();

	case TAGDsTuple:
	    ans = rdup_field_list( superds->DsTuple.tuplefields );
	    ans = concat_field_list(
	        ans,
	        collect_fields_tmstring_list( superds->DsTuple.tinherits )
	    );
    }
    return ans;
}

/* Given a list of strings that presumably are type names, collect the
 * fields that must be inherited from these types.
 */
static field_list collect_fields_tmstring_list( tmstring_list ihl )
{
    unsigned int ix;
    field_list fl;
    field_list new;

    fl = new_field_list();
    for( ix=0; ix<ihl->sz; ix++ ){
        new = collect_fields_tmstring( ihl->arr[ix] );
        fl = concat_field_list( fl, new );
    }
    return fl;
}

/* Given a constructor 'cons', and a list of fields 'fl',
 * augment the constructor with the fields of 'fl'.
 */
static constructor augment_constructor( constructor cons, field_list fl )
{
    cons->fields = concat_field_list( rdup_field_list( fl ), cons->fields );
    return cons;
}

/* Given a list of constructors 'cl', and a list of fields 'fl',
 * augment each of the constructors in the list with the fields of
 * 'fl'.
 */
static constructor_list augment_constructor_list( constructor_list cl, field_list fl )
{
    unsigned int ix;

    for( ix=0; ix<cl->sz; ix++ ){
        cl->arr[ix] = augment_constructor( cl->arr[ix], fl );
    }
    return cl;
}

/* Given a ds 'd', modify it to contain all the fields it inherits from
 * other types.
 */
static ds expand_inherits_ds( ds d )
{
    switch( d->tag ){
        case TAGDsCons:
        {
	    field_list new = collect_fields_tmstring_list( d->DsCons.cinherits );

	    d->DsCons.conslist = augment_constructor_list( d->DsCons.conslist, new );
	    rfre_field_list( new );
	    rfre_tmstring_list( d->DsCons.cinherits ); 
	    d->DsCons.cinherits = new_tmstring_list();
	    ckconstructor( d->DsCons.ctypename, d->DsCons.conslist );
	    break;
	}

        case TAGDsTuple:
        {
	    field_list new = collect_fields_tmstring_list( d->DsTuple.tinherits );
	    d->DsTuple.tuplefields = concat_field_list(
	        new,
		d->DsTuple.tuplefields
	    );
	    rfre_tmstring_list( d->DsTuple.tinherits ); 
	    d->DsTuple.tinherits = new_tmstring_list();
	    cktuple( d->DsTuple.ttypename, d->DsTuple.tuplefields );
	    break;
	}

    }
    return d;
}

/* Given a type name 'nm', expand all inherit references for that type. */
static void expand_inherits_type( tmstring nm )
{
    unsigned int ix;

    ix = find_type_ix( allds, nm );
    if( ix>=allds->sz ){
        sprintf( errarg, "'%s'", nm );
        error( "since this is not a known type, I cannot expand its inherits" );
	return;
    }
    allds->arr[ix] = expand_inherits_ds( allds->arr[ix] );
}

/* Given a list of type names, expand all inherit references of those
 * types.
 */
void expand_inherits( tmstring_list types )
{
    unsigned int ix;

    for( ix=0; ix<types->sz; ix++ ){
        expand_inherits_type( types->arr[ix] );
    }
}
