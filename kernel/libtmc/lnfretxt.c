/* File: $Id$ */

#include "tmc.h"

/* Recursively free a tmtext 't'. */
void fre_tmtext_lognew( tmtext t )
{
    if( t != tmtextNIL ){
        tm_fre_logid( t->lognew_id );
    }
    fre_tmtext_nolognew( t );
}

