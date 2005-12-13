/* File: $Id$
 *
 * Handle expressions.
 */

#include "config.h"

/* Standard UNIX libraries and expressions */
#include <stdio.h>
#include <ctype.h>

/* tm library */
#include <tmc.h>

/* local definitions */
#include "tmdefs.h"

#include "tmcode.h"
#include "tmstring.h"
#include "error.h"
#include "tmexpr.h"
#include "global.h"
#include "misc.h"

static const char *evalbool( const char *x, long *vp );

/* integer expression evaluation.
 * All these functions evaluate a set of operators at one
 * priority level, set a value pointed to by a passed pointer to
 * the evaluated value, and return a pointer to the remaining tmstring.
 *
 * Priorities (in order of increasing binding power:
 *
 * & |
 * < <= > >= == !=
 * + -
 * * / %
 * + - ~ ! (unary)
 */

/* Evaluate integer constants and '()'. */
static const char *evalconst( const char *x, long *vp )
{
    tmstring buf;
    char *bufp;
    const char *s;

    while( isspace( *x ) ){
	x++;
    }
    if( *x == ORBRAC ){
	s = evalbool( x+1, vp );
	while( isspace( *s ) ) s++;
	if( *s != CRBRAC ){
	    return x;
	}
	else{
	    return s+1;
	}
    }
    buf = new_tmstring( x );
    bufp = buf;
    while( isdigit( *x ) ){
	*bufp++ = *x++;
    }
    *bufp = '\0';
    if( buf[0] == '\0' ){
	line_error( "bad expression" );
	*vp = 0;
    }
    else{
	*vp = atoi( buf );
    }
    fre_tmstring( buf );
    return x;
}

/* Evaluate unary operators. */
static const char *evalun( const char *x, long *vp )
{
    const char *s;
    long v;

    while( isspace( *x ) ) x++;
    if( *x == '-' ){
	s = evalun( x+1, &v );
	*vp = -v;
	return s;
    }
    if( *x == '!' ){
	s = evalun( x+1, &v );
	*vp = !v;
	return s;
    }
    if( *x == '+' ){
	return evalun( x+1, vp );
    }
    return evalconst( x, vp);
}

/* Evaluate product operators. */
static const char *evalprod( const char *x, long *vp )
{
    const char *s;
    long v1;
    long v2;

    while( isspace( *x ) ) x++;
    s = evalun( x, &v1 );
    if( s == x ){
	*vp = 0;
	return x;
    }
again:
    while( isspace( *s ) ) s++;
    if( *s == '*' ){
	s = evalun( s+1, &v2 );
	v1 = v1*v2;
	goto again;
    }
    if( *s == '/' ){
	s = evalun( s+1, &v2 );
	if( v2 == 0 ){
	    line_error( "division by zero" );
	    v1 = 1;
	}
	else {
	    v1 = v1/v2;
	}
	goto again;
    }
    if( *s == '%' ){
	s = evalun( s+1, &v2 );
	if( v2 == 0 ){
	    line_error( "modulus by zero" );
	    v1 = 1;
	}
	else {
	    v1 = v1%v2;
	}
	goto again;
    }
    *vp = v1;
    return s;
}

/* Evaluate sum operators. */
static const char *evalsum( const char *x, long *vp )
{
    const char *s;
    long v1;
    long v2;

    while( isspace( *x ) ) x++;
    s = evalprod( x, &v1 );
    if( s == x ){
	*vp = 0;
	return x;
    }
again:
    while( isspace( *s ) ) s++;
    if( *s == '+' ){
	s = evalprod( s+1, &v2 );
	v1 = v1 + v2;
	goto again;
    }
    if( *s == '-' ){
	s = evalprod( s+1, &v2 );
	v1 = v1 - v2;
	goto again;
    }
    *vp = v1;
    return s;
}

/* Evaluate compare operators. */
static const char *evalcmp( const char *x, long *vp )
{
    const char *s;
    long v1;
    long v2;

    while( isspace( *x ) ) x++;
    s = evalsum( x, &v1 );
    if( s == x ){
	*vp = 0;
	return x;
    }
    while( isspace( *s ) ) s++;
    if( s[0] == '!' && s[1] == '=' ){
	s = evalsum( s+2, &v2 );
	*vp = (v1!=v2);
	return s;
    }
    if( s[0] == '=' && s[1] == '=' ){
	s = evalsum( s+2, &v2 );
	*vp = (v1==v2);
	return s;
    }
    if( s[0] == '<' && s[1] == '=' ){
	s = evalsum( s+2, &v2 );
	*vp = (v1<=v2);
	return s;
    }
    if( s[0] == '<' ){
	s = evalsum( s+1, &v2 );
	*vp = (v1<v2);
	return s;
    }
    if( s[0] == '>' && s[1] == '=' ){
	s = evalsum( s+2, &v2 );
	*vp = (v1>=v2);
	return s;
    }
    if( s[0] == '>' ){
	s = evalsum( s+1, &v2 );
	*vp = (v1>v2);
	return s;
    }
    *vp = v1;
    return s;
}

/* Evaluate boolean binary operators. */
static const char *evalbool( const char *x, long *vp )
{
    const char *s;
    long v1;
    long v2;

    s = evalcmp( x, &v1 );
    while( isspace( *s ) ) s++;
    if( s[0] == '&' ){
	s = evalbool( s+1, &v2 );
	*vp = v1 && v2;
	return s;
    }
    if( s[0] == '|' ){
	s = evalbool( s+1, &v2 );
	*vp = v1 || v2;
	return s;
    }
    *vp = v1;
    return s;
}

/* Given a tmstring 'x' containing a numerical expression,
 * evaluate it, and construct a tmstring from the resulting integer.
 */
char *evalexpr( const_tmstring x )
{
    char buf[NUMBUFSIZE];
    const char *s;
    long v;

    if( fntracing ){
	fprintf( tracestream, "evaluating expression $[%s]\n", x );
    }
    s =  evalbool( x, &v );
    while( isspace( *s ) ) s++;
    if( *s != '\0' ){
	(void) strcpy( errarg, s );
	line_error( "bad expression" );
    }
    (void) sprintf( buf, "%ld", v );
    if( fntracing ){
	fprintf( tracestream, "expression value: '%s'\n", buf );
    }
    return new_tmstring( buf );
}
