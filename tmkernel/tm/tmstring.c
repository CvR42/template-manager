/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: tmstring.c
   String manipulation routines.
 */

#include "config.h"

#include "tmdefs.h"
#include <ctype.h>
#include <tmc.h>

#include "tmcode.h"
#include "tmstring.h"
#include "misc.h"
#include "error.h"

/* Given a pointer to a tmstring 's' and a pointer to a character pointer 'w',
   scan the tmstring for a 'word'.
   
   First, all characters matching isspace() are skipped.
   After that a word is scanned, a new tmstring is allocated for the word,
   and assigned to '*w'. If there is no other word in the tmstring, '*w'
   is set to tmstringNIL.

   A word is one of the following regular expressions:
   [^ \t\n\r\f\0]+: An arbitrary tmstring of nonblanks and non-specials.
   "[^"\0]*": Arbitrary characters surrounded by "".
 */
const char *scanword( const char *s, char **w )
{
    unsigned int ix;
    unsigned int room;
    tmstring buf;

    while( isspace( *s ) ) s++;
    if( *s == '\0' ){
	*w = tmstringNIL;
	return( s );
    }
    buf = new_tmstring( s );
    ix = 0;
    room = (int) strlen( s )+1;
    if( *s == DQUOTE ){
	s++;
	while( *s != DQUOTE && *s != '\0' ){
	    if( ix>= room ){
		room += STRSTEP;
		buf = realloc_tmstring( buf, room+1 );
	    }
	    buf[ix++] = *s++;
	}
	if( *s != DQUOTE ){
	    line_error( "unexpected end of line" );
	}
	else {
	    s++;
	}
	buf[ix] = '\0';
	*w = buf;
	return( s );
    }
    while( *s != '\0' && !isspace( *s ) ){
	if( ix>= room ){
	    room += STRSTEP;
	    buf = realloc_tmstring( buf, room+1 );
	}
	buf[ix++] = *s++;
    }
    buf[ix] = '\0';
    *w = buf;
    return s;
}

/***************************************************************
 *   parameter parsing                                         *
 ***************************************************************/

/* Given a parameter tmstring 'p' and a pointer to a tmstring pointer
   'p1', ensure that 'p' contains exactly one parameter and create
   a copy of the tmstring to put in '*p1'.
 */
void scan1par( const char *pl, char **p1 )
{
    pl = scanword( pl, p1 );
    if( *p1 == CHARNIL ){
	line_error( "missing parameter" );
	return;
    }
    cknopar( pl );
}

/***************************************************************
 *   error handling                                            *
 ***************************************************************/

/* Given a tmstring 's', ensure that it does not contain an other
   parameter, or else complain.
 */
void cknopar( const char *s )
{
    while( isspace( *s ) ) s++;
    if( *s != '\0' ){
	(void) sprintf( errarg, "'%s'", s );
	line_error( "excess function parameters" );
    }
}

/* Given a tmstring 's', ensure that it is a correct number,
   or else complain.
 */
void cknumpar( const char *n )
{
    const char *s;

    s = n;
    while( isspace( *s ) ){
	s++;
    }
    if( *s == '-' || *s == '+' ){
	s++;
    }
    while( isdigit( *s ) ){
	s++;
    }
    while( isspace( *s ) ){
	s++;
    }
    if( *s != '\0' ){
	(void) sprintf( errarg, "'%s'", n );
	line_error( "malformed number" );
    }
}

/* Return a new "1" or "0" tmstring reflecting the value of boolean 'b'. */
char *newboolstr( bool b )
{
    return new_tmstring( ( b ? "1" : "0" ) );
}

/* Return a new tmstring reflecting the value of int 'n'. */
char *newintstr( int n )
{
    char buf[NUMBUFSIZE];

    (void) sprintf( buf, "%d", n );
    return new_tmstring( buf );
}

/* Given a tmstring 'p', chop it into words using 'scanword' and return
 * a tmstringlist containing the pieces.
 */
tmstring_list chopstring( const char *p )
{
    char *s;
    tmstring_list sl;

    sl = new_tmstring_list();
    for(;;){
	p = scanword( p, &s );
	if( s == CHARNIL ) break;
	sl = append_tmstring_list( sl, s );
    }
    return sl;
}

/* Given a tmstring_list 'sl' and a separation tmstring 'sep', construct one
 * single (newly allocated) tmstring from all tmstrings in 'sl' separated from
 * each other with a copy of 'sep'.
 *
 * To prevent problems with a fixed buffer, the final length of the
 * tmstring is calculated, and sufficient room is allocated for that
 * tmstring.
 *
 * the total length of the required tmstring is
 *  sum(<all joined tmstrings>) + (n-1)*strlen(sep)
 */
tmstring sepstrings( const tmstring_list sl, const tmstring sep )
{
    char *cp;		/* pointer in copied tmstrings  */
    char *cs;			/* tmstring under construction */
    char *bufp;	/* pointer in tmstring under construction */
    unsigned int ix;	/* index in tmstring array */
    unsigned int len;		/* calculated length of tmstring */

    len = 0;
    if( sl->sz!=0 ){
	len += (sl->sz-1)*(int) strlen(sep);
    }
    for( ix=0; ix<sl->sz; ix++ ){
	len += (int) strlen( sl->arr[ix] );
    }
    cs = new_tmstring( "" );
    cs = realloc_tmstring( cs, len+1 );
    bufp = cs;
    for( ix=0; ix<sl->sz; ix++ ){
	if( ix!=0 ){
	    cp = sep;
	    while( *cp!='\0' ){
		*bufp++ = *cp++;
	    }
	}
	cp = sl->arr[ix];
	while( *cp!='\0' ){
	    *bufp++ = *cp++;
	}
    }
    *bufp = '\0';
    return cs;
}

/* Given a tmstring_list 'sl', construct one single tmstring from by separating
 * all tmstrings in 'sl' from each other with a ' '.
 */
tmstring flatstrings( const tmstring_list sl )
{
    return sepstrings( sl, " " );
}

/* Return TRUE if this tmstring represents FALSE. */
bool isfalsestr( const tmstring s )
{
    const char *p;

    p = s;
    while( isspace( *p ) ){
	p++;
    }
    if( p[0] != '0' ){
	return FALSE;
    }
    return ( isspace( p[1] ) || p[1] == '\0' );
}

/* Return TRUE if this tmstring does not represent FALSE. */
bool istruestr( const tmstring s )
{
    const char *p;

    p = s;
    while( isspace( *p ) ){
	p++;
    }
    if( p[0] != '0' ){
	return TRUE;
    }
    return ( !(isspace( p[1] ) || p[1] == '\0') );
}

/* Given a list prefix 'pre', a type name 'tnm' and a list suffix
 * 'suff', return a new tmstring containing the list name constructed
 * from these ingredients.
 */
tmstring mklistnm( const char *pre, const tmstring tnm, const char *suff )
{
    size_t sz;
    tmstring res;

    sz = strlen( pre ) + strlen( tnm ) + strlen( suff ) + 1;
    res = new_tmstring( "" );
    res = realloc_tmstring( res, sz );
    sprintf( res, "%s%s%s", pre, tnm, suff );
    return res;
}
