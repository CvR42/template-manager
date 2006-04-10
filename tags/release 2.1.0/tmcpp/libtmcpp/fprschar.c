/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

void fprint_schar( FILE *f, const schar c )
{
    fprintf( f, "'%s'", tm_escapestring( (unsigned int) c ) );
}
