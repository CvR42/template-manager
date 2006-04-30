/* File: $Id$ */

#include "tmc.h"
#include "config.h"

void print_tmshort( TMPRINTSTATE *st, const tmshort i )
{
    char buf[sizeof(int)*8];

    if( i<0 ){
	sprintf( buf, "(%hd)", i );
    }
    else {
	sprintf( buf, "%hd", i );
    }
    tm_printword( st, buf );
}
