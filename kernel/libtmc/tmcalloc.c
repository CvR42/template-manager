/* File: $Id$ */

#include "tmc.h"

/* Allocate the given amount of memory and check if
 * it has been done. If not, complain, and stop.
 */
tm_neutralp tm_calloc( size_t n, size_t sz )
{
    tm_neutralp adr;

    if( n == 0 || sz == 0 ){
	n = 1;
	sz = 1;
    }
    adr = (tm_neutralp) calloc( n, sz );
    if( adr == (tm_neutralp)0 ){
	tm_noroom();
        /*@notreached@*/
	exit( EXIT_FAILURE );
    }
    return adr;
}
