/* File: $Id$
 *
 * Handling of open brackets around constructors
 * and lists.
 */

#include <ctype.h>
#include "config.h"
#include "tmc.h"

/* Skip all `isspace()' characters, and count the open brackets (`(')
 * that you encounter up to the first other character. Return the number
 * of open brackets found.
 */
int tm_fscanopenbrac( FILE *f )
{
    int braccnt = 0;
    int c;

    for(;;){
	if( tm_fscanspace( f ) ){
	    break;
	}
	c = getc( f );
	if( c != '(' ){
	    if( c != EOF ){
		ungetc( c, f );
	    }
	    break;
	}
	braccnt++;
    }
    return braccnt;
}
