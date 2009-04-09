/* File: $Id$
 */

#include "tmc.h"

tmbool fscan_tmuchar( FILE *f, tmuchar *p )
{
    unsigned int brac;
    int code;

    *p = '\0';
    brac = tm_fscanopenbrac( f );
    if( tm_fneedc( f, '\'' ) ){
	return TMTRUE;
    }
    if( tm_fscanescapedchar( f, &code ) ){
	return TMTRUE;
    }
    *p = (tmuchar) code;
    if( tm_fneedc( f, '\'' ) ){
	return TMTRUE;
    }
    return tm_fscanclosebrac( f, brac );
}
