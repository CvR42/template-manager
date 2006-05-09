/* File: $Id$
 *
 */

#include "config.h"
#include "tmc.h"

int fscan_tmschar( FILE *f, tmschar *p )
{
    int code;
    unsigned int brac = tm_fscanopenbrac( f );

    *p = 0;
    if( tm_fneedc( f, '\'' ) ){
	return TMTRUE;
    }
    if( tm_fscanescapedchar( f, &code ) ){
	return TMTRUE;
    }
    *p = (tmschar) code;
    if( tm_fneedc( f, '\'' ) ){
	return TMTRUE;
    }
    return tm_fscanclosebrac( f, brac );
}
