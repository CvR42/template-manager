/* File: $Id$
 *
 */

#include "config.h"
#include "tmc.h"

tmbool fscan_long( FILE *f, long int *p )
{
    unsigned int brac = tm_fscanopenbrac( f );

    *p = 0;
    if( fscanf( f, "%ld", p ) != 1 ){
	(void) strcpy( tm_errmsg, "long expected" );
	return TMTRUE;
    }
    return tm_fscanclosebrac( f, brac );
}
