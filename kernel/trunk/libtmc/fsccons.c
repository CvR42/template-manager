/* File: $Id$
 *
 * Reading of constructor names.
 */

#include <ctype.h>
#include "config.h"
#include "tmc.h"

/* Try to read a constructor name in buffer `buf'. The buffer is 'sz'
 * characters long.
 */
tmbool tm_fscancons( FILE *f, char *buf, const unsigned int sz )
{
    int c;
    char charstr[15];
    unsigned int n = 0;		/* Number of characters read. */

    char *p = buf;
    if( tm_fscanspace( f ) ){
        buf[0] = '\0';
	return TMTRUE;
    }
    c = fgetc( f );
    while( (isalnum( c ) || c == '_') && n<sz ){
	*p++ = (char) c;
	c = fgetc( f );
	n++;
    }
    if( isalnum( c ) || c == '_' ){
	buf[sz-1] = '\0';
	(void) sprintf(
	    tm_errmsg,
	    "Constructor name too long; all I got was `%s'",
	    buf
	);
	return TMTRUE;
    }
    (void) ungetc( c, f );
    *p = '\0';
    if( p == buf ){
	if( c == EOF ){
	    (void) sprintf( charstr, "EOF" );
	}
	else if( c>=' ' && c<='~' ){
	    (void) sprintf( charstr, "char '%c'", c );
	}
	else {
	    (void) sprintf( charstr, "char 0x%02x", (unsigned int) c );
	}
	(void) sprintf( tm_errmsg, "Expected constructor name but got %s", charstr );
	return TMTRUE;
    }
    return TMFALSE;
}
