/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmc.h"
#include "config.h"

/* Given a text 't', return a duplicate text. */
tmtext rdup_tmtext_lognew( const tmtext t, const char *file, const int line )
{
    tmtext nw;

    nw = new_tmtext_lognew( file, line );
    nw = setroom_tmtext( nw, t->sz );
    copyblock_tmtext( nw->arr, t->arr, t->sz );
    nw->sz = t->sz;
    nw->curpos = t->curpos;
    return nw;
}
