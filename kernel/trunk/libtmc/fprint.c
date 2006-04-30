/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_int( FILE *f, const int i )
{
    if( i<0 ){
	fprintf( f, "(%d)", i );
    }
    else {
	fprintf( f, "%d", i );
    }
}
