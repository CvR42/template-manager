/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: prsym.c
 * C. van Reeuwijk
 */

#include <ctype.h>
#include "tmcpp.h"
#include "config.h"

#define BACKSLASH '\\'

// definition of 'print' for a 'tmsymbol'.
void print_tmsymbol( TMPRINTSTATE *st, const tmsymbol s )
{
    if( s == tmsymbolNIL ){
	tm_printword( st, "@" );
	return;
    }
    print_tmstring( st, s->name );
}
