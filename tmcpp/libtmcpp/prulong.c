/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmcpp.h"
#include "config.h"

void print_ulong( TmPrintState *st, const ulong u )
{
    char buf[sizeof(ulong)*8];

    sprintf( buf, "%lu", u );
    st->printWord( buf );
}
