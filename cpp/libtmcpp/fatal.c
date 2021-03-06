/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

void tm_fatal( const char *file, const int line, const char *s )
{
    if( file[0] == '\0' && line == 0 ){
	fprintf( stderr, "*** fatal error: %s\n", s );
    }
    else {
	fprintf( stderr, "%s(%d): *** fatal error: %s\n", file, line, s );
    }
    exit( 1 );
}
