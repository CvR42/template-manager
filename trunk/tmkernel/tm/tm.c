/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: tm.c
   main for 'tm': datastructure generation
 */

#include <assert.h>
#include <time.h>

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
#include "checkds.h"

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
    { 'n', &noerrorline, "don't generate line numbers in error messages (useful for diffs)" },
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
    if( env == (char *) 0 ){
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

    start_time = clock();
    init_error();
    init_lex();
    init_var();
    active_libpath = find_active_libpath();
    scanargs( argc, argv, active_libpath );
    if( errfilename != tmstringNIL ){
	ckfreopen( errfilename, "w", stderr );
    }
    allds = parse_ds_file( dsfilename );
    check_ds_list( allds );
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
    errcheck();
    if( get_balance_tm() != 0 || get_balance_tmstring() != 0 ){
	fprintf( statstream, "Object allocation not balanced.\n" );
	prstat = TRUE;
    }
    if( prstat ){
	stat_tm( statstream );
	stat_lex( statstream );
	stat_tmstring( statstream );
	report_lognew( statstream );
    }
    flush_lognew();
    exit( 0 );
    return 0;
}
