/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: tmtrans.c
 *
 * Translate input file into output file given datastructure
 * description.
 */

#include "config.h"

/* Standard UNIX libraries */
#include <stdio.h>
#include <ctype.h>
#include <tmc.h>

/* local definitions */
#include "tmdefs.h"

#include "tmcode.h"
#include "tmstring.h"
#include "fn.h"
#include "tmexpr.h"
#include "error.h"
#include "global.h"
#include "tmpath.h"
#include "misc.h"
#include "tmtrans.h"
#include "var.h"
#include "srchfile.h"
#include "checkds.h"

/* tags for command table */
typedef enum en_tmcommands {
    RENAME,
    APPEND,
    APPENDFILE,
    CALL,
    CASE,
    DEFAULT,
    DELETETYPE,
    ELSE,
    ENDAPPENDFILE,
    ENDFOREACH,
    ENDIF,
    ENDMACRO,
    ENDREDIRECT,
    ENDSWITCH,
    ENDWHILE,
    EOFLINE,		/* special line: end of file */
    ERROR,
    EXIT,
    FOREACH,
    GLOBALAPPEND,
    GLOBALSET,
    IF,
    INCLUDE,
    INSERT,
    MACRO,
    REDIRECT,
    RETURN,
    SET,
    SWITCH,
    WHILE
} tmcommand;

/******************************************************
 *    Input of template lines                         *
 ******************************************************/

/* A table of LCOMCHAR commands. The table must be terminated by
   an entry with empty name.
 */
struct dotcom {
    const char *dotcomname;
    tmcommand dotcomtag;
};

static struct dotcom dotcomlist[] = {
    { "append", APPEND },
    { "appendfile", APPENDFILE },
    { "call", CALL },
    { "case", CASE },
    { "default", DEFAULT },
    { "deletetype", DELETETYPE },
    { "else", ELSE },
    { "endappendfile", ENDAPPENDFILE },
    { "endforeach", ENDFOREACH },
    { "endif", ENDIF },
    { "endmacro", ENDMACRO },
    { "endredirect", ENDREDIRECT },
    { "endswitch", ENDSWITCH },
    { "endwhile", ENDWHILE },
    { "error", ERROR },
    { "exit", EXIT },
    { "foreach", FOREACH },
    { "globalappend", GLOBALAPPEND },
    { "globalset", GLOBALSET },
    { "if", IF },
    { "include", INCLUDE },
    { "insert", INSERT },
    { "macro", MACRO },
    { "redirect", REDIRECT },
    { "rename", RENAME },
    { "return", RETURN },
    { "set", SET },
    { "switch", SWITCH },
    { "while", WHILE },
    { "", SET }		/* end of table mark */
};

static const char *comname( tmcommand com )
{
    unsigned int ix;

    if( com == EOFLINE ){
	return "end of file";
    }
    ix = 0;
    while( dotcomlist[ix].dotcomname[0] != '\0' ){
	if( com == dotcomlist[ix].dotcomtag ){
	    return dotcomlist[ix].dotcomname;
	}
	ix++;
    }
    return "??";
}

/* Generate error messages for unbalance in the .<command> and
   .end<command> pairs.
 */
static void unbalance( int lno, tmcommand isterm, tmcommand needterm )
{
    if( isterm == needterm ){
	return;    /* just for safety */
    }
    if( needterm != EOFLINE ){
	if( isterm != EOFLINE ){
	    sprintf( errarg, "unbalanced command at %s(%d)", tplfilename, lno );
	    line_error( "unexpected dot command" );
	}
	else {
	    sprintf(
		errarg,
		"unterminated command at %s(%d)",
		tplfilename,
		lno
	    );
	    line_error( "unexpected end of file" );
	}
    }
    else {
	sprintf(
	    errarg,
	    "expected %s, but got %s",
	    comname( needterm ),
	    comname( isterm )
	);
	line_error( "unexpected termination command" );
    }
}

typedef enum en_switchstate {
    SWS_NONE, SWS_CASE, SWS_DEFAULT
} switchstate;

/* Given a list of template elements, construct a proper switch
 * from these statements, by searching for the 'case' and 'default'
 * lines.
 */
static tplelm construct_switch( int lno, const char *swval, tplelm_list el )
{
    unsigned int ix;
    tplelm_list block;
    tplelm_list deflt;
    switchcase_list cases;
    switchstate state = SWS_NONE;
    tmstring val;

    block = new_tplelm_list();
    cases = new_switchcase_list();
    deflt = tplelm_listNIL;
    val = tmstringNIL;
    for( ix=0; ix<el->sz; ix++ ){
	const tplelm e = el->arr[ix];

	switch( e->tag ){
	    case TAGCase:
	    case TAGDefault:
		switch( state ){
		    case SWS_NONE:
			if( block->sz != 0 ){
			    int oldtpllineno = tpllineno;

			    tpllineno = lno+1;
			    line_error( "statements outside a case ignored" );
			    tpllineno = oldtpllineno;
			    rfre_tplelm_list( block );
			    block = new_tplelm_list();
			}
			break;

		    case SWS_CASE:
			cases = append_switchcase_list(
			    cases,
			    new_switchcase( rdup_tmstring( val ), block )
			);
			block = new_tplelm_list();
			break;

		    case SWS_DEFAULT:
			if( deflt != tplelm_listNIL ){
			    line_error( "second .deflt block ignored" );
			    rfre_tplelm_list( block );
			}
			else {
			    deflt = block;
			}
			block = new_tplelm_list();
			break;
		}
		if( e->tag == TAGCase ){
		    state = SWS_CASE;
		    val = to_Case(e)->val;
		}
		else {
		    state = SWS_DEFAULT;
		}

	    default:
		block = append_tplelm_list( block, rdup_tplelm( el->arr[ix] ) );
		break;
	}
    }
    /* We know the caller puts an empty case statement at the end, so
     * this block is guaranteed to contain only that. Throw away
     * without checking. Yes, this is not elegant.
     */
    rfre_tplelm_list( block );
    return (tplelm) new_Switch( lno, rdup_tmstring( swval ), cases, deflt );
}

/* Given a file 'f' and a pointer to an int 'endcom', read all lines from
   file 'f' up to the next unbalanced end command and put them in template
   elements. End commands are:
      <eof>
      .else
      .endappendfile
      .endforeach
      .endif
      .endmacro
      .endredirect
      .endswitch
      .endwhile

   Return the list of template elements, and set *endcom to the end command
   that caused termination.
 */
static tplelm_list readtemplate( FILE *f, tmcommand *endcom )
{
    char *com;
    const char *p;
    tplelm_list e1;
    tplelm_list e2;
    struct dotcom *cp;
    tplelm te;
    tplelm_list tel;
    tmcommand subendcom;
    int firstlno;
    size_t inbufsz;
    unsigned int bufix;
    char *inbuf;
    int c;

    inbufsz = 100;	/* reasonable initial value */
    inbuf = TM_MALLOC( char *, inbufsz );
    tel = new_tplelm_list();
    for(;;){
	bufix = 0;
	for(;;){
	    if( bufix>=inbufsz ){
		inbufsz += inbufsz;
		inbuf = TM_REALLOC( char *, inbuf, inbufsz );
	    }
	    c = getc( f );
	    if( c == EOF || c == '\n' ){
		inbuf[bufix] = '\0';
		break;
	    }
	    if( c != '\r' ){
		inbuf[bufix++] = c;
	    }
	}
	tpllineno++;
	if( c == EOF && bufix == 0 ){
	    *endcom = EOFLINE;
	    TM_FREE( inbuf );
	    return tel;
	}
	else if( inbuf[0] == LCOMCHAR ){
	    if( inbuf[1] != LCOMCHAR ){
		p = scanword( inbuf+1, &com );
		if( com == CHARNIL ){
		    com = new_tmstring( "" );
		}
		cp = dotcomlist;
		while( strcmp( com, cp->dotcomname ) != 0 ){
		    if( cp->dotcomname[0] == '\0' ){
			strcpy( errarg, com );
			line_error( "unknown dot command" );
			exit( 1 );
		    }
		    cp++;
		}
		fre_tmstring( com );
		switch( cp->dotcomtag ){
		    case ELSE:
		    case ENDAPPENDFILE:
		    case ENDFOREACH:
		    case ENDIF:
		    case ENDMACRO:
		    case ENDREDIRECT:
		    case ENDSWITCH:
		    case ENDWHILE:
		    case EOFLINE:
			*endcom = cp->dotcomtag;
			TM_FREE( inbuf );
			return tel;

		    case CASE:
			te = (tplelm) new_Case( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case DEFAULT:
			te = (tplelm) new_Default( tpllineno );
			tel = append_tplelm_list( tel, te );
			break;

		    case SWITCH:
		    {
			tplelm_list el;

			firstlno = tpllineno;
			el = readtemplate( f, &subendcom );
			if( subendcom != ENDSWITCH ){
			    unbalance( firstlno, subendcom, ENDSWITCH );
			}
			el = append_tplelm_list(
			    el,
			    (tplelm) new_Case( 0, new_tmstring( "" ) )
			);
			te = construct_switch( firstlno, p, el );
			tel = append_tplelm_list( tel, te );
			rfre_tplelm_list( el );
			break;
		    }

		    case IF:
			firstlno = tpllineno;
			e1 = readtemplate( f, &subendcom );
			if( subendcom == ELSE ){
			    e2 = readtemplate( f, &subendcom );
			}
			else {
			    e2 = new_tplelm_list();
			}
			if( subendcom != ENDIF ){
			    unbalance( firstlno, subendcom, ENDIF );
			}
			te = (tplelm) new_If( firstlno, new_tmstring( p ), e1, e2 );
			tel = append_tplelm_list( tel, te );
			break;

		    case FOREACH:
			firstlno = tpllineno;
			e1 = readtemplate( f, &subendcom );
			if( subendcom != ENDFOREACH ){
			    unbalance( firstlno, subendcom, ENDFOREACH );
			}
			te = (tplelm) new_Foreach( firstlno, new_tmstring( p ), e1 );
			tel = append_tplelm_list( tel, te );
			break;

		    case WHILE:
			firstlno = tpllineno;
			e1 = readtemplate( f, &subendcom );
			if( subendcom != ENDWHILE ){
			    unbalance( firstlno, subendcom, ENDWHILE );
			}
			te = (tplelm) new_While( firstlno, new_tmstring( p ), e1 );
			tel = append_tplelm_list( tel, te );
			break;

		    case MACRO:
			firstlno = tpllineno;
			e1 = readtemplate( f, &subendcom );
			if( subendcom != ENDMACRO ){
			    unbalance( firstlno, subendcom, ENDMACRO );
			}
			te = (tplelm) new_Macro( firstlno, new_tmstring( p ), e1 );
			tel = append_tplelm_list( tel, te );
			break;

		    case APPENDFILE:
			firstlno = tpllineno;
			e1 = readtemplate( f, &subendcom );
			if( subendcom != ENDAPPENDFILE ){
			    unbalance( firstlno, subendcom, ENDAPPENDFILE );
			}
			te = (tplelm) new_Appendfile( firstlno, new_tmstring( p ), e1 );
			tel = append_tplelm_list( tel, te );
			break;

		    case REDIRECT:
			firstlno = tpllineno;
			e1 = readtemplate( f, &subendcom );
			if( subendcom != ENDREDIRECT ){
			    unbalance( firstlno, subendcom, ENDREDIRECT );
			}
			te = (tplelm) new_Redirect( firstlno, new_tmstring( p ), e1 );
			tel = append_tplelm_list( tel, te );
			break;

		    case INSERT:
			te = (tplelm) new_Insert( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case INCLUDE:
			te = (tplelm) new_Include( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case RENAME:
			te = (tplelm) new_Rename( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case SET:
			te = (tplelm) new_Set( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case GLOBALSET:
			te = (tplelm) new_GlobalSet( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case RETURN:
			te = (tplelm) new_Return( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case DELETETYPE:
			te = (tplelm) new_DeleteType( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case APPEND:
			te = (tplelm) new_Append( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case GLOBALAPPEND:
			te = (tplelm) new_GlobalAppend( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case CALL:
			te = (tplelm) new_Call( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case EXIT:
			te = (tplelm) new_Exit( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case ERROR:
			te = (tplelm) new_Error( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;
		}
	    }
	}
	else {
	    te = (tplelm) new_Plain( tpllineno, new_tmstring( inbuf ) );
	    tel = append_tplelm_list( tel, te );
	}
    }
}

/******************************************************
 *                                                    *
 *    VARCHAR expression evaluation                   *
 *                                                    *
 ******************************************************/

/* Given a pointer to an input tmstring 'spi', a pointer to an output tmstring
   'spo', and a stop character 'sc', copy and evaluate the tmstring to the
   stop character 'sc'. Update the position of '*spi' to point to the stop
   character or '\0', and return the evaluated tmstring.
 */
tmstring alevalto( char **spi, const int sc )
{
    tmstring si;
    tmstring cp;		/* pointer to constructed tmstring */
    unsigned int croom;		/* room in constructed tmstring */
    unsigned int six;		/* index in constructed tmstring */
    char var1[2];		/* buffer for 1 char variable */
    char *fnval;
    char *v;
    tmstring ans;
    unsigned int len;

    si = *spi;
    cp = new_tmstring( si );
    croom = (int) strlen( si );
    six = 0;
    if( sevaltr ){
	if( sc == '\0' )
	    fprintf( tracestream, "alevalto: '%s'\n", si );
	else
	    fprintf( tracestream, "alevalto: '%s' to char '%c'\n", si, sc );
    }
    while( *si != '\0' && *si != sc ){
	/* make sure that 1 character will always fit */
	if( six>=croom ){
	    croom += STRSTEP;
	    cp = realloc_tmstring( cp, croom+1 );
	}
	if( *si != VARCHAR ){
	    cp[six++] = *si++;
	    continue;
	}
	si++;
	if( *si == ORBRAC ){
	    si++;
	    *spi = si;
	    ans = alevalto( spi, CRBRAC );
	    si = *spi;
	    if( *si != CRBRAC ){
		(void) sprintf( errarg, "'%c'", CRBRAC );
		line_error( "missing close bracket" );
		fre_tmstring( ans );
		continue;
	    }
	    si++;
	    v = getvar( ans );
	    if( v == CHARNIL ){
		strcpy( errarg, ans );
		line_error( "variable not found" );
		fre_tmstring( ans );
		continue;
	    }
	    fre_tmstring( ans );
	    len = six + (int) strlen( v ) + (int) strlen( si );
	    if( len > croom ){
		croom = len;
		cp = realloc_tmstring( cp, croom+1 );
	    }
	    while( *v!='\0' ) cp[six++] = *v++;
	    continue;
	}
	if( *si == OCBRAC ){
	    si++;
	    *spi = si;
	    ans = alevalto( spi, CCBRAC );
	    si = *spi;
	    if( *si != CCBRAC ){
		(void) sprintf( errarg, "'%c'", CCBRAC );
		line_error( "missing close bracket" );
		fre_tmstring( ans );
		continue;
	    }
	    si++;
	    fnval = evalfn( ans );
	    v = fnval;
	    fre_tmstring( ans );
	    len = six + (int) strlen( fnval ) + (int) strlen( si );
	    if( len > croom ){
		croom = len;
		cp = realloc_tmstring( cp, croom+1 );
	    }
	    while( *v!='\0' ){
		cp[six++] = *v++;
	    }
	    fre_tmstring( fnval );
	    continue;
	}
	if( *si == OSBRAC ){
	    si++;
	    *spi = si;
	    ans = alevalto( spi, CSBRAC );
	    si = *spi;
	    if( *si != CSBRAC ){
		(void) sprintf( errarg, "'%c'", CSBRAC );
		line_error( "missing close bracket" );
		fre_tmstring( ans );
		continue;
	    }
	    si++;
	    fnval = evalexpr( ans );
	    v = fnval;
	    fre_tmstring( ans );
	    len = six + (int) strlen( fnval ) + (int) strlen( si );
	    if( len > croom ){
		croom = len;
		cp = realloc_tmstring( cp, croom+1 );
	    }
	    while( *v!='\0' ){
		cp[six++] = *v++;
	    }
	    fre_tmstring( fnval );
	    continue;
	}
	if( *si == '\0' ){
	    cp[six++] = VARCHAR;
	    continue;
	}
	if( !isalnum( *si ) ){
	    cp[six++] = *si++;
	    continue;
	}
	var1[0] = *si++;
	var1[1] = '\0';
	v = getvar( var1 );
	if( v == CHARNIL ){
	    strcpy( errarg, var1 );
	    line_error( "variable not found" );
	    continue;
	}
	len = six + (int) strlen( v ) + (int) strlen( si );
	if( len > croom ){
	    croom = len;
	    cp = realloc_tmstring( cp, croom+1 );
	}
	while( *v!='\0' ){
	    cp[six++] = *v++;
	}
    }
    cp[six]='\0';
    *spi = si;
    if( sevaltr ){
	fprintf( tracestream, "value is: '%s'\n", cp );
    }
    return cp;
}

/******************************************************
 *    Output file generation                          *
 ******************************************************/

/* Copy an ordinary line to the output and replace all VARCHAR
 * references with the variable.
 */
static void doplain( const tplelm l, FILE *outfile )
{
    tmstring is;
    tmstring os;

    is = to_Plain(l)->line;
    os = alevalto( &is, '\0' );
    if( outfile == NULL ){
	line_error( "no output allowed in expression macro" );
    }
    else {
	fputs( os, outfile );
	putc( '\n', outfile );
    }
    fre_tmstring( os );
}

/* Handle 'insert' command. */
static void doinsert( const tplelm tpl, FILE *outfile )
{
    tmstring fname;
    tmstring oldfname;
    tmstring exfname;
    FILE *infile;
    tmstring is;
    tmstring os;

    is = to_Insert(tpl)->fname;
    os = alevalto( &is, '\0' );
    scan1par( os, &fname );
    fre_tmstring( os );
    if( fname == tmstringNIL ){
	return;
    }
    exfname = search_file( searchpath, fname, PATHSEPSTR, "r" );
    if( exfname == tmstringNIL ){
	sprintf( errarg, "'%s'", fname );
	fre_tmstring( fname );
	line_error( "file not found" );
	return;
    }
    fre_tmstring( fname );
    infile = ckfopen( exfname, "r" );
    oldfname = tplfilename;
    tplfilename = exfname;
    translate( infile, outfile );
    fclose( infile );
    tplfilename = oldfname;
    fre_tmstring( exfname );
}

/* Handle 'redirect' command. */
static void doredirect( const tplelm e )
{
    tmstring fname;
    FILE *outfile;
    char *is;
    char *os;

    is = to_Redirect(e)->fname;
    os = alevalto( &is, '\0' );
    scan1par( os, &fname );
    fre_tmstring( os );
    if( fname == tmstringNIL ){
	line_error( "missing filename" );
	return;
    }
    outfile = ckfopen( fname, "w" );
    dotrans( to_Redirect(e)->body, outfile );
    fclose( outfile );
    fre_tmstring( fname );
}

/* Handle 'appendfile' command. */
static void doappendfile( const tplelm e )
{
    tmstring fname;
    FILE *outfile;
    char *is;
    char *os;

    is = to_Appendfile(e)->fname;
    os = alevalto( &is, '\0' );
    scan1par( os, &fname );
    fre_tmstring( os );
    if( fname == tmstringNIL ){
	line_error( "missing filename" );
	return;
    }
    outfile = ckfopen( fname, "a" );
    dotrans( to_Appendfile(e)->body, outfile );
    fclose( outfile );
    fre_tmstring( fname );
}

/* Handle 'include' command. */
static void doinclude( const tplelm tpl, FILE *outfile )
{
    tmstring fname;
    tmstring oldfname;
    tmstring exfname;
    FILE *infile;
    char *is;
    char *os;

    is = to_Include(tpl)->fname;
    os = alevalto( &is, '\0' );
    scan1par( os, &fname );
    fre_tmstring( os );
    if( fname == tmstringNIL ){
	return;
    }
    exfname = search_file( searchpath, fname, PATHSEPSTR, "r" );
    if( exfname == tmstringNIL ){
	sprintf( errarg, "'%s'", fname );
	fre_tmstring( fname );
	line_error( "file not found" );
	return;
    }
    infile = ckfopen( exfname, "r" );
    oldfname = tplfilename;
    tplfilename = exfname;
    newvarctx();
    setvar( "templatefile", fname );
    fre_tmstring( fname );
    translate( infile, outfile );
    flushvar();
    fclose( infile );
    tplfilename = oldfname;
    fre_tmstring( exfname );
}

/* Handle 'error' command. */
static void doerror( const tplelm tpl )
{
    char *is;
    char *os;

    is = to_Error(tpl)->str;
    os = alevalto( &is, '\0' );
    fprintf( stderr, "%s\n", os );
    fre_tmstring( os );
}

/* Handle 'exit' command. */
static void doexit( const tplelm tpl )
{
    char *is;
    char *os;

    is = to_Exit(tpl)->str;
    os = alevalto( &is, '\0' );
    exit( atoi( os ) );
    /* freeing is no use */
}

/* Handle 'globalset' command. */
static void doglobalset( const tplelm tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring_list sl;
    tmstring nm;

    is = to_GlobalSet(tpl)->line;
    os = alevalto( &is, '\0' );
    sl = chopstring( os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	line_error( "no name specified" );
	rfre_tmstring_list( sl );
	return;
    }
    nm = rdup_tmstring( sl->arr[0] );
    sl = delete_tmstring_list( sl, 0 );
    val = flatstrings( sl );
    rfre_tmstring_list( sl );
    globalsetvar( nm, val );
    fre_tmstring( val );
    fre_tmstring( nm );
}

/* Handle 'set' command. */
static void doset( const tplelm tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring_list sl;
    tmstring nm;

    is = to_Set(tpl)->line;
    os = alevalto( &is, '\0' );
    sl = chopstring( os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	line_error( "no name specified" );
	rfre_tmstring_list( sl );
	return;
    }
    nm = rdup_tmstring( sl->arr[0] );
    sl = delete_tmstring_list( sl, 0 );
    val = flatstrings( sl );
    rfre_tmstring_list( sl );
    setvar( nm, val );
    fre_tmstring( val );
    fre_tmstring( nm );
}

/* Given a tmstring 's', an old type name 'old' and a new type name 'nw'.
 * replace the string with a copy of 'nw'  if it is equal to 'old'.
 */
static tmstring rename_tmstring( tmstring s, tmstring old, tmstring nw )
{
    if( strcmp( s, old ) == 0 ){
	rfre_tmstring( s );
	s = rdup_tmstring( nw );
    }
    return s;
}

/* Given a list of strings, an old type name 'old' and a new
 * type name 'nw', rewrite these strings to use the new type name
 * instead of the old type name.
 */
static tmstring_list rename_tmstring_list( tmstring_list dl, const tmstring old, const tmstring nw )
{
    unsigned int ix;

    for( ix=0; ix<dl->sz; ix++ ){
	dl->arr[ix] = rename_tmstring( dl->arr[ix], old, nw );
    }
    return dl;
}

/* Given a list of fields, an old type name 'old' and a new
 * type name 'nw', rewrite these fields to use the new type name
 * instead of the old type name.
 */
static field rename_field( field f, const tmstring old, const tmstring nw )
{
    f->type = rename_tmstring( f->type, old, nw );
    return f;
}

/* Given a list of fields, an old type name 'old' and a new
 * type name 'nw', rewrite these fields to use the new type name
 * instead of the old type name.
 */
static field_list rename_field_list( field_list dl, const tmstring old, const tmstring nw )
{
    unsigned int ix;

    for( ix=0; ix<dl->sz; ix++ ){
	dl->arr[ix] = rename_field( dl->arr[ix], old, nw );
    }
    return dl;
}

/* Given a ds definition, an old type name 'old' and a new
 * type name 'nw', rewrite this definition to use the new name
 * instead of the old name.
 */
static ds rename_ds( ds d, const tmstring old, const tmstring nw )
{
    d->name = rename_tmstring( d->name, old, nw );
    d->inherits = rename_tmstring_list( d->inherits, old, nw );
    switch( d->tag ){
	case TAGDsConstructorBase:
	{
	    DsConstructorBase dsub = to_DsConstructorBase( d );

	    dsub->constructors = rename_tmstring_list( dsub->constructors, old, nw );
	    break;
	}

	case TAGDsTuple:
	{
	    DsTuple dsub = to_DsTuple( d );

	    dsub->fields = rename_field_list( dsub->fields, old, nw );
	    break;
	}

	case TAGDsClass:
	{
	    DsClass dsub = to_DsClass( d );

	    dsub->fields = rename_field_list( dsub->fields, old, nw );
	    break;
	}

	case TAGDsAlias:
	    break;

	case TAGDsConstructor:
	{
	    DsConstructor dsub = to_DsConstructor( d );

	    dsub->fields = rename_field_list( dsub->fields, old, nw );
	    break;
	}

    }
    return d;
}

/* Given a list of ds definitions, an old type name 'old' and a new
 * type name 'nw', rewrite these definitions to use the new name
 * instead of the old name.
 */
static ds_list rename_ds_list( ds_list dl, const tmstring old, const tmstring nw )
{
    unsigned int ix;

    for( ix=0; ix<dl->sz; ix++ ){
	dl->arr[ix] = rename_ds( dl->arr[ix], old, nw );
    }
    return dl;
}

/* Handle 'rename' command. */
static void dorename( const tplelm tpl )
{
    char *is;
    char *os;
    tmstring_list sl;

    is = to_Rename(tpl)->line;
    os = alevalto( &is, '\0' );
    sl = chopstring( os );
    rfre_tmstring( os );
    if( sl->sz != 2 ){
	line_error( "rename requires exactly two parameters" );
	rfre_tmstring_list( sl );
	return;
    }
    allds = rename_ds_list( allds, sl->arr[0], sl->arr[1] );
    if( !check_ds_list( allds ) ){
	sprintf( errarg, "'%s'->'%s'", sl->arr[0], sl->arr[1] );
	line_error( "The problems were caused by .rename" );
	exit( 1 );
    }
    rfre_tmstring_list( sl );
}

/* Handle 'return' command. */
static void doreturn( const tplelm tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring_list sl;

    is = to_Return(tpl)->retval;
    os = alevalto( &is, '\0' );
    sl = chopstring( os );
    fre_tmstring( os );
    val = flatstrings( sl );
    rfre_tmstring_list( sl );
    setvar( RETVALNAME, val );
    fre_tmstring( val );
}

/* Handle 'append' command. */
static void doappend( const tplelm tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring nm;
    tmstring_list sl;

    is = to_Append(tpl)->line;
    os = alevalto( &is, '\0' );
    sl = chopstring( os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	line_error( "no name specified" );
	rfre_tmstring_list( sl );
	return;
    }
    nm = rdup_tmstring( sl->arr[0] );
    sl = delete_tmstring_list( sl, 0 );
    val = getvar( nm );
    if( val != tmstringNIL && val[0] != '\0' ){
	sl = insert_tmstring_list( sl, 0, rdup_tmstring( val ) );
    }
    val = flatstrings( sl );
    rfre_tmstring_list( sl );
    setvar( nm, val );
    fre_tmstring( val );
    fre_tmstring( nm );
}

/* Handle 'globalappend' command. */
static void doglobalappend( const tplelm tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring nm;
    tmstring_list sl;

    is = to_GlobalAppend(tpl)->line;
    os = alevalto( &is, '\0' );
    sl = chopstring( os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	line_error( "no name specified" );
	rfre_tmstring_list( sl );
	return;
    }
    nm = rdup_tmstring( sl->arr[0] );
    sl = delete_tmstring_list( sl, 0 );
    val = getvar( nm );
    if( val != tmstringNIL && val[0] != '\0' ){
	sl = insert_tmstring_list( sl, 0, rdup_tmstring( val ) );
    }
    val = flatstrings( sl );
    rfre_tmstring_list( sl );
    globalsetvar( nm, val );
    fre_tmstring( val );
    fre_tmstring( nm );
}

/* Given a type list 'types' and a type name 'nm', delete that type from
 * the list of types.
 */
static ds_list delete_type( ds_list types, const tmstring nm )
{
    unsigned int ix = find_type_ix( types, nm );

    if( ix>=types->sz ){
	return types;
    }
    return delete_ds_list( types, ix );
}

/* Handle 'deletetype' command. */
static void dodeletetype( const DeleteType tpl )
{
    char *is;
    char *os;
    tmstring_list sl;
    unsigned int ix;

    is = tpl->line;
    os = alevalto( &is, '\0' );
    sl = chopstring( os );
    fre_tmstring( os );
    for( ix=0; ix<sl->sz; ix++ ){
	allds = delete_type( allds, sl->arr[ix] );
    }
    rfre_tmstring_list( sl );
}

/* Handle 'if' command. */
static void doif( const tplelm tpl, FILE *outfile )
{
    char *is;
    char *os;
    bool cond;

    is = to_If(tpl)->cond;
    os = alevalto( &is, '\0' );
    cond = istruestr( os );
    fre_tmstring( os );
    if( cond ){
	dotrans( to_If(tpl)->ifthen, outfile );
    }
    else {
	dotrans( to_If(tpl)->ifelse, outfile );
    }
}

/* Handle 'switch' command. */
static void doswitch( const Switch tpl, FILE *outfile )
{
    char *is;
    char *os;
    bool visited = FALSE;
    tmstring_list sl;
    unsigned int ix;
    switchcase_list cases;

    is = tpl->val;
    os = alevalto( &is, '\0' );
    sl = chopstring( os );
    fre_tmstring( os );
    if( sl->sz != 1 ){
	line_error( "A switch command requires exactly one parameter" );
	rfre_tmstring_list( sl );
	return;
    }
    cases = tpl->cases;
    for( ix=0; ix<cases->sz; ix++ ){
	char *caseval = cases->arr[ix]->cases;
	tmstring sentence;
	tmstring_list words;

	sentence = alevalto( &caseval, '\0' );
	words = chopstring( sentence );
	rfre_tmstring( sentence );
	if( member_tmstring_list( sl->arr[0], words ) ){
	    /* We've got a match. */
	    dotrans( cases->arr[ix]->action, outfile );
	    visited = TRUE;
	}
	rfre_tmstring_list( words );
    }
    if( !visited ){
	if( tpl->deflt == tplelm_listNIL ){
	    sprintf( errarg, "value '%s'", sl->arr[0] );
	    line_error( "no case matches, and there is no .default" );
	}
	else {
	    dotrans( tpl->deflt, outfile );
	}
    }
    rfre_tmstring_list( sl );
}

/* Handle 'foreach' command.
   Given a list of template lines, starting with a foreach command line,
   generate output lines. Handle local commands by recursion.
 */
static void doforeach( const tplelm tpl, FILE *outfile )
{
    char *nm;
    char *is;
    char *os;
    unsigned int ix;
    tmstring_list sl;

    is = to_Foreach(tpl)->felist;
    os = alevalto( &is, '\0' );
    sl = chopstring( os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	line_error( "no name specified" );
	rfre_tmstring_list( sl );
	return;
    }
    nm = sl->arr[0];
    for( ix=1; ix<sl->sz; ix++ ){
	setvar( nm, sl->arr[ix] );
	dotrans( to_Foreach(tpl)->body, outfile );
    }
    rfre_tmstring_list( sl );
}

/* Handle 'while' command.
   Given a list of template lines, starting with a while command line,
   generate output lines until condition is false. Handle local commands
   by recursion.
 */
static void dowhile( const tplelm tpl, FILE *outfile )
{
    bool done;
    char *is;
    char *os;

    while( TRUE ){
	is = to_While(tpl)->cond;
	os = alevalto( &is, '\0' );
	done = isfalsestr( os );
	fre_tmstring( os );
	if( done ) return;
	dotrans( to_While(tpl)->body, outfile );
    }
}

/* Handle a 'macro' command: break the parameter list up
 * in separate words, copy the macro body, and store it in the
 * macro table.
 */
static void domacro( const tplelm tpl )
{
    char *nm;
    char *is;
    char *os;
    tmstring_list sl;

    is = to_Macro(tpl)->formals;
    os = alevalto( &is, '\0' );
    sl = chopstring( os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	line_error( "no macro name specified" );
	rfre_tmstring_list( sl );
	return;
    }
    nm = rdup_tmstring( sl->arr[0] );
    sl = delete_tmstring_list( sl, 0 );
    setmacro( nm, tplfilename, sl, to_Macro(tpl)->body );
    rfre_tmstring( nm );
    rfre_tmstring_list( sl );
}

/* Handle 'call' command (calls a macro). */
static void docall( const tplelm tpl, FILE *outfile )
{
    char *is;
    char *os;
    tmstring_list sl;
    tmstring nm;
    tmstring_list fpl;
    tmstring oldfname;
    unsigned int ix;
    macro m;

    is = to_Call(tpl)->line;
    os = alevalto( &is, '\0' );
    sl = chopstring( os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	line_error( "no macro name given" );
	rfre_tmstring_list( sl );
	return;
    }
    nm = rdup_tmstring( sl->arr[0] );
    sl = delete_tmstring_list( sl, 0 );
    m = findmacro( nm );
    if( m == macroNIL ){
	sprintf( errarg, "'%s'", nm );
	line_error( "no such macro" );
	rfre_tmstring_list( sl );
	rfre_tmstring( nm );
	return;
    }
    fpl = m->fpl;
    rfre_tmstring( nm );
    if( fpl->sz != sl->sz ){
	sprintf(
	    errarg,
	    "%u instead of %u (macro '%s')",
	    sl->sz,
	    fpl->sz,
	    m->name
	);
	line_error( "wrong number of parameters" );
	rfre_tmstring_list( sl );
	return;
    }
    oldfname = tplfilename;
    tplfilename = m->orgfile;
    newvarctx();
    setvar( "templatefile", m->orgfile );
    for( ix=0; ix<sl->sz; ix++ ){
	setvar( fpl->arr[ix], sl->arr[ix] );
    }
    dotrans( m->body, outfile );
    flushvar();
    tplfilename = oldfname;
    rfre_tmstring_list( sl );
}

/* Recursive translation routine.
   Given a list of template lines in 'tpl' generate text from them,
   and write this text to 'outfile'.
 */
void dotrans( const tplelm_list tpl, FILE *outfile )
{
    unsigned int ix;
    tplelm e;

    for( ix=0; ix<tpl->sz; ix++ ){
	e = tpl->arr[ix];
	tpllineno = e->lno;
	switch( e->tag ){
	    case TAGError:
		doerror( e );
		break;

	    case TAGForeach:
		doforeach( e, outfile );
		break;

	    case TAGIf:
		doif( e, outfile );
		break;

	    case TAGSwitch:
		doswitch( to_Switch(e), outfile );
		break;

	    case TAGCase:
	    case TAGDefault:
		break;

	    case TAGPlain:
		doplain( e, outfile );
		break;

	    case TAGRename:
		dorename( e );
		break;

	    case TAGSet:
		doset( e );
		break;

	    case TAGGlobalSet:
		doglobalset( e );
		break;

	    case TAGReturn:
		doreturn( e );
		break;

	    case TAGDeleteType:
		dodeletetype( to_DeleteType( e ) );
		break;

	    case TAGGlobalAppend:
		doglobalappend( e );
		break;

	    case TAGAppend:
		doappend( e );
		break;

	    case TAGRedirect:
		doredirect( e );
		break;

	    case TAGAppendfile:
		doappendfile( e );
		break;

	    case TAGInclude:
		doinclude( e, outfile );
		break;

	    case TAGInsert:
		doinsert( e, outfile );
		break;

	    case TAGExit:
		doexit( e );
		break;

	    case TAGWhile:
		dowhile( e, outfile );
		break;

	    case TAGMacro:
		domacro( e );
		break;

	    case TAGCall:
		docall( e, outfile );
		break;

	}
    }
}

/******************************************************
 *    Top level of translation routines               *
 ******************************************************/

/* Given an input file 'infile' and an output file 'outfile', read
 * the template from 'infile' and write the translated version to
 * 'outfile'. Neither file is opened or closed.
 */
void translate( FILE *infile, FILE *outfile )
{
    tplelm_list tpl;
    tmcommand endcom;

    tpllineno = 0;
    tpl = readtemplate( infile, &endcom );
    if( endcom != EOFLINE ){
	unbalance( tpllineno, endcom, EOFLINE );
	return;
    }
    dotrans( tpl, outfile );
    rfre_tplelm_list( tpl );
}
