/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

void fprint_sshrt( FILE *f, const sshrt i )
{
    if( i<0 ){
	fprintf( f, "(%hd)", i );
    }
    else {
	fprintf( f, "%hd", i );
    }
}
