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

/* tags for command table */
typedef enum en_tmcommands {
    APPEND,
    CALL,
    ELSE,
    ENDFOREACH,
    ENDIF,
    ENDMACRO,
    ENDREDIRECT,
    ENDWHILE,
    EOFLINE,		/* special line: end of file */
    ERROR,
    EXIT,
    FOREACH,
    IF,
    INCLUDE,
    INSERT,
    MACRO,
    REDIRECT,
    RETURN,
    SET,
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
    { "call", CALL },
    { "else", ELSE },
    { "endforeach", ENDFOREACH },
    { "endif", ENDIF },
    { "endmacro", ENDMACRO },
    { "endredirect", ENDREDIRECT },
    { "endwhile", ENDWHILE },
    { "error", ERROR },
    { "exit", EXIT },
    { "foreach", FOREACH },
    { "if", IF },
    { "include", INCLUDE },
    { "insert", INSERT },
    { "macro", MACRO },
    { "redirect", REDIRECT },
    { "return", RETURN },
    { "set", SET },
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

/* Given a file 'f' and a pointer to an int 'endcom', read all lines from
   file 'f' up to the next unbalanced end command and put them in template
   elements. End commands are:
      <eof>
      .else
      .endforeach
      .endredirect
      .endif
      .endmacro
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
		    case ENDFOREACH:
		    case ENDIF:
		    case ENDMACRO:
		    case ENDREDIRECT:
		    case ENDWHILE:
		    case EOFLINE:
			*endcom = cp->dotcomtag;
			TM_FREE( inbuf );
			return tel;

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
			te = new_If( firstlno, new_tmstring( p ), e1, e2 );
			tel = append_tplelm_list( tel, te );
			break;

		    case FOREACH:
			firstlno = tpllineno;
			e1 = readtemplate( f, &subendcom );
			if( subendcom != ENDFOREACH ){
			    unbalance( firstlno, subendcom, ENDFOREACH );
			}
			te = new_Foreach( firstlno, new_tmstring( p ), e1 );
			tel = append_tplelm_list( tel, te );
			break;

		    case WHILE:
			firstlno = tpllineno;
			e1 = readtemplate( f, &subendcom );
			if( subendcom != ENDWHILE ){
			    unbalance( firstlno, subendcom, ENDWHILE );
			}
			te = new_While( firstlno, new_tmstring( p ), e1 );
			tel = append_tplelm_list( tel, te );
			break;

		    case MACRO:
			firstlno = tpllineno;
			e1 = readtemplate( f, &subendcom );
			if( subendcom != ENDMACRO ){
			    unbalance( firstlno, subendcom, ENDMACRO );
			}
			te = new_Macro( firstlno, new_tmstring( p ), e1 );
			tel = append_tplelm_list( tel, te );
			break;

		    case REDIRECT:
			firstlno = tpllineno;
			e1 = readtemplate( f, &subendcom );
			if( subendcom != ENDREDIRECT ){
			    unbalance( firstlno, subendcom, ENDREDIRECT );
			}
			te = new_Redirect( firstlno, new_tmstring( p ), e1 );
			tel = append_tplelm_list( tel, te );
			break;

		    case INSERT:
			te = new_Insert( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case INCLUDE:
			te = new_Include( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case SET:
			te = new_Set( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case RETURN:
			te = new_Return( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case APPEND:
			te = new_Append( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case CALL:
			te = new_Call( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case EXIT:
			te = new_Exit( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case ERROR:
			te = new_Error( tpllineno, new_tmstring( p ) );
			tel = append_tplelm_list( tel, te );
			break;
		}
	    }
	}
	else {
	    te = new_Plain( tpllineno, new_tmstring( inbuf ) );
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
tmstring alevalto( char **spi, const char sc )
{
    tmstring si;
    tmstring cp;			/* pointer to constructed tmstring */
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

    tpllineno = l->Plain.lno;
    is = l->Plain.plainline;
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

    tpllineno = tpl->Insert.lno;
    is = tpl->Insert.fname;
    os = alevalto( &is, '\0' );
    scan1par( os, &fname );
    fre_tmstring( os );
    if( fname == CHARNIL ){
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

    tpllineno = e->Redirect.lno;
    is = e->Redirect.fname;
    os = alevalto( &is, '\0' );
    scan1par( os, &fname );
    fre_tmstring( os );
    if( fname == tmstringNIL ){
	line_error( "missing filename" );
	return;
    }
    outfile = ckfopen( fname, "w" );
    dotrans( e->Redirect.body, outfile );
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

    tpllineno = tpl->Include.lno;
    is = tpl->Include.fname;
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
    newvarctx();
    setvar( "templatefile", fname );
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

    tpllineno = tpl->Error.lno;
    is = tpl->Error.errstr;
    os = alevalto( &is, '\0' );
    fprintf( stderr, "%s\n", os );
    fre_tmstring( os );
}

/* Handle 'exit' command. */
static void doexit( const tplelm tpl )
{
    char *is;
    char *os;

    tpllineno = tpl->Exit.lno;
    is = tpl->Exit.str;
    os = alevalto( &is, '\0' );
    exit( atoi( os ) );
    /* freeing is no use */
}

/* Handle 'set' command. */
static void doset( const tplelm tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring_list sl;
    tmstring nm;

    tpllineno = tpl->Set.lno;
    is = tpl->Set.setline;
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

/* Handle 'return' command. */
static void doreturn( const tplelm tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring_list sl;

    tpllineno = tpl->Return.lno;
    is = tpl->Return.retval;
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

    tpllineno = tpl->Append.lno;
    is = tpl->Append.appline;
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
    if( val != tmstringNIL ){
	sl = insert_tmstring_list( sl, 0, rdup_tmstring( val ) );
    }
    val = flatstrings( sl );
    rfre_tmstring_list( sl );
    setvar( nm, val );
    fre_tmstring( val );
    fre_tmstring( nm );
}

/* Handle 'if' command. */
static void doif( const tplelm tpl, FILE *outfile )
{
    char *is;
    char *os;
    bool cond;

    tpllineno = tpl->If.lno;
    is = tpl->If.ifcond;
    os = alevalto( &is, '\0' );
    cond = istruestr( os );
    fre_tmstring( os );
    if( cond ){
	dotrans( tpl->If.ifthen, outfile );
    }
    else {
	dotrans( tpl->If.ifelse, outfile );
    }
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

    tpllineno = tpl->Foreach.lno;
    is = tpl->Foreach.felist;
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
	dotrans( tpl->Foreach.felines, outfile );
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

    tpllineno = tpl->While.lno;
    while( TRUE ){
	is = tpl->While.whilecond;
	os = alevalto( &is, '\0' );
	done = isfalsestr( os );
	fre_tmstring( os );
	if( done ) return;
	dotrans( tpl->While.whilelines, outfile );
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

    tpllineno = tpl->Macro.lno;
    is = tpl->Macro.formpar;
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
    setmacro( nm, tplfilename, sl, tpl->Macro.macbody );
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

    tpllineno = tpl->Call.lno;
    is = tpl->Call.callline;
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

	    case TAGPlain:
		doplain( e, outfile );
		break;

	    case TAGSet:
		doset( e );
		break;

	    case TAGReturn:
		doreturn( e );
		break;

	    case TAGAppend:
		doappend( e );
		break;

	    case TAGRedirect:
		doredirect( e );
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

	    default:
		(void) sprintf( errarg, "%d", e->tag );
		crash( "bad tag" );
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
    tplelm_list template;
    tmcommand endcom;

    tpllineno = 0;
    template = readtemplate( infile, &endcom );
    if( endcom != EOFLINE ){
	unbalance( tpllineno, endcom, EOFLINE );
	return;
    }
    dotrans( template, outfile );
    rfre_tplelm_list( template );
}
