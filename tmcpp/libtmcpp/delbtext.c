/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

/* Given a tmtext 't', a position 'from' and a size 'sz', delete 'sz'
 * characters from the tmtext, starting at position 'from'.
 */
tmtext *delblock_tmtext( tmtext *t, const long from, const long to )
{
    long sz = to-from;
    if( sz <= 0 ){
	return t;
    }
    long z = t->sz-(from+sz);
    if( z<=0 ){
	/* All chars until the end of the tmtext are to be deleted,
	 * simply adjust the tmtext size..
	 */
	t->sz = from;
	return t;
    }
    char *d = t->arr+from;
    char *s = t->arr+from+sz;
    t->sz -= sz;
#if HAVE_MEMMOVE
    memmove( d, s, z );
#else
    while( z>0 ){
	*d++ = *s++;
	z--;
    }
#endif
    return t;
}
