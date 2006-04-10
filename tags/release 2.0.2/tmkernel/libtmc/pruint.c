/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"
#include "config.h"

void print_uint( TMPRINTSTATE *st, const uint u )
{
    char buf[sizeof(uint)*8];

    sprintf( buf, "%u", u );
    tm_printword( st, buf );
}
