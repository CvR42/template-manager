/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: fprwrd.c
 * C. van Reeuwijk
 */

#include "config.h"
#include "tmcpp.h"

/* definition of 'fprint' for a 'tmword' */
void fprint_tmword( FILE *f, const tmconstword s )
{
    if( s == 0 ){
	fputs( "@", f );
	return;
    }
    fputs( s, f );
}
