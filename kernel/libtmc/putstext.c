/* File: $Id$ */

#include "tmc.h"
#include "config.h"

/* Given a tmtext datastructure 't' and a string 'str', add the string
 * to the tmtext.
 */
tmtext puts_tmtext( const char *str, tmtext t )
{
    size_t len;

    len = strlen( str );
    t = setroom_tmtext( t, t->curpos+len );
#if HAVE_MEMMOVE
    memcpy( t->arr+t->curpos, str, len );
    t->curpos += len;
#else
    {
	const char *s = str;
	tmtextptr d = t->arr+t->curpos;

	t->curpos += len;
	while( len>0 ){
	    *d++ = *s++;
	    len--;
	}
    }
#endif
    if( t->curpos>t->sz ){
	t->sz = t->curpos;
    }
    return t;
}

