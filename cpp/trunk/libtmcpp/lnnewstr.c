/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

// file: lnnewstr.c
// new_tmstring() version that is used when LOGNEW is activated.

#include "config.h"
#include "tmcpp.h"

// Allocate space for tmstring 's', copy the text into it, and report
// this to lognew.
tmstring new_tmstring_lognew( const char *s, const char *file, const int line )
{
    tmstring adr = new_tmstring_nolognew( s );
    tm_lognew( adr, file, line );
    return adr;
}
