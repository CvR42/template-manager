/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

int fscan_long( FILE *f, long int *p )
{
    int brac;

    *p = 0;
    brac = tm_fscanopenbrac( f );
    if( fscanf( f, "%ld", p ) != 1 ){
	(void) strcpy( tm_errmsg, "long expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
