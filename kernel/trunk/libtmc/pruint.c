/* File: $Id$ */

#include "tmc.h"
#include "config.h"

#define SZ (sizeof(tmuint)*8)
void print_tmuint( TMPRINTSTATE *st, const tmuint u )
{
    char buf[SZ];

    (void) snprintf( buf, SZ, "%u", u );
    tm_printword( st, buf );
}
