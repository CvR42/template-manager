/* File: $Id$ */

#include "tmc.h"
#include "config.h"

#define SZ 10

void print_tmschar( TMPRINTSTATE *st, tmschar c )
{
    char buf[SZ];

    (void) snprintf( buf, SZ, "'%s'", tm_escapestring( (int) c ) );
    tm_printword( st, buf );
}
