/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

int compare( const double a, const double b )
{
     if( a>b ){
	 return 1;
     }
     if( a<b ){
	 return -1;
     }
     return 0;
}
