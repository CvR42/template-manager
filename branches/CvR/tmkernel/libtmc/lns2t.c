/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

/* Given string 's', construct a new tmtext with that string. */
tmtext string_to_tmtext_lognew( const char *s, const char *file, int line )
{
    tmtext nw;

    nw = new_tmtext_lognew( file, line );
    nw = puts_tmtext( s, nw );
    return nw;
}

