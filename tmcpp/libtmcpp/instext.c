/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include <string.h>
#include "tmcpp.h"
#include "config.h"

/* Given a tmtext 't', a position 'pos' and a tmtext 'nw',
 * insert 'nw' at position 'pos' of 't'. If 'pos' falls beyond
 * the range of the text, it is assumed that the text must be
 * appended. If 'pos' is negative, it is assumed that the
 * text must be inserted at the start of 't'.
 */
void tmtext::insert( const long pos_parm, const tmtext *nw )
{
    long pos = pos_parm;

    if( pos<0 ){
	pos = 0;
    }
    if( pos>sz ){
	pos = sz;
    }
    insblock_tmtext( this, pos, nw->sz );
    copyblock_tmtext( arr+pos, nw->arr, nw->sz );
}
