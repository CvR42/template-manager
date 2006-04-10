/* File: $Id$ */

#include "tmc.h"

/* Create a new tmtext. */
tmtext new_tmtext_lognew( const char *file, const int line )
{
    tmtext t = new_tmtext_nolognew();

    t->lognew_id = tm_new_logid( file, line );
    return t;
}

