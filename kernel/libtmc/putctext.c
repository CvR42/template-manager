/* File: $Id$ */

#include "tmc.h"
#include "config.h"

/* Given a tmtext datastructure 't' and a character 'c', add the character
 * to the tmtext.
 */
tmtext putc_tmtext( char c, tmtext t )
{
    if( t->curpos>=t->room ){
	t = setroom_tmtext( t, t->room+TEXTGROWSTEP );
    }
    t->arr[t->curpos++] = c;
    if( t->curpos>t->sz ){
	t->sz = t->curpos;
    }
    return t;
}
