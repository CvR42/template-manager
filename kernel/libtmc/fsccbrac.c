/* File: $Id$
 *
 * Handling of close brackets around constructors and lists.
 */

#include <ctype.h>
#include "tmc.h"

#define CLOSEBRAC ')'

/* Skip all `isspace()' characters, and try to read `n' close
 * brackets. Give an error if this is not possible.
 */
tmbool tm_fscanclosebrac( FILE *f, unsigned int n )
{
    unsigned int cnt = n;

    while( cnt>0 ){
        if( tm_fneedc( f, CLOSEBRAC ) ){
	    return TMTRUE;
	}
	cnt--;
    }
    return TMFALSE;
}
