/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

// Given a position 'from' and a position 'to',
// remove all characters starting from 'from' up to, but not including 'to'.
void tmtext::erase( const long from, const long to )
{
    long gapsz = to-from;
    if( gapsz <= 0 ){
	return;
    }
    long z = sz-(from+gapsz);
    if( z<=0 ){
	// All chars until the end of the tmtext are to be deleted,
	// simply adjust the tmtext size..
	sz = from;
	return;
    }
    char *d = arr+from;
    char *s = arr+from+gapsz;
    sz -= gapsz;
#if HAVE_MEMMOVE
    memmove( d, s, z );
#else
    while( z>0 ){
	*d++ = *s++;
	z--;
    }
#endif
}
