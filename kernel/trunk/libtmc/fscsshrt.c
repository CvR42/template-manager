/* File: $Id$
 *
 */

#include "tmc.h"

tmbool fscan_tmshort( FILE *f, tmshort *p )
{
    unsigned int brac = tm_fscanopenbrac( f );

    *p = 0;
    if( fscanf( f, "%hd", p ) != 1 ){
	(void) strcpy( tm_errmsg, "tmshort expected" );
	return TMTRUE;
    }
    return tm_fscanclosebrac( f, brac );
}
