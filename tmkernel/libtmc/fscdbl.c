/* File: $Id$
 * 
 */

#include "config.h"
#include "tmc.h"

int fscan_double( FILE *f, double *p )
{
    int brac = tm_fscanopenbrac( f );

    *p = (double) 0;
    if( fscanf( f, "%lf", p ) != 1 ){
	(void) strcpy( tm_errmsg, "double expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
