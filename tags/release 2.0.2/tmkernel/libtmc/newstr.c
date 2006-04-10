/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: newstr.c
   String manipulation routines.
 */

/* other standard UNIX functions */
#include <ctype.h>
#include "config.h"
#include "tmc.h"

static long newcnt_tmstring = 0;
static long frecnt_tmstring = 0;


/* Given a size 'sz', create an empty tmstring with that many characters
 * in it.
 */
tmstring create_tmstring_nolognew( const size_t sz )
{
    tmstring adr;
    size_t realsz = sz;

    if( realsz==0 ){
	realsz = 1;	/* Some mallocs/reallocs get upset over sz==0. */
    }
    adr = TM_MALLOC( char *, realsz*sizeof( char ) );
    adr[0] = '\0';
    newcnt_tmstring++;
    return adr;
}

/* Allocate space for tmstring 's' and copy the text into it. */
tmstring new_tmstring_nolognew( const char *s )
{
    size_t len;
    tmstring adr;

    if( s == NULL ){
	return NULL;
    }
    len = strlen( s ) + 1;
    adr = TM_MALLOC( char *, len*sizeof( char ) );
    strcpy( adr, s );
    newcnt_tmstring++;
    return adr;
}

/* De-allocate space for tmstring 's'. */
void fre_tmstring_nolognew( tmstring s )
{
    if( s==NULL ){
	return;
    }
    frecnt_tmstring++;
    TM_FREE( s );
}

/***********************************************************
 *   initalizing and statistics                            *
 ***********************************************************/

/* Give statistics */
void stat_tmstring( FILE *f )
{
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"tmstring",
	newcnt_tmstring,
	frecnt_tmstring,
	((newcnt_tmstring==frecnt_tmstring)? "": "<-")
    );
}

/* Return the balance of the string routines. */
int get_balance_tmstring( void )
{
    if( newcnt_tmstring<frecnt_tmstring ){
	return -1;
    }
    if( newcnt_tmstring>frecnt_tmstring ){
	return 1;
    }
    return 0;
}
