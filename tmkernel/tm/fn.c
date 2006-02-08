/* File: $Id$
 *
 * Handle function expressions.
 */

#include "config.h"

/* Standard UNIX libraries and functions */
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

/* Tm library */
#include <tmc.h>

/* local definitions */
#include "tmdefs.h"

#include "refex.h"
#include "tmcode.h"
#include "tmstring.h"
#include "error.h"
#include "fn.h"
#include "global.h"
#include "tmtrans.h"
#include "misc.h"
#include "var.h"
#include "srchfile.h"

/* Forward declarations. */
static Type_list update_reach_Type( Type_list tl, bool *visited, Type_list blocking, const Type t );

/* Given a list prefix 'pre' and suffix 'suff', and a type 't',
 * return the element type of this type, or tmstringNIL if there is none.
 *
 * If both the prefix and the suffix are empty, consider no type to be
 * a list type.
 */
static tmstring get_element_type( const char *pre, const char *suff, const_tmstring t )
{
    const size_t prelen = strlen( pre );
    const size_t sufflen = strlen( suff );
    const size_t tlen = strlen( t );

    if( prelen == 0 && sufflen == 0 ){
	return tmstringNIL;
    }
    if(
	tlen>prelen+sufflen &&
	strncmp( pre, t, prelen ) == 0 &&
	strncmp( suff, t+tlen-sufflen, sufflen ) == 0 
    ){
	tmstring ns = rdup_tmstring( t+prelen );

	ns[tlen-(prelen+sufflen)] = '\0';
	return ns;
    }
    return tmstringNIL;
}

/* Given a list prefix 'pre' and suffix 'suff', and a type string 't',
 * return a Type representing this type string.
 * given 
 */
static Type split_type( const char *pre, const char *suff, const_tmstring t )
{
    tmstring old;
    tmuint level = 0;
    tmstring nw;
    Type res;

    nw = rdup_tmstring( t );
    for(;;) {
	old = nw;
	nw = get_element_type( pre, suff, old );
	if( nw == tmstringNIL ){
	    break;
	}
	rfre_tmstring( old );
	level++;
    }
    res = new_Type( level, add_tmsymbol( old ) );
    rfre_tmstring( old );
    return res;
}

/* Given a list of types, return a list of strings representing these
 * types.
 */
static tmstring make_typename( const char *pre, const char *suff, const Type t )
{
    return mklistnm( pre, t->basetype->name, suff, t->level );
}

/* Given a list of types, return a list of strings representing these
 * types.
 */
static tmstring_list make_typename_list( const Type_list tl )
{
    unsigned int ix;
    tmstring_list sl;
    const char *pre;
    const char *suff;

    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    sl = setroom_tmstring_list( new_tmstring_list(), tl->sz );
    for( ix=0; ix<tl->sz; ix++ ){
	sl = append_tmstring_list( sl, make_typename( pre, suff, tl->arr[ix] ) );
    }
    return sl;
}

/* Given a list of types, return a list of strings representing these types. */
static tmstring flat_Type_list( const Type_list tl )
{
    tmstring_list sl = make_typename_list( tl );
    tmstring ans;

    ans = flatstrings( sl );
    rfre_tmstring_list( sl );
    return ans;
}

/* ------ tm functions ------ */

/* implementation of functions. Each function is given a parameter
   tmstring and an origin tmstring for error messages
 */

/* -- numerical functions -- */

/* max */
static tmstring fnmax( const_origin org, const_tmstring_list sl )
{
    int max;
    unsigned int ix;

    if( sl->sz<1 ){
	origin_error( org, "'max' requires at least one parameter" );
	return newintstr( 0 );
    }
    max = atoi( sl->arr[0] );
    for( ix=0; ix<sl->sz; ix++ ){
        int n;

	cknumpar( org, sl->arr[ix] );
	n = atoi( sl->arr[ix] );
	if( n>max )
	    max = n;
    }
    return newintstr( max );
}

/* min */
static tmstring fnmin( const_origin org, const_tmstring_list sl )
{
    int min;
    unsigned int ix;

    if( sl->sz<1 ){
	origin_error( org, "'min' requires at least one parameter" );
	return newintstr( 0 );
    }
    min = atoi( sl->arr[0] );
    for( ix=1; ix<sl->sz; ix++ ){
        int n;

	(void) cknumpar( org, sl->arr[ix] );
	n = atoi( sl->arr[ix] );
	if( n<min )
	    min = n;
    }
    return newintstr( min );
}

/* addition */
static tmstring fnplus( const_origin org, const_tmstring_list sl )
{
    int sum = 0;
    unsigned int ix;

    for( ix=0; ix<sl->sz; ix++ ){
      (void) cknumpar( org, sl->arr[ix] );
	sum += atoi( sl->arr[ix] );
    }
    return newintstr( sum );
}

/* subtraction */
static tmstring fnsubtract( const_origin org, const_tmstring_list sl )
{
    int a;

    if( sl->sz != 2 ){
	origin_error( org, "'subtract' requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    (void) cknumpar( org, sl->arr[0] );
    (void) cknumpar( org, sl->arr[1] );
    a = atoi( sl->arr[0] ) - atoi( sl->arr[1] );
    return newintstr( a );
}

/* multiplication */
static tmstring fntimes( const_origin org, const_tmstring_list sl )
{
    int prod = 1;
    unsigned int ix;

    for( ix=0; ix<sl->sz; ix++ ){
        (void) cknumpar( org, sl->arr[ix] );
	prod *= atoi( sl->arr[ix] );
    }
    return newintstr( prod );
}

/* division */
static tmstring fndiv( const_origin org, const_tmstring_list sl )
{
    int a;

    if( sl->sz != 2 ){
	origin_error( org, "division requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    (void) cknumpar( org, sl->arr[0] );
    (void) cknumpar( org, sl->arr[1] );
    a = atoi( sl->arr[0] ) / atoi( sl->arr[1] );
    return newintstr( a );
}

/* modulus */
static tmstring fnmod( const_origin org, const_tmstring_list sl )
{
    int a;

    if( sl->sz != 2 ){
	origin_error( org, "modulus requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    (void) cknumpar( org, sl->arr[0] );
    (void) cknumpar( org, sl->arr[1] );
    a = atoi( sl->arr[0] ) % atoi( sl->arr[1] );
    return newintstr( a );
}

/* -- comparison functions -- */

/* < */
static tmstring fnless( const_origin org, const_tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	origin_error( org, "comparison requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    (void) cknumpar( org, sl->arr[0] );
    (void) cknumpar( org, sl->arr[1] );
    b = atoi( sl->arr[0] ) < atoi( sl->arr[1] );
    return newboolstr( b );
}

/* <= */
static tmstring fnlesseq( const_origin org, const_tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	origin_error( org, "comparison requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    (void) cknumpar( org, sl->arr[0] );
    (void) cknumpar( org, sl->arr[1] );
    b = atoi( sl->arr[0] ) <= atoi( sl->arr[1] );
    return newboolstr( b );
}

/* > */
static tmstring fngreater( const_origin org, const_tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	origin_error( org, "comparison requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    (void) cknumpar( org, sl->arr[0] );
    (void) cknumpar( org, sl->arr[1] );
    b = atoi( sl->arr[0] ) > atoi( sl->arr[1] );
    return newboolstr( b );
}

/* >= */
static tmstring fngreatereq( const_origin org, const_tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	origin_error( org, "comparison requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    (void) cknumpar( org, sl->arr[0] );
    (void) cknumpar( org, sl->arr[1] );
    b = atoi( sl->arr[0] ) >= atoi( sl->arr[1] );
    return newboolstr( b );
}

/* == */
static tmstring fneq( const_origin org, const_tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	origin_error( org, "comparison requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    (void) cknumpar( org, sl->arr[0] );
    (void) cknumpar( org, sl->arr[1] );
    b = atoi( sl->arr[0] ) == atoi( sl->arr[1] );
    return newboolstr( b );
}

/* != */
static tmstring fnneq( const_origin org, const_tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	origin_error( org, "comparison requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    (void) cknumpar( org, sl->arr[0] );
    (void) cknumpar( org, sl->arr[1] );
    b = atoi( sl->arr[0] ) != atoi( sl->arr[1] );
    return newboolstr( b );
}

/* strcmp */
static tmstring fnstrcmp( const_origin org, const_tmstring_list sl )
{
    int cmp;

    if( sl->sz != 2 ){
	origin_error( org, "comparison requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    cmp = strcmp( sl->arr[0] , sl->arr[1] );
    if( cmp == 0 ) return new_tmstring( "0" );
    if( cmp < 0 ) return new_tmstring( "-1" );
    return new_tmstring( "1" );
}

/* eq */
static tmstring fnstreq( const_origin org, const_tmstring_list sl )
{
    int cmp;

    if( sl->sz != 2 ){
	origin_error( org, "comparison requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    cmp = strcmp( sl->arr[0] , sl->arr[1] );
    return newboolstr( cmp == 0 );
}

/* neq */
static tmstring fnstrneq( const_origin org, const_tmstring_list sl )
{
    int cmp;

    if( sl->sz != 2 ){
	origin_error( org, "comparison requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    cmp = strcmp( sl->arr[0] , sl->arr[1] );
    return newboolstr( cmp != 0 );
}

/* -- string functions -- */

/* len */
static tmstring fnlen( const_origin org, const_tmstring_list sl )
{
    (void) org;

    return newintstr( (int) sl->sz );
}

/* strpad */
static tmstring fnstrpad( const_origin org, const_tmstring_list sl )
{
    tmstring w;
    tmstring wp;
    unsigned int len;
    tmstring pw;
    tmstring buf;
    tmstring bufp;

    if( sl->sz != 3 ){
	origin_error( org, "'pad' requires exactly three parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    w = sl->arr[0];
    pw = sl->arr[2];
    if( *pw == '\0' ){
	origin_error( org, "empty padding string" );
	return new_tmstring( "" );
    }
    (void) cknumpar( org, sl->arr[1] );
    len = atoi( sl->arr[1] );
    buf = create_tmstring( len+1 );
    wp = w;
    bufp = buf;
    while( len!=0 && *wp != '\0' ){
	*bufp++ = *wp++;
	len--;
    }
    wp = pw;
    while( len!=0 ){
	if( *wp == '\0' ){
	    wp = pw;
	}
	*bufp++ = *wp++;
	len--;
    }
    *bufp = '\0';
    return buf;
}

/* strlen */
static tmstring fnstrlen( const_origin org, const_tmstring_list sl )
{
    int l;

    (void) org;
    if( sl->sz<1 ){
	l = 0;
    }
    else {
	l = (int) strlen( sl->arr[0] );
    }
    return newintstr( l );
}

/* capitalize */
static tmstring fncapitalize( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;

    (void) org;
    nl = rdup_tmstring_list( sl );
    for( ix=0; ix<nl->sz; ix++ ){
        char *np = nl->arr[ix];

	if( *np != '\0' && islower( *np ) ){
	    *np -= (char) ('a' - 'A');
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* toupper */
static tmstring fntoupper( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;

    (void) org;
    nl = rdup_tmstring_list( sl );
    for( ix=0; ix<nl->sz; ix++ ){
        char *np = nl->arr[ix];

	while( *np != '\0' ){
	    if( islower( *np ) ){
		*np -= (char) ('a' - 'A');
	    }
	    np++;
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* tolower */
static tmstring fntolower( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;

    (void) org;
    nl = rdup_tmstring_list( sl );
    for( ix=0; ix<nl->sz; ix++ ){
        char *np = nl->arr[ix];

	while( *np != '\0' ){
	    if( isupper( *np ) ){
		*np += (char) ('a' - 'A');
	    }
	    np++;
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* tochar */
static tmstring fntochar( const_origin org, const_tmstring_list sl )
{
    tmstring ans = create_tmstring( 1+sl->sz );
    char *p = ans;
    unsigned int ix;

    for( ix=0; ix<sl->sz; ix++ ){
        const_tmstring n = sl->arr[ix];

        if( cknumpar( org, n ) ){
            int v = atoi( n );

            if( v<0 || v>255 ){
                origin_error( org, "tochar: character code %d out of range", v );
            }
            else {
                *p++ = (char) v;
            }
        }
    }
    *p = '\0';
    return ans;
}

/* Given a string 's', a list of old characters 'oldchars' and a list of
 * new characters 'newchars', replace all occurences of characters in
 * 'oldchars' with the corresponding character in 'newchars'.
 *
 * The same string is returned, with the replacements implemented.
 */
static tmstring tr_tmstring( tmstring s, const_tmstring oldchars, const_tmstring newchars )
{
    unsigned int ix = 0;

    while( s[ix] != '\0' ){
	char *pos = strchr( oldchars, s[ix] );

	if( pos != (char *) NULL ){
	    s[ix] = newchars[pos-oldchars];
	}
	ix++;
    }
    return s;
}

/* tr <oldchars> <newchars> s..s */
static tmstring fntr( const_origin org, const_tmstring_list sl )
{
    tmstring oldchars;
    tmstring newchars;
    int ok;
    tmstring_list nl;
    tmstring ans;

    nl = rdup_tmstring_list( sl );
    nl = extract_tmstring_list( nl, 0, &oldchars, &ok );
    if( !ok ){
	origin_error( org, "'tr': no old characters given" );
	rfre_tmstring_list( nl );
	return new_tmstring( "" );
    }
    nl = extract_tmstring_list( nl, 0, &newchars, &ok );
    if( !ok ){
	origin_error( org, "'tr': no new characters given" );
	rfre_tmstring_list( nl );
	rfre_tmstring( oldchars );
	return new_tmstring( "" );
    }
    if( strlen( oldchars ) != strlen( newchars ) ){
	origin_error( org, "'tr': the strings of old and new characters must have the same length" );
    }
    else {
        unsigned int ix;

	for( ix=0; ix<nl->sz; ix++ ){
	    nl->arr[ix] = tr_tmstring( nl->arr[ix], oldchars, newchars );
	}
    }
    rfre_tmstring( oldchars );
    rfre_tmstring( newchars );
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* fnstrindex <c> <word> */
static tmstring fnstrindex( const_origin org, const_tmstring_list sl )
{
    int n;
    char *ixp;

    if( sl->sz != 2 ){
	origin_error( org, "'strindex' requires exactly two parameters, not %u", sl->sz );
	return new_tmstring( "" );
    }
    ixp = strchr( sl->arr[1], sl->arr[0][0] );
    n = ( ixp == CHARNIL ? 0 : 1 + (int)(ixp - sl->arr[1]) );
    return newintstr( n );
}

/* fnleftstr <n> <word> .. <word> */
static tmstring fnleftstr( const_origin org, const_tmstring_list sl )
{
    int n;
    tmstring_list nl = new_tmstring_list();
    unsigned int ix;
    tmstring ans;

    if( sl->sz < 1 ){
	origin_error( org, "'leftstr' requires at least one parameter" );
	return new_tmstring( "" );
    }
    if( cknumpar( org, sl->arr[0] ) ){
        n = atoi( sl->arr[0] );
        if( n<0 ){
            origin_error( org, "'leftstr' requires a non-negative length" );
            n = 0;
        }
    }
    else {
        n = 0;
    }
    for( ix=1; ix<sl->sz; ix++ ){
        tmstring s = rdup_tmstring( sl->arr[ix] );
        size_t sz = strlen( s );
        
        if( sz>(size_t) n ){
            /* Truncate the string. */
            s[n] = '\0';
        }
	nl = append_tmstring_list( nl, s );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* fnrightstr <n> <word> .. <word> */
static tmstring fnrightstr( const_origin org, const_tmstring_list sl )
{
    int n;
    tmstring_list nl = new_tmstring_list();
    unsigned int ix;
    tmstring ans;

    if( sl->sz < 1 ){
	origin_error( org, "'rightstr' requires at least one parameter" );
	return new_tmstring( "" );
    }
    if( cknumpar( org, sl->arr[0] ) ){
        n = atoi( sl->arr[0] );
        if( n<0 ){
            origin_error( org, "'rightstr' requires a non-negative length" );
            n = 0;
        }
    }
    else {
        n = 0;
    }
    for( ix=1; ix<sl->sz; ix++ ){
        tmstring s = rdup_tmstring( sl->arr[ix] );
        size_t sz = strlen( s );
        
        if( sz>(size_t) n  ){
            memmove( s, s+(sz-n), (size_t) n );
            s[n] = '\0';
        }
	nl = append_tmstring_list( nl, s );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* index <elm> <list> */
/* Note that due to a coincidence the index in the tmstring list
 * the correct index to return.
 */
static tmstring fnindex( const_origin org, const_tmstring_list sl )
{
    unsigned int ix;
    tmstring estr;

    if( sl->sz<1 ){
	origin_error( org, "'index' requires at least one parameter" );
	return new_tmstring( "0" );
    }
    estr = sl->arr[0];
    for( ix=1; ix<sl->sz; ix++ ){
	if( strcmp( estr, sl->arr[ix] ) == 0 ){
	    break;
	}
    }
    if( ix>=sl->sz ){
	ix=0;
    }
    return newintstr( (int) ix );
}

/* member <elm> <list> */
/* Note that due to a coincidence the index in the tmstring list
 * the correct index to return.
 */
static tmstring fnmember( const_origin org, const_tmstring_list sl )
{
    unsigned int ix;
    tmstring estr;
    bool found = FALSE;

    if( sl->sz<1 ){
	origin_error( org, "'member' requires at least one parameter" );
	return new_tmstring( "0" );
    }
    estr = sl->arr[0];
    for( ix=1; ix<sl->sz; ix++ ){
	if( strcmp( estr, sl->arr[ix] ) == 0 ){
	    found = TRUE;
	    break;
	}
    }
    return newboolstr( found );
}

/* seplist <str> <list> */
static tmstring fnseplist( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz<1 ){
	origin_error( org, "'seplist' requires at least one parameter" );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    for( ix=1; ix<sl->sz; ix++ ){
	nl = append_tmstring_list( nl, new_tmstring( sl->arr[ix] ) );
    }
    ans = sepstrings( nl, sl->arr[0] );
    rfre_tmstring_list( nl );
    return ans;
}

/* prefix <pf> <list> */
static tmstring fnprefix( const_origin org, const_tmstring_list sl )
{
    tmstring pfstr;
    tmstring ans;
    tmstring buf;
    size_t len;
    size_t maxlen;
    tmstring_list nl;
    unsigned int ix;

    if( sl->sz<1 ){
	origin_error( org, "'prefix' requires at least one parameter" );
	return new_tmstring( "" );
    }
    pfstr = sl->arr[0];
    maxlen = 0;
    for( ix=1; ix<sl->sz; ix++ ){
        len = strlen( sl->arr[ix] );

	if( len>maxlen ){
	    maxlen = len;
	}
    }
    len = 1 + strlen( pfstr ) + maxlen;
    buf = create_tmstring( len );
    nl = new_tmstring_list();
    for( ix=1; ix<sl->sz; ix++ ){
	(void) sprintf( buf, "%s%s", pfstr, sl->arr[ix] );
	nl = append_tmstring_list( nl, new_tmstring( buf ) );
    }
    fre_tmstring( buf );
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* suffix <sf> <list> */
static tmstring fnsuffix( const_origin org, const_tmstring_list sl )
{
    tmstring sfstr;
    tmstring ans;
    tmstring buf;
    size_t len;
    size_t maxlen;
    tmstring_list nl;
    unsigned int ix;

    if( sl->sz<1 ){
	origin_error( org, "'suffix' requires at least one parameter" );
	return new_tmstring( "" );
    }
    sfstr = sl->arr[0];
    maxlen = 0;
    for( ix=1; ix<sl->sz; ix++ ){
	len = strlen( sl->arr[ix] );
	if( len>maxlen ){
	    maxlen = len;
	}
    }
    len = 1 + strlen( sfstr ) + maxlen;
    buf = create_tmstring( len );
    nl = new_tmstring_list();
    for( ix=1; ix<sl->sz; ix++ ){
	(void) sprintf( buf, "%s%s", sl->arr[ix], sfstr );
	nl = append_tmstring_list( nl, new_tmstring( buf ) );
    }
    fre_tmstring( buf );
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

static int sortcmp( const void *pa, const void *pb )
{
     const char * const *sa = (const char * const *) pa;
     const char * const *sb = (const char * const *) pb;

     return strcmp( *sa, *sb );
}

/* sort e1..en */
static tmstring fnsort( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    int (*cmpf)( const void *, const void * );

    (void) org;
    cmpf = sortcmp;
    qsort( sl->arr, sl->sz, sizeof( sl->arr[0] ), cmpf );
    ans = flatstrings( sl );
    return ans;
}

static int sizesortcmp( const void *pa, const void *pb )
{
     const char * const *sa = (const char * const *) pa;
     const char * const *sb = (const char * const *) pb;
     size_t sza = strlen( *sa );
     size_t szb = strlen( *sb );

     if( sza<szb ){
	 return -1;
     }
     if( sza>szb ){
	 return 1;
     }
     return strcmp( *sa, *sb );
}

/* sizesort e1..en */
static tmstring fnsizesort( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    int (*cmpf)( const void *, const void * );

    (void) org;
    cmpf = sizesortcmp;
    qsort( sl->arr, sl->sz, sizeof( sl->arr[0] ), cmpf );
    ans = flatstrings( sl );
    return ans;
}

/* rev e1..en */
static tmstring fnrev( const_origin org, const_tmstring_list sl )
{
    unsigned int lix;
    unsigned int rix;
    tmstring tmp;
    char *ans;

    (void) org;
    lix = 0;
    rix = sl->sz;
    while( lix<rix ){
	rix--;
	tmp = sl->arr[lix];
	sl->arr[lix] = sl->arr[rix];
	sl->arr[rix] = tmp;
	lix++;
    }
    ans = flatstrings( sl );
    return ans;
}

/* comm a "" b */
static tmstring fncomm( const_origin org, const_tmstring_list sl )
{
    unsigned int aix;
    unsigned int bix;
    unsigned int sepix;
    char *ans;
    tmstring_list nl;

    sepix = 0;
    while( sepix<sl->sz && sl->arr[sepix][0] != '\0' ) sepix++;
    if( sepix>=sl->sz ){
	origin_error( org, "no separator" );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    for( aix=0; aix<sepix; aix++ ){
        tmstring tofind = sl->arr[aix];
        bool takeit = FALSE;

	for( bix=sepix+1; bix<sl->sz; bix++ ){
	    if( strcmp( tofind, sl->arr[bix] ) == 0 ){
		takeit = TRUE;
		break;
	    }
	}
	if( takeit ){
	    nl = append_tmstring_list( nl, new_tmstring( tofind ) );
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* excl a "" b */
static tmstring fnexcl( const_origin org, const_tmstring_list sl )
{
    unsigned int sepix;
    unsigned int aix;
    unsigned int bix;
    char *ans;
    tmstring_list nl;

    sepix = 0;
    while( sepix<sl->sz && sl->arr[sepix][0] != '\0' ){
	sepix++;
    }
    if( sepix>=sl->sz ){
	origin_error( org, "no separator" );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    for( aix=0; aix<sepix; aix++ ){
        tmstring tofind = sl->arr[aix];
        bool takeit = TRUE;

	for( bix=sepix+1; bix<sl->sz; bix++ ){
	    if( strcmp( tofind, sl->arr[bix] ) == 0 ){
		takeit = FALSE;
		break;
	    }
	}
	if( takeit ){
	    nl = append_tmstring_list( nl, new_tmstring( tofind ) );
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* uniq e1..en */
static tmstring fnuniq( const_origin org, const_tmstring_list sl )
{
    tmstring_list nl;
    tmstring ans;
    tmstring prevstr;
    unsigned int ix;
    int (*cmpf)( const void *, const void * );

    (void) org;
    cmpf = sortcmp;
    qsort( sl->arr, sl->sz, sizeof( sl->arr[0] ), cmpf );
    nl = new_tmstring_list();
    prevstr = tmstringNIL;
    for( ix=0; ix<sl->sz; ix++ ){
	if( prevstr == tmstringNIL || strcmp( sl->arr[ix], prevstr ) != 0 ){
	    nl = append_tmstring_list( nl, rdup_tmstring( sl->arr[ix] ) );
	    prevstr = sl->arr[ix];
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* filt findpat newpat e1..en
 * find all elements matching 'findpat' and replace them
 * by 'newpat'. Do not copy elements that don't match.
 */
static tmstring fnfilt( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    const char *errm;
    char buf[STRBUFSIZE];
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz < 2 ){
	origin_error( org, "'filt' requires at least two parameters" );
	return new_tmstring( "" );
    }
    errm = ref_comp( sl->arr[0] );
    if( errm != (char *) NULL ){
	origin_error( org, "bad regular expression: %s", errm );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    for( ix=2; ix<sl->sz; ix++ ){
	if( ref_exec( sl->arr[ix] ) ){
	    ref_subs( sl->arr[1], buf );
	    nl = append_tmstring_list( nl, new_tmstring( buf ) );
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* subs findpat newpat e1..en
   find all elements matching 'findpat' and replace them
   by 'newpat'. Copy elements that don't match.
 */
static tmstring fnsubs( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    const char *errm;
    char buf[STRBUFSIZE];
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz < 2 ){
	origin_error( org, "'subs' requires at least two parameters" );
	return new_tmstring( "" );
    }
    errm = ref_comp( sl->arr[0] );
    if( errm != (char *) NULL ){
	origin_error( org, "bad regular expression: %s", errm );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    for( ix=2; ix<sl->sz; ix++ ){
	if( ref_exec( sl->arr[ix] ) ){
	    ref_subs( sl->arr[1], buf );
	    nl = append_tmstring_list( nl, new_tmstring( buf ) );
	}
	else {
	    nl = append_tmstring_list( nl, new_tmstring( sl->arr[ix] ) );
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* rmlist findpat e1..en
   find all elements matching 'findpat' and delete them.
   Copy elements that don't match.
 */
static tmstring fnrmlist( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    const char *errm;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz < 1 ){
	origin_error( org, "'rmlist' requires at least one parameter" );
	return new_tmstring( "" );
    }
    errm = ref_comp( sl->arr[0] );
    if( errm != (char *) NULL ){
	origin_error( org, "bad regular expression: %s", errm );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    for( ix=1; ix<sl->sz; ix++ ){
	if( !ref_exec( sl->arr[ix] ) ){
	    nl = append_tmstring_list( nl, new_tmstring( sl->arr[ix] ) );
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* first */
static tmstring fnfirst( const_origin org, const_tmstring_list sl )
{
    tmstring ans;

    (void) org;
    if( sl->sz <1 ){
	ans = new_tmstring( "" );
    }
    else {
	ans = new_tmstring( sl->arr[0] );
    }
    return ans;
}

/* shift */
static tmstring fnshift( const_origin org, const_tmstring_list sl )
{
    unsigned int ix;
    tmstring_list nl;
    tmstring ans;

    (void) org;
    nl = new_tmstring_list();
    for( ix=1; ix<sl->sz; ix++ ){
        nl = append_tmstring_list( nl, new_tmstring( sl->arr[ix] ) );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* if */
static tmstring fnif( const_origin org, const_tmstring_list sl )
{
    tmstring ans;

    if( sl->sz<1 ){
	origin_error( org, "'if' requires at least a condition expression" );
	return new_tmstring( "" );
    }
    if( istruestr( sl->arr[0] ) ){
	if( sl->sz>=2 ){
	    ans = rdup_tmstring( sl->arr[1] );
	}
	else {
	    ans = new_tmstring( "" );
	}
    }
    else {
	if( sl->sz>=3 ){
	    ans = rdup_tmstring( sl->arr[2] );
	}
	else {
	    ans = new_tmstring( "" );
	}
    }
    return ans;
}

/* -- logic functions -- */

/* and */
static tmstring fnand( const_origin org, const_tmstring_list sl )
{
    bool flag = TRUE;
    unsigned int ix;

    (void) org;
    for( ix=0; ix<sl->sz; ix++ ){
	flag = istruestr( sl->arr[ix] );
	if( !flag ) break;
    }
    return newboolstr( flag );
}

/* or */
static tmstring fnor( const_origin org, const_tmstring_list sl )
{
    bool flag = FALSE;
    unsigned int ix;

    (void) org;
    for( ix=0; ix<sl->sz; ix++ ){
	flag = istruestr( sl->arr[ix] );
	if( flag ) break;
    }
    return newboolstr( flag );
}

/* not */
static tmstring fnnot( const_origin org, const_tmstring_list sl )
{
    bool a;

    (void) org;
    if( sl->sz < 1 ){
	a = TRUE;
    }
    else {
	a = isfalsestr( sl->arr[0] );
    }
    return newboolstr( a );
}

/* -- datastructure access & file name access -- */


/* listtypes <list> */
static tmstring fnlisttypes( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;
    const char *pre;
    const char *suff;

    (void) org;
    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    nl = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	const_tmstring s = sl->arr[ix];
	tmstring et = get_element_type( pre, suff, s );

	if( et != tmstringNIL ){
	    rfre_tmstring( et );
	    nl = append_tmstring_list( nl, rdup_tmstring( s ) );
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* delisttypes <list> */
static tmstring fndelisttypes( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;
    const char *pre;
    const char *suff;

    (void) org;
    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    nl = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	tmstring s = sl->arr[ix];
	tmstring et = get_element_type( pre, suff, s );

	if( et != tmstringNIL ){
	    nl = append_tmstring_list( nl, et );
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* singletypes <list> */
static tmstring fnsingletypes( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;
    const char *pre;
    const char *suff;

    (void) org;
    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    nl = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	tmstring s = sl->arr[ix];
	tmstring et = get_element_type( pre, suff, s );

	if( et == tmstringNIL ){
	    nl = append_tmstring_list( nl, rdup_tmstring( s ) );
	}
	else {
	    rfre_tmstring( et );
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* stemname <list> */
static tmstring fnstemname( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;
    const char *pre;
    const char *suff;

    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    if( pre[0] == '\0' && suff[0] == '\0' ){
	origin_error( org, "'stemname' cannot function if both '" LISTPRE "' and '" LISTSUFF "' are empty" );
	ans = flatstrings( sl );
	return ans;
    }
    nl = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	tmstring old = rdup_tmstring( sl->arr[ix] );
	tmstring nw = get_element_type( pre, suff, old );

	while( nw != tmstringNIL ){
	    rfre_tmstring( old );
	    old = nw;
	    nw = get_element_type( pre, suff, old );
	}
	nl = append_tmstring_list( nl, old );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* mklist <n> <list> */
static tmstring fnmklist( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    int n;
    tmstring_list nl;
    unsigned int ix;
    const char *pre;
    const char *suff;

    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    if( sl->sz<1 ){
	origin_error( org, "'mklist' requires at least one parameter" );
	return new_tmstring( "" );
    }
    cknumpar( org, sl->arr[0] );
    n = atoi( sl->arr[0] );
    nl = new_tmstring_list();
    for( ix=1; ix<sl->sz; ix++ ){
	nl = append_tmstring_list(
	    nl, 
	    mklistnm( pre, sl->arr[ix], suff, (unsigned int) n )
	);
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Construct a list of types. */
static tmstring fntypelist( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    unsigned int ix;
    tmsymbol_list nl;

    if( sl->sz!=0 ){
      origin_error( org, "'typelist' does not need any parameters" );
    }
    nl = new_tmsymbol_list();
    for( ix = 0; ix< allds->sz; ix++ ){
	const_ds d = allds->arr[ix];

	nl = append_tmsymbol_list( nl, d->name->sym );
    }
    ans = flatsymbols( nl );
    rfre_tmsymbol_list( nl );
    return ans;
}

/* Construct a list of constructors. */
static tmstring fnconstructorlist( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    unsigned int ix;
    tmsymbol_list nl;

    if( sl->sz!=0 ){
	origin_error( org, "'constructorlist' does not need any parameters" );
    }
    nl = new_tmsymbol_list();
    for( ix = 0; ix< allds->sz; ix++ ){
        const_ds d = allds->arr[ix];

	switch( d->tag ){
            case TAGDsInclude:
	    case TAGDsConstructorBase:
	    case TAGDsTuple:
	    case TAGDsClass:
	    case TAGDsAlias:
		break;

	    case TAGDsConstructor:
		nl = append_tmsymbol_list( nl, d->name->sym );
		break;
	}
    }
    ans = flatsymbols( nl );
    rfre_tmsymbol_list( nl );
    return ans;
}
/* Construct a list of constructor types. */
static tmstring fnctypelist( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    unsigned int ix;
    tmsymbol_list nl;

    if( sl->sz!=0 ){
	origin_error( org, "'ctypelist' does not need any parameters" );
    }
    nl = new_tmsymbol_list();
    for( ix = 0; ix< allds->sz; ix++ ){
	const_ds d = allds->arr[ix];
	switch( d->tag ){
	    case TAGDsConstructorBase:
		nl = append_tmsymbol_list( nl, d->name->sym );
		break;

            case TAGDsInclude:
	    case TAGDsTuple:
	    case TAGDsAlias:
	    case TAGDsClass:
	    case TAGDsConstructor:
		break;
	}
    }
    ans = flatsymbols( nl );
    rfre_tmsymbol_list( nl );
    return ans;
}

/* Construct a list of tuple types. */
static tmstring fntuplelist( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    unsigned int ix;
    tmsymbol_list nl;

    if( sl->sz!=0 ){
	origin_error( org, "'tuplelist' does not need any parameters" );
    }
    nl = new_tmsymbol_list();
    for( ix = 0; ix< allds->sz; ix++ ){
        const_ds d = allds->arr[ix];
	switch( d->tag ){
	    case TAGDsTuple:
		nl = append_tmsymbol_list( nl, d->name->sym );
		break;

	    case TAGDsConstructorBase:
	    case TAGDsConstructor:
	    case TAGDsClass:
	    case TAGDsAlias:
	    case TAGDsInclude:
		break;

	}
    }
    ans = flatsymbols( nl );
    rfre_tmsymbol_list( nl );
    return ans;
}

/* Construct a list of class types. */
static tmstring fnclasslist( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    unsigned int ix;
    tmsymbol_list nl;

    if( sl->sz!=0 ){
	origin_error( org, "'classlist' does not need any parameters" );
    }
    nl = new_tmsymbol_list();
    for( ix = 0; ix< allds->sz; ix++ ){
	const_ds d = allds->arr[ix];

	switch( d->tag ){
	    case TAGDsTuple:
	    case TAGDsInclude:
	    case TAGDsConstructorBase:
	    case TAGDsConstructor:
	    case TAGDsAlias:
		break;

	    case TAGDsClass:
		nl = append_tmsymbol_list( nl, d->name->sym );
		break;

	}
    }
    ans = flatsymbols( nl );
    rfre_tmsymbol_list( nl );
    return ans;
}

/* Construct a list of aliases. */
static tmstring fnaliases( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    unsigned int ix;
    tmsymbol_list nl;

    if( sl->sz!=0 ){
	origin_error( org, "'aliases' does not need any parameters" );
    }
    nl = new_tmsymbol_list();
    for( ix = 0; ix< allds->sz; ix++ ){
	const_ds d = allds->arr[ix];

	switch( d->tag ){
	    case TAGDsTuple:
	    case TAGDsInclude:
	    case TAGDsConstructorBase:
	    case TAGDsConstructor:
	    case TAGDsClass:
		break;

	    case TAGDsAlias:
		nl = append_tmsymbol_list( nl, d->name->sym );
		break;

	}
    }
    ans = flatsymbols( nl );
    rfre_tmsymbol_list( nl );
    return ans;
}

/* Given a list of types 'dl', search for type with name 't'.
 * Give an error message if it is not found.
 */ 
static ds findtype( const_origin org, ds_list dl, const_tmstring t )
{
    unsigned int ix;

    ix = find_type_ix( dl, add_tmsymbol( t ) );
    if( ix>=dl->sz ){
	origin_error( org, "unknown type `%s'", t );
	return dsNIL;
    }
    return dl->arr[ix];
}

static bool is_virtual( ds_list types, const_tmstring type )
{
    bool ans = FALSE;
    unsigned int ix;

    ix = find_type_ix( types, add_tmsymbol( type ) );
    if( ix<allds->sz ){
	const_ds d = allds->arr[ix];

	switch( d->tag ){
	    case TAGDsConstructorBase:
		ans = TRUE;
		break;

	    case TAGDsTuple:
	    case TAGDsInclude:
	    case TAGDsAlias:
	    case TAGDsConstructor:
		break;

	    case TAGDsClass:
		ans = to_const_DsClass( d )->isvirtual;
		break;

	}
    }
    return ans;
}

/* Given a type name, return TRUE if the type is virtual. */
static tmstring fnisvirtual( const_origin org, const_tmstring_list sl )
{
    bool ans = FALSE;

    if( sl->sz == 1 ){
	ans = is_virtual( allds, sl->arr[0] );
    }
    else {
	origin_error( org, "'isvirtual' requires exactly one parameter, not %u", sl->sz );
    }
    return newboolstr( ans );
}

/* Given a list of types, return the ones that are virtual. */
static tmstring fnvirtual( const_origin org, const_tmstring_list sl )
{
    unsigned int ix;
    tmstring_list res;
    tmstring ans;

    (void) org;
    res = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	if( is_virtual( allds, sl->arr[ix] ) ){
	    res = append_tmstring_list( res, rdup_tmstring( sl->arr[ix] ) );
	}
    }
    ans = flatstrings( res );
    rfre_tmstring_list( res );
    return ans;
}

/* Given a list of types, return the ones that are not virtual. */
static tmstring fnnonvirtual( const_origin org, const_tmstring_list sl )
{
    unsigned int ix;
    tmstring_list res;
    tmstring ans;

    (void) org;
    res = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	if( !is_virtual( allds, sl->arr[ix] ) ){
	    res = append_tmstring_list( res, rdup_tmstring( sl->arr[ix] ) );
	}
    }
    ans = flatstrings( res );
    rfre_tmstring_list( res );
    return ans;
}

static tmstring calc_metaname(
 const char *pre,
 const char *suff,
 const_tmstring type
)
{
    unsigned int ix;

    ix = find_type_ix( allds, add_tmsymbol( type ) );
    if( ix<allds->sz ){
	const_ds d = allds->arr[ix];

	switch( d->tag ){
	    case TAGDsConstructorBase:
		return new_tmstring( "constructorbase" );

	    case TAGDsConstructor:
		return new_tmstring( "constructor" );

	    case TAGDsTuple:
		return new_tmstring( "tuple" );

	    case TAGDsInclude:
		return tmstringNIL;

	    case TAGDsAlias:
		return new_tmstring( "alias" );

	    case TAGDsClass:
		return new_tmstring( "class" );

	}
    }
    {
	tmstring et = get_element_type( pre, suff, type );

	if( et != tmstringNIL ){
	    rfre_tmstring( et );
	    return new_tmstring( "list" );
	}
    }
    return new_tmstring( "atom" );
}

/* Given a type name, return the metatype of this type.  */
static tmstring fnmetatype( const_origin org, const_tmstring_list sl )
{
    const char *pre;
    const char *suff;
    unsigned int ix;
    tmstring_list res;
    tmstring ans;

    (void) org;
    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    res = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	res = append_tmstring_list(
	    res,
	    calc_metaname( pre, suff, sl->arr[ix] )
	);
    }
    ans = flatstrings( res );
    rfre_tmstring_list( res );
    return ans;
}

/* Given a type, return the alias of the type, or the original if
 * it doesn't have one.
 */
static tmstring calc_alias( const char *pre, const char *suff, const_tmstring type )
{
    unsigned int ix;

    ix = find_type_ix( allds, add_tmsymbol( type ) );
    if( ix<allds->sz ){
	const_ds d = allds->arr[ix];
	const_Type t;
	tmstring tnm;
	tmstring res;

	if( d->tag != TAGDsAlias ){
	    return rdup_tmstring( type );
	}
	t = to_const_DsAlias( d )->type;
	tnm = calc_alias( pre, suff, t->basetype->name );
	res = mklistnm( pre, tnm, suff, t->level );
	rfre_tmstring( tnm );
	return res;
    }
    return rdup_tmstring( type );
}

/* Given a type name, return the alias of this type.  */
static tmstring fnalias( const_origin org, const_tmstring_list sl )
{
    unsigned int ix;
    tmstring_list res;
    tmstring ans;
    const char *pre;
    const char *suff;

    (void) org;
    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    res = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	res = append_tmstring_list(
	    res,
	    calc_alias( pre, suff, sl->arr[ix] )
	);
    }
    ans = flatstrings( res );
    rfre_tmstring_list( res );
    return ans;
}

/* Given a type name, return the subclasses (transitive closure of inheritors)
 * of this type.
 */
static tmstring fnsubclasses( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmsymbol_list subclasses;
    unsigned int ix;

    (void) org;
    subclasses = new_tmsymbol_list();
    for( ix=0; ix<sl->sz; ix++ ){
	collect_subclasses( &subclasses, allds, add_tmsymbol( sl->arr[ix] ) );
    }
    ans = flatsymbols( subclasses );
    rfre_tmsymbol_list( subclasses );
    return ans;
}

/* Given a type name, return the superclasses (transitive closure of inherits)
 * of this type.
 */
static tmstring fnsuperclasses( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmsymbol_list superclasses;
    unsigned int ix;

    (void) org;
    superclasses = new_tmsymbol_list();
    for( ix=0; ix<sl->sz; ix++ ){
	collect_superclasses( &superclasses, allds, add_tmsymbol( sl->arr[ix] ) );
    }
    ans = flatsymbols( superclasses );
    rfre_tmsymbol_list( superclasses );
    return ans;
}

/* Given a type name, return the inherits of this type.  */
static tmstring fninherits( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    unsigned int ix;
    tmsymbol_list allinherits;

    (void) org;
    allinherits = new_tmsymbol_list();
    for( ix=0; ix<sl->sz; ix++ ){
	tmsymbol_list inherits = rdup_tmsymbol_list( extract_inherits( allds, add_tmsymbol( sl->arr[ix] ) ) );

	if( inherits != tmsymbol_listNIL ){
	    allinherits = concat_tmsymbol_list( allinherits, inherits );
	}
    }
    ans = flatsymbols( allinherits );
    rfre_tmsymbol_list( allinherits );
    return ans;
}

/* Given a type name, return the inheritors (the types that inherit
 * from this type).
 */
static tmstring fninheritors( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmsymbol_list inheritors;
    unsigned int ix;

    (void) org;
    inheritors = new_tmsymbol_list();
    for( ix=0; ix<sl->sz; ix++ ){
	collect_inheritors( &inheritors, allds, add_tmsymbol( sl->arr[ix] ) );
    }
    ans = flatsymbols( inheritors );
    rfre_tmsymbol_list( inheritors );
    return ans;
}

/* Construct a list of fields (including inherited ones) for the given type.  */
static tmstring fnallfields( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmsymbol_list nl;
    unsigned int ix;

    (void) org;
    nl = new_tmsymbol_list();
    for( ix=0; ix<sl->sz; ix++ ){
	collect_all_fields( &nl, allds, add_tmsymbol( sl->arr[ix] ) );
    }
    ans = flatsymbols( nl );
    rfre_tmsymbol_list( nl );
    return ans;
}

/* Construct a list of fields for the given type.  */
static tmstring fnfields( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    tmsymbol_list nl;
    unsigned int ix;

    (void) org;
    nl = new_tmsymbol_list();
    for( ix=0; ix<sl->sz; ix++ ){
	collect_fields( &nl, allds, add_tmsymbol( sl->arr[ix] ) );
    }
    ans = flatsymbols( nl );
    rfre_tmsymbol_list( nl );
    return ans;
}

/* Given a tuple type name and element name, return the
   type name of the given element.
 */
static tmstring fntypename( const_origin org, const_tmstring_list sl )
{
    const_Field e;

    if( sl->sz != 2 ){
	origin_error( org, "'ttypename' requires a type and an element name" );
	return new_tmstring( "" );
    }
    e = find_field( allds, add_tmsymbol( sl->arr[0] ), add_tmsymbol( sl->arr[1] ) );
    if( e == FieldNIL ){
	origin_error( org, "type `%s' has no field `%s'", sl->arr[0], sl->arr[1] );
	return new_tmstring( "" );
    }
    return new_tmstring( e->type->basetype->name );
}

/* Given a type name and element name, return the
   type class of the given element.

   Possible type classes are: `single' and `list'.
 */
static tmstring fnttypeclass( const_origin org, const_tmstring_list sl )
{
    const_Field e;

    if( sl->sz != 2 ){
	origin_error( org, "'fieldtypeclass' requires a type and an element name" );
	return new_tmstring( "" );
    }
    e = find_field( allds, add_tmsymbol( sl->arr[0] ), add_tmsymbol( sl->arr[1] ) );
    if( e == FieldNIL ){
	origin_error( org, "type `%s' has no field `%s'", sl->arr[0], sl->arr[1] );
	return new_tmstring( "" );
    }
    return new_tmstring( ( e->type->level != 0 ? "list" : "single" ) );
}

/* Given a type name and element name, return the
   list level of the given element.
 */
static tmstring fntypelevel( const_origin org, const_tmstring_list sl )
{
    const_Field e;

    if( sl->sz != 2 ){
	origin_error( org, "'typelevel' requires a type and an element name" );
	return new_tmstring( "" );
    }
    e = find_field( allds, add_tmsymbol( sl->arr[0] ), add_tmsymbol( sl->arr[1] ) );
    if( e == FieldNIL ){
	origin_error( org, "type `%s' has no field `%s'", sl->arr[0], sl->arr[1] );
	return new_tmstring( "" );
    }
    return newuintstr( e->type->level );
}

/* Given a list of types, return the types of the fields of these types,
 * and the list of types they inherit from.
 * Unknown types are ignored.
 * List types for the fields are constructed with LISTPRE and LISTSIFF.
 */
static tmstring fnalltypes( const_origin org, const_tmstring_list tl )
{
    const char *pre;
    const char *suff;
    unsigned int tix;
    tmstring_list nl;
    tmstring ans;

    (void) org;
    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    nl = new_tmstring_list();
    for( tix=0; tix<tl->sz; tix++ ){
	tmsymbol_list fields = new_tmsymbol_list();
	const_tmsymbol tnm = add_tmsymbol( tl->arr[tix] );
	unsigned int fix;

	collect_all_fields( &fields, allds, tnm );
	for( fix=0; fix<fields->sz; fix++ ){
	    const Field e = find_field( allds, tnm, fields->arr[fix] );

	    /* Since we only enumerate the fields we know exist for this
	     * type, this should never fail.
	     */
	    assert( e != FieldNIL );
	    nl = append_tmstring_list(
		nl,
		make_typename( pre, suff, e->type )
	    );
	}
	rfre_tmsymbol_list( fields );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Given a list of types, return the types of the fields of these types.
 * Unknown types are ignored.
 * List types for the fields are constructed with LISTPRE and LISTSIFF.
 */
static tmstring fntypes( const_origin org, const_tmstring_list pl )
{
    unsigned int tix;
    Type_list tl;
    tmstring ans;

    (void) org;
    tl = new_Type_list();
    for( tix=0; tix<pl->sz; tix++ ){
	const_tmsymbol tnm = add_tmsymbol( pl->arr[tix] );
	const unsigned int ix = find_type_ix( allds, tnm );

	if( ix<allds->sz ){
	    const ds d = allds->arr[ix];
	    Field_list fl = Field_listNIL;

	    switch( d->tag ){
		case TAGDsConstructorBase:
		case TAGDsAlias:
		case TAGDsInclude:
		    break;

		case TAGDsTuple:
		    fl = to_DsTuple(d)->fields;
		    break;

		case TAGDsClass:
		    fl = to_DsClass(d)->fields;
		    break;

		case TAGDsConstructor:
		    fl = to_DsConstructor(d)->fields;
		    break;

	    }
	    if( fl != Field_listNIL ){
		unsigned int fix;

		for( fix=0; fix<fl->sz; fix++ ){
		    tl = append_Type_list( tl, rdup_Type( fl->arr[fix]->type ) );
		}
	    }
	}
    }
    ans = flat_Type_list( tl );
    rfre_Type_list( tl );
    return ans;
}

/* Given a list of types 'tl', and a type 't', add it to the list. */
static Type_list add_Type_list( Type_list tl, Type t )
{
    unsigned int ix;

    for( ix=0; ix<tl->sz; ix++ ){
	const_Type lt = tl->arr[ix];

	if( lt->level == t->level && lt->basetype == t->basetype ){
	    rfre_Type( t );
	    return tl;
	}
    }
    return append_Type_list( tl, t );
}

static bool member_Type_list( Type_list tl, const_Type t )
{
    unsigned int ix;

    for( ix=0; ix<tl->sz; ix++ ){
	const_Type e = tl->arr[ix];

	if( e->level == t->level && e->basetype == t->basetype ){
	    return TRUE;
	}
    }
    return FALSE;
}

static bool is_blocked_type( Type_list tl, tmsymbol t )
{
    unsigned int ix;

    for( ix=0; ix<tl->sz; ix++ ){
	const_Type e = tl->arr[ix];

	if( e->level == 0 && e->basetype == t ){
	    return TRUE;
	}
    }
    return FALSE;
}

/* Given a list of type 'tl', an array of 'visited' flags and a type name,
 * update the list of types with the reach of this type.
 */
static Type_list update_reach( Type_list tl, bool *visited, Type_list blocking, tmsymbol tnm )
{
    const unsigned int ix = find_type_ix( allds, tnm );
    Type t;

    if( ix<allds->sz ){
	if( visited[ix] ){
	    /* Been there, done that, got the T-shirt. */
	    return tl;
	}
	visited[ix] = TRUE;
	if( !is_blocked_type( blocking, tnm ) ){
	    tmsymbol_list inheritors;
	    tmsymbol_list fieldnames;
	    const_ds d = allds->arr[ix];
	    unsigned int tix;

	    inheritors = new_tmsymbol_list();
	    collect_inheritors( &inheritors, allds, tnm );
	    for( tix=0; tix<inheritors->sz; tix++ ){
		tl = update_reach( tl, visited, blocking, inheritors->arr[tix] );
	    }
	    rfre_tmsymbol_list( inheritors );
	    fieldnames = new_tmsymbol_list();
	    collect_all_fields( &fieldnames, allds, tnm );
	    for( tix=0; tix<fieldnames->sz; tix++ ){
		Field f = find_field( allds, tnm, fieldnames->arr[tix] );

		if( f != FieldNIL ){
		    tl = update_reach_Type( tl, visited, blocking, f->type );
		}
	    }
	    rfre_tmsymbol_list( fieldnames );
	    switch( d->tag ){
		case TAGDsAlias:
		    tl = update_reach_Type( tl, visited, blocking, to_const_DsAlias(d)->type );
		    break;

		case TAGDsConstructorBase:
		case TAGDsTuple:
		case TAGDsInclude:
		case TAGDsClass:
		case TAGDsConstructor:
		    break;

	    }
	}
    }
    t = new_Type( 0, tnm );
    tl = add_Type_list( tl, t );
    return tl;
}

/* Given a list of types 'tl', an array of 'visited' flags and a type 't',
 * update the list of types with the reach of this type.
 */
static Type_list update_reach_Type( Type_list tl, bool *visited, Type_list blocking, const Type t )
{
    unsigned int level;

    for( level=1; level<=t->level; level++ ){
	Type dt = rdup_Type( t );
	bool is_blocked;

	dt->level = level;
	is_blocked = member_Type_list( blocking, dt );
	tl = add_Type_list( tl, dt );
	if( is_blocked ){
	    return tl;
	}
    }
    tl = update_reach( tl, visited, blocking, t->basetype );
    return tl;
}

/* Given a list of types, return the reach of each of these types.
 * Unknown types have only themselves as reach.
 * Types in the 'blocking' list have only themselves as reach.
 * List types have themselves as reach, plus the reach of their element type.
 * All other types have themselves as reach, plus the reach of the
 * subclasses of the type, and the fields (including inherited ones) of
 * the type.
 * List types for the fields are constructed with LISTPRE and LISTSIFF.
 */
static tmstring fnreach( const_origin org, const_tmstring_list pl )
{
    unsigned int ix;
    Type_list tl;
    tmstring ans;
    bool *visited;
    Type_list blocking;
    unsigned int sz;
    const char *pre;
    const char *suff;
    bool in_blocking;

    (void) org;
    sz = allds->sz;
    tl = new_Type_list();
    blocking = new_Type_list();
    visited = TM_MALLOC( bool *, sizeof(bool)*sz );
    if( visited == NULL ){                          
        return new_tmstring( "" );
    }
    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    for( ix=0; ix<sz; ix++ ){
        visited[ix] = FALSE;
    }
    in_blocking = FALSE;
    for( ix=0; ix<pl->sz; ix++ ){
	Type t;
	tmstring tnm = pl->arr[ix];

	if( tnm[0] == '\0' ){
	    in_blocking = TRUE;
	}
	else if( in_blocking ){
	    t = split_type( pre, suff, tnm );
	    blocking = append_Type_list( blocking, t );
	}
    }
    for( ix=0; ix<pl->sz; ix++ ){
	Type t;
	tmstring tnm = pl->arr[ix];

	if( tnm[0] == '\0' ){
	    break;
	}
	t = split_type( pre, suff, tnm );
	tl = update_reach_Type( tl, visited, blocking, t );
	rfre_Type( t );
    }
    TM_FREE( visited );          
    ans = flat_Type_list( tl );
    rfre_Type_list( tl );
    rfre_Type_list( blocking );
    return ans;
}

/* Given a type name and element name, return the
   type of the given element, constructed from its type name and list level.
 */
static tmstring fntype( const_origin org, const_tmstring_list sl )
{
    const_Field e;
    const char *pre;
    const char *suff;

    if( sl->sz != 2 ){
	origin_error( org, "'type' requires a type and an element name" );
	return new_tmstring( "" );
    }
    e = find_field( allds, add_tmsymbol( sl->arr[0] ), add_tmsymbol( sl->arr[1] ) );
    if( e == FieldNIL ){
	origin_error( org, "type `%s' has no field `%s'", sl->arr[0], sl->arr[1] );
	return new_tmstring( "" );
    }
    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    return make_typename( pre, suff, e->type );
}

/* construct a list of constructors for the given types */
static tmstring fnconslist( const_origin org, const_tmstring_list tl )
{
    tmsymbol_list nl;
    unsigned int tix;
    tmstring ans;

    (void) org;
    nl = new_tmsymbol_list();
    for( tix=0; tix<tl->sz; tix++ ){
	unsigned int dix = find_type_ix( allds, add_tmsymbol( tl->arr[tix] ) );

	if( dix<allds->sz ){
	    const_ds d = allds->arr[dix];

	    if( d->tag == TAGDsConstructorBase ){
		nl = concat_tmsymbol_list(
		    nl,
		    rdup_tmsymbol_list( to_const_DsConstructorBase(d)->constructors )
		);
	    }
	}
    }
    ans = flatsymbols( nl );
    rfre_tmsymbol_list( nl );
    return ans;
}

/* construct a list of fields for given type */
static tmstring fncelmlist( const_origin org, const_tmstring_list sl )
{
    const_ds d;
    const_tmsymbol_list cl;
    tmstring ans;
    tmsymbol_list nl;

    if( sl->sz != 2 ){
	origin_error( org, "'celmlist' requires two parameters" );
	return new_tmstring( "" );
    }
    d = findtype( org, allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsConstructorBase ){
	origin_error( org, "type `%s' is not a constructor type", sl->arr[0] );
	return new_tmstring( "" );
    }
    cl = to_const_DsConstructorBase(d)->constructors;
    if( !member_tmsymbol_list( add_tmsymbol( sl->arr[1] ), cl ) ){
	origin_error( org, "type `%s' does not have a constructor `%s'", sl->arr[0], sl->arr[1] );
    }
    nl = new_tmsymbol_list();
    collect_fields( &nl, allds, add_tmsymbol( sl->arr[1] ) );
    ans = flatsymbols( nl );
    rfre_tmsymbol_list( nl );
    return ans;
}

/* Given a type name, constructor name and element name, return the
   type name of the given element.

   It is not possible to determine whether it is a list of elements
   or not from this list.
 */
static tmstring fnctypename( const_origin org, const_tmstring_list sl )
{
    const_ds d;
    tmsymbol_list cl;
    const_Field e;

    if( sl->sz != 3 ){
	origin_error( org, "'ctypename' requires a type, a constructor and a field name" );
	return new_tmstring( "" );
    }
    d = findtype( org, allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsConstructorBase ){
	origin_error( org, "type `%s' is not a constructor type", sl->arr[0] );
	return new_tmstring( "" );
    }
    cl = to_const_DsConstructorBase(d)->constructors;
    if( !member_tmsymbol_list( add_tmsymbol( sl->arr[1] ), cl ) ){
	origin_error( org, "type `%s' does not have a constructor `%s'", sl->arr[0], sl->arr[1] );
    }
    e = find_field( allds, add_tmsymbol( sl->arr[1] ), add_tmsymbol( sl->arr[2] ) );
    if( e == FieldNIL ){
	origin_error( org, "constructor `%s' does not have a field `%s'", sl->arr[1], sl->arr[2] );
	return new_tmstring( "" );
    }
    return new_tmstring( e->type->basetype->name );
}

/* given a type name, constructor name and element name, return the
   type class of the given element.

   Possible type classes are:
    single
    list
 */
static tmstring fnctypeclass( const_origin org, const_tmstring_list sl )
{
    const_ds d;
    tmsymbol_list cl;
    const_Field e;

    if( sl->sz != 3 ){
	origin_error( org, "'ctypeclass' requires a type, a constructor and a field name" );
	return new_tmstring( "" );
    }
    d = findtype( org, allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsConstructorBase ){
	origin_error( org, "type `%s' is not a constructor type", sl->arr[0] );
	return new_tmstring( "" );
    }
    cl = to_const_DsConstructorBase(d)->constructors;
    if( !member_tmsymbol_list( add_tmsymbol( sl->arr[1] ), cl ) ){
	origin_error( org, "type `%s' does not have a constructor `%s'", sl->arr[0], sl->arr[1] );
    }
    e = find_field( allds, add_tmsymbol( sl->arr[1] ), add_tmsymbol( sl->arr[2] ) );
    if( e == FieldNIL ){
	origin_error( org, "constructor `%s' does not have a field `%s'", sl->arr[1], sl->arr[2] );
	return new_tmstring( "" );
    }
    return new_tmstring( ( e->type->level!=0 ? "list" : "single" ) );
}

/* given a type name, constructor name and element name, return the
   list level of the given element.

 */
static tmstring fnctypellev( const_origin org, const_tmstring_list sl )
{
    const_ds d;
    tmsymbol_list cl;
    const_Field e;

    if( sl->sz != 3 ){
	origin_error( org, "'ctypellev' requires a type, a constructor and a field name" );
	return new_tmstring( "" );
    }
    d = findtype( org, allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsConstructorBase ){
	origin_error( org, "type '%s' is not a constructor type", sl->arr[0] );
	return new_tmstring( "" );
    }
    cl = to_const_DsConstructorBase(d)->constructors;
    if( !member_tmsymbol_list( add_tmsymbol( sl->arr[1] ), cl ) ){
	origin_error( org, "type `%s' does not have a constructor `%s'", sl->arr[0], sl->arr[1] );
    }
    e = find_field( allds, add_tmsymbol( sl->arr[1] ), add_tmsymbol( sl->arr[2] ) );
    if( e == FieldNIL ){
	origin_error( org, "constructor `%s' does not have a field `%s'", sl->arr[1], sl->arr[2] );
	return new_tmstring( "" );
    }
    return newuintstr( e->type->level );
}

/* Given a type name 't' and a list of types 'tl', return 'TRUE' if
 * 't' depends on one of the types in 'tl'. That is, 't' is a tuple
 * type, and at least one of the field types of 't' occurs in tl'.
 *
 * Constructor types are not supposed to depend on other types.
 *
 * List types depend on their element types; for nested types this
 * applies transitively.
 */
static bool depends_on( const char *pre, const char *suff, const_tmsymbol t, const_tmsymbol_list tl )
{
    unsigned int ix;
    const_ds d;

    if( pre[0] != '\0' || suff[0] != '\0' ){
	tmstring base = get_element_type( pre, suff, t->name );

	while( base != tmstringNIL ){
	    tmstring nw;

	    if( member_tmsymbol_list( add_tmsymbol( base ), tl ) ){
		rfre_tmstring( base );
		return TRUE;
	    }
	    nw = get_element_type( pre, suff, base );
	    rfre_tmstring( base );
	    base = nw;
	}
    }
    ix = find_type_ix( allds, t );
    if( ix>=allds->sz ){
	return FALSE;
    }
    d = allds->arr[ix];
    if( any_member_tmsymbol_list( d->inherits, tl ) ){
	return TRUE;
    }
    switch( d->tag ){
	case TAGDsConstructorBase:
	case TAGDsInclude:
	    break;

	case TAGDsAlias:
	{
	    const_Type t = to_const_DsAlias(d)->type;

	    if( t->level==0 && member_tmsymbol_list( t->basetype, tl ) ){
		return TRUE;
	    }
	    break;
	}

	case TAGDsTuple:
	{
	    const_Field_list fl = to_const_DsTuple(d)->fields;

	    for( ix=0; ix<fl->sz; ix++ ){
		const Field e = fl->arr[ix];
		const Type t = e->type;

		if( t->level==0 && member_tmsymbol_list( t->basetype, tl ) ){
		    return TRUE;
		}
	    }
	    break;
	}

	case TAGDsClass:
	{
	    const_Field_list fl = to_const_DsClass(d)->fields;

	    for( ix=0; ix<fl->sz; ix++ ){
		const Field e = fl->arr[ix];
		const Type t = e->type;

		if( t->level==0 && member_tmsymbol_list( t->basetype, tl ) ){
		    return TRUE;
		}
	    }
	    break;
	}

	case TAGDsConstructor:
	{
	    const_Field_list fl = to_const_DsConstructor(d)->fields;

	    for( ix=0; ix<fl->sz; ix++ ){
		const Field e = fl->arr[ix];
		const Type t = e->type;

		if( t->level==0 && member_tmsymbol_list( t->basetype, tl ) ){
		    return TRUE;
		}
	    }
	    break;
	}

    }
    return FALSE;
}

/* Given a list of type names, re-arrange them so that all tuple types
   that use a certain type are placed after the type itself.
   This is done with a topological search: take the first type that
   does not have dependent in the list, delete it from the list.
   Collect these types in a new list.
   Repeat until all types are deleted from the input list.
 */
static tmstring fndepsort( const_origin org, const_tmstring_list real_sl )
{
    tmsymbol_list nl;
    tmsymbol t;
    tmstring ans;
    unsigned int ix;
    const char *pre;
    const char *suff;
    tmsymbol_list sl = setroom_tmsymbol_list( new_tmsymbol_list(), real_sl->sz );

    for( ix=0; ix<real_sl->sz; ix++ ){
        sl = append_tmsymbol_list( sl, add_tmsymbol( real_sl->arr[ix] ) );
    }
    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    nl = new_tmsymbol_list();
    while( sl->sz!=0 ){
	bool found = FALSE;
	unsigned int ix = 0;
	unsigned int foundix = 0;

	while( !found && ix<sl->sz ){
	    t = sl->arr[ix];
	    if( !depends_on( pre, suff, t, sl ) ){
		 found = TRUE;
		 foundix = ix;
	    }
	    ix++;
	}
	if( !found ){
            tmstring baddies = flatsymbols( sl );

	    origin_error( org, "circular dependency: %s", baddies );
	    rfre_tmstring( baddies );
	    break;
	}
	t = sl->arr[foundix];
	nl = append_tmsymbol_list( nl, t );
	sl = delete_tmsymbol_list( sl, foundix );
    }
    rfre_tmsymbol_list( sl );
    ans = flatsymbols( nl );
    rfre_tmsymbol_list( nl );
    return ans;
}

/* Given a type name 't' and a list of types 'tl', return 'TRUE' if
 * 't' depends on one of the types in 'tl'. That is, 't' is a tuple
 * type, and at least one of the field types of 't' occurs in tl'.
 *
 * Constructor types are not supposed to depend on other types.
 *
 * List types depend on their element types; for nested types this
 * applies transitively.
 */
static bool inherit_depends_on( const_tmstring t, const_tmstring_list tl )
{
    unsigned int ix;
    tmsymbol_list inherits;

    inherits = extract_inherits( allds, add_tmsymbol( t ) );
    if( inherits == tmsymbol_listNIL ){
	return FALSE;
    }
    for( ix=0; ix<inherits->sz; ix++ ){
	if( member_tmstring_list( inherits->arr[ix]->name, tl ) ){
	    return TRUE;
	}
    }
    return FALSE;
}

/* Given a list of type names, re-arrange them so that inherited types
   are placed before their inheritors.

   This is done with a topological search: take the first type that
   does not have dependent in the list, delete it from the list.
   Collect these types in a new list.
   Repeat until all types are deleted from the input list.
 */
static tmstring fninheritsort( const_origin org, const_tmstring_list real_sl )
{
    tmstring_list nl;
    tmstring ans;
    tmstring_list sl = rdup_tmstring_list( real_sl );

    nl = new_tmstring_list();
    while( sl->sz!=0 ){
        bool found = FALSE;
        unsigned int ix = 0;
        unsigned int foundix = 0;
        tmstring t;

	while( !found && ix<sl->sz ){
	    t = sl->arr[ix];
	    if( !inherit_depends_on( t, sl ) ){
		 found = TRUE;
		 foundix = ix;
	    }
	    ix++;
	}
	if( !found ){
            tmstring baddies = flatstrings( sl );

	    origin_error( org, "circular dependency: %s", baddies );
	    rfre_tmstring( baddies );
	    break;
	}
	t = sl->arr[foundix];
	nl = append_tmstring_list( nl, rdup_tmstring( t ) );
	sl = delete_tmstring_list( sl, foundix );
    }
    rfre_tmstring_list( sl );
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

static tmstring fndsfilename( const_origin org, const_tmstring_list sl )
{

    if( sl->sz!=0 ){
	origin_error( org, "'dsfilename' does not need any parameters" );
    }
    return new_tmstring( dsfilename );
}

static tmstring fntplfilename( const_origin org, const_tmstring_list sl )
{

    if( sl->sz!=0 ){
	origin_error( org, "'tplfilename' does not need any parameters" );
    }
    return new_tmstring( org->file->name );
}

static tmstring fntpllineno( const_origin org, const_tmstring_list sl )
{

    if( sl->sz != 0 ){
	origin_error( org, "'tpllineno' does not need any parameters" );
    }
    return newuintstr( org->line );
}

/* Return true iff the given argument is the name of a variable. */
static tmstring fndefined( const_origin org, const_tmstring_list sl )
{
    char *v;

    if( sl->sz != 1 ){
	origin_error( org, "'defined' requires exactly one parameter, not %u", sl->sz );
	return newboolstr( 0 );
    }
    v = getvar( sl->arr[0] );
    return newboolstr( v != CHARNIL );
}

/* Return true iff the given argument is the name of a defined macro. */
static tmstring fndefinedmacro( const_origin org, const_tmstring_list sl )
{
    macro v;

    if( sl->sz != 1 ){
	origin_error( org, "'definedmacro' requires exactly one parameter, not %u", sl->sz );
	return newboolstr( 0 );
    }
    v = findmacro( sl->arr[0] );
    return newboolstr( v != macroNIL );
}

/* matchmacro pat
 * Return a list of all macros whose name matches pattern 'pat'.
 */
static tmstring fnmatchmacro( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    const char *errm;
    tmstring_list nl;

    if( sl->sz != 1 ){
	origin_error( org, "'matchmacro' requires exactly one parameter, not %u", sl->sz );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    errm = match_macros( sl->arr[0], &nl );
    if( errm != (char *) NULL ){
	origin_error( org, "bad regular expression: %s", errm );
	rfre_tmstring_list( nl );
	return new_tmstring( "" );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* matchvar pat
 * Return a list of all vars whose name matches pattern 'pat'.
 */
static tmstring fnmatchvar( const_origin org, const_tmstring_list sl )
{
    tmstring ans;
    const char *errm;
    tmstring_list nl;

    if( sl->sz != 1 ){
	origin_error( org, "'matchvar' requires exactly one parameter, not %u", sl->sz );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    errm = match_vars( sl->arr[0], &nl );
    if( errm != NULL ){
	origin_error( org, "bad regular expression: %s", errm );
	rfre_tmstring_list( nl );
	return new_tmstring( "" );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* -- nested evaluation: 'call' and 'eval' -- */

/* Evaluate the given parameters again. */
static tmstring fneval( const_origin org, const_tmstring_list sl )
{
    tmstring_list nl = new_tmstring_list();
    tmstring ans;
    unsigned int ix;

    (void) org;
    for( ix=0; ix<sl->sz; ix++ ){
        tmstring is = sl->arr[ix];
        tmstring os = alevalto( org, &is, '\0' );
	nl = append_tmstring_list( nl, os );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Call a macro. */
static tmstring fncall( const_origin org, const_tmstring_list orgsl )
{
    tmstring_list sl;
    tmstring nm;
    tmstring_list formals;
    unsigned int ix;
    const_macro m;
    tmstring retval;

    if( orgsl->sz<1 ){
	origin_error( org, "no macro name given" );
	return new_tmstring( "" );
    }
    sl = rdup_tmstring_list( orgsl );
    nm = rdup_tmstring( sl->arr[0] );
    sl = delete_tmstring_list( sl, 0 );
    m = findmacro( nm );
    if( m == macroNIL ){
	origin_error( org, "macro `%s' does not exist", nm );
	rfre_tmstring_list( sl );
	rfre_tmstring( nm );
	return new_tmstring( "" );
    }
    formals = m->fpl;
    rfre_tmstring( nm );
    if( formals->sz != sl->sz ){
	origin_error(
            org,
            "wrong number of parameters for macro `%s': %u instead of %u",
	    m->name,
	    sl->sz,
	    formals->sz
        );
	rfre_tmstring_list( sl );
	return new_tmstring( "" );
    }
    newvarctx();
    setvar( "templatefile", m->org->file->name );
    for( ix=0; ix<sl->sz; ix++ ){
	setvar( formals->arr[ix], sl->arr[ix] );
    }
    rfre_tmstring_list( sl );
    dotrans( m->body, (FILE *)0 );
    retval =  getretval();
    flushvar();
    return retval;
}

/* -- OS interface -- */

/* Return the search path */
static tmstring fnsearchpath( const_origin org, const_tmstring_list sl )
{
    if( sl->sz!=0 ){
	origin_error( org, "'searchpath' does not need any parameters" );
    }
    return flatstrings( searchpath );
}

/* Interpret each tmstring in the list as a file name, and search
 * for the file in the search path.
 * If a file can not be found, replace its entry in the resulting
 * list with '?'.
 * The access mode is assumed to be 'r'.
 */
static tmstring fnsearchfile( const_origin org, const_tmstring_list sl )
{
    unsigned int ix;
    tmstring_list nl;
    tmstring ans;

    (void) org;
    nl = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
        tmstring path = search_file( searchpath, sl->arr[ix], PATHSEPSTR, "r" );

	if( path == tmstringNIL ){
	    path = new_tmstring( "?" );
	}
	nl = append_tmstring_list( nl, path );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* See if an environment variable is set. */
static tmstring fnisinenv( const_origin org, const_tmstring_list sl )
{
    char *v;

    if( sl->sz != 1 ){
	origin_error( org, "'isinenv' requires exactly one parameter, not %u", sl->sz );
	return new_tmstring( "0" );
    }
    v = getenv( sl->arr[0] );
    return newboolstr( v == NULL );
}

/* access of environment variables */
static tmstring fngetenv( const_origin org, const_tmstring_list sl )
{
    const char *v;

    if( sl->sz != 1 ){
	origin_error( org, "'getenv' requires exactly one parameter, not %u", sl->sz );
	return new_tmstring( "" );
    }
    v = getenv( sl->arr[0] );
    if( v == NULL ){
	v = "";
    }
    return new_tmstring( v );
}

/* Return the current amount of processor time consumed by the program.
 * The time is expressed in milliseconds.
 */
static tmstring fnprocessortime( const_origin org, const_tmstring_list sl )
{
    clock_t t_ticks = clock()-start_time;
    long t_ms = (1000*((long) t_ticks))/CLOCKS_PER_SEC;
    char buf[30];

    if( sl->sz != 0 ){
	origin_error( org, "'processortime' does not need any parameters" );
	return new_tmstring( "0" );
    }
    sprintf( buf, "%ld", t_ms );
    return new_tmstring( buf );
}

/* Return the current clock time.  */
static tmstring fnnow( const_origin org, const_tmstring_list sl )
{
    char buf[30];

    if( sl->sz != 0 ){
	origin_error( org, "'now' does not need any parameters" );
	return new_tmstring( "0" );
    }
    sprintf( buf, "%ld", time( NULL )  );
    return new_tmstring( buf );
}

/* Given a time and a format string, generate a time string in the
 * given format.
 */
static tmstring fnformattime( const_origin org, const_tmstring_list sl )
{
    char buf[STRBUFSIZE+1];
    time_t t;
    const char *fmt;

    if( sl->sz < 1 ){
	origin_error( org, "'formattime' requires at least a time" );
	return new_tmstring( "" );
    }
    if( sl->sz < 2 ){
	fmt = "%a %b %d %Y %H:%M:%S";
    }
    else {
	fmt = sl->arr[1];
    }
    if( sl->sz>2 ){
	origin_error( org, "'formattime' requires one or two" );
	return new_tmstring( "" );
    }
    cknumpar( org, sl->arr[0] );
    t = (time_t) atol( sl->arr[0] );
    (void) strftime( buf, STRBUFSIZE, fmt, gmtime( &t ) );
    return new_tmstring( buf );
}

/* ------ function table ------ */

typedef tmstring (*charfn)( const_origin org, const_tmstring_list );

/* structure to describe an entry in the table of functions */
struct fnentry {
    const char *fnname;
    const charfn fncode;
};

/* table of functions. It is terminated by an entry with an
   empty function name
 */
static struct fnentry fntab[] = {
     { "!=", fnneq },
     { "%", fnmod },
     { "*", fntimes },
     { "+", fnplus },
     { "-", fnsubtract },
     { "/", fndiv },
     { "<", fnless },
     { "<=", fnlesseq },
     { "==", fneq },
     { ">", fngreater },
     { ">=", fngreatereq },
     { "alias", fnalias },
     { "aliases", fnaliases },
     { "allfields", fnallfields },
     { "alltypes", fnalltypes },
     { "and", fnand },
     { "call", fncall },
     { "capitalize", fncapitalize },
     { "celmlist", fncelmlist },
     { "classlist", fnclasslist },
     { "comm", fncomm },
     { "conslist", fnconslist },
     { "constructorlist", fnconstructorlist },
     { "ctypeclass", fnctypeclass },
     { "ctypelist", fnctypelist },
     { "ctypellev", fnctypellev },
     { "ctypename", fnctypename },
     { "defined", fndefined },
     { "definedmacro", fndefinedmacro },
     { "delisttypes", fndelisttypes },
     { "depsort", fndepsort },
     { "dsfilename", fndsfilename },
     { "eq", fnstreq },
     { "eval", fneval },
     { "excl", fnexcl },
     { "fields", fnfields },
     { "filt", fnfilt },
     { "first", fnfirst },
     { "formattime", fnformattime },
     { "getenv", fngetenv },
     { "if", fnif },
     { "index", fnindex },
     { "inheritors", fninheritors },
     { "inherits", fninherits },
     { "inheritsort", fninheritsort },
     { "isinenv", fnisinenv },
     { "isvirtual", fnisvirtual },
     { "leftstr", fnleftstr },
     { "len", fnlen },
     { "listtypes", fnlisttypes },
     { "matchmacro", fnmatchmacro },
     { "matchvar", fnmatchvar },
     { "max", fnmax },
     { "member", fnmember },
     { "metatype", fnmetatype },
     { "min", fnmin },
     { "mklist", fnmklist },
     { "neq", fnstrneq },
     { "nonvirtual", fnnonvirtual },
     { "not", fnnot },
     { "now", fnnow },
     { "or", fnor },
     { "prefix", fnprefix },
     { "processortime", fnprocessortime },
     { "reach", fnreach },
     { "rev", fnrev },
     { "rightstr", fnrightstr },
     { "rmlist", fnrmlist },
     { "searchfile", fnsearchfile },
     { "searchpath", fnsearchpath },
     { "seplist", fnseplist },
     { "shift", fnshift },
     { "singletypes", fnsingletypes },
     { "sizesort", fnsizesort },
     { "sort", fnsort },
     { "stemname", fnstemname },
     { "strcmp", fnstrcmp },
     { "strindex", fnstrindex },
     { "strlen", fnstrlen },
     { "strpad", fnstrpad },
     { "subclasses", fnsubclasses },
     { "subs", fnsubs },
     { "suffix", fnsuffix },
     { "superclasses", fnsuperclasses },
     { "telmlist", fnfields },
     { "tochar", fntochar },
     { "tolower", fntolower },
     { "toupper", fntoupper },
     { "tplfilename", fntplfilename },
     { "tpllineno", fntpllineno },
     { "tr", fntr },
     { "ttypeclass", fnttypeclass },
     { "ttypelist", fntuplelist },
     { "ttypellev", fntypelevel },
     { "ttypename", fntypename },
     { "tuplelist", fntuplelist },
     { "type", fntype },
     { "typelevel", fntypelevel },
     { "typelist", fntypelist },
     { "typename", fntypename },
     { "types", fntypes },
     { "uniq", fnuniq },
     { "virtual", fnvirtual },
     { "", fnplus }
};

/* Given a function tmstring 'f', evaluate the function
   by looking up the function name in a list and delegating evaluation to
   that function.
 */
tmstring evalfn( const_origin org, const tmstring f )
{
    char *fnname;
    struct fnentry *fp;
    const char *par;
    char *ans;

    if( fntracing ){
	fprintf( tracestream, "evaluating function ${%s}\n", f );
    }
    par = scanword( org, f, &fnname );
    if( fnname == CHARNIL ){
	origin_error( org, "no name specified" );
	return new_tmstring( "" );
    }
    fp = fntab;
    while( fp->fnname[0] != '\0' ){
	if( strcmp( fp->fnname, fnname ) == 0 ) break;
	fp++;
    }
    if( fp->fnname[0] != '\0' ){
	tmstring_list sl = chopstring( org, par );

	ans = (*fp->fncode)( org, sl );
	rfre_tmstring_list( sl );
    }
    else {
	origin_error( org, "no such function: '%s'", fnname );
	ans = new_tmstring( "" );
    }
    fre_tmstring( fnname );
    if( fntracing ){
	fprintf( tracestream, "function value: '%s'\n", ans );
    }
    return ans;
}
