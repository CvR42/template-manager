/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

int fscan_tmushort( FILE *f, tmushort *p )
{
    int brac;

    *p = 0;
    brac = tm_fscanopenbrac( f );
    if( fscanf( f, "%hu", p ) != 1 ){
	(void) strcpy( tm_errmsg, "tmushort expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}