/* File: $Id$ */

#include "config.h"
#include "tmc.h"

tmbool fscan_tmsymbol( FILE *f, tmsymbol *s )
{
    tmstring symstr;

    if( fscan_tmstring_nolognew( f, &symstr ) ){
	*s = add_tmsymbol( "<error>" );
	fre_tmstring_nolognew( symstr );
	return TMTRUE;
    }
    if( symstr == tmstringNIL ){
	*s = tmsymbolNIL;
	return TMFALSE;
    }
    *s = add_tmsymbol( symstr );
    fre_tmstring_nolognew( symstr );
    return TMFALSE;
}
