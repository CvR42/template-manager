/* File: $Id$
 *
 * Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

/* Given a string and a tmtext, compare them. */
int cmp_string_tmtext( const char *s, const tmtext t )
{
    long ix;

    for( ix=0; ix<t->sz; ix++ ){
	if( *s == '\0' || ((unsigned char) *s)<((unsigned char) t->arr[ix]) ){
	    return -1;
	}
	if( ((unsigned char) *s)>((unsigned char) t->arr[ix]) ){
	    return 1;
	}
	s++;
    }
    if( *s != '\0' ){
	return 1;
    }
    return 0;
}
