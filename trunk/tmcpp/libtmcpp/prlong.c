/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmcpp.h"
#include "config.h"

void print_long( TmPrintState *st, const long u )
{
    char buf[sizeof(long)*8];

    sprintf( buf, "%ld", u );
    st->printWord( buf );
}
