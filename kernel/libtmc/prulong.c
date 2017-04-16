/* File: $Id$ */

#include "tmc.h"

#define SZ (sizeof(tmulong)*8)

void print_tmulong( TMPRINTSTATE *st, const tmulong u )
{
    char buf[SZ];

    (void) snprintf( buf, SZ, "%lu", u );
    tm_printword( st, buf );
}
