/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

// Given a position 'from' and a position 'to',
// remove all characters starting from 'from' up to, but not including 'to'.
tmtext *tmtext::erase( const size_type from, const size_type to )
{
    if( to<from ){
	return this;
    }
    size_type gapsz = to-from;
    if( sz<=from+gapsz ){
	// All chars until the end of the tmtext are to be deleted,
	// simply adjust the text size..
	sz = from;
	return this;
    }
    size_type z = sz-(from+gapsz);
    char *d = arr+from;
    char *s = arr+from+gapsz;
    sz -= gapsz;
#if HAVE_MEMMOVE
    memmove( d, s, (unsigned int) z );
#else
    while( z>0 ){
	*d++ = *s++;
	z--;
    }
#endif
    return this;
}
