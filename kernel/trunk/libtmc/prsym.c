/* File: $Id$ */

#include <ctype.h>
#include "tmc.h"

#define BACKSLASH '\\'

/* Implementation of 'print' for a 'tmsymbol'. */
void print_tmsymbol( TMPRINTSTATE *st, const_tmsymbol s )
{
    if( s == tmsymbolNIL ){
	tm_printword( st, "@" );
	return;
    }
    print_tmstring( st, s->name );
}
