/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmcpp.h"
#include "config.h"

/* Given a tmtext 't' and a start and end position 'from' and 'to',
 * return a new tmtext that contains the tmtext between these positions.
 */
tmtext *slice_tmtext( const tmtext *t, const long from_parm, const long to_parm )
{
    long from = from_parm;
    long to = to_parm;

    if( from<0 ){
	from = 0;
    }
    if( to>t->sz ){
	to = t->sz;
    }
    long sz = to-from;
    tmtext *nw = new tmtext( sz );
    if( sz>0 ){
	copyblock_tmtext( nw->arr, t->arr+from, sz );
	nw->sz = sz;
    }
    return nw;
}

