/* File: $Id$ */

#include "tmc.h"

#define SZ (sizeof(int)*8)

void print_int( TMPRINTSTATE *st, const int i )
{
    char buf[SZ];

    if( i<0 ){
	(void) snprintf( buf, SZ, "(%d)", i );
    }
    else {
	(void) snprintf( buf, SZ, "%d", i );
    }
    tm_printword( st, buf );
}
