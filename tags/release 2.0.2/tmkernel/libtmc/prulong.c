/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"
#include "config.h"

void print_ulong( TMPRINTSTATE *st, const ulong u )
{
    char buf[sizeof(ulong)*8];

    sprintf( buf, "%lu", u );
    tm_printword( st, buf );
}
