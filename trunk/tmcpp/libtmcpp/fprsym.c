/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: fprsym.c
 * C. van Reeuwijk
 */

#include "config.h"
#include <ctype.h>
#include "tmcpp.h"

/* definition of 'print' for a 'tmsymbol' */
void fprint_tmsymbol( FILE *f, const tmsymbol s )
{
    if( s == tmsymbolNIL ){
	fputs( "@", f );
	return;
    }
    fprint_tmstring( f, s->name );
}
