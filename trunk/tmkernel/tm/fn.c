/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: fn.c
 *
 * Handle function expressions.
 */

#include "config.h"

/* Standard UNIX libraries and functions */
#include <stdio.h>
#include <ctype.h>

/* tm library */
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

/***************************************************************
 *   tm functions                                              *
 ***************************************************************/

/* implementation of functions. Each function is given a parameter
   tmstring and an origin tmstring for error messages
 */

/* -- numerical functions -- */

/* max */
static tmstring fnmax( const tmstring_list sl )
{
    int max;
    int n;
    unsigned int ix;

    if( sl->sz<1 ){
	line_error( "'max' requires at least one parameter" );
	return newintstr( 0 );
    }
    max = atoi( sl->arr[0] );
    for( ix=0; ix<sl->sz; ix++ ){
	cknumpar( sl->arr[ix] );
	n = atoi( sl->arr[ix] );
	if( n>max )
	    max = n;
    }
    return newintstr( max );
}

/* min */
static tmstring fnmin( const tmstring_list sl )
{
    int min;
    int n;
    unsigned int ix;

    if( sl->sz<1 ){
	line_error( "'min' requires at least one parameter" );
	return newintstr( 0 );
    }
    min = atoi( sl->arr[0] );
    for( ix=0; ix<sl->sz; ix++ ){
	cknumpar( sl->arr[ix] );
	n = atoi( sl->arr[ix] );
	if( n<min )
	    min = n;
    }
    return newintstr( min );
}

/* addition */
static tmstring fnplus( const tmstring_list sl )
{
    int sum;
    unsigned int ix;

    sum = 0;
    for( ix=0; ix<sl->sz; ix++ ){
	cknumpar( sl->arr[ix] );
	sum += atoi( sl->arr[ix] );
    }
    return newintstr( sum );
}

/* subtraction */
static tmstring fnsubtract( const tmstring_list sl )
{
    int a;

    if( sl->sz != 2 ){
	line_error( "'subtract' requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    a = atoi( sl->arr[0] ) - atoi( sl->arr[1] );
    return newintstr( a );
}

/* multiplication */
static tmstring fntimes( const tmstring_list sl )
{
    int prod;
    unsigned int ix;

    prod = 1;
    for( ix=0; ix<sl->sz; ix++ ){
	cknumpar( sl->arr[ix] );
	prod *= atoi( sl->arr[ix] );
    }
    return newintstr( prod );
}

/* division */
static tmstring fndiv( const tmstring_list sl )
{
    int a;

    if( sl->sz != 2 ){
	line_error( "division requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    a = atoi( sl->arr[0] ) / atoi( sl->arr[1] );
    return newintstr( a );
}

/* modulus */
static tmstring fnmod( const tmstring_list sl )
{
    int a;

    if( sl->sz != 2 ){
	line_error( "modulus requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    a = atoi( sl->arr[0] ) % atoi( sl->arr[1] );
    return newintstr( a );
}

/* -- comparison functions -- */

/* < */
static tmstring fnless( const tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "comparison requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) < atoi( sl->arr[1] );
    return newboolstr( b );
}

/* <= */
static tmstring fnlesseq( const tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "comparison requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) <= atoi( sl->arr[1] );
    return newboolstr( b );
}

/* > */
static tmstring fngreater( const tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "comparison requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) > atoi( sl->arr[1] );
    return newboolstr( b );
}

/* >= */
static tmstring fngreatereq( const tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "comparison requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) >= atoi( sl->arr[1] );
    return newboolstr( b );
}

/* == */
static tmstring fneq( const tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "comparison requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) == atoi( sl->arr[1] );
    return newboolstr( b );
}

/* != */
static tmstring fnneq( const tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "comparison requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) != atoi( sl->arr[1] );
    return newboolstr( b );
}

/* strcmp */
static tmstring fnstrcmp( const tmstring_list sl )
{
    int cmp;

    if( sl->sz != 2 ){
	line_error( "comparison requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cmp = strcmp( sl->arr[0] , sl->arr[1] );
    if( cmp == 0 ) return new_tmstring( "0" );
    if( cmp < 0 ) return new_tmstring( "-1" );
    return new_tmstring( "1" );
}

/* eq */
static tmstring fnstreq( const tmstring_list sl )
{
    int cmp;

    if( sl->sz != 2 ){
	line_error( "comparison requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cmp = strcmp( sl->arr[0] , sl->arr[1] );
    return newboolstr( cmp == 0 );
}

/* neq */
static tmstring fnstrneq( const tmstring_list sl )
{
    int cmp;

    if( sl->sz != 2 ){
	line_error( "comparison requires exactly two parameters" );
	return new_tmstring( "" );
    }
    cmp = strcmp( sl->arr[0] , sl->arr[1] );
    return newboolstr( cmp != 0 );
}

/* -- tmstring functions -- */

/* len */
static tmstring fnlen( const tmstring_list sl )
{
    return newintstr( (int) sl->sz );
}

/* strpad */
static tmstring fnstrpad( const tmstring_list sl )
{
    tmstring w;
    tmstring wp;
    unsigned int len;
    tmstring pw;
    tmstring buf;
    tmstring bufp;

    if( sl->sz != 3 ){
	line_error( "'pad' requires exactly three parameters" );
	return new_tmstring( "" );
    }
    w = sl->arr[0];
    pw = sl->arr[2];
    if( *pw == '\0' ){
	line_error( "empty padding string" );
	return new_tmstring( "" );;
    }
    cknumpar( sl->arr[1] );
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
static tmstring fnstrlen( const tmstring_list sl )
{
    int l;

    if( sl->sz<1 ){
	l = 0;
    }
    else {
	l = (int) strlen( sl->arr[0] );
    }
    return newintstr( l );
}

/* capitalize */
static tmstring fncapitalize( const tmstring_list sl )
{
    char *np;
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;

    nl = rdup_tmstring_list( sl );
    for( ix=0; ix<nl->sz; ix++ ){
	np = nl->arr[ix];
	if( *np != '\0' && islower( *np ) ){
	    *np -= (char) ('a' - 'A');
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* toupper */
static tmstring fntoupper( const tmstring_list sl )
{
    char *np;
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;

    nl = rdup_tmstring_list( sl );
    for( ix=0; ix<nl->sz; ix++ ){
	np = nl->arr[ix];
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
static tmstring fntolower( const tmstring_list sl )
{
    char *np;
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;

    nl = rdup_tmstring_list( sl );
    for( ix=0; ix<nl->sz; ix++ ){
	np = nl->arr[ix];
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

/* strindex <c> <word> */
static tmstring fnstrindex( const tmstring_list sl )
{
    int n;
    char *ixp;

    if( sl->sz != 2 ){
	line_error( "'strindex' requires exactly two parameters" );
	return new_tmstring( "" );
    }
    ixp = strchr( sl->arr[1], sl->arr[0][0] );
    n = ( ixp == CHARNIL ? 0 : 1 + (int)(ixp - sl->arr[1]) );
    return newintstr( n );
}

/* index <elm> <list> */
/* Note that due to a coincidence the index in the tmstring list
 * the correct index to return.
 */
static tmstring fnindex( const tmstring_list sl )
{
    unsigned int ix;
    tmstring estr;

    if( sl->sz<1 ){
	line_error( "'index' requires at least one parameter" );
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
static tmstring fnmember( const tmstring_list sl )
{
    unsigned int ix;
    tmstring estr;
    bool found = FALSE;

    if( sl->sz<1 ){
	line_error( "'member' requires at least one parameter" );
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
static tmstring fnseplist( const tmstring_list sl )
{
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz<1 ){
	line_error( "'seplist' requires at least one parameter" );
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
static tmstring fnprefix( const tmstring_list sl )
{
    tmstring pfstr;
    tmstring ans;
    tmstring buf;
    size_t len;
    size_t maxlen;
    tmstring_list nl;
    unsigned int ix;

    if( sl->sz<1 ){
	line_error( "'prefix' requires at least one parameter" );
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
static tmstring fnsuffix( const tmstring_list sl )
{
    tmstring sfstr;
    tmstring ans;
    tmstring buf;
    size_t len;
    size_t maxlen;
    tmstring_list nl;
    unsigned int ix;

    if( sl->sz<1 ){
	line_error( "'suffix' requires at least one parameter" );
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
     const char **sa = (const char **) pa;
     const char **sb = (const char **) pb;

     return strcmp( *sa, *sb );
}

/* sort e1..en */
static tmstring fnsort( const tmstring_list sl )
{
    tmstring ans;
    int (*cmpf)( const void *, const void * );

    cmpf = sortcmp;
    qsort( sl->arr, sl->sz, sizeof( sl->arr[0] ), cmpf );
    ans = flatstrings( sl );
    return ans;
}

static int sizesortcmp( const void *pa, const void *pb )
{
     const char **sa = (const char **) pa;
     const char **sb = (const char **) pb;
     size_t sza;
     size_t szb;

     sza = strlen( *sa );
     szb = strlen( *sb );
     if( sza<szb ){
	 return -1;
     }
     if( sza>szb ){
	 return 1;
     }
     return strcmp( *sa, *sb );
}

/* sizesort e1..en */
static tmstring fnsizesort( const tmstring_list sl )
{
    tmstring ans;
    int (*cmpf)( const void *, const void * );

    cmpf = sizesortcmp;
    qsort( sl->arr, sl->sz, sizeof( sl->arr[0] ), cmpf );
    ans = flatstrings( sl );
    return ans;
}

/* rev e1..en */
static tmstring fnrev( const tmstring_list sl )
{
    unsigned int lix;
    unsigned int rix;
    tmstring tmp;
    char *ans;

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
static tmstring fncomm( const tmstring_list sl )
{
    unsigned int aix;
    unsigned int bix;
    unsigned int sepix;
    tmstring tofind;
    char *ans;
    tmstring_list nl;
    bool takeit;

    sepix = 0;
    while( sepix<sl->sz && sl->arr[sepix][0] != '\0' ) sepix++;
    if( sepix>=sl->sz ){
	line_error( "no separator" );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    for( aix=0; aix<sepix; aix++ ){
	takeit = FALSE;
	tofind = sl->arr[aix];
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
static tmstring fnexcl( const tmstring_list sl )
{
    unsigned int aix;
    unsigned int bix;
    unsigned int sepix;
    tmstring tofind;
    char *ans;
    tmstring_list nl;
    bool takeit;

    sepix = 0;
    while( sepix<sl->sz && sl->arr[sepix][0] != '\0' ){
	sepix++;
    }
    if( sepix>=sl->sz ){
	line_error( "no separator" );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    for( aix=0; aix<sepix; aix++ ){
	takeit = TRUE;
	tofind = sl->arr[aix];
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
static tmstring fnuniq( const tmstring_list sl )
{
    tmstring_list nl;
    tmstring ans;
    tmstring prevstr;
    unsigned int ix;
    int (*cmpf)( const void *, const void * );

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
static tmstring fnfilt( const tmstring_list sl )
{
    tmstring ans;
    tmstring errm;
    char buf[STRBUFSIZE];
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz < 2 ){
	line_error( "'filt' requires at least two parameters" );
	return new_tmstring( "" );
    }
    errm = ref_comp( sl->arr[0] );
    if( errm != tmstringNIL ){
	(void) strcpy( errarg, errm );
	line_error( "bad regular expression" );
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
static tmstring fnsubs( const tmstring_list sl )
{
    tmstring ans;
    tmstring errm;
    char buf[STRBUFSIZE];
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz < 2 ){
	line_error( "'subs' requires at least two parameters" );
	return new_tmstring( "" );
    }
    errm = ref_comp( sl->arr[0] );
    if( errm != tmstringNIL ){
	(void) strcpy( errarg, errm );
	line_error( "bad regular expression" );
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
static tmstring fnrmlist( const tmstring_list sl )
{
    tmstring ans;
    tmstring errm;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz < 1 ){
	line_error( "'rmlist' requires at least one parameter" );
	return new_tmstring( "" );
    }
    errm = ref_comp( sl->arr[0] );
    if( errm != tmstringNIL ){
	(void) strcpy( errarg, errm );
	line_error( "bad regular expression" );
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
static tmstring fnfirst( const tmstring_list sl )
{
    tmstring ans;

    if( sl->sz <1 ){
	ans = new_tmstring( "" );
    }
    else {
	ans = new_tmstring( sl->arr[0] );
    }
    return ans;
}

/* shift */
static tmstring fnshift( const tmstring_list sl )
{
    unsigned int ix;
    tmstring_list nl;
    tmstring ans;

    nl = new_tmstring_list();
    for( ix=1; ix<sl->sz; ix++ ){
        nl = append_tmstring_list( nl, new_tmstring( sl->arr[ix] ) );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* if */
static tmstring fnif( const tmstring_list sl )
{
    tmstring ans;

    if( sl->sz<1 ){
	line_error( "'if' requires at least a condition expression" );
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
static tmstring fnand( const tmstring_list sl )
{
    bool flag;
    unsigned int ix;

    flag = TRUE;
    for( ix=0; ix<sl->sz; ix++ ){
	flag = istruestr( sl->arr[ix] );
	if( !flag ) break;
    }
    return newboolstr( flag );
}

/* or */
static tmstring fnor( const tmstring_list sl )
{
    bool flag;
    unsigned int ix;

    flag = FALSE;
    for( ix=0; ix<sl->sz; ix++ ){
	flag = istruestr( sl->arr[ix] );
	if( flag ) break;
    }
    return newboolstr( flag );
}

/* not */
static tmstring fnnot( const tmstring_list sl )
{
    bool a;

    if( sl->sz < 1 ){
	a = TRUE;
    }
    else {
	a = isfalsestr( sl->arr[0] );
    }
    return newboolstr( a );
}

/* -- datastructure access & file name access -- */

/* Given a list prefix 'pre' and suffix 'suff', and a type 't',
 * return TRUE if 't' is a list type. That is, it starts with the
 * given 
 */
static tmstring get_element_type( const char *pre, const char *suff, const tmstring t )
{
    const size_t prelen = strlen( pre );
    const size_t sufflen = strlen( suff );
    const size_t tlen = strlen( t );

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

/* listtypes <list> */
static tmstring fnlisttypes( const tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;
    char *pre;
    char *suff;

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
	const tmstring s = sl->arr[ix];
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
static tmstring fndelisttypes( const tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;
    char *pre;
    char *suff;
    size_t sufflen;
    size_t prelen;

    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    prelen = strlen( pre );
    sufflen = strlen( suff );
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
static tmstring fnsingletypes( const tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;
    char *pre;
    char *suff;

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
static tmstring fnstemname( const tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;
    char *pre;
    char *suff;
    size_t sufflen;
    size_t prelen;

    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    prelen = strlen( pre );
    sufflen = strlen( suff );
    if( pre[0] == '\0' && suff[0] == '\0' ){
	line_error( "'stemname' cannot function if both '" LISTPRE "' and '" LISTSUFF "' are empty" );
	ans = flatstrings( sl );
	return ans;
    }
    nl = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	tmstring old = rdup_tmstring( sl->arr[ix] );
	tmstring new = get_element_type( pre, suff, old );

	while( new != tmstringNIL ){
	    rfre_tmstring( old );
	    old = new;
	    new = get_element_type( pre, suff, old );
	}
	nl = append_tmstring_list( nl, old );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* mklist <n> <list> */
static tmstring fnmklist( const tmstring_list sl )
{
    tmstring ans;
    int n;
    tmstring_list nl;
    unsigned int ix;
    char *pre;
    char *suff;

    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    if( sl->sz<1 ){
	line_error( "'mklist' requires at least one parameter" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    n = atoi( sl->arr[0] );
    nl = new_tmstring_list();
    for( ix=1; ix<sl->sz; ix++ ){
	nl = append_tmstring_list(
	    nl, 
	    mklistnm( pre, sl->arr[ix], suff, n )
	);
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Construct a list of types. */
static tmstring fntypelist( const tmstring_list sl )
{
    ds d;
    tmstring vp;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz!=0 ){
	line_error( "'typelist' does not need any parameters" );
    }
    nl = new_tmstring_list();
    for( ix = 0; ix< allds->sz; ix++ ){
	d = allds->arr[ix];
	vp = get_type_name( d );
	nl = append_tmstring_list( nl, new_tmstring( vp ) );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Construct a list of constructors. */
static tmstring fnconstructorlist( const tmstring_list sl )
{
    ds d;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz!=0 ){
	line_error( "'constructorlist' does not need any parameters" );
    }
    nl = new_tmstring_list();
    for( ix = 0; ix< allds->sz; ix++ ){
	d = allds->arr[ix];
	switch( d->tag ){
	    case TAGDsCons:
		break;

	    case TAGDsTuple:
		break;

	    case TAGDsClass:
		break;

	    case TAGDsConstructor:
		nl = append_tmstring_list( nl, new_tmstring( d->DsConstructor.name ) );
		break;
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}
/* Construct a list of constructor types. */
static tmstring fnctypelist( const tmstring_list sl )
{
    ds d;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz!=0 ){
	line_error( "'ctypelist' does not need any parameters" );
    }
    nl = new_tmstring_list();
    for( ix = 0; ix< allds->sz; ix++ ){
	d = allds->arr[ix];
	switch( d->tag ){
	    case TAGDsCons:
		nl = append_tmstring_list( nl, new_tmstring( d->DsCons.name ) );
		break;

	    case TAGDsTuple:
		break;

	    case TAGDsClass:
		break;

	    case TAGDsConstructor:
		break;
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Construct a list of tuple types. */
static tmstring fntuplelist( const tmstring_list sl )
{
    ds d;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz!=0 ){
	line_error( "'ttypelist' does not need any parameters" );
    }
    nl = new_tmstring_list();
    for( ix = 0; ix< allds->sz; ix++ ){
	d = allds->arr[ix];
	switch( d->tag ){
	    case TAGDsTuple:
		nl = append_tmstring_list( nl, new_tmstring( d->DsClass.name ) );
		break;

	    case TAGDsCons:
	    case TAGDsConstructor:
	    case TAGDsClass:
		break;

	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Construct a list of class types. */
static tmstring fnclasslist( const tmstring_list sl )
{
    ds d;
    tmstring vp;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz!=0 ){
	line_error( "'classlist' does not need any parameters" );
    }
    nl = new_tmstring_list();
    for( ix = 0; ix< allds->sz; ix++ ){
	d = allds->arr[ix];
	switch( d->tag ){
	    case TAGDsTuple:
	    case TAGDsCons:
	    case TAGDsConstructor:
		break;

	    case TAGDsClass:
		vp = d->DsClass.name;
		nl = append_tmstring_list( nl, new_tmstring( vp ) );
		break;

	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Given a list of types 'dl', search for type with name 't'.
 * Give an error message if it is not found.
 */ 
static ds findtype( ds_list dl, const tmstring t )
{
    unsigned int ix;

    ix = find_type_ix( dl, t );
    if( ix>=dl->sz ){
	(void) strcpy( errarg, t );
	line_error( "unknown type" );
	return dsNIL;
    }
    return dl->arr[ix];
}

/* Given a type name, return TRUE if the type is virtual. */
static tmstring fnisvirtual( const tmstring_list sl )
{
    ds d;
    bool ans;

    if( sl->sz != 1 ){
	line_error( "'isvirtual' requires exactly one parameter" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL ){
	return new_tmstring( "" );
    }
    ans = FALSE;
    switch( d->tag ){
	case TAGDsCons:
	    ans = TRUE;
	    break;

	case TAGDsTuple:
	case TAGDsConstructor:
	    break;

	case TAGDsClass:
	    ans = d->DsClass.virtual;
	    break;

    }
    return newboolstr( ans );
}

/* Given a type name, return the subclasses (transitive closure of inherits)
 * of this type.
 */
static tmstring fnsubclasses( const tmstring_list sl )
{
    tmstring ans;
    tmstring_list subclasses;
    unsigned int ix;

    subclasses = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	collect_subclasses( &subclasses, allds, sl->arr[ix] );
    }
    ans = flatstrings( subclasses );
    rfre_tmstring_list( subclasses );
    return ans;
}

/* Given a type name, return the superclasses (transitive closure of inherits)
 * of this type.
 */
static tmstring fnsuperclasses( const tmstring_list sl )
{
    tmstring ans;
    tmstring_list superclasses;

    if( sl->sz != 1 ){
	line_error( "'superclasses' requires exactly one parameter" );
	return new_tmstring( "" );
    }
    superclasses = new_tmstring_list();
    collect_superclasses( &superclasses, allds, sl->arr[0] );
    ans = flatstrings( superclasses );
    rfre_tmstring_list( superclasses );
    return ans;
}

/* Given a type name, return the inherits of this type.  */
static tmstring fninherits( const tmstring_list sl )
{
    tmstring ans;

    if( sl->sz != 1 ){
	line_error( "'inherits' requires exactly one parameter" );
	return new_tmstring( "" );
    }
    {
	const tmstring_list inherits = extract_inherits( allds, sl->arr[0] );

	if( inherits == tmstring_listNIL ){
	    sprintf( errarg, "'%s'", sl->arr[0] );
	    line_error( "unknown type" );
	    return new_tmstring( "" );
	}
	ans = flatstrings( inherits );
    }
    return ans;
}

/* Given a type name, return the inheritors (the types that inherit
 * from this type).
 */
static tmstring fninheritors( const tmstring_list sl )
{
    tmstring ans;
    tmstring_list inheritors;

    if( sl->sz != 1 ){
	line_error( "'inheritors' requires exactly one parameter" );
	return new_tmstring( "" );
    }
    inheritors = new_tmstring_list();
    collect_inheritors( &inheritors, allds, sl->arr[0] );
    ans = flatstrings( inheritors );
    rfre_tmstring_list( inheritors );
    return ans;
}

/* Construct a list of fields for the given type.  */
static tmstring fnfields( const tmstring_list sl )
{
    ds d;
    tmstring ans;
    tmstring_list nl;
    bool inherited;

    inherited = FALSE;
    if( sl->sz != 1 && sl->sz != 2 ){
	line_error( "'fields' requires one or two parameters" );
	return new_tmstring( "" );
    }
    if( sl->sz == 2 ){
	if( strcmp( sl->arr[1], "inherited" ) == 0 ){
	    inherited = TRUE;
	}
	else {
	    line_error( "'fields' second parameter must be absent or `inherited'" );
	}
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL ){
	/* findtype already complained about this. */
	return new_tmstring( "" );
    }
    if( d->tag == TAGDsCons ){
	sprintf( errarg, "type `%s'", sl->arr[0] );
	line_error( "'fields' does not work on a constructor type" );
	/* Fall through, since nothing chokes on a constructor type. */
    }
    nl = new_tmstring_list();
    if( inherited ){
	collect_all_fields( &nl, allds, sl->arr[0] );
    }
    else {
	collect_fields( &nl, allds, sl->arr[0] );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Given a tuple type name and element name, return the
   type name of the given element.
 */
static tmstring fntypename( const tmstring_list sl )
{
    field e;

    if( sl->sz != 2 ){
	line_error( "'ttypename' requires a type and an element name" );
	return new_tmstring( "" );
    }
    e = find_field( allds, sl->arr[0], sl->arr[1] );
    if( e == fieldNIL ){
	sprintf( errarg, "'%s' in type '%s'", sl->arr[1], sl->arr[0] );
	line_error( "field not found" );
	return new_tmstring( "" );
    }
    return new_tmstring( e->type );
}

/* Given a type name and element name, return the
   type class of the given element.

   Possible type classes are: `single' and `list'.
 */
static tmstring fnttypeclass( const tmstring_list sl )
{
    field e;

    if( sl->sz != 2 ){
	line_error( "'fieldtypeclass' requires a type and an element name" );
	return new_tmstring( "" );
    }
    e = find_field( allds, sl->arr[0], sl->arr[1] );
    if( e == fieldNIL ){
	sprintf( errarg, "'%s' in type '%s'", sl->arr[1], sl->arr[0] );
	line_error( "field not found" );
	return new_tmstring( "" );
    }
    return new_tmstring( ( e->level != 0 ? "list" : "single" ) );
}

/* Given a type name and element name, return the
   list level of the given element.
 */
static tmstring fntypelevel( const tmstring_list sl )
{
    field e;

    if( sl->sz != 2 ){
	line_error( "'typelevel' requires a type and an element name" );
	return new_tmstring( "" );
    }
    e = find_field( allds, sl->arr[0], sl->arr[1] );
    if( e == fieldNIL ){
	sprintf( errarg, "'%s' in type '%s'", sl->arr[1], sl->arr[0] );
	line_error( "field not found" );
	return new_tmstring( "" );
    }
    return newintstr( e->level );
}

/* Given a list of types, return the types of the fields of these types.
 * Unknown types are ignored.
 * List types for the fields are constructed with LISTPRE and LISTSIFF.
 */
static tmstring fntypes( const tmstring_list tl )
{
    char *pre;
    char *suff;
    unsigned int tix;
    tmstring_list nl;
    tmstring ans;

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
	const tmstring tnm = tl->arr[tix];
	const unsigned int ix = find_type_ix( allds, tnm );

	if( ix<allds->sz ){
	    const ds d = allds->arr[ix];
	    field_list fl = field_listNIL;

	    switch( d->tag ){
		case TAGDsCons:
		    break;

		case TAGDsTuple:
		    fl = d->DsTuple.fields;
		    break;

		case TAGDsClass:
		    fl = d->DsClass.fields;
		    break;

		case TAGDsConstructor:
		    fl = d->DsConstructor.fields;
		    break;

	    }
	    if( fl != field_listNIL ){
		unsigned int fix;

		for( fix=0; fix<fl->sz; fix++ ){
		    field e = fl->arr[fix];

		    nl = append_tmstring_list(
			nl,
			mklistnm( pre, e->type, suff, e->level )
		    );
		}
	    }
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Given a type name and element name, return the
   type of the given element, constructed from its type name and list level.
 */
static tmstring fntype( const tmstring_list sl )
{
    field e;
    char *pre;
    char *suff;

    if( sl->sz != 2 ){
	line_error( "'type' requires a type and an element name" );
	return new_tmstring( "" );
    }
    e = find_field( allds, sl->arr[0], sl->arr[1] );
    if( e == fieldNIL ){
	sprintf( errarg, "'%s' in type '%s'", sl->arr[1], sl->arr[0] );
	line_error( "field not found" );
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
    return mklistnm( pre, e->type, suff, e->level );
}

/* construct a list of constructors for the given types */
static tmstring fnconslist( const tmstring_list tl )
{
    tmstring_list nl;
    unsigned int tix;
    tmstring ans;

    nl = new_tmstring_list();
    for( tix=0; tix<tl->sz; tix++ ){
	unsigned int dix = find_type_ix( allds, tl->arr[tix] );

	if( dix<allds->sz ){
	    const ds d = allds->arr[dix];

	    if( d->tag == TAGDsCons ){
		nl = concat_tmstring_list(
		    nl,
		    rdup_tmstring_list( d->DsCons.constructors )
		);
	    }
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* construct a list of fields for given type */
static tmstring fncelmlist( const tmstring_list sl )
{
    ds d;
    tmstring_list cl;
    tmstring ans;
    tmstring_list nl;
    bool inherited;

    inherited = FALSE;
    if( sl->sz != 2 && sl->sz != 3 ){
	line_error( "'celmlist' requires two or three parameters" );
	return new_tmstring( "" );
    }
    if( sl->sz == 3 ){
	if( strcmp( sl->arr[2], "inherited" ) == 0 ){
	    inherited = TRUE;
	}
	else {
	    line_error( "'celmlist' third parameter must be absent or `inherited'" );
	}
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsCons ){
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "not a constructor type" );
	return new_tmstring( "" );
    }
    cl = d->DsCons.constructors;
    if( !member_tmstring_list( sl->arr[1], cl ) ){
	(void) strcpy( errarg, sl->arr[0] );
	sprintf( errarg, "constructor '%s', type '%s'", sl->arr[1], sl->arr[0] );
	line_error( "not a member of this constructor type" );
    }
    nl = new_tmstring_list();
    if( inherited ){
	collect_all_fields( &nl, allds, sl->arr[1] );
    }
    else {
	collect_fields( &nl, allds, sl->arr[1] );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Given a type name, constructor name and element name, return the
   type name of the given element.

   It is not possible to determine whether it is a list of elements
   or not from this list.
 */
static tmstring fnctypename( const tmstring_list sl )
{
    ds d;
    tmstring_list cl;
    field e;

    if( sl->sz != 3 ){
	line_error( "'ctypename' requires a type, a constructor and a field name" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsCons ){
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "not a constructor type" );
	return new_tmstring( "" );
    }
    cl = d->DsCons.constructors;
    if( !member_tmstring_list( sl->arr[1], cl ) ){
	(void) strcpy( errarg, sl->arr[0] );
	sprintf( errarg, "constructor '%s', type '%s'", sl->arr[1], sl->arr[0] );
	line_error( "not a member of this constructor type" );
    }
    e = find_field( allds, sl->arr[1], sl->arr[2] );
    if( e == fieldNIL ){
	sprintf( errarg, "'%s' in constructor '%s'", sl->arr[2], sl->arr[1] );
	line_error( "field not found" );
	return new_tmstring( "" );
    }
    return new_tmstring( e->type );
}

/* given a type name, constructor name and element name, return the
   type class of the given element.

   Possible type classes are:
    single
    list
 */
static tmstring fnctypeclass( const tmstring_list sl )
{
    ds d;
    tmstring_list cl;
    field e;

    if( sl->sz != 3 ){
	line_error( "'ctypeclass' requires a type, a constructor and a field name" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsCons ){
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "not a constructor type" );
	return new_tmstring( "" );
    }
    cl = d->DsCons.constructors;
    if( !member_tmstring_list( sl->arr[1], cl ) ){
	(void) strcpy( errarg, sl->arr[0] );
	sprintf( errarg, "constructor '%s', type '%s'", sl->arr[1], sl->arr[0] );
	line_error( "not a member of this constructor type" );
    }
    e = find_field( allds, sl->arr[1], sl->arr[2] );
    if( e == fieldNIL ){
	sprintf( errarg, "'%s' in type '%s'", sl->arr[2], sl->arr[1] );
	line_error( "field not found" );
	return new_tmstring( "" );
    }
    return new_tmstring( ( e->level!=0 ? "list" : "single" ) );
}

/* given a type name, constructor name and element name, return the
   list level of the given element.

 */
static tmstring fnctypellev( const tmstring_list sl )
{
    ds d;
    tmstring_list cl;
    field e;

    if( sl->sz != 3 ){
	line_error( "'ctypellev' requires a type, a constructor and a field name" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsCons ){
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "not a constructor type" );
	return new_tmstring( "" );
    }
    cl = d->DsCons.constructors;
    if( !member_tmstring_list( sl->arr[1], cl ) ){
	(void) strcpy( errarg, sl->arr[0] );
	sprintf( errarg, "constructor '%s', type '%s'", sl->arr[1], sl->arr[0] );
	line_error( "not a member of this constructor type" );
    }
    e = find_field( allds, sl->arr[1], sl->arr[2] );
    if( e == fieldNIL ){
	sprintf( errarg, "'%s' in type '%s'", sl->arr[2], sl->arr[1] );
	line_error( "field not found" );
	return new_tmstring( "" );
    }
    return newintstr( e->level );
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
static bool depends_on( const char *pre, const char *suff, const tmstring t, const tmstring_list tl )
{
    unsigned int ix;
    ds d;

    if( pre[0] != '\0' || suff[0] != '\0' ){
	tmstring base = get_element_type( pre, suff, t );

	while( base != tmstringNIL ){
	    tmstring new;

	    if( member_tmstring_list( base, tl ) ){
		rfre_tmstring( base );
		return TRUE;
	    }
	    new = get_element_type( pre, suff, base );
	    rfre_tmstring( base );
	    base = new;
	}
    }
    ix = find_type_ix( allds, t );
    if( ix>=allds->sz ) return FALSE;
    d = allds->arr[ix];
    switch( d->tag ){
	case TAGDsCons:
	    break;

	case TAGDsTuple:
	{
	    field_list fl = d->DsTuple.fields;

	    for( ix=0; ix<fl->sz; ix++ ){
		field e = fl->arr[ix];
		if( e->level==0 && member_tmstring_list( e->type, tl ) ){
		    return TRUE;
		}
	    }
	    break;
	}

	case TAGDsClass:
	{
	    field_list fl = d->DsClass.fields;

	    for( ix=0; ix<fl->sz; ix++ ){
		field e = fl->arr[ix];
		if( e->level==0 && member_tmstring_list( e->type, tl ) ){
		    return TRUE;
		}
	    }
	    break;
	}

	case TAGDsConstructor:
	{
	    field_list fl = d->DsConstructor.fields;

	    for( ix=0; ix<fl->sz; ix++ ){
		field e = fl->arr[ix];
		if( e->level==0 && member_tmstring_list( e->type, tl ) ){
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
static tmstring fndepsort( tmstring_list sl )
{
    unsigned int ix;
    unsigned int foundix;
    bool found;
    tmstring_list nl;
    tmstring t;
    tmstring baddies;
    tmstring ans;
    char *pre;
    char *suff;

    pre = getvar( LISTPRE );
    if( pre == CHARNIL ){
	pre = "";
    }
    suff = getvar( LISTSUFF );
    if( suff == CHARNIL ){
	suff = "";
    }
    nl = new_tmstring_list();
    while( sl->sz!=0 ){
	found = FALSE;
	ix = 0;
	foundix = 0;
	while( !found && ix<sl->sz ){
	    t = sl->arr[ix];
	    if( !depends_on( pre, suff, t, sl ) ){
		 found = TRUE;
		 foundix = ix;
	    }
	    ix++;
	}
	if( !found ){
	    baddies = flatstrings( sl );
	    strncpy( errarg, baddies, ERRARGLEN-1 );
	    errarg[ERRARGLEN-1] = '\0';
	    rfre_tmstring( baddies );
	    line_error( "circular dependency" );
	    break;
	}
	t = sl->arr[foundix];
	nl = append_tmstring_list( nl, rdup_tmstring( t ) );
	sl = delete_tmstring_list( sl, foundix );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

static tmstring fndsfilename( const tmstring_list sl )
{

    if( sl->sz!=0 ){
	line_error( "'dsfilename' does not need any parameters" );
    }
    return new_tmstring( dsfilename );
}

static tmstring fntplfilename( const tmstring_list sl )
{

    if( sl->sz!=0 ){
	line_error( "'tplfilename' does not need any parameters" );
    }
    return new_tmstring( tplfilename );
}

static tmstring fntpllineno( const tmstring_list sl )
{

    if( sl->sz != 0 ){
	line_error( "'tpllineno' does not need any parameters" );
    }
    return newintstr( tpllineno );
}

static tmstring fndefined( const tmstring_list sl )
{
    char *v;

    if( sl->sz<1 ){
	return newboolstr( 0 );
    }
    v = getvar( sl->arr[0] );
    return newboolstr( v != CHARNIL );
}

/* matchmacro pat
 * Return a list of all macros whose name matches pattern 'pat'.
 */
static tmstring fnmatchmacro( const tmstring_list sl )
{
    tmstring ans;
    char *errm;
    tmstring_list nl;

    if( sl->sz != 1 ){
	line_error( "'matchmacro' requires exactly one parameter" );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    errm = match_macros( sl->arr[0], &nl );
    if( errm != NULL ){
	(void) strcpy( errarg, errm );
	line_error( "bad regular expression" );
	rfre_tmstring_list( nl );
	return new_tmstring( "" );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* -- nested evaluation: 'call' and 'eval' -- */

/* Evaluate the given parameters again. */
static tmstring fneval( const tmstring_list sl )
{
    tmstring_list nl;
    tmstring ans;
    unsigned int ix;
    tmstring is;
    tmstring os;

    nl = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	is = sl->arr[ix];
	os = alevalto( &is, '\0' );
	nl = append_tmstring_list( nl, os );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Call a macro. */
static tmstring fncall( tmstring_list orgsl )
{
    tmstring_list sl;
    tmstring nm;
    tmstring_list fpl;
    tmstring oldfname;
    unsigned int ix;
    macro m;
    int oldlno;
    tmstring retval;

    if( orgsl->sz<1 ){
	line_error( "no macro name given" );
	return new_tmstring( "" );
    }
    sl = rdup_tmstring_list( orgsl );
    nm = rdup_tmstring( sl->arr[0] );
    sl = delete_tmstring_list( sl, 0 );
    m = findmacro( nm );
    if( m == macroNIL ){
	sprintf( errarg, "'%s'", nm );
	line_error( "no such macro" );
	rfre_tmstring_list( sl );
	rfre_tmstring( nm );
	return new_tmstring( "" );
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
	return new_tmstring( "" );
    }
    oldlno = tpllineno;
    oldfname = tplfilename;
    tplfilename = m->orgfile;
    newvarctx();
    setvar( "templatefile", m->orgfile );
    for( ix=0; ix<sl->sz; ix++ ){
	setvar( fpl->arr[ix], sl->arr[ix] );
    }
    rfre_tmstring_list( sl );
    dotrans( m->body, (FILE *)0 );
    retval =  getretval();
    flushvar();
    tplfilename = oldfname;
    tpllineno = oldlno;
    return retval;
}

/* -- OS interface -- */

/* Return the search path */
static tmstring fnsearchpath( const tmstring_list sl )
{
    if( sl->sz!=0 ){
	line_error( "'searchpath' does not need any parameters" );
    }
    return flatstrings( searchpath );
}

/* Interpret each tmstring in the list as a file name, and search
 * for the file in the search path.
 * If a file can not be found, replace its entry in the resulting
 * list with '?'.
 * The access mode is assumed to be 'r'.
 */
static tmstring fnsearchfile( const tmstring_list sl )
{
    unsigned int ix;
    tmstring_list nl;
    tmstring path;
    tmstring ans;

    nl = new_tmstring_list();
    for( ix=0; ix<sl->sz; ix++ ){
	path = search_file( searchpath, sl->arr[ix], PATHSEPSTR, "r" );
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
static tmstring fnisinenv( const tmstring_list sl )
{
    char *v;

    if( sl->sz != 1 ){
	line_error( "'isinenv' requires exactly one parameter" );
	return new_tmstring( "0" );
    }
    v = getenv( sl->arr[0] );
    return newboolstr( v == NULL );
}

/* access of environment variables */
static tmstring fngetenv( const tmstring_list sl )
{
    char *v;

    if( sl->sz != 1 ){
	line_error( "'getenv' requires exactly one parameter" );
	return new_tmstring( "" );
    }
    v = getenv( sl->arr[0] );
    if( v == NULL ){
	v = "";
    }
    return new_tmstring( v );
}

/***************************************************************
 *                                                             *
 *   function table                                            *
 *                                                             *
 ***************************************************************/

typedef tmstring (*charfn)( tmstring_list );

/* structure to describe an entry in the table of functions */
struct fnentry {
    char *fnname;
    charfn fncode;
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
     { "depsort", fndepsort },
     { "dsfilename", fndsfilename },
     { "eq", fnstreq },
     { "eval", fneval },
     { "excl", fnexcl },
     { "fields", fnfields },
     { "filt", fnfilt },
     { "first", fnfirst },
     { "getenv", fngetenv },
     { "if", fnif },
     { "index", fnindex },
     { "inheritors", fninheritors },
     { "inherits", fninherits },
     { "delisttypes", fndelisttypes },
     { "isinenv", fnisinenv },
     { "isvirtual", fnisvirtual },
     { "len", fnlen },
     { "listtypes", fnlisttypes },
     { "matchmacro", fnmatchmacro },
     { "max", fnmax },
     { "member", fnmember },
     { "min", fnmin },
     { "mklist", fnmklist },
     { "neq", fnstrneq },
     { "not", fnnot },
     { "or", fnor },
     { "prefix", fnprefix },
     { "rev", fnrev },
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
     { "tolower", fntolower },
     { "toupper", fntoupper },
     { "tplfilename", fntplfilename },
     { "tpllineno", fntpllineno },
     { "ttypeclass", fnttypeclass },
     { "ttypelist", fntuplelist },
     { "ttypellev", fntypelevel },
     { "ttypename", fntypename },
     { "tuplelist", fntuplelist },
     { "type", fntype },
     { "typelevel", fntypelevel },
     { "types", fntypes },
     { "typelist", fntypelist },
     { "typename", fntypename },
     { "uniq", fnuniq },
     { "", fnplus }
};

/* Given a function tmstring 'f', evaluate the function
   by looking up the function name in a list and delegating evaluation to
   that function.
 */
tmstring evalfn( const tmstring f )
{
    char *fnname;
    struct fnentry *fp;
    const char *par;
    char *ans;
    tmstring_list sl;

    if( fntr ){
	fprintf( tracestream, "evaluating function ${%s}\n", f );
    }
    par = scanword( f, &fnname );
    if( fnname == CHARNIL ){
	line_error( "no name specified" );
	return new_tmstring( "" );
    }
    fp = fntab;
    while( fp->fnname[0] != '\0' ){
	if( strcmp( fp->fnname, fnname ) == 0 ) break;
	fp++;
    }
    if( fp->fnname[0] != '\0' ){
	sl = chopstring( par );
	ans = (*fp->fncode)( sl );
	rfre_tmstring_list( sl );
    }
    else {
	(void) strcpy( errarg, fnname );
	line_error( "no such function" );
	ans = new_tmstring( "" );
    }
    fre_tmstring( fnname );
    if( fntr ){
	fprintf( tracestream, "function value: '%s'\n", ans );
    }
    return ans;
}
