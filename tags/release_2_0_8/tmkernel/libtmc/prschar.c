/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"
#include "config.h"

void print_tmschar( TMPRINTSTATE *st, const tmschar c )
{
    char buf[10];

    sprintf( buf, "'%s'", tm_escapestring( (unsigned int) c ) );
    tm_printword( st, buf );
}
