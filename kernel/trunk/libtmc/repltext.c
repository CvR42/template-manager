/* File: $Id$ */

#include <string.h>
#include "tmc.h"
#include "config.h"

/* Given a tmtext 't', a range 'from' to 'to' and a tmtext 'nw',
 * replace the tmtext in range 'from'..'to' in 't' with the
 * tmtext in 'nw'.
 */
tmtext replace_tmtext(
 tmtext t,
 long from_parm,
 long to_parm,
 const_tmtext nw
)
{
    long h;
    long oldsz;
    long inssz;
    long from = from_parm;
    long to = to_parm;

    if( to<from ){
	h = to;
	to = from;
	from = h;
    }
    if( from<0 ){
	from = 0;
    }
    if( to>t->sz ){
	to = t->sz;
    }
    oldsz = to-from;
    inssz = nw->sz-oldsz;
    if( inssz>0 ){
	insblock_tmtext( t, to, inssz );
    }
    else if( inssz<0 ){
	t = delblock_tmtext( t, to+inssz, to );
    }
    copyblock_tmtext( t->arr+from, nw->arr, nw->sz );
    return t;
}

