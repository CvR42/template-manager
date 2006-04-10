/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

/* Implementation of 'print' for a 'tmstring'. */
void fprint_tmstring( FILE *f, const_tmstring s )
{
    int c;

    if( s == tmstringNIL ){
	fputc( '@', f );
	return;
    }
    putc( '"', f );
    while( *s != '\0' ){
	c = *s++;
	fputs( tm_escapestring( c ), f );
    }
    putc( '"', f );
}
