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
    if( s == tmstringNIL ){
	(void) fputc( '@', f );
	return;
    }
    (void) fputc( '"', f );
    while( *s != '\0' ){
	int c = (int) *s++;
	(void) fputs( tm_escapestring( c ), f );
    }
    (void) fputc( '"', f );
}
