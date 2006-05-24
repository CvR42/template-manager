/* File: $Id$ */

#include "tmc.h"
#include "config.h"

void print_tmuchar( TMPRINTSTATE *st, const tmuchar c )
{
    char buf[10];

    sprintf( buf, "'%s'", tm_escapestring( (int) c ) );
    tm_printword( st, buf );
}
