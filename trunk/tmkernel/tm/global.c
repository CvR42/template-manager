/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: global.c
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

FILE *tracestream = stderr;
FILE *statstream = stderr;

char *tplfilename = CHARNIL;
int tpllineno = 0;
tmstring dsfilename = tmstringNIL;
FILE *dsfile = stdin;
int dslineno = 0;
ds_list allds;
tmstring_list searchpath = tmstring_listNIL;

time_t start_time;

int fntr = FALSE;
int listing = FALSE;
int maintr = FALSE;
int prstat = FALSE;
int sevaltr = FALSE;
int vartr = FALSE;
int lextr = FALSE;
int noerrorline = FALSE;
