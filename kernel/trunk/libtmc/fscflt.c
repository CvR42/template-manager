/* File: $Id$
 *
 */

#include "config.h"
#include "tmc.h"

int fscan_float( FILE *f, float *p )
{
    int brac = tm_fscanopenbrac( f );

    *p = (float) 0;
    if( fscanf( f, "%f", p ) != 1 ){
	(void) strcpy( tm_errmsg, "float expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
