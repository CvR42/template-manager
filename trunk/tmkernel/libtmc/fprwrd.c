/* File: $Id$
 *
 * Tm - an interface code generator.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

/* Implementation of 'fprint' for a 'tmword', */
void fprint_tmword( FILE *f, const char *s )
{
    if( s == 0 ){
	fputs( "@", f );
	return;
    }
    fputs( s, f );
}
