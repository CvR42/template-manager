/* File: $Id$
 * 
 * Handle 'fscan_<type>' for type 'tmstring'.
 * Version for use with lognew.
 */

#include "config.h"
#include <ctype.h>
#include "tmc.h"

/* Try to read a tmstring in the buffer 'buf'. Give an error
 * message if this is not successful. A tmstring may contain
 * escape sequences with a '\', but no newlines. The '"'
 * around the tmstring are stripped.
 */
int fscan_tmstring_lognew( FILE *f, tmstring *s, const char *file, const int line )
{
    int c;
    unsigned int brac;
    unsigned int ix = 0;
    unsigned int sz = INITIAL_STRINGSIZE;
    tmstring buf;

    *s = tmstringNIL;
    brac = tm_fscanopenbrac( f );
    c = fgetc( f );
    if( c == '@' ){
	return 0;
    }
    if( c != '"' ){
	(void) sprintf( tm_errmsg, "tmstring expected, but got ascii code 0x%02x", (c & 0xff) );
	return 1;
    }
    buf = create_tmstring_lognew( sz, file, line );
    for(;;){
	c = fgetc( f );
	if( c == '\n' ){
	    (void) strcpy( tm_errmsg, "newline in tmstring" );
	    fre_tmstring_nolognew( buf );
	    return 1;
	}
	if( c == '"' ){
	    break;
	}
	ungetc( c, f );
	if( tm_fscanescapedchar( f, &c ) ){
	    return 1;
	}
	if( ix+1>sz ){
	    sz += sz+1;
	    buf = realloc_tmstring_lognew( buf, sz, file, line );
	}
	buf[ix++] = c;
    }
    buf[ix] = '\0';
    *s = buf;
    return tm_fscanclosebrac( f, brac );
}
