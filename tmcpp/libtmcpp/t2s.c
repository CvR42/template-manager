/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmcpp.h"
#include "config.h"

// Given a tmtext 't' return a tmstring .
// This function assumes the tmtext contains no '\0'.
tmstring tmtext_to_tmstring( const tmtext *t )
{

    size_t sz = (size_t) t->sz;
    // Create a string big enough to hold the text and the terminating '\0'.
    tmstring s = create_tmstring( sz+1 );
    if( s == tmstringNIL ){
	return s;
    }
#if HAVE_MEMMOVE
    memcpy( s, t->arr, sz );
#else
    for( size_t ix=0; ix<t->sz; ix++ ){
	s[ix] = t->arr[ix];
    }
#endif
    s[sz] = '\0';
    return s;
}
