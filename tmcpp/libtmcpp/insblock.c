/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include <string.h>
#include "config.h"
#include "tmcpp.h"

/* Given a position 'pos' and a size 'blk_sz', make room for 'blk_sz'
 * characters in the ext, starting at position 'pos'.
 */
void tmtext::insblock( const long pos, const long blk_sz )
{
    reserve( sz+blk_sz );
    long z = sz-pos;
    if( z<=0 ){
	// The chars are to be inserted at the end of the tmtext
	sz += blk_sz;
	return;
    }
#if HAVE_MEMMOVE
    char *s = arr+pos;
    char *d = arr+pos+blk_sz;
    memmove( d, s, z );
#else
    char *s = arr+sz;
    char *d = arr+sz+blk_sz;
    while( z>0 ){
	d--;
	s--;
	*d = *s;
	z--;
    }
#endif
    sz += blk_sz;
}
