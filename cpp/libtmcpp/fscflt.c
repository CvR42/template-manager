/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

int fscan_float( FILE *f, float *p )
{
    int brac;

    *p = (float) 0;
    brac = tm_fscanopenbrac( f );
    if( fscanf( f, "%f", p ) != 1 ){
	(void) strcpy( tm_errmsg, "float expected" );
	return 1;
    }
    return tm_fscanclosebrac( f, brac );
}
