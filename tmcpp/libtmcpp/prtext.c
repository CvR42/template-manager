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
    tmtext *fmt = new tmtext();
    fmt->reserve( t->sz+2 );
    putc_tmtext( '"', fmt );
    for( long ix=0; ix<t->sz; ix++ ){
	unsigned int c = ((unsigned int) t->arr[ix]) & 0xff;
	puts_tmtext( tm_escapestring( c ), fmt );
    }
    putc_tmtext( '"', fmt );
    str_fmt = tmtext_to_tmstring( fmt );
    fmt->destroy();
    st->printWord( str_fmt );
    fre_tmstring( str_fmt );
}
