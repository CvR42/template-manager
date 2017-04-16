/* File: $Id$ */

#include "tmc.h"

/* Allocate the given amount of memory and check if
   it has been done. If not, complain, and stop.
 */
tm_neutralp tm_realloc( tm_neutralp old, size_t sz )
{
    tm_neutralp adr;

    if( sz == 0 ){
	sz = 1;
    }
    adr = (tm_neutralp) realloc( old, sz );
    if( adr == (tm_neutralp)0 ){
	tm_noroom();
        /*@notreached@*/
	exit( EXIT_FAILURE );
    }
    return adr;
}
