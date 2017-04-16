/* File: $Id$
 *
 * Tm - an interface code generator.
 *
 * All rights reserved.
 */

#include "tmc.h"

/* Implementation of 'fprint' for a 'tmword', */
void fprint_tmword( FILE *f, const char *s )
{
    if( s == 0 ){
	(void) fputs( "@", f );
	return;
    }
    (void) fputs( s, f );
}
