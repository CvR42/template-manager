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
 const long from_parm,
 const long to_parm,
 const tmtext *nw
)
{
    long from = from_parm;
    long to = to_parm;

    if( to<from ){
	long h = to;
	to = from;
	from = h;
    }
    if( from<0 ){
	from = 0;
    }
    if( to>sz ){
	to = sz;
    }
    long oldsz = to-from;
    long inssz = nw->sz-oldsz;
    if( inssz>0 ){
	insblock( to, inssz );
    }
    else if( inssz<0 ){
	erase( to+inssz, to );
    }
    copyblock( arr+from, nw->arr, nw->sz );
    return this;
}

// Given a range 'from' to 'to', a text 'nw', and a range 'nw_from' to
// 'nw_to', replace the text in range 'from'..'to' with the
// range 'nw_from' to 'nw_to' of 'nw'.
tmtext *tmtext::replace(
 const long from_parm,
 const long to_parm,
 const tmtext *nw,
 const long nw_from_parm,
 const long nw_to_parm
)
{
    long from = from_parm;
    long to = to_parm;
    long nw_from = nw_from_parm;
    long nw_to = nw_to_parm;

    if( to<from ){
	long h = to;
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
    long oldsz = to-from;
    long nw_sz = nw_to-nw_from;
    long inssz = nw_sz-oldsz;
    if( inssz>0 ){
	insblock( to, inssz );
    }
    else if( inssz<0 ){
	erase( to+inssz, to );
    }
    copyblock( arr+from, nw->arr+nw_from, nw_sz );
    return this;
}
