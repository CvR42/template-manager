/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

/* Implementation of 'print' for a 'tmtext'. */
void fprint_tmtext( FILE *f, const tmtext t )
{
    long ix;

    if( t == tmtextNIL ){
	fputc( '@', f );
	return;
    }
    putc( '"', f );
    for( ix=0; ix<t->sz; ix++ ){
	fputs( tm_escapestring( t->arr[ix] ), f );
    }
    putc( '"', f );
}
