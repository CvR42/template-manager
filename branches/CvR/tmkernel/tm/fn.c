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
static tmstring fnmax( tmstring_list sl )
{
    int max;
    int n;
    unsigned int ix;

    if( sl->sz<1 ){
	line_error( "bad number of parameters" );
	return( newintstr( 0 ) );
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
static tmstring fnmin( tmstring_list sl )
{
    int min;
    int n;
    unsigned int ix;

    if( sl->sz<1 ){
	line_error( "bad number of parameters" );
	return( newintstr( 0 ) );
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
static tmstring fnplus( tmstring_list sl )
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
static tmstring fnsubtract( tmstring_list sl )
{
    int a;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    a = atoi( sl->arr[0] ) - atoi( sl->arr[1] );
    return newintstr( a );
}

/* multiplication */
static tmstring fntimes( tmstring_list sl )
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
static tmstring fndiv( tmstring_list sl )
{
    int a;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    a = atoi( sl->arr[0] ) / atoi( sl->arr[1] );
    return newintstr( a );
}

/* modulus */
static tmstring fnmod( tmstring_list sl )
{
    int a;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    a = atoi( sl->arr[0] ) % atoi( sl->arr[1] );
    return newintstr( a );
}

/* -- comparison functions -- */

/* < */
static tmstring fnless( tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) < atoi( sl->arr[1] );
    return newboolstr( b );
}

/* <= */
static tmstring fnlesseq( tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) <= atoi( sl->arr[1] );
    return newboolstr( b );
}

/* > */
static tmstring fngreater( tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) > atoi( sl->arr[1] );
    return newboolstr( b );
}

/* >= */
static tmstring fngreatereq( tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) >= atoi( sl->arr[1] );
    return newboolstr( b );
}

/* == */
static tmstring fneq( tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) == atoi( sl->arr[1] );
    return newboolstr( b );
}

/* != */
static tmstring fnneq( tmstring_list sl )
{
    bool b;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cknumpar( sl->arr[0] );
    cknumpar( sl->arr[1] );
    b = atoi( sl->arr[0] ) != atoi( sl->arr[1] );
    return newboolstr( b );
}

/* strcmp */
static tmstring fnstrcmp( tmstring_list sl )
{
    int cmp;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cmp = strcmp( sl->arr[0] , sl->arr[1] );
    if( cmp == 0 ) return( new_tmstring( "0" ) );
    if( cmp < 0 ) return( new_tmstring( "-1" ) );
    return new_tmstring( "1" );
}

/* eq */
static tmstring fnstreq( tmstring_list sl )
{
    int cmp;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cmp = strcmp( sl->arr[0] , sl->arr[1] );
    return newboolstr( cmp == 0 );
}

/* neq */
static tmstring fnstrneq( tmstring_list sl )
{
    int cmp;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    cmp = strcmp( sl->arr[0] , sl->arr[1] );
    return newboolstr( cmp != 0 );
}

/* -- tmstring functions -- */

/* len */
static tmstring fnlen( tmstring_list sl )
{
    return newintstr( (int) sl->sz );
}

/* strpad */
static tmstring fnstrpad( tmstring_list sl )
{
    tmstring w;
    tmstring wp;
    unsigned int len;
    tmstring pw;
    tmstring buf;
    tmstring bufp;

    if( sl->sz != 3 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    buf = new_tmstring( "" );
    w = sl->arr[0];
    pw = sl->arr[2];
    if( *pw == '\0' ){
	line_error( "empty padding string" );
	return buf;
    }
    cknumpar( sl->arr[1] );
    len = atoi( sl->arr[1] );
    buf = realloc_tmstring( buf, len+1 );
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
static tmstring fnstrlen( tmstring_list sl )
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
static tmstring fncapitalize( tmstring_list sl )
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
static tmstring fntoupper( tmstring_list sl )
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
static tmstring fntolower( tmstring_list sl )
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
static tmstring fnstrindex( tmstring_list sl )
{
    int n;
    char *ixp;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
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
static tmstring fnindex( tmstring_list sl )
{
    unsigned int ix;
    tmstring estr;

    if( sl->sz<1 ){
	line_error( "missing expression" );
	return( new_tmstring( "0" ) );
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
static tmstring fnmember( tmstring_list sl )
{
    unsigned int ix;
    tmstring estr;
    bool found = FALSE;

    if( sl->sz<1 ){
	line_error( "missing expression" );
	return( new_tmstring( "0" ) );
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
static tmstring fnseplist( tmstring_list sl )
{
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz<1 ){
	line_error( "missing expression" );
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
static tmstring fnprefix( tmstring_list sl )
{
    tmstring pfstr;
    tmstring ans;
    tmstring buf;
    unsigned int len;
    unsigned int maxlen;
    tmstring_list nl;
    unsigned int ix;

    buf = new_tmstring( "" );
    if( sl->sz<1 ){
	line_error( "missing expression" );
	return buf;
    }
    pfstr = sl->arr[0];
    maxlen = 0;
    for( ix=1; ix<sl->sz; ix++ ){
	len = (int) strlen( sl->arr[ix] );
	if( len>maxlen ){
	    maxlen = len;
	}
    }
    len = 1 + (int) strlen( pfstr ) + maxlen;
    buf = realloc_tmstring( buf, len );
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
static tmstring fnsuffix( tmstring_list sl )
{
    tmstring sfstr;
    tmstring ans;
    tmstring buf;
    unsigned int len;
    unsigned int maxlen;
    tmstring_list nl;
    unsigned int ix;

    buf = new_tmstring( "" );
    if( sl->sz<1 ){
	line_error( "missing expression" );
	return buf;
    }
    sfstr = sl->arr[0];
    maxlen = 0;
    for( ix=1; ix<sl->sz; ix++ ){
	len = (int) strlen( sl->arr[ix] );
	if( len>maxlen ){
	    maxlen = len;
	}
    }
    len = 1 + (int) strlen( sfstr ) + maxlen;
    buf = realloc_tmstring( buf, len );
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
static tmstring fnsort( tmstring_list sl )
{
    tmstring ans;
    int (*cmpf)( const void *, const void * );

    cmpf = sortcmp;
    qsort( sl->arr, sl->sz, sizeof( sl->arr[0] ), cmpf );
    ans = flatstrings( sl );
    return ans;
}

/* rev e1..en */
static tmstring fnrev( tmstring_list sl )
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
static tmstring fncomm( tmstring_list sl )
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
static tmstring fnexcl( tmstring_list sl )
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
static tmstring fnuniq( tmstring_list sl )
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
   find all elements matching 'findpat' and replace them
   by 'newpat'. Do not copy elements that don't match.
 */
static tmstring fnfilt( tmstring_list sl )
{
    tmstring ans;
    tmstring errm;
    char buf[STRBUFSIZE];
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz < 2 ){
	line_error( "missing parameter" );
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
static tmstring fnsubs( tmstring_list sl )
{
    tmstring ans;
    tmstring errm;
    char buf[STRBUFSIZE];
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz < 2 ){
	line_error( "missing parameter" );
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
static tmstring fnrmlist( tmstring_list sl )
{
    tmstring ans;
    tmstring errm;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz < 1 ){
	line_error( "missing parameter" );
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
static tmstring fnfirst( tmstring_list sl )
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
static tmstring fnshift( tmstring_list sl )
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

/* -- logic functions -- */

/* and */
static tmstring fnand( tmstring_list sl )
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
static tmstring fnor( tmstring_list sl )
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
static tmstring fnnot( tmstring_list sl )
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

/* stemname <list> */
static tmstring fnstemname( tmstring_list sl )
{
    tmstring ans;
    tmstring_list nl;
    unsigned int ix;
    char *pre;
    char *suff;
    tmstring nwin;
    tmstring nwout;
    char *suffstart;
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
	nwin = rdup_tmstring( sl->arr[ix] );
	suffstart = &nwin[strlen( nwin )-sufflen];
	while(
	    (prelen!=0 || sufflen != 0) &&
	    suffstart>&nwin[prelen] &&
	    strncmp( nwin, pre, prelen )==0 &&
	    strcmp( suffstart, suff )==0
	){
	    suffstart[0] = '\0';
	    nwout = new_tmstring( nwin+prelen );
	    rfre_tmstring( nwin );
	    nwin = nwout;
	    suffstart = &nwin[strlen( nwin )-sufflen];
	}
	nl = append_tmstring_list( nl, nwin );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* mklist <n> <list> */
static tmstring fnmklist( tmstring_list sl )
{
    tmstring ans;
    tmstring buf;
    size_t len;
    size_t maxlen;
    int cnt;
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
    buf = new_tmstring( "" );
    if( sl->sz<1 ){
	line_error( "missing expression" );
	return buf;
    }
    cknumpar( sl->arr[0] );
    n = atoi( sl->arr[0] );
    maxlen = 0;
    for( ix=1; ix<sl->sz; ix++ ){
	len = strlen( sl->arr[ix] );
	if( len>maxlen ) maxlen = len;
    }
    len = 1 + n*( strlen( pre ) + strlen( suff ) ) + maxlen;
    buf = realloc_tmstring( buf, len );
    nl = new_tmstring_list();
    for( ix=1; ix<sl->sz; ix++ ){
	for( cnt=0; cnt<n; cnt++ ){
	    strcat( buf, pre );
	}
	strcat( buf, sl->arr[ix] );
	for( cnt=0; cnt<n; cnt++ ){
	    strcat( buf, suff );
	}
	nl = append_tmstring_list( nl, new_tmstring( buf ) );
	buf[0] = '\0';
    }
    fre_tmstring( buf );
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Construct a list of types. */
static tmstring fntypelist( tmstring_list sl )
{
    ds d;
    tmstring vp;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz!=0 ){
	line_error( "bad number of parameters" );
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

/* Construct a list of constructor types. */
static tmstring fnctypelist( tmstring_list sl )
{
    ds d;
    tmstring vp;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz!=0 ){
	line_error( "bad number of parameters" );
    }
    nl = new_tmstring_list();
    for( ix = 0; ix< allds->sz; ix++ ){
	d = allds->arr[ix];
	switch( d->tag ){
	    case TAGDsCons:
		vp = d->DsCons.ctypename;
		nl = append_tmstring_list( nl, new_tmstring( vp ) );
		break;

	    case TAGDsTuple:
		break;

	    default:
		(void) sprintf( errarg, "%d", d->tag );
		crash( "bad tag" );
	}
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Construct a list of tuple types. */
static tmstring fnttypelist( tmstring_list sl )
{
    ds d;
    tmstring vp;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz!=0 ){
	line_error( "bad number of parameters" );
    }
    nl = new_tmstring_list();
    for( ix = 0; ix< allds->sz; ix++ ){
	d = allds->arr[ix];
	switch( d->tag ){
	    case TAGDsTuple:
		vp = d->DsTuple.ttypename;
		nl = append_tmstring_list( nl, new_tmstring( vp ) );
		break;

	    case TAGDsCons:
		break;

	    default:
		(void) sprintf( errarg, "%d", d->tag );
		crash( "bad tag" );
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
	line_error( "no such type" );
	return dsNIL;
    }
    return dl->arr[ix];
}

/* Given a list of constructors 'dl', search for
   constructor with name 'nm'. Give an error message if it is not found.
 */ 
static constructor find_constructor( constructor_list cl, const tmstring nm )
{
    unsigned int ix;

    ix = find_constructor_ix( cl, nm );
    if( ix<cl->sz ){
	return cl->arr[ix];
    }
    (void) strcpy( errarg, nm );
    line_error( "no such constructor" );
    return constructorNIL;
}

/* Given a list of constructor elements 'el',
   search for constructor element with name 'nm'.
 */ 
static field findfield( field_list el, const tmstring nm )
{
    unsigned int ix;
    field e;

    for( ix=0; ix<el->sz; ix++ ){
	e = el->arr[ix];
	if( strcmp( e->name, nm ) == 0 )
	    return e;
    }
    (void) strcpy( errarg, nm );
    line_error( "no such constructor element" );
    return fieldNIL;
}

/* Given a type name, return the inherits of this type.  */
static tmstring fninherits( tmstring_list sl )
{
    ds d;
    tmstring ans;

    if( sl->sz != 1 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL ){
	return new_tmstring( "" );
    }
    ans = tmstringNIL;
    switch( d->tag ){
	case TAGDsCons:
	    ans = flatstrings( d->DsCons.cinherits );
	    break;

	case TAGDsTuple:
	    ans = flatstrings( d->DsTuple.tinherits );
	    break;

    }
    return ans;
}

/* Construct a list of fields for given tuple type.
 * A constructor type is incorrect.
 */
static tmstring fntelmlist( tmstring_list sl )
{
    ds d;
    field_list el;
    field e;
    tmstring vp;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz != 1 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL ){
	/* findtype already complained about this. */
	return new_tmstring( "" );
    }
    if( d->tag != TAGDsTuple ){
	sprintf( errarg, "'%s'", sl->arr[0] );
	line_error( "not a tuple type" );
	return new_tmstring( "" );
    }
    nl = new_tmstring_list();
    el = d->DsTuple.tuplefields;
    for( ix=0; ix<el->sz; ix++ ){
	e = el->arr[ix];
	vp = e->name;
	nl = append_tmstring_list( nl, new_tmstring( vp ) );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Given a tuple type name and element name, return the
   type name of the given element.
 */
static tmstring fnttypename( tmstring_list sl )
{
    ds d;
    field_list el;
    field e;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsTuple ){
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "not a tuple type" );
	return new_tmstring( "" );
    }
    el = d->DsTuple.tuplefields;
    e = findfield( el, sl->arr[1] );
    if( e == fieldNIL ){
	return new_tmstring( "" );
    }
    return new_tmstring( e->type );
}

/* Given a type name and element name, return the
   type class of the given element.

   Possible type classes are: `single' and `list'.
 */
static tmstring fnttypeclass( tmstring_list sl )
{
    ds d;
    field_list el;
    field e;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsTuple ){
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "not a tuple type" );
	return new_tmstring( "" );
    }
    el = d->DsTuple.tuplefields;
    e = findfield( el, sl->arr[1] );
    if( e == fieldNIL ) return new_tmstring( "" );
    return new_tmstring( ( e->level != 0 ? "list" : "single" ) );
}

/* Given a type name and element name, return the
   list level of the given element.
 */
static tmstring fnttypellev( tmstring_list sl )
{
    ds d;
    field_list el;
    field e;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsTuple ){
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "not a tuple type" );
	return new_tmstring( "" );
    }
    el = d->DsTuple.tuplefields;
    e = findfield( el, sl->arr[1] );
    if( e == fieldNIL ) return new_tmstring( "" );
    return newintstr( e->level );
}

/* construct a list of constructors for given type */
static tmstring fnconslist( tmstring_list sl )
{
    ds d;
    constructor_list cl;
    constructor c;
    tmstring vp;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz != 1 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL ){
	/* findtype already complained about this. */
	return new_tmstring( "" );
    }
    if( d->tag != TAGDsCons ){
	sprintf( errarg, "'%s'", sl->arr[0] );
	line_error( "not a constructor type" );
	return new_tmstring( "" );
    }
    cl = d->DsCons.conslist;
    nl = new_tmstring_list();
    for( ix=0; ix<cl->sz; ix++ ){
	c = cl->arr[ix];
	vp = c->name;
	nl = append_tmstring_list( nl, new_tmstring( vp ) );
    }
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* construct a list of fields for given type */
static tmstring fncelmlist( tmstring_list sl )
{
    ds d;
    constructor_list cl;
    constructor c;
    field_list el;
    field e;
    tmstring vp;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;

    if( sl->sz != 2 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsCons ){
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "not a constructor type" );
	return new_tmstring( "" );
    }
    cl = d->DsCons.conslist;
    c = find_constructor( cl, sl->arr[1] );
    if( c == constructorNIL ){
	return new_tmstring( "" );
    }
    el = c->fields;
    nl = new_tmstring_list();
    for( ix=0; ix<el->sz; ix++ ){
	e = el->arr[ix];
	vp = e->name;
	nl = append_tmstring_list( nl, new_tmstring( vp ) );
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
static tmstring fnctypename( tmstring_list sl )
{
    ds d;
    constructor_list cl;
    constructor c;
    field_list el;
    field e;

    if( sl->sz != 3 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsCons ){
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "not a constructor type" );
	return new_tmstring( "" );
    }
    cl = d->DsCons.conslist;
    c = find_constructor( cl, sl->arr[1] );
    if( c == constructorNIL ){
	return new_tmstring( "" );
    }
    el = c->fields;
    e = findfield( el, sl->arr[2] );
    if( e == fieldNIL ) return new_tmstring( "" );
    return new_tmstring( e->type );
}

/* given a type name, constructor name and element name, return the
   type class of the given element.

   Possible type classes are:
    single
    list
 */
static tmstring fnctypeclass( tmstring_list sl )
{
    ds d;
    constructor_list cl;
    constructor c;
    field_list el;
    field e;

    if( sl->sz != 3 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsCons ){
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "not a constructor type" );
	return new_tmstring( "" );
    }
    cl = d->DsCons.conslist;
    c = find_constructor( cl, sl->arr[1] );
    if( c == constructorNIL ){
	return new_tmstring( "" );
    }
    el = c->fields;
    e = findfield( el, sl->arr[2] );
    if( e == fieldNIL ) return new_tmstring( "" );
    return new_tmstring( ( e->level!=0 ? "list" : "single" ) );
}

/* given a type name, constructor name and element name, return the
   list level of the given element.

 */
static tmstring fnctypellev( tmstring_list sl )
{
    ds d;
    constructor_list cl;
    constructor c;
    field_list el;
    field e;

    if( sl->sz != 3 ){
	line_error( "bad number of parameters" );
	return new_tmstring( "" );
    }
    d = findtype( allds, sl->arr[0] );
    if( d == dsNIL || d->tag != TAGDsCons ){
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "not a constructor type" );
	return new_tmstring( "" );
    }
    cl = d->DsCons.conslist;
    c = find_constructor( cl, sl->arr[1] );
    if( c == constructorNIL ){
	return new_tmstring( "" );
    }
    el = c->fields;
    e = findfield( el, sl->arr[2] );
    if( e == fieldNIL ) return new_tmstring( "" );
    return newintstr( e->level );
}

/* Given a type name 'tnm', a list level 'listlev', an array of marked
 * flags 'marked', an array of list levels 'levels' and a list of type
 * definitions 'dl', mark type 'tnm' as dependent with a list level of
 * at least 'listlev'.
 *
 * If this type is not yet marked, mark it, and also mark all types
 * occurring in the constructor or tuple elements of this type.
 */
static void markdep(
    bool *marked,
    int *levels,
    const tmstring tnm,
    int listlev,
    ds_list dl
)
{
    unsigned int tix;
    bool found;
    ds d;
    unsigned int cix;
    constructor_list cl;
    constructor c;
    unsigned int eix;
    field_list el;
    field e;

    found = FALSE;
    d = dsNIL;
    for( tix = 0; tix<dl->sz; tix++ ){
	d = dl->arr[tix];
	if( strcmp( get_type_name( d ), tnm ) == 0 ){
	    found = TRUE;
	    break;
	}
    }
    if( !found ){
	return;
    }
    if( marked[tix] ){
	if( levels[tix]<listlev ){
	    levels[tix] = listlev;
	}
	return;
    }
    marked[tix] = TRUE;
    levels[tix] = listlev;
    switch( d->tag ){
	case TAGDsCons:
	    cl = d->DsCons.conslist;
	    for( cix=0; cix<cl->sz; cix++ ){
		c = cl->arr[cix];
		el = c->fields;
		for( eix=0; eix<el->sz; eix++ ){
		    e = el->arr[eix];
		    markdep( marked, levels, e->type, e->level, dl );
		}
	    }
	    break;

	case TAGDsTuple:
	    el = d->DsTuple.tuplefields;
	    for( eix=0; eix<el->sz; eix++ ){
		e = el->arr[eix];
		markdep( marked, levels, e->type, e->level, dl );
	    }
	    break;

	default:
	    (void) sprintf( errarg, "%d", d->tag );
	    crash( "bad tag" );
    }
}

/* Given a class name, and a list of type names, determine which types and
   lists of types are dependent on these types.
   If class name is 'single' return the list of types that required for
   the given types.
   If class name is 'single' return the list of type lists that required for
   the given types.
   The top level types are assumed to be 'single'.
 */
static tmstring fndeptype( tmstring_list sl )
{
    bool *marked;
    int *levels;
    tmstring ans;
    unsigned int ix;
    tmstring_list nl;
    tmstring vp;
    char *bufin;
    char *bufout;
    char *pre;
    char *suff;
    bool islist;
    int lev;

    if( sl->sz<1 ){
	line_error( "missing expression" );
	return new_tmstring( "" );
    }
    if( strcmp( sl->arr[0], "single" ) == 0 ){
	islist = FALSE;
    }
    else if( strcmp( sl->arr[0], "list" ) == 0 ){
	islist = TRUE;
    }
    else {
	(void) strcpy( errarg, sl->arr[0] );
	line_error( "bad parameter" );
	return new_tmstring( "" );
    }
    /* The +1 below is to ensure no malloc of size 0 */
    marked = TM_MALLOC( bool *,(allds->sz+1)*sizeof(bool) );
    levels = TM_MALLOC( int *, (allds->sz+1)*sizeof(int) );
    for( ix=0; ix<allds->sz; ix++ ){
	marked[ix] = FALSE;
	levels[ix] = 0;
    }
    for( ix=1; ix<sl->sz; ix++ ){
	markdep( marked, levels, sl->arr[ix], 0, allds );
    }
    nl = new_tmstring_list();
    if( islist ){
	pre = getvar( LISTPRE );
	if( pre == CHARNIL ){
	    pre = "";
	}
	suff = getvar( LISTSUFF );
	if( suff == CHARNIL ){
	    suff = "";
	}
	for( ix=0; ix<allds->sz; ix++ ){
	    vp = get_type_name( allds->arr[ix] );
	    if( marked[ix] ){
		bufin = rdup_tmstring( vp );
		for( lev=1; lev<=levels[ix]; lev++ ){
		    bufout = mklistnm( pre, bufin, suff );
		    nl = append_tmstring_list( nl, bufin );
		    bufin = bufout;
		}
		rfre_tmstring( bufin );
	    }
	}
    }
    else {
	for( ix=0; ix<allds->sz; ix++ ){
	    if( marked[ix] ){
		vp = get_type_name( allds->arr[ix] );
		nl = append_tmstring_list( nl, new_tmstring( vp ) );
	    }
	}
    }
    TM_FREE( marked );
    TM_FREE( levels );
    ans = flatstrings( nl );
    rfre_tmstring_list( nl );
    return ans;
}

/* Given a type name 't' and a list of types 'tl', return 'TRUE' if
 * 't' depends on one of the types in 'tl'. That is, 't' is a tuple
 * type, and at least one of the field types of 't' occurs in tl'.
 *
 * Constructor types are not supposed to depend on other types.
 */
static bool depends_on( const tmstring t, tmstring_list tl )
{
    unsigned int ix;
    ds d;
    field_list fl;

    ix = find_type_ix( allds, t );
    if( ix>=allds->sz ) return FALSE;
    d = allds->arr[ix];
    switch( d->tag ){
	case TAGDsCons:
	    break;

	case TAGDsTuple:
	{
	    field e;

	    fl = d->DsTuple.tuplefields;
	    for( ix=0; ix<fl->sz; ix++ ){
		e = fl->arr[ix];
		if( e->level==0 && member_tmstring_list( e->type, tl ) ){
		    return TRUE;
		}
	    }
	    break;
	}

	default:
	    (void) sprintf( errarg, "%d", d->tag );
	    crash( "bad tag" );
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

    nl = new_tmstring_list();
    while( sl->sz!=0 ){
	found = FALSE;
	ix = 0;
	foundix = 0;
	while( !found && ix<sl->sz ){
	    t = sl->arr[ix];
	    if( !depends_on( t, sl ) ){
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

static tmstring fndsfilename( tmstring_list sl )
{

    if( sl->sz!=0 ){
	line_error( "bad number of parameters" );
    }
    return new_tmstring( dsfilename );
}

static tmstring fntplfilename( tmstring_list sl )
{

    if( sl->sz!=0 ){
	line_error( "bad number of parameters" );
    }
    return new_tmstring( tplfilename );
}

static tmstring fntpllineno( tmstring_list sl )
{

    if( sl->sz != 0 ){
	line_error( "bad number of parameters" );
    }
    return newintstr( tpllineno );
}

static tmstring fndefined( tmstring_list sl )
{
    char *v;

    if( sl->sz<1 ){
	return newboolstr( 0 );
    }
    v = getvar( sl->arr[0] );
    return newboolstr( v != CHARNIL );
}

/* -- nested evaluation: 'call' and 'eval' -- */

/* Evaluate the given parameters again. */
static tmstring fneval( tmstring_list sl )
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
static tmstring fnsearchpath( tmstring_list sl )
{
    if( sl->sz!=0 ){
	line_error( "bad number of parameters" );
    }
    return flatstrings( searchpath );
}

/* Interpret each tmstring in the list as a file name, and search
 * for the file in the search path.
 * If a file can not be found, replace its entry in the resulting
 * list with '?'.
 * The access mode is assumed to be 'r'.
 */
static tmstring fnsearchfile( tmstring_list sl )
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
static tmstring fnisinenv( tmstring_list sl )
{
    char *v;

    if( sl->sz != 1 ){
	line_error( "bad number of parameters" );
	return( new_tmstring( "0" ) );
    }
    v = getenv( sl->arr[0] );
    return newboolstr( v == NULL );
}

/* access of environment variables */
static tmstring fngetenv( tmstring_list sl )
{
    char *v;

    if( sl->sz != 1 ){
	line_error( "bad number of parameters" );
	return( "" );
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
     { "comm", fncomm },
     { "conslist", fnconslist },
     { "ctypeclass", fnctypeclass },
     { "ctypelist", fnctypelist },
     { "ctypellev", fnctypellev },
     { "ctypename", fnctypename },
     { "defined", fndefined },
     { "depsort", fndepsort },
     { "deptype", fndeptype },
     { "dsfilename", fndsfilename },
     { "eq", fnstreq },
     { "eval", fneval },
     { "excl", fnexcl },
     { "filt", fnfilt },
     { "first", fnfirst },
     { "getenv", fngetenv },
     { "index", fnindex },
     { "inherits", fninherits },
     { "isinenv", fnisinenv },
     { "len", fnlen },
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
     { "sort", fnsort },
     { "stemname", fnstemname },
     { "strcmp", fnstrcmp },
     { "strindex", fnstrindex },
     { "strlen", fnstrlen },
     { "strpad", fnstrpad },
     { "subs", fnsubs },
     { "suffix", fnsuffix },
     { "telmlist", fntelmlist },
     { "tolower", fntolower },
     { "toupper", fntoupper },
     { "tplfilename", fntplfilename },
     { "tpllineno", fntpllineno },
     { "ttypeclass", fnttypeclass },
     { "ttypelist", fnttypelist },
     { "ttypellev", fnttypellev },
     { "ttypename", fnttypename },
     { "typelist", fntypelist },
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