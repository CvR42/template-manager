/* File: $Id$
 * 
 * Handle 'fscan_<type>' for type 'tmtext'.
 */

#include <ctype.h>
#include "tmc.h"

/* Try to read a tmtext in the buffer 'buf'. Give an error
   message if this is not successful. A tmtext may contain
   escape sequences with a '\', but no newlines. The '"'
   around the tmtext are stripped.
 */
tmbool fscan_tmtext_nolognew( FILE *f, tmtext *s )
{
    int c;
    unsigned int brac;

    *s = tmtextNIL;
    brac = tm_fscanopenbrac( f );
    c = fgetc( f );
    if( c == '@' ){
	*s = tmtextNIL;
	return TMFALSE;
    }
    if( c != '"' ){
	(void) strcpy( tm_errmsg, "tmtext expected" );
	return TMTRUE;
    }
    *s = new_tmtext_nolognew();
    for(;;){
	c = fgetc( f );
	if( c == '\n' ){
	    (void) strcpy( tm_errmsg, "newline in tmtext" );
	    return TMTRUE;
	}
	if( c == '"' ){
	    break;
	}
	else {
	    (void) ungetc( c, f );
	    if( tm_fscanescapedchar( f, &c ) ){
		return TMTRUE;
	    }
	    *s = putc_tmtext( (char) c, *s );
	}
    }
    return tm_fscanclosebrac( f, brac );
}
