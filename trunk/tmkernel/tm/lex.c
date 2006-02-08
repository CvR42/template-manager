/* File: $Id$
 *
 * Lexical analyzer for Tm datastructure definitions.
 */

#include "config.h"
#include <ctype.h>
#include <tmc.h>

#include "tmdefs.h"
#include "tmcode.h"
#include "tmstring.h"
#include "error.h"
#include "global.h"
#include "lex.h"
#include "misc.h"

YYSTYPE yylval;

#if 1
#define lexshow(tok,nm) if(lextr) fprintf(tracestream,"token: %s(%d) yytext=\"%s\".\n",nm,tok,yytext)
#else
#define lexshow(tok,nm)
#endif

static char yytext[256];
static char linebuf[LINESIZE] = "";
static unsigned int lineix = 0;
static unsigned int oldlineix = 0;
static unsigned int lexlineno = 0;
static tmstring lexfilename = tmstringNIL;
static FILE *lexfile;	/* file to read from. */
static bool lextr = FALSE;

/******************************************************
 *            SCANNING TREES                          *
 ******************************************************/

/* Scanning trees are used to recogize separator tokens.
   They form a linked list of possible acceptable characters.
   Each node may have a sub-list of possible extensions
   and an the token value for the current match.
 */

struct sctnode {
    struct sctnode *next;	/* next possibility in list */
    int sctchar;		/* char to match            */
    struct sctnode *sub;	/* subtree to use on match. */
    bool valid;			/* is acceptable token?     */
    lextok tokval;		/* token value for yacc     */
    const char *toknm;		/* token name for debugging */
};

#define SCTNIL (struct sctnode *)0

static long newsctnodecnt;
static long fresctnodecnt;

static struct sctnode *toktree;

/* Create a new scan tree node to match character 'c'. The next character
   to be considered is described by node 'nxt'. The subtree is set empty,
   and token is set invalid.
 */
static struct sctnode *newsctnode( struct sctnode *nxt, int c )
{
    struct sctnode *nw;

    nw = TM_MALLOC( struct sctnode *, sizeof( struct sctnode ) );
    newsctnodecnt++;
    nw->next    = nxt;
    nw->sctchar = c;
    nw->sub     = SCTNIL;
    nw->valid   = FALSE;
    return nw;
}

/* Recursively free scan tree node 'n'. */
static void rfre_sctnode( struct sctnode *n )
{
    if( n == SCTNIL ){
	return;
    }
    rfre_sctnode( n->next );
    rfre_sctnode( n->sub );
    TM_FREE( n );
    fresctnodecnt++;
}

/* Add to the scan tree 'tree' a new token with string 'str',
   YACC value 'val' and (debugging) name 'nm'.
   Return a pointer to the modified tree.
 */
static struct sctnode *addtok(
    struct sctnode *tree,
    const char *str,
    lextok val,
    const char *nm
)
{
    struct sctnode *tp;

    for( tp=tree; tp!=SCTNIL; tp=tp->next ){
	if( tp->sctchar == str[0] ) break;
    }
    if( tp == SCTNIL ){
	tree = newsctnode( tree, str[0] );
	tp = tree;
    }
    if( str[1] == '\0' ){
	tp->valid = TRUE;
	tp->tokval= val;
	tp->toknm = nm;
    }
    else{
	tp->sub = addtok( tp->sub, &str[1], val, nm );
    }
    return tree;
}

/******************************************************
 *            TOKEN AND RESERVED WORD TABLES          *
 ******************************************************/

/* A structure to describe tokens and reserved words */
struct tok {
    const char *tokstr;		/* the string to match. */
    lextok tokval;		/* associated token value for yacc */
    const char *toknm;		/* name for debugging */
};

#define TOKNIL (struct tok *) 0;

/* A table of tokens. Is terminated by an entry with empty string. */
static struct tok toktab[] =
{
    { "(", LRBRAC, "LRBRAC" },
    { "+", PLUS, "PLUS" },
    { ")", RRBRAC, "RRBRAC" },
    { ",", COMMA, "COMMA" },
    { ":", COLON, "COLON" },
    { "::=", COLCOLEQ, "COLCOLEQ" },
    { ";", SEMI, "SEMI" },
    { "==", EQEQ, "EQEQ" },
    { "->", ARROW, "ARROW" },
    { "=", EQ, "EQ" },
    { "~=", TILDEQ, "TILDEQ" },
    { "{", LCBRAC, "LCBRAC" },
    { "}", RCBRAC, "RCBRAC" },
    { "[", LSBRAC, "LSBRAC" },
    { "]", RSBRAC, "RSBRAC" },
    { "|", BAR, "BAR" },
    { "%include", INCLUDE, "INCLUDE" },
    { NULL, NONE, "" }
};

/* A table of reserved words: symbols that have a special meaning.
   Is terminated by an entry with NULL string.
 */

static struct tok rwtab[] =
{
    { NULL, NONE, "" }
};

/******************************************************
 *            File management                         *
 ******************************************************/

#define UNGETBUFLENSTEP 10

/* variables for a dynamic unget buffer:
 * length, pointer to buffer and index of next char to un-get.
 */
static unsigned int ungetbuflen;
static int *ungetbuf;
static unsigned int ungetbufix;

/* Push back character 'c' in local pushback queue.
 * Enlarge queue if necessary.
 */
static void lexungetc( int c )
{
    if( lineix>0 ){
	lineix--;
	return;
    }
    if( ungetbufix >= ungetbuflen ){
	ungetbuflen+=UNGETBUFLENSTEP;
	ungetbuf = TM_REALLOC( int *, ungetbuf, ungetbuflen*sizeof(int) );
    }
    ungetbuf[ungetbufix++] = c;
}

/* Get a character from input stream or pushback queue. */
static int lexgetc( void )
{
    int c;

    if( ungetbufix != 0 ){
	c = ungetbuf[--ungetbufix];
    }
    else {
	if( linebuf[lineix] == '\0' ){
	    if( fgets( linebuf, LINESIZE, lexfile ) == NULL ){
		return EOF;
	    }
	    lineix = 0;
	    oldlineix = 0;
	}
	return linebuf[lineix++];
    }
    return c;
}

/* Return a new origin descriptor. */
origin make_origin()
{
    return new_origin( add_tmsymbol( lexfilename ), lexlineno );
}

static void show_parse_context( FILE *f )
{
    unsigned int ix;
    bool shown = FALSE;

    fputs( linebuf, f );
    if( oldlineix>lineix ){
	oldlineix = lineix;
    }
    for( ix=0; ix<oldlineix; ix++ ){
	if( linebuf[ix] == '\t' ){
	    fputc( '\t', f );
	}
	else {
	    fputc( ' ', f );
	}
    }
    for( ix=ix; ix<lineix; ix++ ){
	fputc( '^', f );
	shown = TRUE;
    }
    if( !shown ){
	fputc( '^', f );
    }
    fputc( '\n', f );
}

void parserror( const char *message )
{
    fileline_error( lexfilename, lexlineno, message );
    show_parse_context( stderr );
}

/* Try to read a string. Return TRUE if this is successful, and set '*s'
   to point to that string, else return FALSE. A string may contain escape
   sequences with a '\\', but no newlines. The '"' around
   the string are stripped.
 */
static bool scan_string( tmstring *s )
{
    int c;
    bool done;
    tmstring bufp;
    unsigned int ix;
    unsigned int sz;

    c = lexgetc();
    if( c != '"' ){
	lexungetc( c );
	return FALSE;
    }
    ix = 0;
    sz = 5;	/* Initial guess for a reasonable string size. */
    bufp = create_tmstring( sz );
    bufp[0] = '\0';
    done = FALSE;
    while( !done ){
	if( ix>= sz ){
	    sz += 2+sz;
	    bufp = realloc_tmstring( bufp, sz );
	}
	c = lexgetc();
	if (c == '\n' ){
	    parserror( "End of line in string" );
	    done = TRUE;
	}
	if( c == '"' ){
	    done = TRUE;
	}
	if( c == '\\' ){
	    c = lexgetc();
	    switch( c ){
		case 'b': c = '\b'; break;
		case 'f': c = '\f'; break;
		case 'n': c = '\n'; break;
		case 'r': c = '\r'; break;
		case 't': c = '\t'; break;
		default: break;
	    }
	}
	if( !done ){
	    bufp[ix++] = c;
	}
    }
    bufp[ix] = '\0';
    *s = bufp;
    return TRUE;
}

/* Try to read characters from 'lexgetc()' to match one of the tokens from the
   table 'toktab' in the string 'buf'. The token characters to match are given 
   by the scan tree 'tree'.
   Fill '*tokval' with the token value, and '*toknm' with the name
   of the token. Return TRUE if this is successful, else return FALSE.
 */
static bool scan_token(
    const struct sctnode *tree,
    char *buf,
    lextok *tokval,
    const char **toknm
)
{
    int c;
    const struct sctnode *tp;

    c = lexgetc();
    if( c == EOF ){
	return FALSE;
    }
    for( tp=tree; tp!=SCTNIL; tp=tp->next ){
	if( tp->sctchar == c ) break;
    }
    if( tp == SCTNIL ){
	lexungetc( c );
	return FALSE;
    }
    buf[0] = (char) c;
    if( scan_token( tp->sub, &buf[1], tokval, toknm ) ){
	return TRUE;
    }
    if( tp->valid ){
	*tokval = tp->tokval;
	*toknm = tp->toknm;
	buf[1] = '\0';
	return TRUE;
    }
    lexungetc( c );
    return FALSE;
}

/* Try to read a symbol in the string 'buf' using lexgetc(). Return TRUE if
   this is successful, else return FALSE.
   A symbol is of the form [a-zA-Z_][a-zA-Z0-9_]*.
 */
static bool scan_symbol( char *buf )
{
    int c;

    c = lexgetc();
    if( !isalpha( c ) && c != '_' ){
	lexungetc( c );
	return FALSE;
    }
    do{
	*buf++ = (char) c;
	c = lexgetc();
    } while( isalnum( c ) || c == '_' );
    *buf = '\0';
    lexungetc( c );
    return TRUE;
}

/* "||" encountered, skip characters until end of line. */
static void skipcomment( void )
{
    int c;

    c = lexgetc();
    while( c != '\n' && c != EOF ){
	c = lexgetc();
    }
    lexlineno++;
}

/* Return next token from lex input file. Set 'yytext' to the characters
 * of the next token, and 'yylval' to the associated value of the token.
 */
lextok yylex( void )
{
    int c;
    const char *toknm;
    lextok tokval;

again:
    c = lexgetc();
    if( c == '|' ){
	c = lexgetc();
	if( c == '|' ){
	    skipcomment();
	    goto again;
	}
	lexungetc( c );
	c = '|';
    }
    if( c == '\n' ){
	lexlineno++;
	goto again;
    }
    if( isspace( c ) ) goto again;
    if( c == EOF ){
	yytext[0] = '\0';
	oldlineix = lineix;
	lexshow(EOF,"EOF");
	return LEXEOF;
    }
    lexungetc( c );
    oldlineix = lineix;
    if( scan_string( &yylval.parstring ) ){
	return STRING;
    }
    if( scan_symbol( yytext ) ){
	struct tok *rwp;

	for( rwp = rwtab; rwp->tokstr != NULL; rwp++ ){
	    if( strcmp( rwp->tokstr, yytext ) == 0 ){
		lexshow(rwp->tokval,rwp->toknm);
		return rwp->tokval;
	    }
	}
	yylval.parsymbol = add_tmsymbol( yytext );
	lexshow( NAME, "NAME" );
	return NAME;
    }
    if( scan_token( toktree, yytext, &tokval, &toknm ) ){
	lexshow( tokval, toknm );
	return tokval;
    }
    c = lexgetc();
    parserror( "bad token" );
    return NONE;
}

/* Initialize lexical analysis routines. */
void init_lex( void )
{
    struct tok *ttp;

    newsctnodecnt = 0;
    fresctnodecnt = 0;
    ungetbuflen = 2;	/* Don't make this 0, some mallocs don't like it */
    ungetbuf = TM_MALLOC( int *, ungetbuflen*sizeof(int) );
    ungetbufix = 0;
    toktree = SCTNIL;
    for( ttp = toktab; ttp->tokstr != NULL; ttp++ ){
	toktree = addtok( toktree, ttp->tokstr, ttp->tokval, ttp->toknm );
    }
}

/* Specify that lex routines should read from file 'f'. This file has
 * name 'nm'.
 */
void set_lexfile( FILE *f, const char *nm )
{
    lexfile = f;
    if( lexfilename != tmstringNIL ){
        rfre_tmstring( lexfilename );
    }
    lexfilename = new_tmstring( nm );
    lexlineno = 1;
}

void set_lex_debugging( tmbool flag )
{
    lextr = flag;
}

/* Terminate lexcial analysis routines. Free all allocated memory. */
void end_lex( void )
{
    rfre_sctnode( toktree );
    toktree = SCTNIL;
    TM_FREE( ungetbuf );
    ungetbuflen = 0;
    ungetbufix = 0;
}

/* Give allocation statistics of lex routines. */
void stat_lex( FILE *f )
{
    fprintf( f, "ungetbuflen=%d\n", ungetbuflen );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"sctnode",
	newsctnodecnt,
	newsctnodecnt,
	((newsctnodecnt==fresctnodecnt)? "": "<-")
    );
}
