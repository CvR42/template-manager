/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: fprstr.c
 * C. van Reeuwijk
 */

#include "config.h"
#include "tmcpp.h"

/* definition of 'print' for a 'tmstring' */
void fprint_tmstring( FILE *f, tmconststring s )
{
    unsigned int c;

    if( s == tmstringNIL ){
	fputc( '@', f );
	return;
    }
    putc( '"', f );
    while( *s != '\0' ){
	c = (unsigned int) *s++;
	fputs( tm_escapestring( c ), f );
    }
    putc( '"', f );
}
