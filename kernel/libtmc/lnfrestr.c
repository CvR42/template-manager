/* File: $Id$
 *
 * fre_tmstring() version that is used when LOGNEW is activated.
 */

#include "tmc.h"

/* De-allocate space for tmstring 's', and report it to lognew. */
void fre_tmstring_lognew( tmstring s )
{
    if( s != tmstringNIL ){
        tm_logfre( s );
    }
    fre_tmstring_nolognew( s );
}
