/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include <string.h>
#include "config.h"
#include "tmcpp.h"

// Given a range 'from' to 'to' and a tmtext 'nw',
// replace the text in range 'from'..'to' in 't' with the
// text in 'nw'.
tmtext *tmtext::replace(
 const size_type from_parm,
 const size_type to_parm,
 const tmtext *nw
)
{
    size_type from = from_parm;
    size_type to = to_parm;

    if( to<from ){
	size_type h = to;
	to = from;
	from = h;
    }
    if( from<0 ){
	from = 0;
    }
    if( to>sz ){
	to = sz;
    }
    size_type oldsz = to-from;
    if( nw->sz>oldsz ){
	insblock( to, nw->sz-oldsz );
    }
    else if( nw->sz<oldsz ){
	erase( to+nw->sz-oldsz, to );
    }
    copyblock( arr+from, nw->arr, nw->sz );
    return this;
}

// Given a range 'from' to 'to', a text 'nw', and a range 'nw_from' to
// 'nw_to', replace the text in range 'from'..'to' with the
// range 'nw_from' to 'nw_to' of 'nw'.
tmtext *tmtext::replace(
 const size_type from_parm,
 const size_type to_parm,
 const tmtext *nw,
 const size_type nw_from_parm,
 const size_type nw_to_parm
)
{
    size_type from = from_parm;
    size_type to = to_parm;
    size_type nw_from = nw_from_parm;
    size_type nw_to = nw_to_parm;

    if( to<from ){
	size_type h = to;
	to = from;
	from = h;
    }
    if( from<0 ){
	from = 0;
    }
    if( to>sz ){
	to = sz;
    }
    if( nw_from<0 ){
	nw_from = 0;
    }
    if( nw_to>nw->sz ){
	nw_to = nw->sz;
    }
    if( nw_from>nw_to ){
	nw_from = nw_to;
    }
    size_type oldsz = to-from;
    size_type nw_sz = nw_to-nw_from;
    size_type inssz = nw_sz-oldsz;
    if( inssz>0 ){
	insblock( to, inssz );
    }
    else if( inssz<0 ){
	erase( to+inssz, to );
    }
    copyblock( arr+from, nw->arr+nw_from, nw_sz );
    return this;
}
