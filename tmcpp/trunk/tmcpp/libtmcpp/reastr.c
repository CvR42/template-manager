/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: reastr.c
   Reallocate tmstring size.
 */

#include <ctype.h>
#include "config.h"
#include "tmcpp.h"

// Reallocate tmstring size to 'sz'. Notice that the tmstring
// count is unaffected.
tmstring realloc_tmstring_nolognew( tmstring s, const size_t sz )
{
    tmstring adr;
    size_t realsz = sz;

    if( realsz==0 ){
	realsz = 1;	// Some mallocs/reallocs get upset over sz==0.
    }
    if( s == NULL ){
	adr = (char *) tm_malloc( realsz*sizeof( char ) );
    }
    else {
	adr = (char *) tm_realloc( s, realsz*sizeof( char ) );
    }
    return adr;
}
