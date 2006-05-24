/* File: $Id$
 *
 */

#include "config.h"
#include "tmc.h"

tmbool fscan_int( FILE *f, int *p )
{
    unsigned int brac = tm_fscanopenbrac( f );

    *p = 0;
    if( fscanf( f, "%d", p ) != 1 ){
	(void) strcpy( tm_errmsg, "int expected" );
	return TMTRUE;
    }
    return tm_fscanclosebrac( f, brac );
}
