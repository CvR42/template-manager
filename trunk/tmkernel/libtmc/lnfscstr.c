/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: fscstr.c
 * 
 * Handle 'fscan_<type>' for type 'tmstring'.
 * Version for use with lognew.
 */

#include "config.h"
#include <ctype.h>
#include "tmc.h"

/* Try to read a tmstring in the buffer 'buf'. Give an error
   message if this is not successful. A tmstring may contain
   escape sequences with a '\', but no newlines. The '"'
   around the tmstring are stripped.
 */
int fscan_tmstring_lognew( FILE *f, tmstring *s, const char *file, const int line )
{
    int c;
    char buf[STRBUFSZ];
    char *bufp;
    int brac;

    *s = tmstringNIL;
    bufp = buf;
    brac = tm_fscanopenbrac( f );
    c = fgetc( f );
    if( c == '@' ){
	*s = tmstringNIL;
	return 0;
    }
    if( c != '"' ){
	(void) sprintf( tm_errmsg, "tmstring expected, but got ascii code 0x%02x", (c & 0xff) );
	return 1;
    }
    for(;;){
	c = fgetc( f );
	if( c == '\n' ){
	    (void) strcpy( tm_errmsg, "newline in tmstring" );
	    return 1;
	}
	if( c == '"' ){
	    break;
	}
	else {
	    ungetc( c, f );
	    if( tm_fscanescapedchar( f, &c ) ){
		return 1;
	    }
	    *bufp++ = c;
	}
    }
    *bufp = '\0';
    *s = new_tmstring_lognew( buf, file, line );
    return tm_fscanclosebrac( f, brac );
}
