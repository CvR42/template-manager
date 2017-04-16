/* File: $Id$ */

#include "tmc.h"

/* Implementation of 'print' for a 'tmword' */
void print_tmword( TMPRINTSTATE *st, const const_tmword s )
{
    if( s == 0 ){
	tm_printword( st, "@" );
	return;
    }
    tm_printword( st, s );
}
