/* File: fscbool.c
 * 
 * Handle 'fscan_<type>' for type 'bool'.
 */

#include <ctype.h>
#include "config.h"
#include "tmcpp.h"

#define WORDBUFSZ 20

int fscan_bool( FILE *f, bool *s )
{
    char buf[WORDBUFSZ];

    int braccnt = tm_fscanopenbrac( f );
    int err = tm_fscancons( f, buf, WORDBUFSZ );
    if( err ){
	return err;
    }
    if( strcmp( buf, "false" ) == 0 ){
	*s = false;
    }
    else if( strcmp( buf, "true" ) == 0 ){
	*s = true;
    }
    else {
	(void) strcpy( tm_errmsg, "bool expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, braccnt );
}

