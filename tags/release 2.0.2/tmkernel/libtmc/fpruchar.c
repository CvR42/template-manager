/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_uchar( FILE *f, const uchar c )
{
    fprintf( f, "'%s'", tm_escapestring( (unsigned int) c ) );
}
