/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

int cmp_double( const double a, const double b )
{
     if( a>b ){
	 return 1;
     }
     if( a<b ){
	 return -1;
     }
     return 0;
}
