/* File: $Id$
 *
 * Handling of close brackets around constructors and lists.
 */

#include <ctype.h>
#include "config.h"
#include "tmc.h"

/* line number counter */
int tm_lineno;

/* Skip all `isspace()' characters and Miranda style comment.
 * Note that since comment is introduced by '||' the pattern
 * '|[^|]' causes grave problems. It is 'solved' by generating
 * an error message and returning 1.
 */
int tm_fscanspace( FILE *f )
{
    int c;

    for(;;){
	c = fgetc( f );
	while( isspace( c ) ){
	    if( c == '\n' ){
		tm_lineno++;
	    }
	    c = fgetc( f );
	}
	if( c != '|' ){
	    (void) ungetc( c, f );
	    break;
	}
	c = fgetc( f );
	if( c != '|' ){
	    (void) sprintf( tm_errmsg, "fscanspace(): single '|' found" );
	    return 1;
	}
	do {
	    c = fgetc( f );
	} while( c != '\n' );
	tm_lineno++;
    }
    return 0;
}
