/* File: $Id$
 *
 */

#include "config.h"
#include "tmc.h"

int fscan_tmuint( FILE *f, tmuint *p )
{
    unsigned int brac = tm_fscanopenbrac( f );

    *p = 0;
    if( fscanf( f, "%u", p ) != 1 ){
	(void) strcpy( tm_errmsg, "unsigned int expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
