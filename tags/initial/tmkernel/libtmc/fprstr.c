/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: fprstr.c
 * C. van Reeuwijk
 */

#include "config.h"
#include "tmc.h"

/* definition of 'print' for a 'tmstring' */
void fprint_tmstring( FILE *f, const tmstring s_parm )
{
    int c;
    tmstring s = s_parm;

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