/* File: $Id$
 *
 * Tm - an interface code generator.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_tmulong( FILE *f, const tmulong u )
{
    fprintf( f, "%lu", u );
}
