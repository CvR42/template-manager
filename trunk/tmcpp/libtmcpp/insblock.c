/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include <string.h>
#include "tmcpp.h"
#include "config.h"

/* Given a tmtext 't', a position 'pos' and a size 'sz', make room for 'sz'
 * characters in the tmtext, starting at position 'pos'.
 */
void insblock_tmtext( tmtext *t, const long pos, const long sz )
{
    t->reserve( t->sz+sz );
    long z = t->sz-pos;
    if( z<=0 ){
	/* The chars are to be inserted at the end of the tmtext,	 */
	t->sz += sz;
	return;
    }
#if HAVE_MEMMOVE
    char *s = t->arr+pos;
    char *d = t->arr+pos+sz;
    memmove( d, s, z );
#else
    char *s = t->arr+t->sz;
    char *d = t->arr+t->sz+sz;
    while( z>0 ){
	d--;
	s--;
	*d = *s;
	z--;
    }
#endif
    t->sz += sz;
}
