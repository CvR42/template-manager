/* File: $Id$ */

#include "tmc.h"

/* Given a tmtext 't', a position 'pos' and a tmtext 'nw',
 * insert 'nw' at position 'pos' of 't'. If 'pos' falls beyond
 * the range of the text, it is assumed that the text must be
 * appended. If 'pos' is negative, it is assumed that the
 * text must be inserted at the start of 't'.
 */
tmtext insert_tmtext( tmtext t, long pos_parm, const_tmtext nw )
{
    long pos = pos_parm;

    if( pos<0 ){
	pos = 0;
    }
    if( pos>t->sz ){
	pos = t->sz;
    }
    t = insblock_tmtext( t, pos, nw->sz );
    copyblock_tmtext( t->arr+pos, nw->arr, nw->sz );
    return t;
}

