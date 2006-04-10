/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_tmuint( FILE *f, const tmuint u )
{
    fprintf( f, "%u", (unsigned int) u );
}
