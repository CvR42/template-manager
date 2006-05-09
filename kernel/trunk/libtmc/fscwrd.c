/* File: $Id$
 * 
 * Handle 'fscan_<type>' for type 'tmword'.
 * Version for use without lognew.
 */

#include <ctype.h>
#include "config.h"
#include "tmc.h"

/* Try to read a tmword in the buffer 'buf'. Give an error
   message if this is not successful.
 */
int fscan_tmword_nolognew( FILE *f, tmword *s )
{
    int c;
    unsigned int brac;

    *s = tmwordNIL;
    brac = tm_fscanopenbrac( f );
    c = fgetc( f );
    if( c != '@' ){
	unsigned int sz = INITIAL_STRINGSIZE;
	tmstring buf = create_tmstring_nolognew( sz );
	unsigned int ix = 0;

	for(;;){
	    if( isspace( c ) || strchr( "(),|@[]", c ) != NULL ){
		if( ix == 0 ){
		    (void) sprintf(
			tm_errmsg,
			"tmword expected, but got ascii code 0x%02x",
			(c & 0xff)
		    );
		    fre_tmstring_nolognew( buf );
		    return 1;
		}
		ungetc( c, f );
		break;
	    }
	    if( ix+1>sz ){
		sz += sz+1;
		buf = realloc_tmstring_nolognew( buf, sz );
	    }
	    buf[ix++] = c;
	    c = fgetc( f );
	}
	buf[ix] = '\0';
	*s = buf;
    }
    return tm_fscanclosebrac( f, brac );
}
