/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include <string.h>
#include "config.h"
#include "tmcpp.h"

// Given a text 'nw', append 'nw'.
tmtext *tmtext::append( const tmtext *nw )
{
    reserve( sz+nw->sz );
    copyblock( arr+sz, nw->arr, nw->sz );
    sz += nw->sz;
    return this;
}

// Given a string 's', append 's'.
tmtext *tmtext::append( const char *s )
{
    size_t s_sz = strlen( s );

    reserve( sz+s_sz );
    copyblock( arr+sz, s, s_sz );
    sz += s_sz;
    return this;
}

// Given a tmtext 't' and a character 'c' append 'c'.
tmtext *tmtext::append( const char c )
{
    reserve( sz+1 );
    arr[sz] = c;
    sz++;
    return this;
}
