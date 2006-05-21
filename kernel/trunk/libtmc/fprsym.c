/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include <ctype.h>
#include "tmc.h"

/* Implementation of 'print' for a 'tmsymbol'. */
void fprint_tmsymbol( FILE *f, const tmsymbol s )
{
    if( s == tmsymbolNIL ){
	(void) fputs( "@", f );
	return;
    }
    fprint_tmstring( f, s->name );
}
