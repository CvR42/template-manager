/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

/* Given string 's', construct a new tmtext with that string. */
tmtext string_to_tmtext_nolognew( const char *s )
{
    tmtext nw;

    nw = new_tmtext_nolognew();
    nw = puts_tmtext( s, nw );
    return nw;
}

