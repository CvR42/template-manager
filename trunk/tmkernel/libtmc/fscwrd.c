/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: fscstr.c
 * 
 * Handle 'fscan_<type>' for type 'tmword'.
 * Version for use without lognew.
 */

#include <ctype.h>
#include "config.h"
#include "tmc.h"

/* Try to read a tmword in the buffer 'buf'. Give an error
   message if this is not successful. A tmword may contain
   escape sequences with a '\', but no newlines. The '"'
   around the tmword are stripped.
 */
int fscan_tmword_nolognew( FILE *f, tmword *s )
{
    int c;
    int brac;
    unsigned int ix = 0;
    unsigned int sz = 4;
    tmstring buf = create_tmstring_nolognew( sz );

    *s = tmwordNIL;
    brac = tm_fscanopenbrac( f );
    c = fgetc( f );
    if( c != '@' ){
	for(;;){
	    if( isspace( c ) || strchr( "(),@[]", c ) != NULL ){
		if( ix == 0 ){
		    (void) sprintf(
			tm_errmsg,
			"tmword expected, but got ascii code 0x%02x",
			(c & 0xff)
		    );
		    return 1;
		}
		ungetc( c, f );
		break;
	    }
	    if( ix+1>sz ){
		buf = realloc_tmstring_nolognew( buf, sz+sz );
	    }
	    buf[ix++] = c;
	    c = fgetc( f );
	}
    }
    buf[ix] = '\0';
    *s = buf;
    return tm_fscanclosebrac( f, brac );
}
