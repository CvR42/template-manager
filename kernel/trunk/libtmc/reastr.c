/* File: $Id$
 *
 * Reallocate tmstring size.
 */

#include <ctype.h>
#include "tmc.h"

/* Reallocate tmstring size to 'sz'. Notice that the tmstring
 * count is unaffected.
 */
tmstring realloc_tmstring_nolognew( tmstring s, size_t sz )
{
    tmstring adr;
    size_t realsz = sz;

    if( realsz==0 ){
	realsz = 1;	/* Some mallocs/reallocs get upset over sz==0. */
    }
    if( s == NULL ){
	adr = TM_MALLOC( char *, realsz*sizeof( char ) );
        adr[0] = '\0';
    }
    else {
	adr = TM_REALLOC( char *, s, realsz*sizeof( char ) );
    }
    return adr;
}
