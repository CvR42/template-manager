/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: escstr.c
 * Last modified: CvR
 *
 * Convert a character to an escape sequence suitable for use in a string.
 */

/* The header of this library */
#include "config.h"
#include "tmcpp.h"

#define BACKSLASH '\\'

static char escchar_buf[6];

/* Given an unsigned int 'code' representing the ASCII code of a character, 
 * return a pointer to a string representing this character in an
 * escape sequence (or an ordinary character, if that is possible).
 * The returned pointer points to a static buffer that is overwritten
 * upon the next invocation of the function.
 */
const char *tm_escapestring( const unsigned int code )
{
    char *p = escchar_buf;
    const unsigned int code1 = code & 0xff;

    if( code1 == BACKSLASH || code1 == '"' || code1 == '\'' ){
	*p++ = BACKSLASH;
	*p++ = code1;
    }
    else if( code1>=' ' && code1<='~' ){
	*p++ = code1;
    }
    else {
	switch( code1 ){
	    case '\b': *p++ = BACKSLASH; *p++ = 'b'; break;
	    case '\f': *p++ = BACKSLASH; *p++ = 'f'; break;
	    case '\n': *p++ = BACKSLASH; *p++ = 'n'; break;
	    case '\r': *p++ = BACKSLASH; *p++ = 'r'; break;
	    case '\t': *p++ = BACKSLASH; *p++ = 't'; break;
	    case '\v': *p++ = BACKSLASH; *p++ = 'v'; break;
	    default:
		sprintf( escchar_buf, "\\%03o", code1 );
		return &escchar_buf[0];
	}
    }
    *p = '\0';
    return &escchar_buf[0];
}
