/* File: $Id$ */
 
#include "tmc.h"
#include "config.h"

void print_long( TMPRINTSTATE *st, const long u )
{
    char buf[sizeof(long)*8];

    sprintf( buf, "%ld", u );
    tm_printword( st, buf );
}
