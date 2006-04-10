/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

int fscan_sshrt( FILE *f, sshrt *p )
{
    int brac;

    *p = 0;
    brac = tm_fscanopenbrac( f );
    if( fscanf( f, "%hd", p ) != 1 ){
	(void) strcpy( tm_errmsg, "short int expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
