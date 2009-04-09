/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* Convert a character to an escape sequence suitable for use in a string.  */

#include "tmc.h"

#define BACKSLASH '\\'

#define ESCCHAR_BUF_SZ 6
static char escchar_buf[ESCCHAR_BUF_SZ];

/* Given an unsigned int 'code' representing the ASCII code of a character, 
 * return a pointer to a string representing this character in an
 * escape sequence (or an ordinary character, if that is possible).
 * The returned pointer points to a static buffer that is overwritten
 * upon the next invocation of the function.
 */
const char *tm_escapestring( const int code )
{
    char *p = escchar_buf;
    char code1 = (char) (code & 0xffU);

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
		(void) snprintf( escchar_buf, ESCCHAR_BUF_SZ, "\\%03o", (code & 0xffU) );
		return escchar_buf;
	}
    }
    *p = '\0';
    return escchar_buf;
}
