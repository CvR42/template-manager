/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

void print_int( TmPrintState *st, const int i )
{
    char buf[sizeof(int)*8];

    if( i<0 ){
	sprintf( buf, "(%d)", i );
    }
    else {
	sprintf( buf, "%d", i );
    }
    st->printWord( buf );
}
