/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"
#include <string.h>

/* Given two pointers to text blocks 'd' and 's', and a block size 'sz',
 * copy 'sz' characters from 's' to 'd'. The blocks should not overlap,
 * there are special functions to insert or delete blocks in a text.
 */
void tmtext::copyblock( char *d, const char *s, const size_type sz )
{
    const char *p = s;
    size_type cnt = sz;

#if HAVE_MEMMOVE
    memcpy( d, p, (unsigned int) cnt );
#else
    while( cnt>0 ){
	*d++ = *p++;
	cnt--;
    }
#endif
}
