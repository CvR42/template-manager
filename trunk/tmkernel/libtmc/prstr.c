/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: prstr.c
 * C. van Reeuwijk
 */

#include "config.h"
#include "tmc.h"

#define BACKSLASH '\\'

/* definition of 'print' for a 'tmstring' */
void print_tmstring( TMPRINTSTATE *st, const tmstring s )
{
    char buf[STRBUFSZ+10];
    char *bufp;
    char *bufend;
    unsigned int c;
    char *sp;
    const char *pp;

    if( s == tmstringNIL ){
	tm_printword( st, "@" );
	return;
    }
    sp = s;
    bufp = buf;
    bufend = &buf[STRBUFSZ];
    *bufp++ = '"';
    while( *sp != '\0' ){
	c = ((unsigned int) *sp++) & 0xff;
	pp = tm_escapestring( c );
	while( *pp != '\0' && bufp<bufend ){
	    *bufp++ = *pp++;
	}
	if( bufp>=bufend ){
	    tm_fatal( __FILE__, __LINE__, "tmstring too long" );
	}
    }
    *bufp++ = '"';
    *bufp = '\0';
    tm_printword( st, buf );
}
