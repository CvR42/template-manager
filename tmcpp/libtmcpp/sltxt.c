/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmcpp.h"
#include "config.h"

/* Given a start and end position 'from' and 'to',
 * return a new tmtext that contains the text between these positions.
 */
tmtext *tmtext::slice( const long from_parm, const long to_parm ) const
{
    long from = from_parm;
    long to = to_parm;

    if( from<0 ){
	from = 0;
    }
    if( to>sz ){
	to = sz;
    }
    long sl_sz = to-from;
    tmtext *nw = new tmtext( sl_sz );
    if( sl_sz>0 ){
	copyblock( nw->arr, arr+from, sl_sz );
	nw->sz = sl_sz;
    }
    return nw;
}

