/* File: $Id$
 *
 * Handler for optimized printing of datastructures.
 *
 * Note that this file uses the version of the string manipulation routines
 * without lognew administration, since this is trusted code.
 */

#include "config.h"
#include <ctype.h>
#include "tmc.h"

#define FATAL(msg) tm_fatal( __FILE__, __LINE__, msg )
#define FATALTAG(tag) tm_badtag( __FILE__, __LINE__, (int) (tag) );

/* datastructures */
typedef struct str_Sstack *Sstack;
typedef struct str_sunit *sunit;
typedef struct str_SuWord *SuWord;
typedef struct str_SuCons *SuCons;
typedef struct str_SuList *SuList;
typedef struct str_SuTuple *SuTuple;

#define SstackNIL (Sstack)0
#define sunitNIL (sunit)0
#define SuWordNIL (SuWord)0
#define SuConsNIL (SuCons)0
#define SuListNIL (SuList)0

/* possible tags for sunit: */
#define TAGSuWord 1
#define TAGSuCons 2
#define TAGSuList 3
#define TAGSuTuple 4

struct str_SuWord {
    /*@null@*/ sunit next;
    int tag;
    tmstring word;
};

struct str_SuCons {
    /*@null@*/ sunit next;
    int tag;
    /*@null@*/ sunit ulist;
};

struct str_SuList {
    /*@null@*/ sunit next;
    int tag;
    /*@null@*/ sunit ulist;
};

struct str_SuTuple {
    /*@null@*/ sunit next;
    int tag;
    /*@null@*/ sunit ulist;
};

/* Forwared declaraties. */
static void rfresunit_list( /*@null@*/ /*@only@*/ sunit e );
static void vertprintsunit( /*@temp@*/ TMPRINTSTATE *st, sunit l, int lev );

/*******************************************************************
 *    Allocation routines                                          *
 *******************************************************************/

static Sstack newSstack( /*@only@*/ /*@null@*/ sunit par_ulist, /*@null@*/ /*@only@*/ Sstack next )
{
    struct str_Sstack *nw = TM_MALLOC( Sstack, sizeof( Sstack ) );

    nw->ulist = par_ulist;
    nw->next = next;
    return nw;
}

static sunit newSuWord( /*@null@*/ /*@only@*/ tmstring par_word )
{
    SuWord nw;

    nw = TM_MALLOC( SuWord, sizeof( *nw ) );
    nw->next = sunitNIL;
    nw->tag = TAGSuWord;
    nw->word = par_word;
    return (sunit) nw;
}

static sunit newSuCons( /*@null@*/ /*@only@*/ sunit par_ulist )
{
    SuCons nw;

    nw = TM_MALLOC( SuCons, sizeof( *nw ) );
    nw->next = sunitNIL;
    nw->tag = TAGSuCons;
    nw->ulist = par_ulist;
    return (sunit) nw;
}

static sunit newSuList( /*@null@*/ /*@only@*/ sunit par_ulist )
{
    SuList nw;

    nw = TM_MALLOC( SuList, sizeof( *nw )  );
    nw->next = sunitNIL;
    nw->tag = TAGSuList;
    nw->ulist = par_ulist;
    return (sunit) nw;
}

static sunit newSuTuple( /*@null@*/ /*@only@*/ sunit par_ulist )
{
    SuTuple nw;

    nw = TM_MALLOC( SuTuple, sizeof( *nw ) );
    nw->next = sunitNIL;
    nw->tag = TAGSuTuple;
    nw->ulist = par_ulist;
    return (sunit) nw;
}

/*******************************************************************
 *    Freeing routines                                             *
 *******************************************************************/

#define freSstack(e) TM_FREE( e );
#define freSuWord(e) TM_FREE( e );
#define freSuCons(e) TM_FREE( e );
#define freSuList(e) TM_FREE( e );
#define freSuTuple(e) TM_FREE( e );

/*******************************************************************
 *    Recursive freeing routines                                   *
 *******************************************************************/

/* free an element of type sunit, constructor SuWord, and all elements
   in the constructor.
 */
static void rfreSuWord( /*@only@*/ SuWord e )
{
    fre_tmstring_nolognew( e->word );
    freSuWord( e );
}

/* free an element of type sunit, constructor SuCons, and all elements in the constructor
 */
static void rfreSuCons( /*@only@*/ SuCons e )
{
    rfresunit_list( e->ulist );
    freSuCons( e );
}

/* free an element of type sunit, constructor SuList, and all elements in the
   constructor
 */
static void rfreSuList( /*@only@*/ SuList e )
{
    rfresunit_list( e->ulist );
    freSuList( e );
}

/* free an element of type sunit, constructor SuTuple, and all elements in the
   constructor
 */
static void rfreSuTuple( /*@only@*/ SuTuple e )
{
    rfresunit_list( e->ulist );
    freSuTuple( e );
}


/* recursively free an element of type sunit
   and all elements in it.
 */
static void rfresunit( /*@only@*/ sunit e )
{
    switch( e->tag ){
        case TAGSuWord:
	    rfreSuWord( (SuWord) e );
	    break;

        case TAGSuCons:
	    rfreSuCons( (SuCons) e );
	    break;

        case TAGSuList:
	    rfreSuList( (SuList) e );
	    break;

        case TAGSuTuple:
	    rfreSuTuple( (SuTuple) e );
	    break;

        default:
	    FATALTAG( e->tag );
    }
}

/* recursively free a list of elements of type sunit */
static void rfresunit_list( sunit e )
{
    while( e != sunitNIL ){
        sunit n = e->next;

	rfresunit( e );
	e = n;
    }
}

/*******************************************************************\
*    Append routines                                                *
\*******************************************************************/

/* append list of sunit 'b' after list of sunit 'a' */
static /*@null@*/ /*@only@*/ sunit appsunitlist( /*@null@*/ /*@returned@*/ sunit a, /*@null@*/ /*@only@*/ sunit b )
{
   sunit tl;

   if( a == sunitNIL ){
       return b;
   }
   tl = a;
   while( tl->next != sunitNIL ){
       tl = tl->next;
   }
   tl->next = b;
   return a;
}

static void doindent( TMPRINTSTATE *st, int n )
{
    if( st->tabwidth>0 ){
	while( n >= st->tabwidth ){
	    (void) fputc( '\t', st->file );
	    n -= st->tabwidth;
	}
    }
    while( n > 0 ){
	(void) fputc( ' ', st->file );
	n--;
    }
}

/******************************************************
 *            DETERMINATION OF STRING LENGTH          *
 ******************************************************/

/* Determine the length of a constructor tmstring when printed
   on one line.

   This is done as follows:
   - the length of a list containing sub-lists is 0.
   - the length of a constructor without members is 2 (for the brackets).
   - For a word list of length 1 the length is the length of the word.
   - Otherwise the opening and closing brackets cause an overhead
     of 2 spaces.
   - Each word adds its tmstring length.
   - All words are separated by 1 space.

   When counting a space for each word in the list, the netto overhead
   of the brackets is 1 spaces.
 */
static int lencons( /*@null@*/ sunit l )
{
    int len = 1;	/* overhead */

    if( l == sunitNIL ){
	return 2;
    }
    if( l->next == sunitNIL && l->tag == TAGSuWord ){
	return (int) strlen( ((SuWord)l)->word );
    }
    while( l != sunitNIL ){
	if( l->tag != TAGSuWord ){
	    return 0;
	}
	len += 1 + (int) strlen( ((SuWord)l)->word );
	l = l->next;
    }
    return len;
}

/* Determine the length of a list tmstring when printed
   on one line.

   This is done as follows:
   - The length of a list containing sub-lists is 0.
   - For a word list of length 0 the length is 2 (since "[]" is printed).
   - Otherwise the opening and closing brackets cause an overhead
     of 2 spaces.
   - Each word adds its tmstring length.
   - All words are separated by 1 comma and 1 space.

   When counting a space and comma for each word in the list,
   the netto overhead of the brackets is 0 spaces.
 */
static int lenlist( /*@null@*/ sunit l )
{
    int len = 0;	/* overhead */

    if( l == sunitNIL ){
	return 2;
    }
    while( l != sunitNIL ){
	if( l->tag != TAGSuWord ){
	    return 0;
	}
	len += 2 + (int) strlen( ((SuWord)l)->word );
	l = l->next;
    }
    return len;
}

/* Determine the length of a tuple tmstring when printed
   on one line.

   This is done as follows:
   - The length of a tuple containing sub-tuples is 0.
   - For a word tuple of length 0 the length is 2 (since "()" is printed).
   - Otherwise the opening and closing brackets cause an overhead
     of 2 spaces.
   - Each word adds its tmstring length.
   - All words are separated by 1 comma and 1 space.

   When counting a space and comma for each word in the list,
   the netto overhead of the brackets is 0 spaces.
 */
static int lentuple( /*@null@*/ sunit l )
{
    int len = 0;	/* overhead */

    if( l == sunitNIL ){
	return 2;
    }
    while( l != sunitNIL ){
	if( l->tag != TAGSuWord ){
	    return 0;
	}
	len += 2 + (int) strlen( ((SuWord)l)->word );
	l = l->next;
    }
    return len;
}

/******************************************************
 *            HORIZONTAL PRINTING ROUTINE             *
 ******************************************************/

/* Print constructor 'c' in vertical mode. */
static void vertprintcons( /*@temp@*/ TMPRINTSTATE *st, SuCons c, int lev )
{
    sunit l;

    l = c->ulist;
    if( l != sunitNIL && l->next == sunitNIL ){
	vertprintsunit( st, l, lev );
	return;
    }
    doindent( st, st->istep * lev );
    (void) fputs( "(\n", st->file );
    while( l != sunitNIL ){
	vertprintsunit( st, l, (lev+1) );
	l = l->next;
	(void) fputc( '\n', st->file );
    }
    doindent( st, st->istep * lev );
    (void) fputc( ')', st->file );
    return;
}

/* Print list 'lst' in vertical mode. */
static void vertprintlist( /*@temp@*/ TMPRINTSTATE *st, SuList lst, int lev )
{
    sunit l;

    l = lst->ulist;
    if( l == sunitNIL ){
	doindent( st, st->istep * lev );
	(void) fputs( "[]", st->file );
	return;
    }
    doindent( st, st->istep * lev );
    (void) fputs( "[\n", st->file );
    while( l != sunitNIL ){
	vertprintsunit( st, l, (lev+1) );
	l = l->next;
	if( l != sunitNIL ){
	    (void) fputc( ',', st->file );
	}
	(void) fputc( '\n', st->file );
    }
    doindent( st, st->istep * lev );
    (void) fputc( ']', st->file );
    return;
}

/* Print tuple 'tpl' in vertical mode. */
static void vertprinttuple( /*@temp@*/ TMPRINTSTATE *st, SuTuple lst, int lev )
{
    sunit l;

    l = lst->ulist;
    if( l == sunitNIL ){
	doindent( st, st->istep * lev );
	(void) fputs( "()", st->file );
	return;
    }
    doindent( st, st->istep * lev );
    (void) fputs( "(\n", st->file );
    while( l != sunitNIL ){
	vertprintsunit( st, l, (lev+1) );
	l = l->next;
	if( l != sunitNIL ){
	    (void) fputc( ',', st->file );
	}
	(void) fputc( '\n', st->file );
    }
    doindent( st, st->istep * lev );
    (void) fputc( ')', st->file );
    return;
}

/* Given a unit 'l' and a indent level 'lev', print given
   unit to 'st->file'. When neccary delegate printing to
   specialized routines 'vertprint{list,tuple,cons}()'.

   NOTE: no return is printed after the last line, so
   that a comma can be appended when necessary.
 */
static void vertprintsunit( /*@temp@*/ TMPRINTSTATE *st, sunit l, int lev )
{
    switch( l->tag ){
	case TAGSuWord:
	    doindent( st, st->istep * lev );
	    (void) fputs( ((SuWord)l)->word, st->file );
	    break;

	case TAGSuCons:
	    vertprintcons( st, (SuCons) l, lev );
	    break;

	case TAGSuList:
	    vertprintlist( st, (SuList) l, lev );
	    break;

	case TAGSuTuple:
	    vertprinttuple( st, (SuTuple) l, lev );
	    break;
    }
}

/* Print list consisting of sunits in 'l' in
   horizontal mode, and return a new tmstring for it.
 */
static tmstring horprintlist( /*@temp@*/ TMPRINTSTATE *st, /*@null@*/ sunit l )
{
    char *bufp;
    char *v;

    if( l == sunitNIL ){
	return new_tmstring_nolognew( "[]" );
    }
    bufp = st->linebuf;
    *bufp++ = '[';
    while( l != sunitNIL ){
	v = ((SuWord)l)->word;
	while( *v != '\0' ){
	    *bufp++ = *v++;
	}
	l = l->next;
	if( l != sunitNIL ){
	    *bufp++ = ',';
	    *bufp++ = ' ';
	}
    }
    *bufp++ = ']';
    *bufp = '\0';
    return new_tmstring_nolognew( st->linebuf );
}

/* Print tuple consisting of sunits in 'l' in
   horizontal mode, and return a new tmstring for it.
 */
static tmstring horprinttuple( /*@temp@*/ TMPRINTSTATE *st, /*@null@*/ sunit l )
{
    char *bufp;
    char *v;

    if( l == sunitNIL ){
	return new_tmstring_nolognew( "()" );
    }
    bufp = st->linebuf;
    *bufp++ = '(';
    while( l != sunitNIL ){
	v = ((SuWord)l)->word;
	while( *v ){
	    *bufp++ = *v++;
	}
	l = l->next;
	if( l != sunitNIL ){
	    *bufp++ = ',';
	    *bufp++ = ' ';
	}
    }
    *bufp++ = ')';
    *bufp = '\0';
    return new_tmstring_nolognew( st->linebuf );
}

/* Print constructor consisting of sunits in 'l' in
   horizontal mode, and return a new tmstring for it.
 */
static tmstring horprintcons( /*@temp@*/ TMPRINTSTATE *st, /*@null@*/ sunit l )
{
    char *bufp;
    char *v;

    if( l == sunitNIL ){
	return new_tmstring_nolognew( "()" );
    }
    if( l->next == sunitNIL ){
	return new_tmstring_nolognew( ((SuWord)l)->word );
    }
    bufp = st->linebuf;
    *bufp++ = '(';
    while( l != sunitNIL ){
	v = ((SuWord)l)->word;
	while( *v ){
	    *bufp++ = *v++;
	}
	l = l->next;
	if( l != sunitNIL ){
	    *bufp++ = ' ';
	}
    }
    *bufp++ = ')';
    *bufp = '\0';
    return new_tmstring_nolognew( st->linebuf );
}

/******************************************************
 *            STACK MANAGEMENT ROUTINES               *
 ******************************************************/

/* push current level on st->stack */
static void pushlev( /*@temp@*/ TMPRINTSTATE *st )
{
    Sstack nw = newSstack( st->curlist, st->stack );
    st->curlist = NULL;
    st->stack = nw;
}

static void poplev( /*@temp@*/ TMPRINTSTATE *st )
{
    Sstack e;

    if( st->stack == SstackNIL ){
        FATAL( "pop of empty printst->stack" );
    }
    e = st->stack;
    rfresunit_list( st->curlist );
    st->stack = e->next;
    st->curlist = e->ulist;
    freSstack( e );
}

/******************************************************
 *            TOP LEVEL ROUTINES                      *
 ******************************************************/

/* start a new constructor */
void tm_opencons( TMPRINTSTATE *st )
{
    pushlev( st );
    st->braclev++;
}

/* terminate current constructor */
void tm_closecons( TMPRINTSTATE *st )
{
    sunit nw;
    int len = lencons( st->curlist );

    st->braclev--;
    if( len != 0 && (len + (st->braclev * st->istep)) < st->width ){
	nw = newSuWord( horprintcons( st, st->curlist ) );
    }
    else {
	nw = newSuCons( st->curlist );
        st->curlist = NULL;
    }
    poplev( st );
    if( st->braclev<1 ){
	vertprintsunit( st, nw, 0 );
	(void) fputc( '\n', st->file );
	rfresunit( nw );
	return;
    }
    st->curlist = appsunitlist( st->curlist, nw );
}

/* start a new list */
void tm_openlist( TMPRINTSTATE *st )
{
    pushlev( st );
    st->braclev++;
}

/* terminate current list */
void tm_closelist( TMPRINTSTATE *st )
{
    sunit nw;
    int len;

    st->braclev--;
    len = lenlist( st->curlist );
    if( len != 0 && (len + (st->braclev * st->istep)) < st->width ){
	nw = newSuWord( horprintlist( st, st->curlist ) );
    }
    else {
	nw = newSuList( st->curlist );
        st->curlist = NULL;
    }
    poplev( st );
    if( st->braclev<1 ){
	vertprintsunit( st, nw, 0 );
	(void) fputc( '\n', st->file );
	rfresunit( nw );
	return;
    }
    st->curlist = appsunitlist( st->curlist, nw );
}

/* start a new tuple */
void tm_opentuple( TMPRINTSTATE *st )
{
    pushlev( st );
    st->braclev++;
}

/* terminate current tuple */
void tm_closetuple( TMPRINTSTATE *st )
{
    sunit nw;
    int len;

    st->braclev--;
    len = lentuple( st->curlist );
    if( len != 0 && (len + (st->braclev * st->istep)) < st->width ){
	nw = newSuWord( horprinttuple( st, st->curlist ) );
    }
    else {
	nw = newSuTuple( st->curlist );
        st->curlist = NULL;
    }
    poplev( st );
    if( st->braclev<1 ){
	vertprintsunit( st, nw, 0 );
	(void) fputc( '\n', st->file );
	rfresunit( nw );
	return;
    }
    st->curlist = appsunitlist( st->curlist, nw );
}

/* Add word 'w' to the current unit list, or print it
   directly if no brackets are opened.
 */
void tm_printword( TMPRINTSTATE *st, const char *w )
{
    sunit nw;

    if( st->braclev<1 ){
	(void) fputs( w, st->file );
	(void) fputc( '\n', st->file );
	return;
    }
    nw = newSuWord( new_tmstring_nolognew( w ) );
    st->curlist = appsunitlist( st->curlist, nw );
}

TMPRINTSTATE *tm_setprint(
    FILE *f,
    const int istep,
    const int width,
    const int tabwidth,
    const unsigned int flags
)
{
    TMPRINTSTATE *st;

    st = TM_MALLOC( TMPRINTSTATE *, sizeof( *st ) );
    st->file = f;
    st->istep = istep;
    st->width = width;
    st->tabwidth = tabwidth;
    st->flags = flags;
    st->braclev = 0;
    st->curlist = sunitNIL;
    st->stack = SstackNIL;
    st->linebuf = TM_MALLOC( char *, (width+10)*sizeof( char ) );
    st->linebuf[0] = '\0'; /* To make lint happy. */
    return st;
}

int tm_endprint( TMPRINTSTATE *st )
{
    int braclev = st->braclev;

    TM_FREE( st->linebuf );
    TM_FREE( st );
    return braclev;
}

