/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

int fscan_int( FILE *f, int *p )
{
    int brac = tm_fscanopenbrac( f );

    *p = 0;
    if( fscanf( f, "%d", p ) != 1 ){
	(void) strcpy( tm_errmsg, "int expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
