/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmcpp.h"
#include "config.h"

void print_uchar( TMPRINTSTATE *st, const uchar c )
{
    char buf[10];

    sprintf( buf, "'%s'", tm_escapestring( (unsigned int) c ) );
    tm_printword( st, buf );
}
