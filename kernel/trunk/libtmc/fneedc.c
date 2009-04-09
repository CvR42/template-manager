/* $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* Ensure that the next non-blank character in the input stream is the
 * required character. Else complain.
 */

#include <ctype.h>
#include "tmc.h"

#define BUFSZ 15

/* Skip all `isspace()' characters, and try to character 'needc'.
   Compose an error message in 'tm_errmsg' and return 1 if this
   is not possible, else return 0.
 */
tmbool tm_fneedc( FILE *f, int needc )
{
    int c;
    char charstr[BUFSZ];
    char needcharstr[BUFSZ];

    if( tm_fscanspace( f ) ){
	return TMTRUE;
    }
    c = fgetc( f );
    if( c != needc ){
	if( c == EOF ){
	    (void) snprintf( charstr, BUFSZ, "EOF" );
	}
	else if( c>=' ' && c<='~' ){
	    (void) snprintf( charstr, BUFSZ, "char '%c'", c );
	}
	else {
	    (void) snprintf( charstr, BUFSZ, "char 0x%02x", (unsigned int) c );
	}
	if( c>=' ' && c<='~' ){
	    (void) snprintf( needcharstr, BUFSZ, "'%c'", needc );
	}
	else {
	    (void) snprintf( needcharstr, BUFSZ, "0x%02x", (unsigned int) needc );
	}
	(void) snprintf(
	    tm_errmsg,
            TM_ERRLEN,
	    "Expected character %s but got %s",
	    needcharstr,
	    charstr
	);
	return TMTRUE;
    }
    return TMFALSE;
}
