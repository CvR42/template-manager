/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmcpp.h"
#include "config.h"

#ifndef DIGITS
#define DIGITS 60
#endif

void print_double( TMPRINTSTATE *st, const double d )
{
    char buf[2*DIGITS+15];

    if( d<0 ){
	sprintf( buf, "(%.60g)", d );
    }
    else {
	sprintf( buf, "%.60g", d );
    }
    tm_printword( st, buf );
}
