/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

// tmtext copy constructor
void tmtext::settext( const tmtext &c )
{
    reserve( c.sz );
    copyblock( arr, c.arr, c.sz );
    sz = c.sz;
    curpos = c.curpos;
}
