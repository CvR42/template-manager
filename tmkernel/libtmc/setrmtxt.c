/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

#include "config.h"
#include "tmc.h"

/* Given a tmtext 't', ensure that it has room for at least 'sz'
 * characters.
 */
tmtext setroom_tmtext( tmtext t, const long rm )
{
    if( rm>t->room ){
	t->arr = TM_REALLOC( tmtextptr, t->arr, rm );
	t->room = rm;
    }
    return t;
}
