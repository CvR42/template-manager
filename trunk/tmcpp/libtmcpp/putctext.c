/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "tmcpp.h"
#include "config.h"

/* Given a tmtext datastructure 't' and a character 'c', add the character
 * to the tmtext.
 */
tmtext *putc_tmtext( const char c, tmtext *t )
{
    if( t->curpos>=t->capacity() ){
	t->reserve( t->capacity()+TEXTGROWSTEP );
    }
    t->arr[t->curpos++] = c;
    if( t->curpos>t->size() ){
	t->sz = t->curpos;
    }
    return t;
}
