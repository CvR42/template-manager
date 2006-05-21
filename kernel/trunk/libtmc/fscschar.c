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
	return 1;
    }
    if( tm_fscanescapedchar( f, &code ) ){
	return 1;
    }
    *p = (tmschar) code;
    if( tm_fneedc( f, '\'' ) ){
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
