/* File: $Id$ */

#include "tmc.h"

/* Given a text 't', return a duplicate text. */
tmtext rdup_tmtext_nolognew( const_tmtext t )
{
    tmtext nw = new_tmtext_nolognew();

    nw = setroom_tmtext( nw, t->sz );
    copyblock_tmtext( nw->arr, t->arr, t->sz );
    nw->sz = t->sz;
    nw->curpos = t->curpos;
    return nw;
}
