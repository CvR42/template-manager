/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: fsctext.c
 * 
 * Handle 'fscan_<type>' for type 'tmtext'.
 */

#include <ctype.h>
#include "config.h"
#include "tmcpp.h"

/* Try to read a tmtext in the buffer 'buf'. Give an error
   message if this is not successful. A tmtext may contain
   escape sequences with a '\', but no newlines. The '"'
   around the tmtext are stripped.
 */
int fscan_tmtext( FILE *f, tmtext **s )
{
    *s = tmtextNIL;
    int brac = tm_fscanopenbrac( f );
    int c = fgetc( f );
    if( c == '@' ){
	*s = tmtextNIL;
	return 0;
    }
    if( c != '"' ){
	(void) strcpy( tm_errmsg, "tmtext expected" );
	return 1;
    }
    *s = new tmtext();
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
	    putc_tmtext( (char) c, *s );
	}
    }
    return tm_fscanclosebrac( f, brac );
}
