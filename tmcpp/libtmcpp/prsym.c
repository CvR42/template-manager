// File: prsym.c
// C. van Reeuwijk

#include <ctype.h>
#include "config.h"
#include "tmcpp.h"

#define BACKSLASH '\\'

// definition of 'print' for a 'tmsymbol'.
void print_tmsymbol( TmPrintState *st, const tmsymbol s )
{
    if( s == tmsymbolNIL ){
	st->printWord( "@" );
	return;
    }
    print_tmstring( st, s->name );
}
