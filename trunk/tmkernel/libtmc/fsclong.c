/* File: $Id$
 *
 */

#include "config.h"
#include "tmc.h"

int fscan_long( FILE *f, long int *p )
{
    int brac = tm_fscanopenbrac( f );

    *p = 0;
    if( fscanf( f, "%ld", p ) != 1 ){
	(void) strcpy( tm_errmsg, "long expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
