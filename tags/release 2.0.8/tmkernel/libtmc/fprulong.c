/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_tmulong( FILE *f, const tmulong u )
{
    fprintf( f, "%lu", u );
}
