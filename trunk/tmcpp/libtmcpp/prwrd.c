/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: prwrd.c
 * C. van Reeuwijk
 */

#include "config.h"
#include "tmcpp.h"

/* definition of 'print' for a 'tmword' */
void print_tmword( TMPRINTSTATE *st, const tmconstword s )
{
    if( s == 0 ){
	tm_printword( st, "@" );
	return;
    }
    tm_printword( st, s );
}
