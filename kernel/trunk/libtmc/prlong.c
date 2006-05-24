/* File: $Id$ */
 
#include "tmc.h"
#include "config.h"

#define SZ (sizeof(long)*8)

void print_long( TMPRINTSTATE *st, const long u )
{
    char buf[SZ];

    (void) snprintf( buf, SZ, "%ld", u );
    tm_printword( st, buf );
}
