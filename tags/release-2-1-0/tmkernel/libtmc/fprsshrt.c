/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_tmshort( FILE *f, const tmshort i )
{
    if( i<0 ){
	fprintf( f, "(%hd)", i );
    }
    else {
	fprintf( f, "%hd", i );
    }
}
