/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include <string.h>
#include "tmc.h"
#include "config.h"

/* Given a tmtext 't', a position 'pos' and a size 'sz', make room for 'sz'
 * characters in the tmtext, starting at position 'pos'.
 */
void insblock_tmtext( tmtext t, const long pos, const long sz )
{
    tmtextptr s;
    tmtextptr d;
    long z;		/* The size of the block to move. */

    t = setroom_tmtext( t, t->sz+sz );
    z = t->sz-pos;
    if( z<=0 ){
	/* The chars are to be inserted at the end of the tmtext,	 */
	t->sz += sz;
	return;
    }
#if HAVE_MEMMOVE
    s = t->arr+pos;
    d = t->arr+pos+sz;
    memmove( d, s, z );
#else
    s = t->arr+t->sz;
    d = t->arr+t->sz+sz;
    while( z>0 ){
	d--;
	s--;
	*d = *s;
	z--;
    }
#endif
    t->sz += sz;
}
