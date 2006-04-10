/* File: $Id$
 *
 * Evaluate template expressions.
 */

/* Standard UNIX libraries and expressions */
#include <stdio.h>
#include <ctype.h>

/* tm library */
#include <tmc.h>

/* local definitions */
#include "tmdefs.h"

#include "tmcode.h"
#include "error.h"
#include "tmexpr.h"
#include "global.h"

static const char *evalbool( const_origin org, const char *x, long *vp );

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
static const char *evalconst( const_origin org, const char *x, long *vp )
{
    tmstring buf;
    char *bufp;
    const char *s;

    while( isspace( *x ) ){
	x++;
    }
    if( *x == ORBRAC ){
	s = evalbool( org, x+1, vp );
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
	origin_error( org, "bad expression" );
	*vp = 0;
    }
    else{
	*vp = atoi( buf );
    }
    fre_tmstring( buf );
    return x;
}

/* Evaluate unary operators. */
static const char *evalun( const_origin org, const char *x, long *vp )
{
    const char *s;
    long v;

    while( isspace( *x ) ) x++;
    if( *x == '-' ){
	s = evalun( org, x+1, &v );
	*vp = -v;
	return s;
    }
    if( *x == '!' ){
	s = evalun( org, x+1, &v );
	*vp = !v;
	return s;
    }
    if( *x == '+' ){
	return evalun( org, x+1, vp );
    }
    return evalconst( org, x, vp);
}

/* Evaluate product operators. */
static const char *evalprod( const_origin org, const char *x, long *vp )
{
    const char *s;
    long v1;
    long v2;

    while( isspace( *x ) ) x++;
    s = evalun( org, x, &v1 );
    if( s == x ){
	*vp = 0;
	return x;
    }
again:
    while( isspace( *s ) ) s++;
    if( *s == '*' ){
	s = evalun( org, s+1, &v2 );
	v1 = v1*v2;
	goto again;
    }
    if( *s == '/' ){
	s = evalun( org, s+1, &v2 );
	if( v2 == 0 ){
	    origin_error( org, "division by zero" );
	    v1 = 1;
	}
	else {
	    v1 = v1/v2;
	}
	goto again;
    }
    if( *s == '%' ){
	s = evalun( org, s+1, &v2 );
	if( v2 == 0 ){
	    origin_error( org, "modulus by zero" );
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
static const char *evalsum( const_origin org, const char *x, long *vp )
{
    const char *s;
    long v1;
    long v2;

    while( isspace( *x ) ) x++;
    s = evalprod( org, x, &v1 );
    if( s == x ){
	*vp = 0;
	return x;
    }
again:
    while( isspace( *s ) ) s++;
    if( *s == '+' ){
	s = evalprod( org, s+1, &v2 );
	v1 = v1 + v2;
	goto again;
    }
    if( *s == '-' ){
	s = evalprod( org, s+1, &v2 );
	v1 = v1 - v2;
	goto again;
    }
    *vp = v1;
    return s;
}

/* Evaluate compare operators. */
static const char *evalcmp( const_origin org, const char *x, long *vp )
{
    const char *s;
    long v1;
    long v2;

    while( isspace( *x ) ) x++;
    s = evalsum( org, x, &v1 );
    if( s == x ){
	*vp = 0;
	return x;
    }
    while( isspace( *s ) ) s++;
    if( s[0] == '!' && s[1] == '=' ){
	s = evalsum( org, s+2, &v2 );
	*vp = (v1!=v2);
	return s;
    }
    if( s[0] == '=' && s[1] == '=' ){
	s = evalsum( org, s+2, &v2 );
	*vp = (v1==v2);
	return s;
    }
    if( s[0] == '<' && s[1] == '=' ){
	s = evalsum( org, s+2, &v2 );
	*vp = (v1<=v2);
	return s;
    }
    if( s[0] == '<' ){
	s = evalsum( org, s+1, &v2 );
	*vp = (v1<v2);
	return s;
    }
    if( s[0] == '>' && s[1] == '=' ){
	s = evalsum( org, s+2, &v2 );
	*vp = (v1>=v2);
	return s;
    }
    if( s[0] == '>' ){
	s = evalsum( org, s+1, &v2 );
	*vp = (v1>v2);
	return s;
    }
    *vp = v1;
    return s;
}

/* Evaluate boolean binary operators. */
static const char *evalbool( const_origin org, const char *x, long *vp )
{
    const char *s;
    long v1;
    long v2;

    s = evalcmp( org, x, &v1 );
    while( isspace( *s ) ) s++;
    if( s[0] == '&' ){
	s = evalbool( org, s+1, &v2 );
	*vp = v1 && v2;
	return s;
    }
    if( s[0] == '|' ){
	s = evalbool( org, s+1, &v2 );
	*vp = v1 || v2;
	return s;
    }
    *vp = v1;
    return s;
}

/* Given a tmstring 'x' containing a numerical expression,
 * evaluate it, and construct a tmstring from the resulting integer.
 */
char *evalexpr( const_origin org, const_tmstring x )
{
    char buf[NUMBUFSIZE];
    const char *s;
    long v;

    if( fntracing ){
	fprintf( tracestream, "evaluating expression $[%s]\n", x );
    }
    s =  evalbool( org, x, &v );
    while( isspace( *s ) ) s++;
    if( *s != '\0' ){
	origin_error( org, "bad expression '%s'", s );
    }
    (void) sprintf( buf, "%ld", v );
    if( fntracing ){
	fprintf( tracestream, "expression value: '%s'\n", buf );
    }
    return new_tmstring( buf );
}
