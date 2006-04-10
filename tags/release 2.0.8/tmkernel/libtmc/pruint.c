/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"
#include "config.h"

void print_tmuint( TMPRINTSTATE *st, const tmuint u )
{
    char buf[sizeof(tmuint)*8];

    sprintf( buf, "%u", u );
    tm_printword( st, buf );
}
