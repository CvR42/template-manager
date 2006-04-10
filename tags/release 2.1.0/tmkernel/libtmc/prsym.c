/* File: $Id$ */

#include <ctype.h>
#include "tmc.h"
#include "config.h"

#define BACKSLASH '\\'

/* Implementation of 'print' for a 'tmsymbol'. */
void print_tmsymbol( TMPRINTSTATE *st, const tmsymbol s )
{
    if( s == tmsymbolNIL ){
	tm_printword( st, "@" );
	return;
    }
    print_tmstring( st, s->name );
}
