/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

#ifndef DIGITS
#define DIGITS 60
#endif

void print_double( TmPrintState *st, const double d )
{
    char buf[2*DIGITS+15];

    if( d<0 ){
	sprintf( buf, "(%.60g)", d );
    }
    else {
	sprintf( buf, "%.60g", d );
    }
    st->printWord( buf );
}
