/* File: $Id$ */

#include "tmc.h"

/* Compare two texts. */
tmbool isequal_tmtext( const const_tmtext a, const const_tmtext b )
{
    long i;
    long sz;

    if( a == b ){
	return TMTRUE;
    }
    if( a == tmtextNIL || b == tmtextNIL ){
	return TMFALSE;
    }
    if( a->sz != b->sz ){
	return TMFALSE;
    }

    sz = a->sz;
    for( i=0; i<sz; i++ ){
	if( a->arr[i]!=b->arr[i] ){
	    return TMFALSE;
	}
    }
    return TMTRUE;
}

