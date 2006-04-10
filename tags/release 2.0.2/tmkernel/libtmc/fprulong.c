/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_ulong( FILE *f, const ulong u )
{
    fprintf( f, "%lu", u );
}
