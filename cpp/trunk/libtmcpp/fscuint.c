/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

int fscan_uint( FILE *f, uint *p )
{
    int brac;

    *p = 0;
    brac = tm_fscanopenbrac( f );
    if( fscanf( f, "%u", p ) != 1 ){
	(void) strcpy( tm_errmsg, "unsigned int expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
