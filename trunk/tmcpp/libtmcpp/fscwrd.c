/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: fscwrd.c
 * 
 * Handle 'fscan_<type>' for type 'tmword'.
 */

#include <ctype.h>
#include "config.h"
#include "tmcpp.h"

/* Try to read a tmword in the buffer 'buf'. Give an error
   message if this is not successful.
 */
int fscan_tmword( FILE *f, tmword *s )
{
    int c;
    int brac;

    *s = tmwordNIL;
    brac = tm_fscanopenbrac( f );
    c = fgetc( f );
    if( c != '@' ){
	unsigned int sz = INITIAL_STRINGSIZE;
	tmstring buf = create_tmstring( sz );
	unsigned int ix = 0;

	for(;;){
	    if( isspace( c ) || strchr( "(),|@[]", c ) != NULL ){
		if( ix == 0 ){
		    (void) sprintf(
			tm_errmsg,
			"tmword expected, but got ascii code 0x%02x",
			(c & 0xff)
		    );
		    fre_tmstring( buf );
		    return 1;
		}
		ungetc( c, f );
		break;
	    }
	    if( ix+1>sz ){
		sz += sz+1;
		buf = realloc_tmstring( buf, sz );
	    }
	    buf[ix++] = c;
	    c = fgetc( f );
	}
	buf[ix] = '\0';
	*s = buf;
    }
    return tm_fscanclosebrac( f, brac );
}
