/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmcpp.h"

/* Given a tmtext datastructure 't' and a string 'str', add the string
 * to the tmtext.
 */
tmtext *puts_tmtext( const char *str, tmtext *t )
{
    tmtext::size_type len = (tmtext::size_type) strlen( str );
    t->reserve( t->curpos+len );
#if HAVE_MEMMOVE
    memcpy( t->arr+t->curpos, str, (unsigned int) len );
    t->curpos += len;
#else
    {
	const char *s = str;
	char *d = t->arr+t->curpos;

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

