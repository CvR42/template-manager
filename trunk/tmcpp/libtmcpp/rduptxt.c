/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmcpp.h"
#include "config.h"

// tmtext copy constructor
tmtext::tmtext( const tmtext &c ): arr(0), curpos(0), sz(0), room(0)
{
    reserve( c.sz );
    copyblock( arr, c.arr, c.sz );
    sz = c.sz;
    curpos = c.curpos;
    newcount++;
}
