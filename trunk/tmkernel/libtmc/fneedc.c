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

/* Skip all `isspace()' characters, and try to character 'needc'.
   Compose an error message in 'tm_errmsg' and return 1 if this
   is not possible, else return 0.
 */
int tm_fneedc( FILE *f, int needc )
{
    int c;
    char charstr[15];
    char needcharstr[15];

    if( tm_fscanspace( f ) ){
	return 1;
    }
    c = getc( f );
    if( c != needc ){
	if( c == EOF ){
	    (void) sprintf( charstr, "EOF" );
	}
	else if( c>=' ' && c<='~' ){
	    (void) sprintf( charstr, "char '%c'", c );
	}
	else {
	    (void) sprintf( charstr, "char 0x%02x", c );
	}
	if( c>=' ' && c<='~' ){
	    (void) sprintf( needcharstr, "'%c'", needc );
	}
	else {
	    (void) sprintf( needcharstr, "0x%02x", needc );
	}
	(void) sprintf(
	    tm_errmsg,
	    "Expected character %s but got %s",
	    needcharstr,
	    charstr
	);
	return 1;
    }
    return 0;
}
