/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

// Ensure that this tmtext has room for at least 'sz' characters.
void tmtext::reserve( const long rm )
{
    if( rm>room ){
	arr = (char *) tm_realloc( arr, rm );
	room = rm;
    }
}
