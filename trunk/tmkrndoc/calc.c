#include <tmc.h>
#include "calc.h"

/* Requirement analysis took 120 milliseconds. */
/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /usr/local/lib/tmc.ct ---- */

/* Routines for 'calc'.

   template file:      /usr/local/lib/tmc.ct
   datastructure file: calc.ds
   tm version:         36
   tm kernel version:  2.0-beta19
 */

#ifndef FIRSTROOM
#define FIRSTROOM 0
#endif

/* Counters for allocation and freeing. */
static long newcnt_command_list = 0, frecnt_command_list = 0;
static long newcnt_ExprConst = 0, frecnt_ExprConst = 0;
static long newcnt_ExprNegate = 0, frecnt_ExprNegate = 0;
static long newcnt_ExprPlus = 0, frecnt_ExprPlus = 0;
static long newcnt_ExprSymbol = 0, frecnt_ExprSymbol = 0;
static long newcnt_ExprTimes = 0, frecnt_ExprTimes = 0;
static long newcnt_command = 0, frecnt_command = 0;


static char tm_srcfile[] = __FILE__;

#ifndef FATAL
#define FATAL(msg) tm_fatal(tm_srcfile,__LINE__,msg)
#endif

/* Error strings. */
static char tm_nilptr[] = "NIL pointer";
static char tm_badcons[] = "bad constructor for '%s': '%s'";
static char tm_badeof[] = "unexpected end of file";

#ifndef FATALTAG
#define FATALTAG(tag) tm_badtag(tm_srcfile,__LINE__,(int) tag)
#endif

/**************************************************
 *    set array room routines                     *
 **************************************************/

/* Announce that you will need room for 'rm' elements in
 *  command_list 'l'.
 */
static command_list setroom_command_list( command_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( command *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( command *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/**************************************************
 *    Allocation routines                         *
 **************************************************/

#ifdef LOGNEW
#undef new_ExprConst
#define new_ExprConst(n) real_new_ExprConst(n,_f,_l)
#undef new_ExprNegate
#define new_ExprNegate(x) real_new_ExprNegate(x,_f,_l)
#undef new_ExprPlus
#define new_ExprPlus(a,b) real_new_ExprPlus(a,b,_f,_l)
#undef new_ExprSymbol
#define new_ExprSymbol(s) real_new_ExprSymbol(s,_f,_l)
#undef new_ExprTimes
#define new_ExprTimes(a,b) real_new_ExprTimes(a,b,_f,_l)
#undef new_command
#define new_command(lhs,rhs) real_new_command(lhs,rhs,_f,_l)
#undef new_command_list
#define new_command_list() real_new_command_list(_f,_l)
#endif

#ifdef LOGNEW
command_list real_new_command_list( const char *_f, const int _l )
#else
command_list new_command_list( void )
#endif
{
    command_list nw;

    nw = TM_MALLOC( command_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (command *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( command *, FIRSTROOM*sizeof(command) );
    nw->room = FIRSTROOM;
#endif
    newcnt_command_list++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'ExprConst'. */
#ifdef LOGNEW
ExprConst real_new_ExprConst( int p_n, const char *_f, const int _l )
#else
ExprConst new_ExprConst( int p_n )
#endif
{
    ExprConst nw;

    nw = TM_MALLOC( ExprConst, sizeof(*nw) );
    nw->tag = TAGExprConst;
    nw->n = p_n;
    newcnt_ExprConst++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'ExprNegate'. */
#ifdef LOGNEW
ExprNegate real_new_ExprNegate( expr p_x, const char *_f, const int _l )
#else
ExprNegate new_ExprNegate( expr p_x )
#endif
{
    ExprNegate nw;

    nw = TM_MALLOC( ExprNegate, sizeof(*nw) );
    nw->tag = TAGExprNegate;
    nw->x = p_x;
    newcnt_ExprNegate++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'ExprPlus'. */
#ifdef LOGNEW
ExprPlus real_new_ExprPlus( expr p_a, expr p_b, const char *_f, const int _l )
#else
ExprPlus new_ExprPlus( expr p_a, expr p_b )
#endif
{
    ExprPlus nw;

    nw = TM_MALLOC( ExprPlus, sizeof(*nw) );
    nw->tag = TAGExprPlus;
    nw->a = p_a;
    nw->b = p_b;
    newcnt_ExprPlus++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'ExprSymbol'. */
#ifdef LOGNEW
ExprSymbol real_new_ExprSymbol( tmstring p_s, const char *_f, const int _l )
#else
ExprSymbol new_ExprSymbol( tmstring p_s )
#endif
{
    ExprSymbol nw;

    nw = TM_MALLOC( ExprSymbol, sizeof(*nw) );
    nw->tag = TAGExprSymbol;
    nw->s = p_s;
    newcnt_ExprSymbol++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'ExprTimes'. */
#ifdef LOGNEW
ExprTimes real_new_ExprTimes( expr p_a, expr p_b, const char *_f, const int _l )
#else
ExprTimes new_ExprTimes( expr p_a, expr p_b )
#endif
{
    ExprTimes nw;

    nw = TM_MALLOC( ExprTimes, sizeof(*nw) );
    nw->tag = TAGExprTimes;
    nw->a = p_a;
    nw->b = p_b;
    newcnt_ExprTimes++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'command'. */
#ifdef LOGNEW
command real_new_command( tmstring p_lhs, expr p_rhs, const char *_f, const int _l )
#else
command new_command( tmstring p_lhs, expr p_rhs )
#endif
{
    command nw;

    nw = TM_MALLOC( command, sizeof(*nw) );
    nw->tag = TAGcommand;
    nw->lhs = p_lhs;
    nw->rhs = p_rhs;
    newcnt_command++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/**************************************************
 *    Freeing routines                            *
 **************************************************/

static void fre_command_list( command_list );
static void fre_command( command );
static void fre_ExprConst( ExprConst );
static void fre_ExprNegate( ExprNegate );
static void fre_ExprPlus( ExprPlus );
static void fre_ExprSymbol( ExprSymbol );
static void fre_ExprTimes( ExprTimes );
/* Free an element 'e' of class type 'command'. */
static void fre_command( command e )
{
    if( e == commandNIL ){
	return;
    }
    switch( e->tag ){
	case TAGcommand:
	    frecnt_command++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'ExprConst'. */
static void fre_ExprConst( ExprConst e )
{
    if( e == ExprConstNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExprConst:
	    frecnt_ExprConst++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'ExprNegate'. */
static void fre_ExprNegate( ExprNegate e )
{
    if( e == ExprNegateNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExprNegate:
	    frecnt_ExprNegate++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'ExprPlus'. */
static void fre_ExprPlus( ExprPlus e )
{
    if( e == ExprPlusNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExprPlus:
	    frecnt_ExprPlus++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'ExprSymbol'. */
static void fre_ExprSymbol( ExprSymbol e )
{
    if( e == ExprSymbolNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExprSymbol:
	    frecnt_ExprSymbol++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'ExprTimes'. */
static void fre_ExprTimes( ExprTimes e )
{
    if( e == ExprTimesNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExprTimes:
	    frecnt_ExprTimes++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free a list of command elements 'l'. */
static void fre_command_list( command_list l )
{
    if( l == command_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
    frecnt_command_list++;
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
    TM_FREE( l );
}

/**************************************************
 *    Append routines                             *
 **************************************************/

/* Append a command element 'e' to list 'l', and return the new list. */
command_list append_command_list( command_list l, command e )
{
    if( l->sz >= l->room ){
	l = setroom_command_list( l, 1+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/**************************************************
 *    Recursive freeing routines                  *
 **************************************************/

static void rfre_command( command );
static void rfre_ExprConst( ExprConst );
static void rfre_ExprNegate( ExprNegate );
static void rfre_ExprPlus( ExprPlus );
static void rfre_ExprSymbol( ExprSymbol );
static void rfre_ExprTimes( ExprTimes );
/* Recursively free an element 'e' of class type 'expr'
 * and all elements in it.
 */
void rfre_expr( expr e )
{
    if( e == exprNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExprPlus:
	    rfre_ExprPlus( (ExprPlus) e );
	    break;

	case TAGExprTimes:
	    rfre_ExprTimes( (ExprTimes) e );
	    break;

	case TAGExprNegate:
	    rfre_ExprNegate( (ExprNegate) e );
	    break;

	case TAGExprConst:
	    rfre_ExprConst( (ExprConst) e );
	    break;

	case TAGExprSymbol:
	    rfre_ExprSymbol( (ExprSymbol) e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'command'
 * and all elements in it.
 */
static void rfre_command( command e )
{
    if( e == commandNIL ){
	return;
    }
    switch( e->tag ){
	case TAGcommand:
	    rfre_tmstring( e->lhs );
	    rfre_expr( e->rhs );
	    fre_command( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'ExprConst'
 * and all elements in it.
 */
static void rfre_ExprConst( ExprConst e )
{
    if( e == ExprConstNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExprConst:
	    rfre_int( e->n );
	    fre_ExprConst( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'ExprNegate'
 * and all elements in it.
 */
static void rfre_ExprNegate( ExprNegate e )
{
    if( e == ExprNegateNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExprNegate:
	    rfre_expr( e->x );
	    fre_ExprNegate( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'ExprPlus'
 * and all elements in it.
 */
static void rfre_ExprPlus( ExprPlus e )
{
    if( e == ExprPlusNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExprPlus:
	    rfre_expr( e->a );
	    rfre_expr( e->b );
	    fre_ExprPlus( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'ExprSymbol'
 * and all elements in it.
 */
static void rfre_ExprSymbol( ExprSymbol e )
{
    if( e == ExprSymbolNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExprSymbol:
	    rfre_tmstring( e->s );
	    fre_ExprSymbol( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'ExprTimes'
 * and all elements in it.
 */
static void rfre_ExprTimes( ExprTimes e )
{
    if( e == ExprTimesNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExprTimes:
	    rfre_expr( e->a );
	    rfre_expr( e->b );
	    fre_ExprTimes( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free a list of elements 'e' of type command. */
void rfre_command_list( command_list e )
{
    unsigned int ix;

    if( e == command_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_command( e->arr[ix] );
    }
    fre_command_list( e );
}

/**************************************************
 *    print_<type> and print_<type>_list routines *
 **************************************************/

static void print_command( TMPRINTSTATE *st, const command );
static void print_expr( TMPRINTSTATE *st, const expr );
static void print_ExprConst( TMPRINTSTATE *st, const ExprConst );
static void print_ExprNegate( TMPRINTSTATE *st, const ExprNegate );
static void print_ExprPlus( TMPRINTSTATE *st, const ExprPlus );
static void print_ExprSymbol( TMPRINTSTATE *st, const ExprSymbol );
static void print_ExprTimes( TMPRINTSTATE *st, const ExprTimes );
/* Print an element 't' of class type 'command'
 * using print optimizer.
 */
static void print_command( TMPRINTSTATE *st, const command t )
{
    if( t == commandNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGcommand:
	    tm_opencons( st );
	    tm_printword( st, "command" );
	    print_tmstring( st, t->lhs );
	    print_expr( st, t->rhs );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'expr'
 * using print optimizer.
 */
static void print_expr( TMPRINTSTATE *st, const expr t )
{
    if( t == exprNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGExprPlus:
	    print_ExprPlus( st, (ExprPlus) t );
	    break;

	case TAGExprTimes:
	    print_ExprTimes( st, (ExprTimes) t );
	    break;

	case TAGExprNegate:
	    print_ExprNegate( st, (ExprNegate) t );
	    break;

	case TAGExprConst:
	    print_ExprConst( st, (ExprConst) t );
	    break;

	case TAGExprSymbol:
	    print_ExprSymbol( st, (ExprSymbol) t );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'ExprConst'
 * using print optimizer.
 */
static void print_ExprConst( TMPRINTSTATE *st, const ExprConst t )
{
    if( t == ExprConstNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGExprConst:
	    tm_opencons( st );
	    tm_printword( st, "ExprConst" );
	    print_int( st, t->n );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'ExprNegate'
 * using print optimizer.
 */
static void print_ExprNegate( TMPRINTSTATE *st, const ExprNegate t )
{
    if( t == ExprNegateNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGExprNegate:
	    tm_opencons( st );
	    tm_printword( st, "ExprNegate" );
	    print_expr( st, t->x );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'ExprPlus'
 * using print optimizer.
 */
static void print_ExprPlus( TMPRINTSTATE *st, const ExprPlus t )
{
    if( t == ExprPlusNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGExprPlus:
	    tm_opencons( st );
	    tm_printword( st, "ExprPlus" );
	    print_expr( st, t->a );
	    print_expr( st, t->b );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'ExprSymbol'
 * using print optimizer.
 */
static void print_ExprSymbol( TMPRINTSTATE *st, const ExprSymbol t )
{
    if( t == ExprSymbolNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGExprSymbol:
	    tm_opencons( st );
	    tm_printword( st, "ExprSymbol" );
	    print_tmstring( st, t->s );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'ExprTimes'
 * using print optimizer.
 */
static void print_ExprTimes( TMPRINTSTATE *st, const ExprTimes t )
{
    if( t == ExprTimesNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGExprTimes:
	    tm_opencons( st );
	    tm_printword( st, "ExprTimes" );
	    print_expr( st, t->a );
	    print_expr( st, t->b );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print a list of elements 'l' of type 'command'
   using print optimizer.
 */
void print_command_list( TMPRINTSTATE *st, const command_list l )
{
    unsigned int ix;

    if( l == command_listNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_openlist( st );
    for( ix=0; ix<l->sz; ix++ ){
	print_command( st, l->arr[ix] );
    }
    tm_closelist( st );
}

/**************************************************
 *    Duplication routines                        *
 **************************************************/

#ifdef LOGNEW
#undef rdup_command
#define rdup_command(e) real_rdup_command(e,_f,_l)
#undef rdup_expr
#define rdup_expr(e) real_rdup_expr(e,_f,_l)
#define rdup_ExprConst(e) real_rdup_ExprConst(e,_f,_l)
#define rdup_ExprNegate(e) real_rdup_ExprNegate(e,_f,_l)
#define rdup_ExprPlus(e) real_rdup_ExprPlus(e,_f,_l)
#define rdup_ExprSymbol(e) real_rdup_ExprSymbol(e,_f,_l)
#define rdup_ExprTimes(e) real_rdup_ExprTimes(e,_f,_l)
static ExprConst real_rdup_ExprConst( const ExprConst, const char *, const int );
static ExprNegate real_rdup_ExprNegate( const ExprNegate, const char *, const int );
static ExprPlus real_rdup_ExprPlus( const ExprPlus, const char *, const int );
static ExprSymbol real_rdup_ExprSymbol( const ExprSymbol, const char *, const int );
static ExprTimes real_rdup_ExprTimes( const ExprTimes, const char *, const int );
#else
static ExprConst rdup_ExprConst( const ExprConst );
static ExprNegate rdup_ExprNegate( const ExprNegate );
static ExprPlus rdup_ExprPlus( const ExprPlus );
static ExprSymbol rdup_ExprSymbol( const ExprSymbol );
static ExprTimes rdup_ExprTimes( const ExprTimes );
#endif
/* Recursively duplicate a class command element 'e'. */
#ifdef LOGNEW
command real_rdup_command( const command e, const char *_f, const int _l )
#else
command rdup_command( const command e )
#endif
{
    tmstring i_lhs;
    expr i_rhs;

    if( e == commandNIL ){
	return commandNIL;
    }
    i_lhs = rdup_tmstring( e->lhs );
    i_rhs = rdup_expr( e->rhs );
    return new_command( i_lhs, i_rhs );
}

/* Recursively duplicate a class expr element 'e'. */
#ifdef LOGNEW
expr real_rdup_expr( const expr e, const char *_f, const int _l )
#else
expr rdup_expr( const expr e )
#endif
{
    if( e == exprNIL ){
	return exprNIL;
    }
    switch( e->tag ){
	case TAGExprPlus:
	    return (expr) rdup_ExprPlus( (ExprPlus) e );

	case TAGExprTimes:
	    return (expr) rdup_ExprTimes( (ExprTimes) e );

	case TAGExprNegate:
	    return (expr) rdup_ExprNegate( (ExprNegate) e );

	case TAGExprConst:
	    return (expr) rdup_ExprConst( (ExprConst) e );

	case TAGExprSymbol:
	    return (expr) rdup_ExprSymbol( (ExprSymbol) e );

	default:
	    FATALTAG( e->tag );
    }
    return exprNIL;
}

/* Recursively duplicate a class ExprConst element 'e'. */
#ifdef LOGNEW
static ExprConst real_rdup_ExprConst( const ExprConst e, const char *_f, const int _l )
#else
static ExprConst rdup_ExprConst( const ExprConst e )
#endif
{
    int i_n;

    if( e == ExprConstNIL ){
	return ExprConstNIL;
    }
    i_n = rdup_int( e->n );
    return new_ExprConst( i_n );
}

/* Recursively duplicate a class ExprNegate element 'e'. */
#ifdef LOGNEW
static ExprNegate real_rdup_ExprNegate( const ExprNegate e, const char *_f, const int _l )
#else
static ExprNegate rdup_ExprNegate( const ExprNegate e )
#endif
{
    expr i_x;

    if( e == ExprNegateNIL ){
	return ExprNegateNIL;
    }
    i_x = rdup_expr( e->x );
    return new_ExprNegate( i_x );
}

/* Recursively duplicate a class ExprPlus element 'e'. */
#ifdef LOGNEW
static ExprPlus real_rdup_ExprPlus( const ExprPlus e, const char *_f, const int _l )
#else
static ExprPlus rdup_ExprPlus( const ExprPlus e )
#endif
{
    expr i_a;
    expr i_b;

    if( e == ExprPlusNIL ){
	return ExprPlusNIL;
    }
    i_a = rdup_expr( e->a );
    i_b = rdup_expr( e->b );
    return new_ExprPlus( i_a, i_b );
}

/* Recursively duplicate a class ExprSymbol element 'e'. */
#ifdef LOGNEW
static ExprSymbol real_rdup_ExprSymbol( const ExprSymbol e, const char *_f, const int _l )
#else
static ExprSymbol rdup_ExprSymbol( const ExprSymbol e )
#endif
{
    tmstring i_s;

    if( e == ExprSymbolNIL ){
	return ExprSymbolNIL;
    }
    i_s = rdup_tmstring( e->s );
    return new_ExprSymbol( i_s );
}

/* Recursively duplicate a class ExprTimes element 'e'. */
#ifdef LOGNEW
static ExprTimes real_rdup_ExprTimes( const ExprTimes e, const char *_f, const int _l )
#else
static ExprTimes rdup_ExprTimes( const ExprTimes e )
#endif
{
    expr i_a;
    expr i_b;

    if( e == ExprTimesNIL ){
	return ExprTimesNIL;
    }
    i_a = rdup_expr( e->a );
    i_b = rdup_expr( e->b );
    return new_ExprTimes( i_a, i_b );
}

/**************************************************
 *    Scan routines.                              *
 **************************************************/

#ifdef LOGNEW
#define fscan_command(f,ep) real_fscan_command(f,ep,_f,_l)
#define fscan_expr(f,ep) real_fscan_expr(f,ep,_f,_l)
#undef fscan_command_list
#define fscan_command_list(f,lp) real_fscan_command_list(f,lp,_f,_l)
static int real_fscan_command( FILE *, command *, const char *_f, const int _l );
static int real_fscan_expr( FILE *, expr *, const char *_f, const int _l );
#else
static int fscan_command( FILE *, command * );
static int fscan_expr( FILE *, expr * );
#endif

/* Read a class of type command
   from file 'f' and allocate space for it.
   Set the pointer 'p' to point to that structure.
 */
#ifdef LOGNEW
static int real_fscan_command( FILE *f, command *p, const char *_f, const int _l )
#else
static int fscan_command( FILE *f, command *p )
#endif
{
    int n;
    int c;
    char tm_word[11];	/* Largest constructor should fit in it.. */
    int err;

    *p = commandNIL;
    n = tm_fscanopenbrac( f );
    err = tm_fscanspace( f );
    if( err ){
	return 1;
    }
    c = getc( f );
    if( c == '@' ){
	return tm_fscanclosebrac( f, n );
    }
    ungetc( c, f );
    if( tm_fscancons( f, tm_word, 11 ) ){
	return 1;
    }
    if( strcmp( tm_word, "command" ) == 0 ){
	tmstring l_lhs;
	expr l_rhs;

	l_lhs = tmstringNIL;
	if( !err ){
	    err = fscan_tmstring( f, &l_lhs );
	}
	l_rhs = exprNIL;
	if( !err ){
	    err = fscan_expr( f, &l_rhs );
	}
	*p = new_command( l_lhs, l_rhs );
    }
    else {
	(void) sprintf( tm_errmsg, tm_badcons, "command", tm_word );
	return 1;
    }
    if( err ){
	return 1;
    }
    return tm_fscanclosebrac( f, n );
}

/* Read a class of type expr
   from file 'f' and allocate space for it.
   Set the pointer 'p' to point to that structure.
 */
#ifdef LOGNEW
static int real_fscan_expr( FILE *f, expr *p, const char *_f, const int _l )
#else
static int fscan_expr( FILE *f, expr *p )
#endif
{
    int n;
    int c;
    char tm_word[14];	/* Largest constructor should fit in it.. */
    int err;

    *p = exprNIL;
    n = tm_fscanopenbrac( f );
    err = tm_fscanspace( f );
    if( err ){
	return 1;
    }
    c = getc( f );
    if( c == '@' ){
	return tm_fscanclosebrac( f, n );
    }
    ungetc( c, f );
    if( tm_fscancons( f, tm_word, 14 ) ){
	return 1;
    }
    if( strcmp( tm_word, "ExprPlus" ) == 0 ){
	expr l_a;
	expr l_b;

	l_a = exprNIL;
	if( !err ){
	    err = fscan_expr( f, &l_a );
	}
	l_b = exprNIL;
	if( !err ){
	    err = fscan_expr( f, &l_b );
	}
	*p =  (expr) new_ExprPlus( l_a, l_b );
    }
    else if( strcmp( tm_word, "ExprTimes" ) == 0 ){
	expr l_a;
	expr l_b;

	l_a = exprNIL;
	if( !err ){
	    err = fscan_expr( f, &l_a );
	}
	l_b = exprNIL;
	if( !err ){
	    err = fscan_expr( f, &l_b );
	}
	*p =  (expr) new_ExprTimes( l_a, l_b );
    }
    else if( strcmp( tm_word, "ExprNegate" ) == 0 ){
	expr l_x;

	l_x = exprNIL;
	if( !err ){
	    err = fscan_expr( f, &l_x );
	}
	*p =  (expr) new_ExprNegate( l_x );
    }
    else if( strcmp( tm_word, "ExprConst" ) == 0 ){
	int l_n;

	l_n = intNIL;
	if( !err ){
	    err = fscan_int( f, &l_n );
	}
	*p =  (expr) new_ExprConst( l_n );
    }
    else if( strcmp( tm_word, "ExprSymbol" ) == 0 ){
	tmstring l_s;

	l_s = tmstringNIL;
	if( !err ){
	    err = fscan_tmstring( f, &l_s );
	}
	*p =  (expr) new_ExprSymbol( l_s );
    }
    else {
	(void) sprintf( tm_errmsg, tm_badcons, "expr", tm_word );
	return 1;
    }
    if( err ){
	return 1;
    }
    return tm_fscanclosebrac( f, n );
}

/* Read an instance of a list of datastructure of type command
   from file 'f' and allocate space for it. Set the pointer 'p' to
   point to that structure.
 */
#ifdef LOGNEW
int real_fscan_command_list( FILE *f, command_list *p, const char *_f, const int _l )
#else
int fscan_command_list( FILE *f, command_list *p )
#endif
{
    int c;
    int n;
    command nw;
    int err = 0;

    *p = command_listNIL;
    n = tm_fscanopenbrac( f );
    if( tm_fscanspace( f ) ){
	return 1;
    }
    c = getc( f );
    if( c == '@' ){
	return tm_fscanclosebrac( f, n );
    }
    ungetc( c, f );
    if( tm_fneedc( f, '[' ) ){
	return 1;
    }
    *p = new_command_list();
    if( tm_fscanspace( f ) ){
	return 1;
    }
    c = getc( f );
    if( c == ']' ){
	return 0;
    }
    if( c == EOF ){
	(void) strcpy( tm_errmsg, tm_badeof );
	return 1;
    }
    ungetc( c, f );
    for(;;){
	if( !err ){
	    err = fscan_command( f, &nw );
	}
	*p = append_command_list( *p, nw );
	if( err || tm_fscanspace( f ) ){
	    return 1;
	}
	c = getc( f );
	if( c == EOF ){
	    (void) strcpy( tm_errmsg, tm_badeof );
	    return 1;
	}
	if( c != ',' ){
	    ungetc( c, f );
	    break;
	}
    }
    if( tm_fneedc( f, ']' ) ){
	return 1;
    }
    return tm_fscanclosebrac( f, n );
}

/**************************************************
 *    delete_<type>_list routines                 *
 **************************************************/

/* Delete 'command' element at position 'pos' in list 'l'. */
command_list delete_command_list( command_list l, const unsigned int pos )
{
    unsigned int ix;

    if( l == command_listNIL ){
	FATAL( tm_nilptr );
    }
    if( pos >= l->sz ){
	return l;
    }
    rfre_command( l->arr[pos] );
    l->sz--;
    for( ix=pos; ix<l->sz; ix++ ){
	l->arr[ix] = l->arr[ix+1];
    }
    return l;
}

/**************************************************
 *    Miscellaneous routines                      *
 **************************************************/
/* Print allocation and freeing statistics to file 'f'. */
void stat_calc( FILE *f )
{
    const char tm_allocfreed[] = "%-20s: %6ld allocated, %6ld freed.%s\n";

    fprintf(
	f,
	tm_allocfreed,
	"ExprConst",
	newcnt_ExprConst,
	frecnt_ExprConst,
	((newcnt_ExprConst==frecnt_ExprConst)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"ExprNegate",
	newcnt_ExprNegate,
	frecnt_ExprNegate,
	((newcnt_ExprNegate==frecnt_ExprNegate)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"ExprPlus",
	newcnt_ExprPlus,
	frecnt_ExprPlus,
	((newcnt_ExprPlus==frecnt_ExprPlus)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"ExprSymbol",
	newcnt_ExprSymbol,
	frecnt_ExprSymbol,
	((newcnt_ExprSymbol==frecnt_ExprSymbol)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"ExprTimes",
	newcnt_ExprTimes,
	frecnt_ExprTimes,
	((newcnt_ExprTimes==frecnt_ExprTimes)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"command",
	newcnt_command,
	frecnt_command,
	((newcnt_command==frecnt_command)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed, "command_list",
	newcnt_command_list,
	frecnt_command_list,
	((newcnt_command_list==frecnt_command_list)? "": "<-")
    );
}

/* Return -1 if there is a structure that has freed more than allocated, or
 * else return 1 if there is a structure that has been freed less than
 * allocated, or else return 0.
 */
int get_balance_calc( void )
{
    /* Check for too many fre()s. */
    if( newcnt_command_list<frecnt_command_list ){
	return -1;
    }
    if( newcnt_ExprConst<frecnt_ExprConst ){
	return -1;
    }
    if( newcnt_ExprNegate<frecnt_ExprNegate ){
	return -1;
    }
    if( newcnt_ExprPlus<frecnt_ExprPlus ){
	return -1;
    }
    if( newcnt_ExprSymbol<frecnt_ExprSymbol ){
	return -1;
    }
    if( newcnt_ExprTimes<frecnt_ExprTimes ){
	return -1;
    }
    if( newcnt_command<frecnt_command ){
	return -1;
    }
    /* Check for too few free()s. */
    if( newcnt_command_list>frecnt_command_list ){
	return 1;
    }
    if( newcnt_ExprConst>frecnt_ExprConst ){
	return 1;
    }
    if( newcnt_ExprNegate>frecnt_ExprNegate ){
	return 1;
    }
    if( newcnt_ExprPlus>frecnt_ExprPlus ){
	return 1;
    }
    if( newcnt_ExprSymbol>frecnt_ExprSymbol ){
	return 1;
    }
    if( newcnt_ExprTimes>frecnt_ExprTimes ){
	return 1;
    }
    if( newcnt_command>frecnt_command ){
	return 1;
    }
    return 0;
}

/* ---- end of /usr/local/lib/tmc.ct ---- */
/* Code generation required 180 milliseconds. */
