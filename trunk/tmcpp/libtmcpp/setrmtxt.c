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
	arr = TM_REALLOC( char *, arr, rm );
	room = rm;
    }
}
