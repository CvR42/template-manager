/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: tm.c
   main for 'tm': datastructure generation
 */

#include <assert.h>

#include "config.h"

#include "tmdefs.h"

#include <tmc.h>

#include "flag.h"
#include "tmcode.h"
#include "tmstring.h"
#include "error.h"
#include "fn.h"
#include "lex.h"
#include "dsparser.h"
#include "misc.h"
#include "tmtrans.h"
#include "var.h"
#include "global.h"
#include "tmpath.h"
#include "srchfile.h"
#include "version.h"

static char *prognm;
static FILE *tplfile;
static tmstring outfilename;	/* Possible output redirection file. */
static tmstring errfilename;	/* Possible error redirection file. */

/* Table of debugging flags plus associated information.

   Table is ended by an entry with flagchar '\0'
 */
static dbflag flagtab[] = {
    { 'e', &sevaltr, "tracing of string evaluations" },
    { 'f', &fntr, "tracing of function evaluations" },
    { 'l', &listing, "list parsetree" },
    { 'm', &maintr, "tracing of main actions" },
    { 's', &prstat, "statistics" },
    { 'v', &vartr, "variable and macro tracing" },
    { 'x', &lextr, "tracing of lexical analyzer" },
    { '\0', &fntr, "" }
};

/* Return the library path to be used. If there is an environment
 * variable 'TMLIBPATH' use that, else use the predefined variable
 * libpath.
 */
static tmstring find_active_libpath( void )
{
    char *env;

    env = getenv( "TMLIBPATH" );
    if( env == NULL ){
#ifdef LIBPATH
	return new_tmstring( LIBPATH );
#else
	return new_tmstring( libpath );
#endif
    }
    return new_tmstring( env );
}

static const char helptext[] =
    "Usage: tm [<flags>] <dsfile> [<infile>]\n"
    " -d<debugflags>  Set given debug flags\n"
    " -e<file>        Redirect errors to file <file>\n"
    " -h              Show this help text\n"
    " -I<path>        Append <path> to the search path\n"
    " -o<file>        Redirect output to file <file>\n"
    " -s<var>         Set variable <var> to the empty string\n"
    " -s<var>=<val>   Set variable <var> to string <val>\n"
    " -v              Set 'verbose' variable (equivalent to `-sverbose')\n"
    "\n"
;

/* Given a list of datastructure definitions, an index in the list,
 * a list of visited flags and a list of accepted flags, check the
 * data structure with the given index for circular inheritances.
 */
static void check_ds_inheritance(
 ds_list dl,
 unsigned int theds,
 bool *visited,
 bool *accepted
)
{
    tmstring_list supers;	/* The list of superclasses. */
    unsigned int ix;
    ds me = dl->arr[theds];
    tmstring myname;

    assert( theds<dl->sz );
    myname = tmstringNIL;
    supers = tmstring_listNIL;
    switch( me->tag ){
        case TAGDsCons:
            supers = me->DsCons.inherits;
            myname = me->DsCons.name;
            break;

	case TAGDsTuple:
            supers = me->DsTuple.inherits;
            myname = me->DsTuple.name;
            break;

	case TAGDsClass:
	    supers = me->DsClass.inherits;
            myname = me->DsClass.name;
            break;

    }
    if( accepted[theds] ){
        return;
    }
    if( visited[theds] ){
	sprintf( errpos, "type '%s'", myname );
	error( "circular inheritance" );
	accepted[theds] = TRUE;		/* Break the circle to allow further checks. */
	return;
    }
    visited[theds] = TRUE;
    for( ix=0; ix<supers->sz; ix++ ){
        tmstring super = supers->arr[ix];
        unsigned int superix = find_type_ix( dl, super );
        if( superix<dl->sz ){
	    check_ds_inheritance( dl, superix, visited, accepted );
        }
    }
    visited[theds] = FALSE;
    accepted[theds] = TRUE;
}

/* Given a list of datastructure definitions, ensure that it does not
 * contain circular inheritances.
 */
static void check_ds_list_inheritance( ds_list dl )
{
    bool *visited;	/* The data structures currently under examination */
    bool *accepted;	/* The data structures that already passed the test. */
    unsigned int ix;
    unsigned int sz;

    sz = dl->sz;
    visited = TM_MALLOC( bool *, sizeof(bool)*sz );
    if( visited == NULL ){
        /* No room. Don't report it; the check is not that important anyway.  */
        return;
    }
    accepted = TM_MALLOC( bool *, sizeof(bool)*sz );
    if( accepted == NULL ){
        /* No room. Don't report it; the check is not that important anyway. */
        TM_FREE( visited );
        return;
    }
    for( ix=0; ix<sz; ix++ ){
        visited[ix] = accepted[ix] = FALSE;
    }
    for( ix=0; ix<sz; ix++ ){
        check_ds_inheritance( dl, ix, visited, accepted );
    }
    TM_FREE( accepted );
    TM_FREE( visited );
}

/* Scan command line arguments and options as passed by 'argc' and 'argv'. */
static void scanargs( int argc, char **argv, tmstring lp )
{
    int printusage = FALSE;
    int exitcode = 0;
    int op;
    tmstring tplfnm;

    dsfilename = tmstringNIL;
    tplfnm = tmstringNIL;
    outfilename = tmstringNIL;
    errfilename = tmstringNIL;
    searchpath = new_tmstring_list();
    searchpath = append_tmstring_list( searchpath, rdup_tmstring( lp ) );
    prognm = argv[0];
    if( prognm[0] == 0 ){
	prognm = "tm";
    }
    argv++;
    argc--;
    while( argc>0 ){
	if( argv[0][0] != '-' ) break;
	op = argv[0][1];
	switch( op ){
	    case 'd':
		setdbflags( &argv[0][2], flagtab, TRUE );
		break;

	    case 'e':
	    case 'E':
		if( argv[0][2] != '\0' ){
		    if( errfilename != tmstringNIL ){
			rfre_tmstring( errfilename );
		    }
		    errfilename = new_tmstring( argv[0]+2 );
		}
		else {
		    if( argc<1 ){
			error( "Missing argument for -e" );
		    }
		    else {
			if( errfilename != tmstringNIL ){
			    rfre_tmstring( errfilename );
			}
			errfilename = new_tmstring( argv[1] );
			argc--;
			argv++;
		    }
		}
		break;

	    case 'h':
	    case 'H':
		printusage = TRUE;
		exitcode = 0;
		break;

	    case 'I':
		if( argv[0][2] != '\0' ){
		    searchpath = append_tmstring_list( searchpath, new_tmstring( argv[0]+2 ) );
		}
		else {
		    if( argc<1 ){
			error( "Missing argument for -I" );
		    }
		    else {
			searchpath = append_tmstring_list( searchpath, new_tmstring( argv[1] ) );
			argc--;
			argv++;
		    }
		}
		break;

	    case 'o':
	    case 'O':
		if( argv[0][2] != '\0' ){
		    if( outfilename != tmstringNIL ){
			rfre_tmstring( outfilename );
		    }
		    outfilename = new_tmstring( argv[0]+2 );
		}
		else {
		    if( argc<1 ){
			error( "Missing argument for -o" );
		    }
		    else {
			if( outfilename != tmstringNIL ){
			    rfre_tmstring( outfilename );
			}
			outfilename = new_tmstring( argv[1] );
			argc--;
			argv++;
		    }
		}
		break;

	    case 's':
	    case 'S':
	    {
		char *s;
		char *pos;

		if( argv[0][2] != '\0' ){
		    s = argv[0]+2;
		}
		else {
		    if( argc<1 ){
			error( "Missing argument for -s" );
			s = argv[0]+2;
		    }
		    else {
			s = argv[1];
			argc--;
			argv++;
		    }
		}
		pos = strchr( s, '=' );
		if( pos == NULL ){
		    setvar( s, "" );
		}
		else {
		    *pos = '\0';
		    setvar( s, pos+1 );
		}
		break;
	    }

	    case 'v':
		setvar( "verbose", "" );
		break;

	    case '?':
	    default:
		printusage = TRUE;
		exitcode = 1;
		break;
	}
	argc--;
	argv++;
    }
    if( printusage ){
	fprintf( stdout, "Tm version %d, tmkernel version %s\n", VERSION, TMKERNEL_VERSION );
	fputs( helptext, stdout);
	helpdbflags( stdout, flagtab );
	exit( exitcode );
    }
    if( argc>0 ){
	dsfilename = new_tmstring( argv[0] );
	argc--;
	argv++;
    }
    if( argc>0 ){
	tplfnm = new_tmstring( argv[0] );
	argc--;
	argv++;
    }
    if( argc>0 ){
	fprintf(
	    stdout,
	    "%s: only one input file allowed\n",
	    argv[0]
	);
	exit( 1 );
    }
    if( tplfnm != tmstringNIL ){
	tplfilename = search_file( searchpath, tplfnm, PATHSEPSTR, "r" );
	if( tplfilename == tmstringNIL ){
	    sprintf( errarg, "'%s'", tplfnm );
	    error( "file not found" );
	    exit( 1 );
	}
	rfre_tmstring( tplfnm );
    }
    else {
	tplfilename = tmstringNIL;
    }
}

int main( int argc, char **argv )
{
    tmstring active_libpath;		/* The libpath really used. */
    TMPRINTSTATE *st;
    int lev;
    char buf[10];

    init_error();
    init_lex();
    init_var();
    active_libpath = find_active_libpath();
    scanargs( argc, argv, active_libpath );
    if( errfilename != tmstringNIL ){
	ckfreopen( errfilename, "w", stderr );
    }
    allds = parse_ds_file( dsfilename );
    check_ds_list_inheritance( allds );
    errcheck();
    if( tplfilename != tmstringNIL ){
	tplfile = ckfopen( tplfilename, "r" );
    }
    else{
	tplfile = stdin;
	tplfilename = new_tmstring( "<stdin>" );
    }
    if( outfilename != tmstringNIL ){
	ckfreopen( outfilename, "w", stdout );
    }
    if( listing ){
	st = tm_setprint( stdout, 2, 79, 8, 0 );
	print_ds_list( st, allds );
	lev = tm_endprint( st );
	if( st != 0 ){
	    fprintf( stderr, "Internal botch: print level is %d\n", lev );
	}
    }
    errcheck();
    sprintf( buf, "%d", VERSION );
    setvar( "tmvers", buf );
    setvar( "kernel-version", TMKERNEL_VERSION );
    setvar( "libpath", active_libpath );
    setvar( "pathsep", PATHSEPSTR );
    translate( tplfile, stdout );
    fclose( tplfile );
    end_lex();
    rfre_ds_list( allds );
    rfre_tmstring( dsfilename );
    rfre_tmstring( tplfilename );
    rfre_tmstring( outfilename );
    rfre_tmstring( errfilename );
    rfre_tmstring_list( searchpath );
    rfre_tmstring( active_libpath );
    end_var();
    flush_tm();
    if( prstat ){
	stat_tm( statstream );
	stat_lex( statstream );
	stat_tmstring( statstream );
	report_lognew( statstream );
    }
    flush_lognew();
    errcheck();
    exit( 0 );
    return 0;
}
