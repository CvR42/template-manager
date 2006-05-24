/* File: $Id$
 *
 * Tm - an interface code generator.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_tmuchar( FILE *f, const tmuchar c )
{
    fprintf( f, "'%s'", tm_escapestring( (int) c ) );
}
