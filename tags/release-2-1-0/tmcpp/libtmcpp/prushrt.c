/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

void print_ushrt( TmPrintState *st, const ushrt i )
{
    char buf[sizeof(ushrt)*8];

    sprintf( buf, "%hu", i );
    st->printWord( buf );
}
