/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include <string.h>
#include "tmcpp.h"
#include "config.h"

// Given a tmtext 't' and a tmtext 'nw', append 'nw'.
void tmtext::append( const tmtext *nw )
{
    reserve( sz+nw->sz );
    copyblock_tmtext( arr+sz, nw->arr, nw->sz );
    sz += nw->sz;
}

// Given a tmtext 't' and a string 's' append 's'.
void tmtext::append( const char *s )
{
    size_t s_sz = strlen( s );

    reserve( sz+s_sz );
    copyblock_tmtext( arr+sz, s, s_sz );
    sz += s_sz;
}
