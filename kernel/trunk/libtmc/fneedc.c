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

#include "config.h"
#include <ctype.h>
#include "tmc.h"

#define SZ 15

/* Skip all `isspace()' characters, and try to character 'needc'.
   Compose an error message in 'tm_errmsg' and return 1 if this
   is not possible, else return 0.
 */
tmbool tm_fneedc( FILE *f, int needc )
{
    int c;
    char charstr[SZ];
    char needcharstr[SZ];

    if( tm_fscanspace( f ) ){
	return TMTRUE;
    }
    c = fgetc( f );
    if( c != needc ){
	if( c == EOF ){
	    (void) snprintf( charstr, SZ, "EOF" );
	}
	else if( c>=' ' && c<='~' ){
	    (void) snprintf( charstr, SZ, "char '%c'", c );
	}
	else {
	    (void) snprintf( charstr, SZ, "char 0x%02x", (unsigned int) c );
	}
	if( c>=' ' && c<='~' ){
	    (void) snprintf( needcharstr, SZ, "'%c'", needc );
	}
	else {
	    (void) snprintf( needcharstr, SZ, "0x%02x", (unsigned int) needc );
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
