/* File: $Id$
 *
 */

#include "config.h"
#include "tmc.h"

int fscan_tmulong( FILE *f, tmulong *p )
{
    unsigned int brac = tm_fscanopenbrac( f );

    *p = 0;
    if( fscanf( f, "%lu", p ) != 1 ){
	(void) strcpy( tm_errmsg, "tmulong expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
