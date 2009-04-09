/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"

/* Implementation of 'print' for a 'tmtext'. */
void fprint_tmtext( FILE *f, const_tmtext t )
{
    long ix;

    if( t == tmtextNIL ){
	(void) fputc( '@', f );
	return;
    }
    (void) fputc( '"', f );
    for( ix=0; ix<t->sz; ix++ ){
	(void) fputs( tm_escapestring( (int) t->arr[ix] ), f );
    }
    (void) fputc( '"', f );
}
