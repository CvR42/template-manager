/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

static long newcnt_tmtext = 0;
static long frecnt_tmtext = 0;

#define STARTROOM 32

/* Create a new tmtext. */
tmtext new_tmtext_nolognew( void )
{
    tmtext t;

    newcnt_tmtext++;
    t = TM_MALLOC( tmtext, sizeof( *t ) );
    t->arr = TM_MALLOC( tmtextptr, sizeof( unsigned char )*STARTROOM );
    t->room = STARTROOM;
    t->curpos = 0;
    t->sz = 0;
    t->lognew_id = 0;
    return t;
}

/* Recursively free a tmtext 't'. */
void fre_tmtext_nolognew( tmtext t )
{
    if( t == tmtextNIL ){
	return;
    }
    TM_FREE( t->arr );
    TM_FREE( t );
    frecnt_tmtext++;
}

/* Print statistics of tmtext usage to file 'f'. */
void stat_tmtext( FILE *f )
{
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"tmtext",
	newcnt_tmtext,
	frecnt_tmtext,
	((newcnt_tmtext==frecnt_tmtext)? "": "<-")
    );
}

/* Return the balance of the text routines. */
int get_balance_tmtext( void )
{
    if( newcnt_tmtext<frecnt_tmtext ){
	return -1;
    }
    if( newcnt_tmtext>frecnt_tmtext ){
	return 1;
    }
    return 0;
}
