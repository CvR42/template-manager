/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

unsigned long tmtext::newcount = 0;
unsigned long tmtext::freecount = 0;

// Print statistics of tmtext usage to file 'f'.
void tmtext::stat( FILE *f )
{
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"tmtext",
	newcount,
	freecount,
	((newcount==freecount)? "": "<-")
    );
}

// Return the balance of the text routines.
int tmtext::get_balance()
{
    if( newcount<freecount ){
	return -1;
    }
    if( newcount>freecount ){
	return 1;
    }
    return 0;
}
