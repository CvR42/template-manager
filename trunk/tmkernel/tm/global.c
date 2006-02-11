/* File: $Id$
 *
 * Global variables.
 */

#include "config.h"

#include <time.h>
#include <stdio.h>

#include <tmc.h>

#include "tmdefs.h"
#include "tmcode.h"
#include "tmstring.h"
#include "global.h"

FILE *tracestream = 0;
FILE *statstream = 0;

tmstring tplfilename = tmstringNIL;
tmstring dsfilename = tmstringNIL;
ds_list allds;
tmstring_list searchpath = tmstring_listNIL;

clock_t start_time;

tmbool fntracing = FALSE;
tmbool listing = FALSE;
tmbool maintr = FALSE;
tmbool prstat = FALSE;
tmbool sevaltr = FALSE;
tmbool vartr = FALSE;
tmbool noerrorline = FALSE;
