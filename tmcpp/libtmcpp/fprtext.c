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

/* Definition of 'fprint' for a 'tmtext'. */
void fprint_tmtext( FILE *f, const tmtext *t )
{
    if( t == tmtextNIL ){
	fputc( '@', f );
	return;
    }
    putc( '"', f );
    for( long ix=0; ix<t->sz; ix++ ){
	fputs( tm_escapestring( t->arr[ix] ), f );
    }
    putc( '"', f );
}
