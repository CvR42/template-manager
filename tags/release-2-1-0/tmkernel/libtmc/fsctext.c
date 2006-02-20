/* File: $Id$
 * 
 * Handle 'fscan_<type>' for type 'tmtext'.
 */

#include <ctype.h>
#include "config.h"
#include "tmc.h"

/* Try to read a tmtext in the buffer 'buf'. Give an error
   message if this is not successful. A tmtext may contain
   escape sequences with a '\', but no newlines. The '"'
   around the tmtext are stripped.
 */
int fscan_tmtext_nolognew( FILE *f, tmtext *s )
{
    int c;
    int brac;

    *s = tmtextNIL;
    brac = tm_fscanopenbrac( f );
    c = fgetc( f );
    if( c == '@' ){
	*s = tmtextNIL;
	return 0;
    }
    if( c != '"' ){
	(void) strcpy( tm_errmsg, "tmtext expected" );
	return 1;
    }
    *s = new_tmtext_nolognew();
    for(;;){
	c = fgetc( f );
	if( c == '\n' ){
	    (void) strcpy( tm_errmsg, "newline in tmtext" );
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
	    putc_tmtext( c, *s );
	}
    }
    return tm_fscanclosebrac( f, brac );
}