/* File: $Id$ */

#include "tmc.h"
#include "config.h"

/* Given a tmtext 't' and a start and end position 'from' and 'to',
 * return a new tmtext that contains the tmtext between these positions.
 */
tmtext slice_tmtext_lognew( const_tmtext t, long from_parm, long to_parm, const char *file, int line )
{
    tmtext nw;
    long sz;
    long from = from_parm;
    long to = to_parm;

    if( from<0 ){
	from = 0;
    }
    if( to>t->sz ){
	to = t->sz;
    }
    nw = new_tmtext_lognew( file, line );
    sz = to-from;
    if( sz>0 ){
	nw = setroom_tmtext( nw, sz );
	copyblock_tmtext( nw->arr, t->arr+from, sz );
	nw->sz = sz;
    }
    return nw;
}

