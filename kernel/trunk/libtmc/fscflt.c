/* File: $Id$
 *
 */

#include "config.h"
#include "tmc.h"

tmbool fscan_float( FILE *f, float *p )
{
    unsigned int brac = tm_fscanopenbrac( f );

    *p = (float) 0;
    if( fscanf( f, "%f", p ) != 1 ){
	(void) strcpy( tm_errmsg, "float expected" );
	return TMTRUE;
    }
    return tm_fscanclosebrac( f, brac );
}
