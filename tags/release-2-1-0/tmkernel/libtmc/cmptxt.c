/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: cmptxt.c */

#include "config.h"
#include "tmc.h"

/* Compare two texts. */
int cmp_tmtext( const const_tmtext a, const const_tmtext b )
{
    long sz;
    long i;

    sz = a->sz;
    if( b->sz<sz ){
	sz = b->sz;
    }
    for( i=0; i<sz; i++ ){
	if( a->arr[i]!=b->arr[i] ){
	    return (int) (a->arr[i]-b->arr[i]);
	}
    }
    if( a->sz == b->sz ){
	return 0;
    }
    if( a->sz<b->sz ){
	return -1;
    }
    return 1;
}

