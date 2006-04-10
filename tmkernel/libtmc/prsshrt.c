/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"
#include "config.h"

void print_sshrt( TMPRINTSTATE *st, const sshrt i )
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
