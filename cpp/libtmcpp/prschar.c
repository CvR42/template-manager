/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

void print_schar( TmPrintState *st, const schar c )
{
    char buf[10];

    sprintf( buf, "'%s'", tm_escapestring( (unsigned int) c ) );
    st->printWord( buf );
}
