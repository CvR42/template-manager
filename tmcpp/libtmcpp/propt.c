/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

// file: propt.c
//
// Handler for optimized printing of datastructures.

#include "config.h"
#include <ctype.h>
#include "tmcpp.h"

#define FATAL(msg) tm_fatal( __FILE__, __LINE__, msg )
#define FATALTAG(tag) tm_badtag( __FILE__, __LINE__, (int) (tag) );

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

// datastructures
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

// possible tags for sunit:
#define TAGSuWord 1
#define TAGSuCons 2
#define TAGSuList 3
#define TAGSuTuple 4

struct str_SuWord {
    sunit next;
    int tag;
    tmstring word;
};

struct str_SuCons {
    sunit next;
    int tag;
    sunit ulist;
};

struct str_SuList {
    sunit next;
    int tag;
    sunit ulist;
};

struct str_SuTuple {
    sunit next;
    int tag;
    sunit ulist;
};

// Forward declarations.
static void rfresunit_list( sunit e );

/*******************************************************************
 *    Allocation routines                                          *
 *******************************************************************/

static Sstack newSstack( sunit par_ulist )
{
    Sstack nw;

    nw = TM_MALLOC( Sstack, sizeof( *nw ) );
    nw->next = SstackNIL;
    nw->ulist = par_ulist;
    return nw;
}

static sunit newSuWord( tmstring par_word )
{
    SuWord nw;

    nw = TM_MALLOC( SuWord, sizeof( *nw ) );
    nw->next = sunitNIL;
    nw->tag = TAGSuWord;
    nw->word = par_word;
    return (sunit) nw;
}

static sunit newSuCons( sunit par_ulist )
{
    SuCons nw;

    nw = TM_MALLOC( SuCons, sizeof( *nw ) );
    nw->next = sunitNIL;
    nw->tag = TAGSuCons;
    nw->ulist = par_ulist;
    return (sunit) nw;
}

static sunit newSuList( sunit par_ulist )
{
    SuList nw;

    nw = TM_MALLOC( SuList, sizeof( *nw )  );
    nw->next = sunitNIL;
    nw->tag = TAGSuList;
    nw->ulist = par_ulist;
    return (sunit) nw;
}

static sunit newSuTuple( sunit par_ulist )
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
static void rfreSuWord( SuWord e )
{
    fre_tmstring( e->word );
    freSuWord( e );
}

/* free an element of type sunit, constructor SuCons, and all elements in the constructor
 */
static void rfreSuCons( SuCons e )
{
    rfresunit_list( e->ulist );
    freSuCons( e );
}

/* free an element of type sunit, constructor SuList, and all elements in the
   constructor
 */
static void rfreSuList( SuList e )
{
    rfresunit_list( e->ulist );
    freSuList( e );
}

/* free an element of type sunit, constructor SuTuple, and all elements in the
   constructor
 */
static void rfreSuTuple( SuTuple e )
{
    rfresunit_list( e->ulist );
    freSuTuple( e );
}


/* recursively free an element of type sunit
   and all elements in it.
 */
static void rfresunit( sunit e )
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

// recursively free a list of elements of type sunit.
static void rfresunit_list( sunit e )
{
    sunit n;

    while( e!=sunitNIL ){
	n = e->next;
	rfresunit( e );
	e = n;
    }
}

/*******************************************************************\
*    Append routines                                                *
\*******************************************************************/

/* append list of sunit 'b' after list of sunit 'a' */
static sunit appsunitlist( sunit a, sunit b )
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

void TmPrintState::doIndent( const int n )
{
    int pos = 0;
    if( tabwidth>0 ){
	while( (n-pos) >= tabwidth ){
	    fputc( '\t', file );
	    pos += tabwidth;
	}
    }
    while( pos<n ){
	fputc( ' ', file );
	pos++;
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
static int lencons( sunit l )
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
static int lenlist( sunit l )
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
static int lentuple( sunit l )
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

// Print constructor 'c' in vertical mode.
void TmPrintState::vertPrintConstructor( const sunit c, const int lev )
{
    sunit l;

    l = ((SuCons)c)->ulist;
    if( l != sunitNIL && l->next == sunitNIL ){
	vertPrintSunit( l, lev );
	return;
    }
    doIndent( istep * lev );
    fputs( "(\n", file );
    while( l != sunitNIL ){
	vertPrintSunit( l, (lev+1) );
	l = l->next;
	fputc( '\n', file );
    }
    doIndent( istep * lev );
    fputc( ')', file );
    return;
}

// Print list 'lst' in vertical mode.
void TmPrintState::vertPrintList( const sunit lst, const int lev )
{
    sunit l = ((SuList) lst)->ulist;
    if( l == sunitNIL ){
	doIndent( istep * lev );
	fputs( "[]", file );
	return;
    }
    doIndent( istep * lev );
    fputs( "[\n", file );
    while( l != sunitNIL ){
	vertPrintSunit( l, (lev+1) );
	l = l->next;
	if( l != sunitNIL ){
	    fputc( ',', file );
	}
	fputc( '\n', file );
    }
    doIndent( istep * lev );
    fputc( ']', file );
    return;
}

// Print tuple 'tpl' in vertical mode.
void TmPrintState::vertPrintTuple( const sunit lst, const int lev )
{
    sunit l = ((SuTuple)lst)->ulist;
    if( l == sunitNIL ){
	doIndent( istep * lev );
	fputs( "()", file );
	return;
    }
    doIndent( istep * lev );
    fputs( "(\n", file );
    while( l != sunitNIL ){
	vertPrintSunit( l, (lev+1) );
	l = l->next;
	if( l != sunitNIL ) fputc( ',', file );
	fputc( '\n', file );
    }
    doIndent( istep * lev );
    fputc( ')', file );
    return;
}

/* Given a unit 'l' and a indent level 'lev', print given
   unit to 'file'. When neccary delegate printing to
   specialized routines 'vertprint{list,tuple,cons}()'.

   NOTE: no return is printed after the last line, so
   that a comma can be appended when necessary.
 */
void TmPrintState::vertPrintSunit( sunit l, const int lev )
{
    switch( l->tag ){
	case TAGSuWord:
	    doIndent( istep * lev );
	    fputs( ((SuWord)l)->word, file );
	    break;

	case TAGSuCons:
	    vertPrintConstructor( l, lev );
	    break;

	case TAGSuList:
	    vertPrintList( l, lev );
	    break;

	case TAGSuTuple:
	    vertPrintTuple( l, lev );
	    break;
    }
}

/* Print list consisting of sunits in 'l' in
   horizontal mode, and return a nw tmstring for it.
 */
tmstring TmPrintState::horPrintList( sunit l )
{
    char *bufp;
    char *v;

    if( l == sunitNIL ){
	return new_tmstring( "[]" );
    }
    bufp = linebuf;
    *bufp++ = '[';
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
    *bufp++ = ']';
    *bufp = '\0';
    return new_tmstring( linebuf );
}

/* Print tuple consisting of sunits in 'l' in
   horizontal mode, and return a nw tmstring for it.
 */
tmstring TmPrintState::horPrintTuple( sunit l )
{
    if( l == sunitNIL ){
	return new_tmstring( "()" );
    }
    char *bufp = linebuf;
    *bufp++ = '(';
    while( l != sunitNIL ){
	char *v = ((SuWord)l)->word;
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
    return new_tmstring( linebuf );
}

/* Print constructor consisting of sunits in 'l' in
   horizontal mode, and return a nw tmstring for it.
 */
tmstring TmPrintState::horPrintConstructor( sunit l )
{
    char *v;

    if( l == sunitNIL ){
	return new_tmstring( "()" );
    }
    if( l->next == sunitNIL ){
	return new_tmstring( ((SuWord)l)->word );
    }
    char *bufp = linebuf;
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
    return new_tmstring( linebuf );
}

/******************************************************
 *            STACK MANAGEMENT ROUTINES               *
 ******************************************************/

// push current level on stack
void TmPrintState::pushLevel()
{
    Sstack nw = newSstack( curlist );
    nw->next = stack;
    stack = nw;
}

void TmPrintState::popLevel()
{
    if( stack == SstackNIL ){
	FATAL( "pop of empty printstack" );
    }
    Sstack e = (Sstack) stack;
    curlist = e->ulist;
    stack = e->next;
    freSstack( (Sstack) e );
}

/******************************************************
 *            TOP LEVEL ROUTINES                      *
 ******************************************************/

// start a new constructor */
void TmPrintState::openConstructor()
{
    pushLevel();
    braclev++;
    curlist = sunitNIL;
}

// terminate current constructor */
void TmPrintState::closeConstructor()
{
    sunit nw;

    braclev--;
    int len = lencons( curlist );
    if( len != 0 && (len + (braclev * istep)) < width ){
	nw = newSuWord( horPrintConstructor( curlist ) );
	rfresunit_list( curlist );
    }
    else {
	nw = newSuCons( curlist );
    }
    popLevel();
    if( braclev<1 ){
	vertPrintSunit( nw, 0 );
	fputc( '\n', file );
	rfresunit( nw );
	return;
    }
    curlist = appsunitlist( curlist, nw );
}

/* start a nw list */
void TmPrintState::openList()
{
    pushLevel();
    braclev++;
    curlist = sunitNIL;
}

/* terminate current list */
void TmPrintState::closeList()
{
    sunit nw;
    int len;

    braclev--;
    len = lenlist( curlist );
    if( len != 0 && (len + (braclev * istep)) < width ){
	nw = newSuWord( horPrintList( curlist ) );
	rfresunit_list( curlist );
    }
    else {
	nw = newSuList( curlist );
    }
    popLevel();
    if( braclev<1 ){
	vertPrintSunit( nw, 0 );
	fputc( '\n', file );
	rfresunit( nw );
	return;
    }
    curlist = appsunitlist( curlist, nw );
}

// start a new tuple
void TmPrintState::openTuple()
{
    pushLevel();
    braclev++;
    curlist = sunitNIL;
}

// terminate current tuple
void TmPrintState::closeTuple()
{
    sunit nw;

    braclev--;
    int len = lentuple( curlist );
    if( len != 0 && (len + (braclev * istep)) < width ){
	nw = newSuWord( horPrintTuple( curlist ) );
	rfresunit_list( curlist );
    }
    else {
	nw = newSuTuple( curlist );
    }
    popLevel();
    if( braclev<1 ){
	vertPrintSunit( nw, 0 );
	fputc( '\n', file );
	rfresunit( nw );
	return;
    }
    curlist = appsunitlist( curlist, nw );
}

// Add word 'w' to the current unit list, or print it
// directly if no brackets are opened.
void TmPrintState::printWord( const char *w )
{
    if( braclev<1 ){
	fputs( w, file );
	fputc( '\n', file );
	return;
    }
    sunit nw = newSuWord( new_tmstring( w ) );
    curlist = appsunitlist( curlist, nw );
}

TmPrintState::TmPrintState(
    FILE *f,
    const int p_istep,
    const int p_width,
    const int p_tabwidth,
    const unsigned int p_flags
): file(f), linebuf(0), istep(p_istep), width(p_width), tabwidth(p_tabwidth),
   flags(p_flags), braclev(0), curlist(sunitNIL), stack(SstackNIL)
{
    linebuf = TM_MALLOC( char *, (width+10)*sizeof( char ) );
}

TmPrintState::~TmPrintState()
{
    TM_FREE( linebuf );
}
