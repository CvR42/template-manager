/* File: $Id$
 *
 * Scan a (possibly escaped) character from the given file.
 */

#include "config.h"
#include <ctype.h>
#include "tmc.h"

/* Try to read a (possibly escaped) character from the file 'f'. Give
 * an error message if this is not successful. 
 */
int tm_fscanescapedchar( FILE *f, int *code )
{
    int c;

    *code = 0;
    c = fgetc( f );
    if( c == EOF ){
	return 1;
    }
    if( c == '\\' ){
	c = fgetc( f );
	if( c == EOF ){
	    return 1;
	}
	switch( c ){
	    case 'b': c = '\b'; break;
	    case 'f': c = '\f'; break;
	    case 'n': c = '\n'; break;
	    case 'r': c = '\r'; break;
	    case 't': c = '\t'; break;
	    case 'v': c = '\v'; break;
	    default:
		if( isdigit( c ) ){
		    int val;

		    val = c-'0';
		    c = fgetc( f );
		    if( isdigit( c ) ){
			val = val*8 + (c-'0');
			c = fgetc( f );
			if( isdigit( c ) ){
			    val = val*8 + (c-'0');
			}
			else
			    ungetc( c, f );
		    }
		    else
			ungetc( c, f );
		    c = val;
		}
		break;
	}
    }
    *code = c;
    return 0;
}
