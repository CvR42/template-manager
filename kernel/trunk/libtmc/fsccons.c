/* File: $Id$
 *
 * Reading of constructor names.
 */

#include <ctype.h>
#include "config.h"
#include "tmc.h"

#define SZ 15

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
	(void) snprintf(
	    tm_errmsg,
            TM_ERRLEN,
	    "Constructor name too long; all I got was `%s'",
	    buf
	);
	return TMTRUE;
    }
    (void) ungetc( c, f );
    *p = '\0';
    if( p == buf ){
	if( c == EOF ){
	    (void) snprintf( charstr, SZ, "EOF" );
	}
	else if( c>=' ' && c<='~' ){
	    (void) snprintf( charstr, SZ, "char '%c'", c );
	}
	else {
	    (void) snprintf( charstr, SZ, "char 0x%02x", (unsigned int) c );
	}
	(void) snprintf( tm_errmsg, TM_ERRLEN, "Expected constructor name but got %s", charstr );
	return TMTRUE;
    }
    return TMFALSE;
}
