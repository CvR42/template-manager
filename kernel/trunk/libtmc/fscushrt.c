/* File: $Id$
 *
 */

#include "tmc.h"

tmbool fscan_tmushort( FILE *f, tmushort *p )
{
    unsigned int brac;

    *p = 0;
    brac = tm_fscanopenbrac( f );
    if( fscanf( f, "%hu", p ) != 1 ){
	(void) strcpy( tm_errmsg, "tmushort expected" );
	return TMTRUE;
    }
    return tm_fscanclosebrac( f, brac );
}
