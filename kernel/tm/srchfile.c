/* File: $Id$ */

#include <stdio.h>
#include <tmc.h>

#include "tmcode.h"
#include "srchfile.h"

/* Given a list of directories 'path', a file name 'fnm', a path separator
 * 'sep' and a file mode 'mode', see if a file with the name 'fnm' can be
 * opened, and if not, search the path for a directory with a file 'fnm' that
 * can be opened in mode 'mode'.
 *
 * If found, return a new tmstring with the name of the file, or return
 * tmstringNIL if not found.
 *
 * Notice that the straight filename is tried first. This is correct for
 * use in Tm, but may not be in general.
 */
tmstring search_file(
    const_tmstring_list path,
    const char *fnm,
    const char *sep,
    const char *mode
)
{
    tmstring ans;	/* The resulting tmstring. */
    unsigned int ix;
    FILE *f;
    size_t maxlen = 0;	/* The maximum length of the constructed path name. */

    f = fopen( fnm, mode );
    if( f!=NULL ){
	fclose( f );
	return new_tmstring( fnm );
    }
    for( ix=0; ix<path->sz; ix++ ){
        size_t len = strlen( path->arr[ix] );

	if( len>maxlen ){
	    maxlen = len;
	}
    }
    maxlen += strlen( sep );
    maxlen += strlen( fnm );
    maxlen++;
    ans = create_tmstring( maxlen );
    for( ix=0; ix<path->sz; ix++ ){
	(void) snprintf( ans, maxlen, "%s%s%s", path->arr[ix], sep, fnm );
	f = fopen( ans, mode );
	if( f!=NULL ){
	    fclose( f );
	    return ans;
	}
    }
    rfre_tmstring( ans );
    return tmstringNIL;
}
