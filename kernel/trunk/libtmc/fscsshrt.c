/* File: $Id$
 *
 */

#include "config.h"
#include "tmc.h"

int fscan_tmshort( FILE *f, tmshort *p )
{
    int brac = tm_fscanopenbrac( f );

    *p = 0;
    if( fscanf( f, "%hd", p ) != 1 ){
	(void) strcpy( tm_errmsg, "tmshort expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
