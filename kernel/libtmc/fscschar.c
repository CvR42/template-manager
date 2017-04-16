/* File: $Id$
 *
 */

#include "tmc.h"

tmbool fscan_tmschar( FILE *f, tmschar *p )
{
    int code;
    unsigned int brac = tm_fscanopenbrac( f );

    *p = '\0';
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
