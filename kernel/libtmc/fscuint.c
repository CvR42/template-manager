/* File: $Id$
 *
 */

#include "tmc.h"

tmbool fscan_tmuint( FILE *f, tmuint *p )
{
    unsigned int brac = tm_fscanopenbrac( f );

    *p = 0;
    if( fscanf( f, "%u", p ) != 1 ){
	(void) strcpy( tm_errmsg, "unsigned int expected" );
	return TMTRUE;
    }
    return tm_fscanclosebrac( f, brac );
}
