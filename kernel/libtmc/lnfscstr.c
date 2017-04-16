/* File: $Id$
 * 
 * Handle 'fscan_<type>' for type 'tmstring'.
 * Version for use with lognew.
 */

#include <ctype.h>
#include "tmc.h"
#include "config.h"

/* Try to read a tmstring in the buffer 'buf'. Give an error
 * message if this is not successful. A tmstring may contain
 * escape sequences with a '\', but no newlines. The '"'
 * around the tmstring are stripped.
 */
tmbool fscan_tmstring_lognew( FILE *f, tmstring *s, const char *file, const int line )
{
    int c;
    unsigned int brac;
    size_t ix = 0;
    size_t sz = INITIAL_STRINGSIZE;
    tmstring buf;

    *s = tmstringNIL;
    brac = tm_fscanopenbrac( f );
    c = fgetc( f );
    if( c == '@' ){
	return TMFALSE;
    }
    if( c != '"' ){
	(void) snprintf( tm_errmsg, TM_ERRLEN, "tmstring expected, but got ascii code 0x%02x", (c & 0xffU) );
	return TMTRUE;
    }
    buf = create_tmstring_lognew( sz, file, line );
    for(;;){
	c = fgetc( f );
	if( c == '\n' ){
	    (void) snprintf( tm_errmsg, TM_ERRLEN, "newline in tmstring" );
	    fre_tmstring_nolognew( buf );
	    return TMTRUE;
	}
	if( c == '"' ){
	    break;
	}
	(void) ungetc( c, f );
	if( tm_fscanescapedchar( f, &c ) ){
	    fre_tmstring_nolognew( buf );
	    return TMTRUE;
	}
	if( ix+1>sz ){
	    sz += sz+1;
	    buf = realloc_tmstring_lognew( buf, sz, file, line );
	}
	buf[ix++] = (char) c;
    }
    buf[ix] = '\0';
    *s = buf;
    return tm_fscanclosebrac( f, brac );
}
