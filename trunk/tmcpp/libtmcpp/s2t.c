/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

// Construct a text from a string
tmtext::tmtext( const char *s ): arr(0), curpos(0), sz(0), room(0)
{
    puts_tmtext( s, this );
    curpos = 0;
    newcount++;
}
