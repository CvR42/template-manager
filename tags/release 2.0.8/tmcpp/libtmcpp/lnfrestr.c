// file: lnfrestr.c
// fre_tmstring() version that is used when LOGNEW is activated.

#include "config.h"
#include "tmcpp.h"

// de-allocate space for tmstring 's', and report it to lognew.
void fre_tmstring_lognew( tmstring s )
{
    if( s==NULL ){
	return;
    }
    tm_logfre( s );
    fre_tmstring_nolognew( s );
}
