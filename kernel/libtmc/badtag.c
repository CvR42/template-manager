/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"

void tm_badtag( const char *file, const int line, const int tag ) 
{
    fprintf( stderr, "%s(%d): bad tag: %d=0x%x\n", file, line, tag, (unsigned int) tag );
    exit( EXIT_FAILURE );
}
