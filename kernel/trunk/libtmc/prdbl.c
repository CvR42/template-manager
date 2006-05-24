/* File: $Id$ */

#include "tmc.h"
#include "config.h"

#ifndef DIGITS
#define DIGITS 60
#endif

#define SZ (2*DIGITS+15)

void print_double( TMPRINTSTATE *st, const double d )
{
    char buf[SZ];

    if( d<0 ){
	snprintf( buf, SZ, "(%.60g)", d );
    }
    else {
	snprintf( buf, SZ, "%.60g", d );
    }
    tm_printword( st, buf );
}
