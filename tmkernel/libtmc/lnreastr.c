/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: nlreastr.c
   Realloc tmstring size. Version for use with lognew.
 */

#include <ctype.h>
#include "config.h"
#include "tmc.h"

/* Reallocate tmstring size to 'sz'. Notice that the tmstring
 * count is unaffected.
 */
tmstring realloc_tmstring_lognew( tmstring s, const size_t sz, const char *file, const int line )
{
    tmstring adr;

    tm_logfre( s );
    adr = realloc_tmstring_nolognew( s, sz );
    tm_lognew( adr, file, line );
    return adr;
}
