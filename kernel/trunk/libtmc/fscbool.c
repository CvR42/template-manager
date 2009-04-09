/* File: $Id$
 *
 * Tm - an interface code generator.
 *
 * All rights reserved.
 */

#include <ctype.h>
#include "tmc.h"

#define WORDBUFSZ 20

/* Handle 'fscan_<type>' for type 'bool'.  */
tmbool fscan_tmbool( FILE *f, tmbool *s )
{
    char buf[WORDBUFSZ];
    unsigned int braccnt;
    tmbool err;

    braccnt = tm_fscanopenbrac( f );
    err = tm_fscancons( f, buf, WORDBUFSZ );
    if( err ){
        *s = TMFALSE;
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
        *s = TMFALSE;
	return TMTRUE;
    }
    return tm_fscanclosebrac( f, braccnt );
}

