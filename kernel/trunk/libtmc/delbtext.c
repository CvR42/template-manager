/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"
#include "config.h"

/* Given a tmtext 't', a position 'from' and a size 'sz', delete 'sz'
 * characters from the tmtext, starting at position 'from'.
 */
tmtext delblock_tmtext( tmtext t, const long from, const long to )
{
    tmtextptr s;
    tmtextptr d;
    long sz;
    long z;		/* The size of the block to move. */

    sz = to-from;
    if( sz <= 0 ){
	return t;
    }
    z = t->sz-(from+sz);
    if( z<=0 ){
	/* All chars until the end of the tmtext are to be deleted,
	 * simply adjust the tmtext size..
	 */
	t->sz = from;
	return t;
    }
    d = t->arr+from;
    s = t->arr+from+sz;
    t->sz -= sz;
#if HAVE_MEMMOVE
    memmove( d, s, (size_t) z );
#else
    while( z>0 ){
	*d++ = *s++;
	z--;
    }
#endif
    return t;
}
