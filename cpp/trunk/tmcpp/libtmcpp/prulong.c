/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

void print_ulong( TmPrintState *st, const ulong u )
{
    char buf[sizeof(ulong)*8];

    sprintf( buf, "%lu", u );
    st->printWord( buf );
}
