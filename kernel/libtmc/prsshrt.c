/* File: $Id$ */

#include "tmc.h"

#define SZ (sizeof(int)*8)

void print_tmshort( TMPRINTSTATE *st, const tmshort i )
{
    char buf[SZ];

    if( i<0 ){
	(void) snprintf( buf, SZ, "(%hd)", i );
    }
    else {
	(void) snprintf( buf, SZ, "%hd", i );
    }
    tm_printword( st, buf );
}
