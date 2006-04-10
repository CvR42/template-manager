/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

tm_neutralp tm_badcast( const char *file, const int line )
{
    tm_fatal( file, line, "Bad cast" );
    return (tm_neutralp) 0;
}
