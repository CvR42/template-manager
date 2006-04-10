/* file: error.c
 * Error handling.
 */

#include "config.h"
#include "tmdefs.h"
#include <tmc.h>
#include <string.h>
#include "tmcode.h"
#include "tmstring.h"
#include "global.h"
#include "error.h"

#if !HAVE_STRERROR
extern int sys_nerr;
extern const char *sys_errlist[];
#endif

char errpos[ERRARGLEN];
char errarg[ERRARGLEN];

static bool goterror;      /* true if a general error has occurred */

/******************************************************
 *            ERROR HANDLERS                          *
 ******************************************************/

/* Initialize error handling routines. */
void init_error( void )
{
   errarg[0] = '\0';
   errpos[0] = '\0';
   goterror = FALSE;
}

/* General error printing routine: print error message possibly preceded
   by string in 'errpos', and possibly followed by string in 'errarg'.
   Set flag 'goterror' to indicate an error has occurred. At the next call to
   errcheck() this flag will be checked, and the program will be stopped if
   it was set.
 */
static void printerror( const char *msg )
{
    if( errpos[0] != '\0' ) fprintf( stderr, "%s: ", errpos );
    fputs( msg, stderr );
    if( errarg[0] != '\0' ) fprintf( stderr, ": %s", errarg );
    fputs( "\n", stderr );
    errarg[0] = '\0';
    errpos[0] = '\0';
    goterror = TRUE;
}

/* Print error message 'msg'. */
void error( const char *msg )
{
    printerror( msg );
}

/* Print error message 'msg' and stop immediately. */
void fatal( const char *msg )
{
    printerror( msg );
    exit( 1 );
}

/* System error handler. */
void sys_error( int no )
{
#if HAVE_STRERROR
    printerror( strerror( no ) );
#else
    if( no>sys_nerr ){
	(void) sprintf( errarg, "%d", no );
	printerror( "unknown system error" );
    }
    else {
	printerror( sys_errlist[no] );
    }
#endif
}

/* Error handler that supplies line number and file name from the
   global variables 'tpllineno' and 'tplfilename'.
 */
void line_error( const char *msg )
{
    if( tplfilename == CHARNIL ){
	if( noerrorline ){
	    errpos[0] = '\0';
	}
	else {
	    (void) sprintf( errpos, "(%d)", tpllineno );
	}
    }
    else {
	if( noerrorline ){
	    (void) sprintf( errpos, "%s", tplfilename );
	}
	else {
	    (void) sprintf( errpos, "%s(%d)", tplfilename, tpllineno );
	}
    }
    error( msg );
}

/* Internal error handler. Print the given message 'msg'
   with given position in the source: file name and line number.
 */
void docrash( const char *file, int line, const char *msg )
{
   (void) sprintf( errpos, "internal error at %s(%d)", file, line );
   error( msg );
}

/* Check if 'goterror' flag is set, and do exit(1) if it is. */
void errcheck( void )
{
   if( !goterror ) return;
   error( "errors detected, program aborted" );
   exit( 1 );
}
