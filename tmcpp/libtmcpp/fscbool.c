/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: fscstr.c
 * 
 * Handle 'fscan_<type>' for type 'string'.
 */

#include <ctype.h>
#include "tmcpp.h"
#include "config.h"

#define WORDBUFSZ 20

int fscan_tmbool( FILE *f, tmbool *s )
{
    char buf[WORDBUFSZ];
    int braccnt;
    int err;

    braccnt = tm_fscanopenbrac( f );
    err = tm_fscancons( f, buf, WORDBUFSZ );
    if( err ){
	return err;
    }
    if( strcmp( buf, TMFALSESTR ) == 0 ){
	*s = TMFALSE;
    }
    else if( strcmp( buf, TMTRUESTR ) == 0 ){
	*s = TMTRUE;
    }
    else {
	(void) strcpy( tm_errmsg, "boolean expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, braccnt );
}

