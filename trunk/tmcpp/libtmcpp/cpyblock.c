/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"
#include <string.h>

/* Given two pointers to tmtext blocks 'd' and 's', and a block size 'sz',
 * copy 'sz' characters from 's' to 'd'. The blocks should not overlap,
 * there are special functions to insert or delete blocks in a tmtext.
 */
void copyblock_tmtext( char *d, const char *s, const long sz )
{
    const char *p = s;
    long cnt = sz;

#if HAVE_MEMMOVE
    memcpy( d, p, cnt );
#else
    while( cnt>0 ){
	*d++ = *p++;
	cnt--;
    }
#endif
}
