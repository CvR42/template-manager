/* File: $Id$ */

#include "tmc.h"
#include "config.h"

void print_int( TMPRINTSTATE *st, const int i )
{
    char buf[sizeof(int)*8];

    if( i<0 ){
	sprintf( buf, "(%d)", i );
    }
    else {
	sprintf( buf, "%d", i );
    }
    tm_printword( st, buf );
}
