/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_tmushort( FILE *f, const tmushort i )
{
    fprintf( f, "%hu", i );
}
