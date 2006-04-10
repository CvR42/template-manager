/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_ushrt( FILE *f, const ushrt i )
{
    fprintf( f, "%hu", i );
}
