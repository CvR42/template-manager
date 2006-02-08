/* File: $Id$
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
#include "checkds.h"
#include "refex.h"
#include "srchfile.h"

/* Forward declaration */
static void internal_translate( FILE *infile, const char *filenm, FILE *outfile );

/* tags for command table */
typedef enum en_tmcommands {
    APPEND,
    APPENDFILE,
    CALL,
    CASE,
    DEFAULT,
    DELETETYPE,
    ELSE,
    ENDAPPENDFILE,
    ENDFOR,
    ENDFOREACH,
    ENDIF,
    ENDMACRO,
    ENDREDIRECT,
    ENDSWITCH,
    ENDWHILE,
    EOFLINE,		/* special line: end of file */
    ERROR,
    EXIT,
    FOR,
    FOREACH,
    GLOBALAPPEND,
    GLOBALSET,
    GLOBALSPLIT,
    IF,
    INCLUDE,
    INSERT,
    MACRO,
    REDIRECT,
    RENAME,
    RETURN,
    SET,
    SPLIT,
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
    { "endfor", ENDFOR },
    { "endforeach", ENDFOREACH },
    { "endif", ENDIF },
    { "endmacro", ENDMACRO },
    { "endredirect", ENDREDIRECT },
    { "endswitch", ENDSWITCH },
    { "endwhile", ENDWHILE },
    { "error", ERROR },
    { "exit", EXIT },
    { "for", FOR },
    { "foreach", FOREACH },
    { "globalappend", GLOBALAPPEND },
    { "globalset", GLOBALSET },
    { "globalsplit", GLOBALSPLIT },
    { "if", IF },
    { "include", INCLUDE },
    { "insert", INSERT },
    { "macro", MACRO },
    { "redirect", REDIRECT },
    { "rename", RENAME },
    { "return", RETURN },
    { "set", SET },
    { "split", SPLIT },
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
static void unbalance( const char *filenm, unsigned int firstlno, unsigned int lno, tmcommand isterm, tmcommand needterm )
{
    if( isterm == needterm ){
	return;    /* just for safety */
    }
    if( needterm == EOFLINE ){
        fileline_error( filenm, firstlno, "got `.%s', but there is nothing to terminate", comname( isterm ) );
    }
    else {
        if( isterm == EOFLINE ){
            fileline_error( filenm, firstlno, "'.%s' is not terminated", comname( needterm ) );
        }
        else {
            fileline_error( filenm, lno, "line %d requires '.%s', but this is '.%s'", firstlno, comname( needterm ), comname( isterm ) );
        }
    }
}

typedef enum en_switchstate {
    SWS_NONE, SWS_CASE, SWS_DEFAULT
} switchstate;

/* Given a list of template elements, construct a proper switch
 * from these statements, by searching for the 'case' and 'default'
 * lines.
 */
static Switch construct_switch( origin org, const char *swval, tplelm_list el )
{
    unsigned int ix;
    tplelm_list block;
    tplelm_list deflt = tplelm_listNIL;
    Switchcase_list cases;
    switchstate state = SWS_NONE;
    tmstring val = tmstringNIL;

    block = new_tplelm_list();
    cases = new_Switchcase_list();
    for( ix=0; ix<el->sz; ix++ ){
	const_tplelm e = el->arr[ix];

	switch( e->tag ){
	    case TAGCase:
	    case TAGDefault:
		switch( state ){
		    case SWS_NONE:
			if( block->sz != 0 ){
			    origin_error( block->arr[0]->org, "statements outside a case ignored" );
			    rfre_tplelm_list( block );
			    block = new_tplelm_list();
			}
			break;

		    case SWS_CASE:
			cases = append_Switchcase_list(
			    cases,
			    new_Switchcase( rdup_tmstring( val ), block )
			);
			block = new_tplelm_list();
			break;

		    case SWS_DEFAULT:
			if( deflt != tplelm_listNIL ){
			    origin_error( block->arr[0]->org, "second .default block ignored" );
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
		    val = to_const_Case(e)->val;
		}
		else {
		    state = SWS_DEFAULT;
		}
                break;

	    default:
		block = append_tplelm_list( block, rdup_tplelm( el->arr[ix] ) );
		break;
	}
    }
    rfre_tplelm_list( block );
    return new_Switch( org, rdup_tmstring( swval ), cases, deflt );
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
static tplelm_list readtemplate( FILE *f, const_tmstring filenm, tmcommand *endcom, unsigned int *lineno )
{
    char *com;
    const char *p;
    struct dotcom *cp;
    tplelm te;
    tplelm_list tel;
    tmcommand subendcom;
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
		inbuf[bufix++] = (char) c;
	    }
	}
	(*lineno)++;
	if( c == EOF && bufix == 0 ){
	    *endcom = EOFLINE;
	    TM_FREE( inbuf );
	    return tel;
	}
	else if( inbuf[0] == LCOMCHAR ){
	    if( inbuf[1] != LCOMCHAR ){
                /* Not a comment  */
                origin org = new_origin( add_tmsymbol( filenm ), *lineno );
		p = scanword( org, inbuf+1, &com );
		if( com == CHARNIL ){
		    com = new_tmstring( "" );
		}
		cp = dotcomlist;
		while( strcmp( com, cp->dotcomname ) != 0 ){
		    if( cp->dotcomname[0] == '\0' ){
			origin_error( org, "unknown dot command '%s'", com );
                        rfre_origin( org );
                        /* FIXME: that's a bit rude! */
			exit( 1 );
		    }
		    cp++;
		}
		fre_tmstring( com );

                /* cp now points to the descriptor of this command. */
		switch( cp->dotcomtag ){
		    case ELSE:
		    case ENDAPPENDFILE:
		    case ENDFOR:
		    case ENDFOREACH:
		    case ENDIF:
		    case ENDMACRO:
		    case ENDREDIRECT:
		    case ENDSWITCH:
		    case ENDWHILE:
		    case EOFLINE:
			*endcom = cp->dotcomtag;
                        rfre_origin( org );
			TM_FREE( inbuf );
			return tel;

		    case CASE:
			te = to_tplelm( new_Case( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case DEFAULT:
			te = to_tplelm( new_Default( org ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case SWITCH:
		    {
			unsigned int firstlno = *lineno;
			tplelm_list el = readtemplate( f, filenm, &subendcom, lineno );

			if( subendcom != ENDSWITCH ){
			    unbalance( filenm, firstlno, *lineno, subendcom, ENDSWITCH );
			}
			el = append_tplelm_list(
			    el,
			    to_tplelm( new_Case( 0, new_tmstring( "" ) ) )
			);
			te = to_tplelm( construct_switch( org, p, el ) );
			tel = append_tplelm_list( tel, te );
			rfre_tplelm_list( el );
			break;
		    }

		    case IF:
                    {
			unsigned int firstlno = *lineno;
			tplelm_list e1 = readtemplate( f, filenm, &subendcom, lineno );
                        tplelm_list e2;

			if( subendcom == ELSE ){
			    e2 = readtemplate( f, filenm, &subendcom, lineno );
			}
			else {
			    e2 = new_tplelm_list();
			}
			if( subendcom != ENDIF ){
			    unbalance( filenm, firstlno, *lineno, subendcom, ENDIF );
			}
			te = to_tplelm( new_If( org, new_tmstring( p ), e1, e2 ) );
			tel = append_tplelm_list( tel, te );
			break;
                    }

		    case FOREACH:
                    {
			unsigned int firstlno = *lineno;
			tplelm_list e1 = readtemplate( f, filenm, &subendcom, lineno );
			if( subendcom != ENDFOREACH ){
			    unbalance( filenm, firstlno, *lineno, subendcom, ENDFOREACH );
			}
			te = to_tplelm( new_Foreach( org, new_tmstring( p ), e1 ) );
			tel = append_tplelm_list( tel, te );
			break;
                    }

		    case FOR:
                    {
			unsigned int firstlno = *lineno;
			tplelm_list e1 = readtemplate( f, filenm, &subendcom, lineno );
			if( subendcom != ENDFOR ){
			    unbalance( filenm, firstlno, *lineno, subendcom, ENDFOR );
			}
			te = to_tplelm( new_For( org, new_tmstring( p ), e1 ) );
			tel = append_tplelm_list( tel, te );
			break;
                    }

		    case WHILE:
                    {
			unsigned int firstlno = *lineno;
			tplelm_list e1 = readtemplate( f, filenm, &subendcom, lineno );

			if( subendcom != ENDWHILE ){
			    unbalance( filenm, firstlno, *lineno, subendcom, ENDWHILE );
			}
			te = to_tplelm( new_While( org, new_tmstring( p ), e1 ) );
			tel = append_tplelm_list( tel, te );
			break;
                    }

		    case MACRO:
                    {
			unsigned int firstlno = *lineno;
			tplelm_list e1 = readtemplate( f, filenm, &subendcom, lineno );
			if( subendcom != ENDMACRO ){
			    unbalance( filenm, firstlno, *lineno, subendcom, ENDMACRO );
			}
			te = to_tplelm( new_Macro( org, new_tmstring( p ), e1 ) );
			tel = append_tplelm_list( tel, te );
			break;
                    }

		    case APPENDFILE:
                    {
			unsigned int firstlno = *lineno;
			tplelm_list e1 = readtemplate( f, filenm, &subendcom, lineno );

			if( subendcom != ENDAPPENDFILE ){
			    unbalance( filenm, firstlno, *lineno, subendcom, ENDAPPENDFILE );
			}
			te = to_tplelm( new_Appendfile( org, new_tmstring( p ), e1 ) );
			tel = append_tplelm_list( tel, te );
			break;
                    }

		    case REDIRECT:
                    {
			unsigned int firstlno = *lineno;
			tplelm_list e1 = readtemplate( f, filenm, &subendcom, lineno );

			if( subendcom != ENDREDIRECT ){
			    unbalance( filenm, firstlno, *lineno, subendcom, ENDREDIRECT );
			}
			te = to_tplelm( new_Redirect( org, new_tmstring( p ), e1 ) );
			tel = append_tplelm_list( tel, te );
			break;
                    }

		    case INSERT:
			te = to_tplelm( new_Insert( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case INCLUDE:
			te = to_tplelm( new_Include( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case RENAME:
			te = to_tplelm( new_Rename( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case SET:
			te = to_tplelm( new_Set( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case GLOBALSET:
			te = to_tplelm( new_GlobalSet( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case SPLIT:
			te = to_tplelm( new_Split( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case GLOBALSPLIT:
			te = to_tplelm( new_GlobalSplit( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case RETURN:
			te = to_tplelm( new_Return( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case DELETETYPE:
			te = to_tplelm( new_DeleteType( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case APPEND:
			te = to_tplelm( new_Append( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case GLOBALAPPEND:
			te = to_tplelm( new_GlobalAppend( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case CALL:
			te = to_tplelm( new_Call( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case EXIT:
			te = to_tplelm( new_Exit( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;

		    case ERROR:
			te = to_tplelm( new_Error( org, new_tmstring( p ) ) );
			tel = append_tplelm_list( tel, te );
			break;
		}
	    }
	}
	else {
            origin org = new_origin( add_tmsymbol( filenm ), *lineno );
	    te = to_tplelm( new_Plain( org, new_tmstring( inbuf ) ) );
	    tel = append_tplelm_list( tel, te );
	}
    }
}

/* Given a pointer to an input string 'spi', a pointer to an output string
   'spo', and a stop character 'sc', copy and evaluate the string to the
   stop character 'sc'. Update the position of '*spi' to point to the stop
   character or '\0', and return the evaluated tmstring.
 */
tmstring alevalto( const_origin org, char **spi, const int sc )
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
    croom = (unsigned int) strlen( si );
    six = 0;
    if( sevaltr ){
	if( sc == '\0' ){
	    fprintf( tracestream, "alevalto: '%s'\n", si );
	}
	else {
	    fprintf( tracestream, "alevalto: '%s' to char '%c'\n", si, sc );
	}
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
	    ans = alevalto( org, spi, CRBRAC );
	    si = *spi;
	    if( *si != CRBRAC ){
		origin_error( org, "missing close bracket '%c'", CRBRAC );
		fre_tmstring( ans );
		continue;
	    }
	    si++;
	    v = getvar( ans );
	    if( v == CHARNIL ){
		origin_error( org, "variable '%s' not found", ans );
		fre_tmstring( ans );
		continue;
	    }
	    fre_tmstring( ans );
	    len = six + (unsigned int) strlen( v ) + (unsigned int) strlen( si );
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
	    ans = alevalto( org, spi, CCBRAC );
	    si = *spi;
	    if( *si != CCBRAC ){
		origin_error( org, "missing close bracket '%c'", CCBRAC );
		fre_tmstring( ans );
		continue;
	    }
	    si++;
	    fnval = evalfn( org, ans );
	    v = fnval;
	    fre_tmstring( ans );
	    len = six + (unsigned int) strlen( fnval ) + (unsigned int) strlen( si );
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
	    ans = alevalto( org, spi, CSBRAC );
	    si = *spi;
	    if( *si != CSBRAC ){
		origin_error( org, "missing close bracket '%c'", CSBRAC );
		fre_tmstring( ans );
		continue;
	    }
	    si++;
	    fnval = evalexpr( org, ans );
	    v = fnval;
	    fre_tmstring( ans );
	    len = six + (unsigned int) strlen( fnval ) + (unsigned int) strlen( si );
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
	    origin_error( org, "variable '%s' not found", var1 );
	    continue;
	}
	len = six + (unsigned int) strlen( v ) + (unsigned int) strlen( si );
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
static void doplain( const_Plain l, FILE *outfile )
{
    tmstring is;
    tmstring os;

    is = l->line;
    os = alevalto( l->org, &is, '\0' );
    if( outfile == NULL ){
	origin_error( l->org, "no output allowed in expression macro" );
    }
    else {
	fputs( os, outfile );
	putc( '\n', outfile );
    }
    fre_tmstring( os );
}

/* Handle 'insert' command. */
static void doinsert( const_Insert tpl, FILE *outfile )
{
    tmstring fname;
    tmstring exfname;
    FILE *infile;
    tmstring is;
    tmstring os;

    is = tpl->fname;
    os = alevalto( tpl->org, &is, '\0' );
    scan1par( tpl->org, os, &fname );
    fre_tmstring( os );
    if( fname == tmstringNIL ){
	return;
    }
    exfname = search_file( searchpath, fname, PATHSEPSTR, "r" );
    if( exfname == tmstringNIL ){
	origin_error( tpl->org, "file '%s' not found", fname );
	fre_tmstring( fname );
	return;
    }
    fre_tmstring( fname );
    infile = ckfopen( exfname, "r" );
    internal_translate( infile, exfname, outfile );
    fclose( infile );
    fre_tmstring( exfname );
}

/* Handle 'redirect' command. */
static void doredirect( const_Redirect e )
{
    tmstring fname;
    FILE *outfile;
    char *is;
    char *os;

    is = e->fname;
    os = alevalto( e->org, &is, '\0' );
    scan1par( e->org, os, &fname );
    fre_tmstring( os );
    if( fname == tmstringNIL ){
	origin_error( e->org, "missing filename" );
	return;
    }
    outfile = ckfopen( fname, "w" );
    dotrans( e->body, outfile );
    fclose( outfile );
    fre_tmstring( fname );
}

/* Handle 'appendfile' command. */
static void doappendfile( const_Appendfile e )
{
    tmstring fname;
    FILE *outfile;
    char *is;
    char *os;

    is = e->fname;
    os = alevalto( e->org, &is, '\0' );
    scan1par( e->org, os, &fname );
    fre_tmstring( os );
    if( fname == tmstringNIL ){
	origin_error( e->org, "missing filename" );
	return;
    }
    outfile = ckfopen( fname, "a" );
    dotrans( e->body, outfile );
    fclose( outfile );
    fre_tmstring( fname );
}

/* Handle 'include' command. */
static void doinclude( const_Include tpl, FILE *outfile )
{
    tmstring fname;
    tmstring exfname;
    FILE *infile;
    char *is;
    char *os;

    is = tpl->fname;
    os = alevalto( tpl->org, &is, '\0' );
    scan1par( tpl->org, os, &fname );
    fre_tmstring( os );
    if( fname == tmstringNIL ){
	return;
    }
    exfname = search_file( searchpath, fname, PATHSEPSTR, "r" );
    if( exfname == tmstringNIL ){
	origin_error( tpl->org, "file '%s' not found", fname );
	fre_tmstring( fname );
	return;
    }
    infile = ckfopen( exfname, "r" );
    newvarctx();
    setvar( "templatefile", fname );
    fre_tmstring( fname );
    internal_translate( infile, exfname, outfile );
    flushvar();
    fclose( infile );
    fre_tmstring( exfname );
}

/* Handle 'error' command. */
static void doerror( const_Error tpl )
{
    char *is;
    char *os;

    is = tpl->str;
    os = alevalto( tpl->org, &is, '\0' );
    fprintf( stderr, "%s\n", os );
    fre_tmstring( os );
}

/* Handle 'exit' command. */
static void doexit( const_Exit tpl )
{
    char *is;
    char *os;

    is = tpl->str;
    os = alevalto( tpl->org, &is, '\0' );
    exit( atoi( os ) );
    /* freeing is no use */
}

/* Handle 'globalset' command. */
static void doglobalset( const_GlobalSet tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring_list sl;
    tmstring nm;

    is = tpl->line;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	origin_error( tpl->org, "no name specified" );
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
static void doset( const_Set tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring_list sl;
    tmstring nm;

    is = tpl->line;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	origin_error( tpl->org, "no name specified" );
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

/* Handle 'split' command. */
static void dosplit( const_Split tpl )
{
    tmstring val;
    tmstring_list sl;
    tmstring_list rest;
    unsigned int seppos = 0;
    unsigned int valix;
    unsigned int varix;

    char *is = tpl->line;
    char *os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );

    while( seppos<sl->sz ){
        tmstring s = sl->arr[seppos];

        if( s[0] == '=' && s[1] == '\0' ){
            break;
        }
        seppos++;
    }
    if( seppos>=sl->sz ){
	origin_error( tpl->org, ".split: no '=' found" );
	rfre_tmstring_list( sl );
	return;
    }
    if( seppos==0 ){
	origin_error( tpl->org, ".split: no variables" );
	rfre_tmstring_list( sl );
	return;
    }
    valix = seppos+1;
    varix = 0;

    while( varix+1<seppos ){
        if( valix<sl->sz ){
            setvar( sl->arr[varix], sl->arr[valix] );
            valix++;
        }
        else {
            setvar( sl->arr[varix], "" );
        }
        varix++;
    }
    sl = extractlist_tmstring_list( sl, valix, sl->sz, &rest );
    val = flatstrings( rest );
    setvar( sl->arr[varix], val );
    rfre_tmstring_list( sl );
    rfre_tmstring_list( rest );
    fre_tmstring( val );
}

/* Handle 'globalsplit' command. */
static void doglobalsplit( const_GlobalSplit tpl )
{
    tmstring val;
    tmstring_list sl;
    tmstring_list rest;
    unsigned int seppos = 0;
    unsigned int valix;
    unsigned int varix;

    char *is = tpl->line;
    char *os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );

    while( seppos<sl->sz ){
        tmstring s = sl->arr[seppos];

        if( s[0] == '=' && s[1] == '\0' ){
            break;
        }
        seppos++;
    }
    if( seppos>=sl->sz ){
	origin_error( tpl->org, ".globalsplit: no '=' found" );
	rfre_tmstring_list( sl );
	return;
    }
    if( seppos==0 ){
	origin_error( tpl->org, ".globalsplit: no variables" );
	rfre_tmstring_list( sl );
	return;
    }
    valix = seppos+1;
    varix = 0;

    while( varix+1<seppos ){
        if( valix<sl->sz ){
            globalsetvar( sl->arr[varix], sl->arr[valix] );
            valix++;
        }
        else {
            globalsetvar( sl->arr[varix], "" );
        }
        varix++;
    }
    sl = extractlist_tmstring_list( sl, valix, sl->sz, &rest );
    val = flatstrings( rest );
    globalsetvar( sl->arr[varix], val );
    rfre_tmstring_list( rest );
    rfre_tmstring_list( sl );
    fre_tmstring( val );
}

/* Given a tmsymbol 's', an old type name 'old' and a new type name 'nw'.
 * replace the symbol with a copy of 'nw'  if it is equal to 'old'.
 */
static tmsymbol rename_tmsymbol( tmsymbol s, const_tmsymbol old, tmsymbol nw )
{
    if( s == old ){
	s = nw;
    }
    return s;
}

/* Given a list of symbols, an old type name 'old' and a new
 * type name 'nw', rewrite these symbols to use the new type name
 * instead of the old type name.
 */
static tmsymbol_list rename_tmsymbol_list( tmsymbol_list dl, const_tmsymbol old, tmsymbol nw )
{
    unsigned int ix;

    for( ix=0; ix<dl->sz; ix++ ){
	dl->arr[ix] = rename_tmsymbol( dl->arr[ix], old, nw );
    }
    return dl;
}

/* Given a list of fields, an old type name 'old' and a new
 * type name 'nw', rewrite these fields to use the new type name
 * instead of the old type name.
 */
static Type rename_Type( Type t, const_tmsymbol old, tmsymbol nw )
{
    t->basetype = rename_tmsymbol( t->basetype, old, nw );
    return t;
}

/* Given a list of fields, an old type name 'old' and a new
 * type name 'nw', rewrite these fields to use the new type name
 * instead of the old type name.
 */
static Field rename_Field( Field f, const_tmsymbol old, tmsymbol nw )
{
    f->type = rename_Type( f->type, old, nw );
    return f;
}

/* Given a list of fields, an old type name 'old' and a new
 * type name 'nw', rewrite these fields to use the new type name
 * instead of the old type name.
 */
static Field_list rename_Field_list( Field_list dl, const_tmsymbol old, tmsymbol nw )
{
    unsigned int ix;

    for( ix=0; ix<dl->sz; ix++ ){
	dl->arr[ix] = rename_Field( dl->arr[ix], old, nw );
    }
    return dl;
}

/* Given a ds definition, an old type name 'old' and a new
 * type name 'nw', rewrite this definition to use the new name
 * instead of the old name.
 */
static ds rename_ds( ds d, const_tmsymbol old, tmsymbol nw )
{
    d->name->sym = rename_tmsymbol( d->name->sym, old, nw );
    d->inherits = rename_tmsymbol_list( d->inherits, old, nw );
    switch( d->tag ){
        case TAGDsInclude:
            break;

	case TAGDsConstructorBase:
	{
	    DsConstructorBase dsub = to_DsConstructorBase( d );

	    dsub->constructors = rename_tmsymbol_list( dsub->constructors, old, nw );
	    break;
	}

	case TAGDsTuple:
	{
	    DsTuple dsub = to_DsTuple( d );

	    dsub->fields = rename_Field_list( dsub->fields, old, nw );
	    break;
	}

	case TAGDsClass:
	{
	    DsClass dsub = to_DsClass( d );

	    dsub->fields = rename_Field_list( dsub->fields, old, nw );
	    break;
	}

	case TAGDsAlias:
	{
	    DsAlias dsub = to_DsAlias( d );
	    dsub->type = rename_Type( dsub->type, old, nw );
	    break;
	}

	case TAGDsConstructor:
	{
	    DsConstructor dsub = to_DsConstructor( d );

	    dsub->fields = rename_Field_list( dsub->fields, old, nw );
	    break;
	}

    }
    return d;
}

/* Given a list of ds definitions, an old type name 'old' and a new
 * type name 'nw', rewrite these definitions to use the new name
 * instead of the old name.
 */
static ds_list rename_ds_list( ds_list dl, const_tmsymbol old, tmsymbol nw )
{
    unsigned int ix;

    for( ix=0; ix<dl->sz; ix++ ){
	dl->arr[ix] = rename_ds( dl->arr[ix], old, nw );
    }
    return zap_memoized_inheritors( dl );
}

/* Handle 'rename' command. */
static void dorename( const_Rename tpl )
{
    char *is;
    char *os;
    tmstring_list sl;

    is = tpl->line;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    rfre_tmstring( os );
    if( sl->sz != 2 ){
	origin_error( tpl->org, "rename requires exactly two parameters" );
	rfre_tmstring_list( sl );
	return;
    }
    allds = rename_ds_list( allds, add_tmsymbol( sl->arr[0] ), add_tmsymbol( sl->arr[1] ) );
    if( !check_ds_list( allds ) ){
	origin_error( tpl->org, "The problems were caused by .rename of `%s' to `%s'", sl->arr[0], sl->arr[1] );
	exit( 1 );
    }
    rfre_tmstring_list( sl );
}

/* Handle 'return' command. */
static void doreturn( const_Return tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring_list sl;

    is = tpl->retval;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );
    val = flatstrings( sl );
    rfre_tmstring_list( sl );
    setvar( RETVALNAME, val );
    fre_tmstring( val );
}

/* Handle 'append' command. */
static void doappend( const_Append tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring nm;
    tmstring_list sl;

    is = tpl->line;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	origin_error( tpl->org, "no name specified" );
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
static void doglobalappend( const_GlobalAppend tpl )
{
    char *is;
    char *os;
    tmstring val;
    tmstring nm;
    tmstring_list sl;

    is = tpl->line;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	origin_error( tpl->org, "no name specified" );
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
static ds_list delete_type( ds_list types, const_tmstring nm )
{
    unsigned int ix = find_type_ix( types, add_tmsymbol( nm ) );

    if( ix>=types->sz ){
	return types;
    }
    return delete_ds_list( types, ix );
}

/* Handle 'deletetype' command. */
static void dodeletetype( const_DeleteType tpl )
{
    char *is;
    char *os;
    tmstring_list sl;
    unsigned int ix;

    is = tpl->line;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );
    for( ix=0; ix<sl->sz; ix++ ){
	allds = delete_type( allds, sl->arr[ix] );
    }
    rfre_tmstring_list( sl );
}

/* Handle 'if' command. */
static void doif( const_If tpl, FILE *outfile )
{
    char *is;
    char *os;
    bool cond;

    is = tpl->cond;
    os = alevalto( tpl->org, &is, '\0' );
    cond = istruestr( os );
    fre_tmstring( os );
    if( cond ){
	dotrans( tpl->ifthen, outfile );
    }
    else {
	dotrans( tpl->ifelse, outfile );
    }
}

static bool matches_tmstring( const_origin org, const_tmstring word, const_tmstring pattern )
{
    const char *errm = ref_comp( pattern );
    if( errm != NULL ){
        origin_error( org, "bad regular expression: %s", errm );
        return FALSE;
    }
    return ref_exec( word );
}

static bool matches_tmstring_list( const_origin org, const_tmstring word, const_tmstring_list patterns )
{
    unsigned int i;

    for( i=0; i<patterns->sz; i++ ){
        if( matches_tmstring( org, word, patterns->arr[i] ) ){
            return TRUE;
        }
    }
    return FALSE;
}

/* Handle 'switch' command. */
static void doswitch( const_Switch tpl, FILE *outfile )
{
    char *is;
    char *os;
    bool visited = FALSE;
    tmstring_list sl;
    unsigned int ix;
    const_Switchcase_list cases;

    is = tpl->val;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );
    if( sl->sz != 1 ){
	if( sl->sz == 0 ){
            origin_error( tpl->org, "A switch command requires exactly one parameter, but this one has no parameters" );
	}
	else {
            origin_error( tpl->org, "A switch command requires exactly one parameter, but this one has %u parameters", sl->sz );
	}
	rfre_tmstring_list( sl );
	return;
    }
    cases = tpl->cases;
    for( ix=0; ix<cases->sz; ix++ ){
	char *caseval = cases->arr[ix]->cases;
	tmstring sentence;
	tmstring_list words;

	sentence = alevalto( tpl->org, &caseval, '\0' );
	words = chopstring( tpl->org, sentence );
	rfre_tmstring( sentence );
	if( matches_tmstring_list( tpl->org, sl->arr[0], words ) ){
	    /* We've got a match. */
	    dotrans( cases->arr[ix]->action, outfile );
	    visited = TRUE;
	}
	rfre_tmstring_list( words );
    }
    if( !visited ){
        /* None of the cases matched; we need to do the default. */
	if( tpl->deflt == tplelm_listNIL ){
	    origin_error( tpl->org, "no case matches value '%s', and there is no .default", sl->arr[0] );
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
static void doforeach( const_Foreach tpl, FILE *outfile )
{
    char *nm;
    char *is;
    char *os;
    unsigned int ix;
    tmstring_list sl;

    is = tpl->felist;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	origin_error( tpl->org, "no name specified" );
	rfre_tmstring_list( sl );
	return;
    }
    nm = sl->arr[0];
    for( ix=1; ix<sl->sz; ix++ ){
	setvar( nm, sl->arr[ix] );
	dotrans( tpl->body, outfile );
    }
    rfre_tmstring_list( sl );
}

/* Handle 'for' command.
   Given a list of template lines, starting with a foreach command line,
   generate output lines. Handle local commands by recursion.
 */
static void dofor( const_For tpl, FILE *outfile )
{
    char *nm;
    char *is;
    char *os;
    tmstring_list sl;
    int start;
    int end;
    int stride = 1;
    int v;

    is = tpl->parms;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );
    if( sl->sz<3 ){
	origin_error( tpl->org, "too few parameter for `for' command" );
	rfre_tmstring_list( sl );
	return;
    }
    if( sl->sz>4 ){
	origin_error( tpl->org, "too many parameter for `for' command" );
	rfre_tmstring_list( sl );
	return;
    }
    (void) cknumpar( tpl->org, sl->arr[1] );	/* start */
    start = atoi( sl->arr[1] );
    (void) cknumpar( tpl->org, sl->arr[2] );	/* end */
    end = atoi( sl->arr[2] );
    if( sl->sz == 4 ){
	(void) cknumpar( tpl->org, sl->arr[3] );	/* stride */
	stride = atoi( sl->arr[3] );
	if( stride<1 ){
	    origin_error( tpl->org, "stride cannot be negative or zero" );
	    rfre_tmstring_list( sl );
	    return;
	}
    }
    nm = sl->arr[0];
    for( v=start; v<end; v += stride ){
	char vstr[50];

	sprintf( vstr, "%d", v );
	setvar( nm, vstr );	/* Set the iteration variable. */
	dotrans( tpl->body, outfile );
    }
    rfre_tmstring_list( sl );
}

/* Handle 'while' command.
   Given a list of template lines, starting with a while command line,
   generate output lines until condition is false. Handle local commands
   by recursion.
 */
static void dowhile( const_While tpl, FILE *outfile )
{
    for(;;){
        bool done;
        char *is;
        char *os;

	is = tpl->cond;
	os = alevalto( tpl->org, &is, '\0' );
	done = isfalsestr( os );
	fre_tmstring( os );
	if( done ){
	    return;
	}
	dotrans( tpl->body, outfile );
    }
}

/* Handle a 'macro' command: break the parameter list up
 * in separate words, copy the macro body, and store it in the
 * macro table.
 */
static void domacro( const_Macro tpl )
{
    char *nm;
    char *is;
    char *os;
    tmstring_list sl;

    is = tpl->formals;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );
    if( sl->sz<1 ){
	origin_error( tpl->org, "no macro name specified" );
	rfre_tmstring_list( sl );
	return;
    }
    nm = rdup_tmstring( sl->arr[0] );
    sl = delete_tmstring_list( sl, 0 );
    setmacro( nm, tpl->org, sl, tpl->body );
    rfre_tmstring( nm );
    rfre_tmstring_list( sl );
}

/* Handle 'call' command (calls a macro). */
static void docall( const_Call tpl, FILE *outfile )
{
    char *is;
    char *os;
    tmstring_list sl;
    tmstring nm;
    tmstring_list fpl;
    unsigned int ix;
    const_macro m;
    int valid;

    is = tpl->line;
    os = alevalto( tpl->org, &is, '\0' );
    sl = chopstring( tpl->org, os );
    fre_tmstring( os );
    sl = extract_tmstring_list( sl, 0, &nm, &valid );
    if( !valid ){
	origin_error( tpl->org, "no macro name given" );
	rfre_tmstring_list( sl );
	return;
    }
    m = findmacro( nm );
    if( m == macroNIL ){
	origin_error( tpl->org, "macro '%s' does not exist", nm );
	rfre_tmstring_list( sl );
	rfre_tmstring( nm );
	return;
    }
    fpl = m->fpl;
    rfre_tmstring( nm );
    if( fpl->sz != sl->sz ){
	origin_error(
            tpl->org,
            "wrong number of parameters for macro '%s': %u instead of %u",
	    m->name,
	    sl->sz,
	    fpl->sz
        );
	rfre_tmstring_list( sl );
	return;
    }
    newvarctx();
    setvar( "templatefile", m->org->file->name );
    for( ix=0; ix<sl->sz; ix++ ){
	setvar( fpl->arr[ix], sl->arr[ix] );
    }
    dotrans( m->body, outfile );
    flushvar();
    rfre_tmstring_list( sl );
}

/* Recursive translation routine.
   Given a list of template lines in 'tpl' generate text from them,
   and write this text to 'outfile'.
 */
void dotrans( const_tplelm_list tpl, FILE *outfile )
{
    unsigned int ix;

    for( ix=0; ix<tpl->sz; ix++ ){
        const_tplelm e = tpl->arr[ix];

	switch( e->tag ){
	    case TAGError:
		doerror( to_const_Error( e ) );
		break;

	    case TAGForeach:
		doforeach( to_const_Foreach( e ), outfile );
		break;

	    case TAGFor:
		dofor( to_const_For( e ), outfile );
		break;

	    case TAGIf:
		doif( to_const_If( e ), outfile );
		break;

	    case TAGSwitch:
		doswitch( to_const_Switch(e), outfile );
		break;

	    case TAGCase:
	    case TAGDefault:
		break;

	    case TAGPlain:
		doplain( to_const_Plain( e ), outfile );
		break;

	    case TAGRename:
		dorename( to_const_Rename( e ) );
		break;

	    case TAGSet:
		doset( to_const_Set( e ) );
		break;

	    case TAGGlobalSet:
		doglobalset( to_const_GlobalSet( e ) );
		break;

	    case TAGSplit:
		dosplit( to_const_Split( e ) );
		break;

	    case TAGGlobalSplit:
		doglobalsplit( to_const_GlobalSplit( e ) );
		break;

	    case TAGReturn:
		doreturn( to_const_Return( e ) );
		break;

	    case TAGDeleteType:
		dodeletetype( to_const_DeleteType( e ) );
		break;

	    case TAGGlobalAppend:
		doglobalappend( to_const_GlobalAppend( e ) );
		break;

	    case TAGAppend:
		doappend( to_const_Append( e ) );
		break;

	    case TAGRedirect:
		doredirect( to_const_Redirect( e ) );
		break;

	    case TAGAppendfile:
		doappendfile( to_const_Appendfile( e ) );
		break;

	    case TAGInclude:
		doinclude( to_const_Include( e ), outfile );
		break;

	    case TAGInsert:
		doinsert( to_const_Insert( e ), outfile );
		break;

	    case TAGExit:
		doexit( to_const_Exit( e ) );
		break;

	    case TAGWhile:
		dowhile( to_const_While( e ), outfile );
		break;

	    case TAGMacro:
		domacro( to_const_Macro( e ) );
		break;

	    case TAGCall:
		docall( to_const_Call( e ), outfile );
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
static void internal_translate( FILE *infile, const char *filenm, FILE *outfile )
{
    tplelm_list tpl;
    tmcommand endcom;
    unsigned int lineno = 0;

    tpl = readtemplate( infile, filenm, &endcom, &lineno );
    if( endcom != EOFLINE ){
	unbalance( filenm, lineno, lineno, endcom, EOFLINE );
	return;
    }
    dotrans( tpl, outfile );
    rfre_tplelm_list( tpl );
}

void translate( FILE *infile, const char *filenm, FILE *outfile )
{
    internal_translate( infile, filenm, outfile );
    errcheck();
}
