/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

void print_uint( TmPrintState *st, const uint u )
{
    char buf[sizeof(uint)*8];

    sprintf( buf, "%u", u );
    st->printWord( buf );
}
