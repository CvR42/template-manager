/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

void fprint_uint( FILE *f, const uint u )
{
    fprintf( f, "%u", u );
}
