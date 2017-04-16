/* File: $Id$ */

#include "tmc.h"

#define SZ 10

void print_tmuchar( TMPRINTSTATE *st, const tmuchar c )
{
    char buf[SZ];

    (void) snprintf( buf, SZ, "'%s'", tm_escapestring( (int) c ) );
    tm_printword( st, buf );
}
