/* File: $Id$ */

#include "tmc.h"

#define SZ (sizeof(tmushort)*8)

void print_tmushort( TMPRINTSTATE *st, const tmushort i )
{
    char buf[SZ];

    (void) snprintf( buf, SZ, "%hu", i );
    tm_printword( st, buf );
}
