/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: prstr.c
 * C. van Reeuwijk
 */

#include "config.h"
#include "tmcpp.h"

/* definition of 'print' for a 'tmtext' */
void print_tmtext( TmPrintState *st, const tmtext *t )
{
    tmstring str_fmt;

    if( t == tmtextNIL ){
	st->printWord( "@" );
	return;
    }
    tmtext *fmt = new tmtext( t->sz+2 );
    fmt->append( '"' );
    for( long ix=0; ix<t->sz; ix++ ){
	unsigned int c = ((unsigned int) t->arr[ix]) & 0xff;
	fmt->append( tm_escapestring( c ) );
    }
    fmt->append( '"' );
    str_fmt = tmtext_to_tmstring( fmt );
    fmt->destroy();
    st->printWord( str_fmt );
    fre_tmstring( str_fmt );
}
