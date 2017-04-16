/* File: $Id$
 * 
 */

#include "tmc.h"

tmbool fscan_double( FILE *f, double *p )
{
    unsigned int brac = tm_fscanopenbrac( f );

    *p = (double) 0;
    if( fscanf( f, "%lf", p ) != 1 ){
	(void) strcpy( tm_errmsg, "double expected" );
	return TMTRUE;
    }
    return tm_fscanclosebrac( f, brac );
}
