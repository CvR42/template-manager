/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"
#include "config.h"

void print_tmushort( TMPRINTSTATE *st, const tmushort i )
{
    char buf[sizeof(tmushort)*8];

    sprintf( buf, "%hu", i );
    tm_printword( st, buf );
}
