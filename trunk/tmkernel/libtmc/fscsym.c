/* File: $Id$ */

#include "config.h"
#include "tmc.h"

int fscan_tmsymbol( FILE *f, tmsymbol *s )
{
    tmstring symstr;

    if( fscan_tmstring_nolognew( f, &symstr ) ){
	*s = add_tmsymbol( "<error>" );
	fre_tmstring_nolognew( symstr );
	return 1;
    }
    if( symstr == tmstringNIL ){
	*s = tmsymbolNIL;
	return 0;
    }
    *s = add_tmsymbol( symstr );
    fre_tmstring_nolognew( symstr );
    return 0;
}
