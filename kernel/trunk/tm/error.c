/* File: $Id$
 *
 * Error handling.
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include <tmc.h>

#include "tmdefs.h"
#include "config.h"
#include "tmcode.h"
#include "error.h"
#include "global.h"

#define ERRARGLEN 256

static char errpos[ERRARGLEN] = "";

static tmbool goterr = FALSE;

/* Given an origin filename and line number, fill 'errpos' with that
 * origin info.
 */
static void fileline_errpos( const char *fnm, unsigned int lineno )
{
    if( noerrorline ){
        (void) snprintf( errpos, ERRARGLEN, "%s", fnm );
    }
    else {
        (void) snprintf( errpos, ERRARGLEN, "%s:%u", fnm, lineno );
    }
}

/* Given an origin 'org', fill 'errpos' with the origin info from 'org'. */
static void orig_errpos( const_origin org )
{
    if( org != originNIL ){
        fileline_errpos( org->file->name, org->line );
    }
}

/* Given an origsymbol 'org', fill 'errpos' with the origin and symbol info from 'org'. */
static void origsymbol_errpos( const_origsymbol s )
{
    const_origin org;

    if( s == origsymbolNIL ){
        return;
    }
    org = s->org;
    if( org == originNIL ){
        (void) snprintf( errpos, ERRARGLEN, "%s", s->sym->name );
    }
    else {
        if( noerrorline ){
            (void) snprintf( errpos, ERRARGLEN, "%s: %s", org->file->name, s->sym->name );
        }
        else {
            (void) snprintf( errpos, ERRARGLEN, "%s:%u: %s", org->file->name, org->line, s->sym->name );
        }
    }
}

/* Central handler for all error and warning printing routines. */
static void vmessage( const char *prefix, const char *msg, va_list args )
{
    if( errpos[0] != '\0' ){
        (void) fputs( errpos, stderr );
        (void) fputs( ": ", stderr );
    }
    if( prefix != NULL ){
        (void) fputs( prefix, stderr );
        (void) fputs( ": ", stderr );
    }
    (void) vfprintf( stderr, msg, args );
    (void) fputs( "\n", stderr );
    errpos[0] = '\0';
}

/* Central handler of all error printing routines. */
static void verror( const char *msg, va_list args )
{
    vmessage( NULL, msg, args );
    goterr = TRUE;
}

#if 0
/* Central handler of all warning printing routines. */
static void vwarning( const char *msg, va_list args )
{
    vmessage( "Warning", msg, args );
}
#endif

/* Central handler of all internal error printing routines. */
static void vinternal( const char *msg, va_list args )
{
    vmessage( "Internal error", msg, args );
    exit( EXIT_FAILURE );
}

/* General error printing routine: print error message 'msg' possibly preceded
 * by string in 'errpos'.
 *
 * Set a flag to indicate an error has occurred. If the function errcheck()
 * is called, it will cause an exit( EXIT_FAILURE ) if 'goterr' is now
 * true.
 */
void error( const char *msg, ... )
{
    va_list args;

    va_start( args, msg );
    verror( msg, args );
    va_end( args );
}

/* Handle an internal error. */
void internal_error( const char *msg, ... )
{
    va_list args;

    va_start( args, msg );
    vinternal( msg, args );
    va_end( args );
}

/* Given an origin 'org' and a message 'msg', fill errpos 
 * with the position of the symbol, and generate an
 * internal error message 'msg'.
 */
void origin_internal_error( const_origin org, const char *msg, ... )
{
    va_list args;

    orig_errpos( org );
    va_start( args, msg );
    vinternal( msg, args );
    va_end( args );
}

/* Given an origsymbol 's' and a message 'msg', fill errpos
 * with the position of the symbol, and generate an
 * internal error message 'msg'.
 */
void origsymbol_internal_error( const_origsymbol s, const char *msg, ... )
{
    va_list args;

    va_start( args, msg );
    origsymbol_errpos( s );
    vinternal( msg, args );
    va_end( args );
}

/* Check if 'goterr' flag is set, and do exit(EXIT_FAILURE) if it is. */
void errcheck( void )
{
    if( goterr ){
        fprintf( stderr, "errors detected, program aborted\n" );
	exit( EXIT_FAILURE );
    }
}

/* Returns true iff there has been an error. */
bool error_seen()
{
    return goterr;
}

/* Given a filename, a line number, and a message 'msg', 
 * generate an error message.
 */
void fileline_error( const char *nm, unsigned int lineno, const char *msg, ... )
{
    va_list args;

    fileline_errpos( nm, lineno );
    va_start( args, msg );
    verror( msg, args );
    va_end( args );
}

/* Given an origsymbol 's' and a message 'msg', fill errpos
 * with the position of the symbol, and generate error
 * message 'msg'.
 */
void origin_error( const_origin s, const char *msg, ... )
{
    va_list args;

    orig_errpos( s );
    va_start( args, msg );
    verror( msg, args );
    va_end( args );
}

/* Given an origsymbol 's' and a message 'msg', fill errpos
 * with the position of the symbol, and generate error
 * message 'msg'.
 */
void origsymbol_error( const_origsymbol s, const char *msg, ... )
{
    va_list args;

    va_start( args, msg );
    origsymbol_errpos( s );
    verror( msg, args );
    va_end( args );
}

#ifndef HAVE_STRERROR
/* On some systems (notably SunOS 4.1.4), there isn't a strerror function,
 * so provide one.
 */
static const char *strerror( int no )
{
    if( no>sys_nerr ){
	// TODO: somehow convey the error number.
	return "unknown system error";
    }
    else {
	return sys_errlist[no];
    }
}
#endif

/* System error handler.  */
void sys_error( int no, const char *msg, ... )
{
    va_list args;

    va_start( args, msg );
    (void) fputs( strerror( no ), stderr );
    (void) fputs( ": ", stderr );
    verror( msg, args );
    va_end( args );
}
