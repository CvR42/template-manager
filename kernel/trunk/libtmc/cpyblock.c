/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"
#include "config.h"

/* Given two pointers to tmtext blocks 'd' and 's', and a block size 'sz',
 * copy 'sz' characters from 's' to 'd'. The blocks should not overlap,
 * there are special functions to insert or delete blocks in a tmtext.
 */
void copyblock_tmtext( tmtextptr d, const_tmtextptr s, long sz )
{
    long cnt = sz;

#if HAVE_MEMMOVE
    memcpy( d, s, (size_t) cnt );
#else
    const_tmtextptr p = s;

    while( cnt>0 ){
	*d++ = *p++;
	cnt--;
    }
#endif
}
