/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: noroom.c
 * C. van Reeuwijk
 */

#include "config.h"
#include "tmc.h"

/* Print 'out of memory' using tm_fatal. */
void tm_noroom( void )
{
    tm_fatal( "", 0, "out of memory" );
}
