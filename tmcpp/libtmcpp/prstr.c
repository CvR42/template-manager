/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: prstr.c
 * C. van Reeuwijk
 */

#include "config.h"
#include "tmcpp.h"

// definition of 'print' for a 'tmstring'
void print_tmstring( TmPrintState *st, tmconststring s )
{
    tmstring buf;
    const char *sp;
    unsigned int ix = 0;

    if( s == tmstringNIL ){
	st->printWord( "@" );
	return;
    }
    unsigned int sz = strlen( s )+20;
    buf = create_tmstring( sz );
    sp = s;
    buf[ix++] = '"';
    while( *sp != '\0' ){
	unsigned int esz;
	const char *pp;
	unsigned int c;

	c = ((unsigned int) *sp++) & 0xff;
	pp = tm_escapestring( c );
	esz = strlen( pp );
	if( ix+esz+2>=sz ){
	    sz += TEXTGROWSTEP+2+esz;
	    buf = realloc_tmstring( buf, sz );
	}
	while( *pp != '\0' ){
	    buf[ix++] = *pp++;
	}
    }
    /* Since we've ensured that there is always room for these two
     * characters, we can blindly write into the buffer.
     */
    buf[ix++] = '"';
    buf[ix] = '\0';
    st->printWord( buf );
    fre_tmstring( buf );
}
