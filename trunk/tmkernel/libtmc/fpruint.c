/* File: $Id$
 *
 * Tm - an interface code generator.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_tmuint( FILE *f, const tmuint u )
{
    fprintf( f, "%u", (unsigned int) u );
}
