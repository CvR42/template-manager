/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

int fscan_double( FILE *f, double *p )
{
    int brac;

    *p = (double) 0;
    brac = tm_fscanopenbrac( f );
    if( fscanf( f, "%lf", p ) != 1 ){
	(void) strcpy( tm_errmsg, "double expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
