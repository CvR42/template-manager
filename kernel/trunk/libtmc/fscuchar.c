/* File: $Id$
 */

#include "config.h"
#include "tmc.h"

int fscan_tmuchar( FILE *f, tmuchar *p )
{
    unsigned int brac;
    int code;

    *p = '\0';
    brac = tm_fscanopenbrac( f );
    if( tm_fneedc( f, '\'' ) ){
	return 1;
    }
    if( tm_fscanescapedchar( f, &code ) ){
	return 1;
    }
    *p = (tmuchar) code;
    if( tm_fneedc( f, '\'' ) ){
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
