/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"
#include "config.h"

/* Given a tmtext 't' return a tmstring .
 * This function assumes the tmtext contains no '\0'.
 */
tmstring tmtext_to_tmstring_lognew( const tmtext t, const char *file, const int line )
{
    size_t sz;
    long ix;
    tmstring s;

    sz = (size_t) t->sz;
    s = new_tmstring_lognew( "", file, line );
    /* Allocate room for the tmstring and the terminating '\0'. */
    s = realloc_tmstring_lognew( s, sz+1, file, line );
    for( ix=0; ix<t->sz; ix++ ){
	s[ix] = t->arr[ix];
    }
    s[sz] = '\0';
    return s;
}
