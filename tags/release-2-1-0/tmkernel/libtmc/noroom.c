/* File: $Id$ */

#include "config.h"
#include "tmc.h"

/* Print 'out of memory' using tm_fatal. */
void tm_noroom( void )
{
    tm_fatal( "", 0, "out of memory" );
}
