/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"
#include "config.h"

void print_tmulong( TMPRINTSTATE *st, const tmulong u )
{
    char buf[sizeof(tmulong)*8];

    sprintf( buf, "%lu", u );
    tm_printword( st, buf );
}
