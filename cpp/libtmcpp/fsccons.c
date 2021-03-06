/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: fsccons.c
 * Last modified: CvR
 *
 * Reading of constructor names.
 */

#include <ctype.h>
#include "config.h"
#include "tmcpp.h"

/* Try to read a constructor name in buffer `buf'. The buffer is 'sz'
 * characters long.
 */
int tm_fscancons( FILE *f, char *buf, const int sz )
{
    int c;
    char *p;
    char charstr[15];
    int n;		/* Number of characters read. */

    p = buf;
    if( tm_fscanspace( f ) ){
	return 1;
    }
    c = getc( f );
    n = 0;
    while( isalnum( c ) && n<sz ){
	*p++ = (char) c;
	c = getc( f );
	n++;
    }
    if( isalnum( c ) ){
	buf[sz-1] = '\0';
	(void) sprintf(
	    tm_errmsg,
	    "Constructor name too long; all I got was `%s'",
	    buf
	);
	return 1;
    }
    ungetc( c, f );
    *p = '\0';
    if( p == buf ){
	if( c == EOF ){
	    (void) sprintf( charstr, "EOF" );
	}
	else if( c>=' ' && c<='~' ){
	    (void) sprintf( charstr, "char '%c'", c );
	}
	else {
	    (void) sprintf( charstr, "char 0x%02x", c );
	}
	(void) sprintf( tm_errmsg, "Expected constructor name but got %s", charstr );
	return 1;
    }
    return 0;
}
