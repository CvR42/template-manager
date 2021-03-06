/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

// Construct a text from a string
tmtext::tmtext( const char *s ): room(0), arr(0), curpos(0), sz(0)
{
    append( s );
    curpos = 0;
    newcount++;
}
