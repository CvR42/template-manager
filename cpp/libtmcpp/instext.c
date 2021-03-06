/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include <string.h>
#include "config.h"
#include "tmcpp.h"

/* Given a position 'pos' and a tmtext 'nw',
 * insert 'nw' at position 'pos'. If 'pos' falls beyond
 * the range of the text, it is assumed that the text must be
 * appended. If 'pos' is negative, it is assumed that the
 * text must be inserted at the start.
 */
tmtext *tmtext::insert( const size_type pos_parm, const tmtext *nw )
{
    size_type pos = pos_parm;

    if( pos>sz ){
	pos = sz;
    }
    insblock( pos, nw->sz );
    copyblock( arr+pos, nw->arr, nw->sz );
    return this;
}

/* Given a position 'pos' and a string 's',
 * insert 's' at position 'pos'. If 'pos' falls beyond
 * the range of the text, it is assumed that the text must be
 * appended. If 'pos' is negative, it is assumed that the
 * text must be inserted at the start.
 */
tmtext *tmtext::insert( const size_type pos_parm, const char *s )
{
    size_type pos = pos_parm;
    size_type s_sz = (size_type) strlen( s );

    if( pos<0 ){
	pos = 0;
    }
    if( pos>sz ){
	pos = sz;
    }
    insblock( pos, s_sz );
    copyblock( arr+pos, s, s_sz );
    return this;
}

/* Given a position 'pos' and a character 'c',
 * insert 'c' at position 'pos'. If 'pos' falls beyond
 * the range of the text, it is assumed that the char must be
 * appended. If 'pos' is negative, it is assumed that the
 * char must be inserted at the start.
 */
tmtext *tmtext::insert( const size_type pos_parm, const char c )
{
    size_type pos = pos_parm;

    if( pos<0 ){
	pos = 0;
    }
    if( pos>sz ){
	pos = sz;
    }
    insblock( pos, 1 );
    arr[pos] = c;
    return this;
}
