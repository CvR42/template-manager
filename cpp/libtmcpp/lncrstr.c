// file: lncrstr.c
// Tmstring creation with size. Version for use with lognew.

#include <ctype.h>
#include "config.h"
#include "tmcpp.h"

// Given a size 'sz', create an empty string with that many characters.
tmstring create_tmstring_lognew( const size_t sz, const char *file, const int line )
{
    tmstring adr = create_tmstring_nolognew( sz );
    tm_lognew( adr, file, line );
    return adr;
}
