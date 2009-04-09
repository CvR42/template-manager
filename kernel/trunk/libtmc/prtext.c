/* File: $Id$ */

#include "tmc.h"

/* definition of 'print' for a 'tmtext' */
void print_tmtext( TMPRINTSTATE *st, const_tmtext t )
{
    tmtext fmt;
    tmstring str_fmt;
    long ix;

    if( t == tmtextNIL ){
	tm_printword( st, "@" );
	return;
    }
    fmt = new_tmtext_nolognew();
    fmt = setroom_tmtext( fmt, t->sz+2 );
    fmt = putc_tmtext( '"', fmt );
    for( ix=0; ix<t->sz; ix++ ){
        int c = ((int) t->arr[ix]) & 0xff;

	fmt = puts_tmtext( tm_escapestring( c ), fmt );
    }
    fmt = putc_tmtext( '"', fmt );
    str_fmt = tmtext_to_tmstring_nolognew( fmt );
    fre_tmtext_nolognew( fmt );
    tm_printword( st, str_fmt );
    fre_tmstring_nolognew( str_fmt );
}
