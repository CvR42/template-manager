/* File: fscsym.c */

#include "config.h"
#include "tmcpp.h"

int fscan_tmsymbol( FILE *f, tmsymbol *s )
{
    tmstring symstr;

    if( fscan_tmstring( f, &symstr ) ){
	*s = add_tmsymbol( "<error>" );
	fre_tmstring( symstr );
	return 1;
    }
    if( symstr == tmstringNIL ){
	*s = tmsymbolNIL;
	return 0;
    }
    *s = add_tmsymbol( symstr );
    fre_tmstring( symstr );
    return 0;
}
