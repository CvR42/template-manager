/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

/* Given a start and end position 'from' and 'to',
 * return a new tmtext that contains the text between these positions.
 */
tmtext *tmtext::slice( const size_type from_parm, const size_type to_parm ) const
{
    size_type from = from_parm;
    size_type to = to_parm;

    if( from<0 ){
	from = 0;
    }
    if( to>sz ){
	to = sz;
    }
    if( to<from ){
	return new tmtext( 0 );
    }
    size_type sl_sz = to-from;
    tmtext *nw = new tmtext( sl_sz );
    copyblock( nw->arr, arr+from, sl_sz );
    nw->sz = sl_sz;
    return nw;
}

