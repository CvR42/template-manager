/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_double( FILE *f, const double d )
{
    if( d<0 ){
	fprintf( f, "(%.60g)", d );
    }
    else {
	fprintf( f, "%.60g", d );
    }
}
