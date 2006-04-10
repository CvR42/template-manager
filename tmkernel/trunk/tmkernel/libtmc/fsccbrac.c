/* File: $Id$
 *
 * Handling of close brackets around constructors and lists.
 */

#include <ctype.h>
#include "tmc.h"
#include "config.h"

#define CLOSEBRAC ')'

/* Skip all `isspace()' characters, and try to read `n' close
 * brackets. Give an error if this is not possible.
 */
int tm_fscanclosebrac( FILE *f, const int n )
{
    int cnt = n;

    while( cnt>0 ){
        if( tm_fneedc( f, CLOSEBRAC ) ){
	    return 1;
	}
	cnt--;
    }
    return 0;
}
