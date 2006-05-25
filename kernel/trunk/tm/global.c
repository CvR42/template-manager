/* File: $Id$
 *
 * Global variables.
 */

#include <time.h>
#include <stdio.h>

#include <tmc.h>

#include "tmdefs.h"
#include "tmcode.h"
#include "global.h"

FILE *tracestream;
FILE *statstream;

tmstring tplfilename = tmstringNIL;
tmstring dsfilename = tmstringNIL;
ds_list allds;
tmstring_list searchpath = tmstring_listNIL;

clock_t start_time;

tmbool fntracing = TMFALSE;
tmbool listing = TMFALSE;
tmbool maintr = TMFALSE;
tmbool prstat = TMFALSE;
tmbool sevaltr = TMFALSE;
tmbool vartr = TMFALSE;
tmbool noerrorline = TMFALSE;
