#include <tmc.h>
#include "calc.h"

/* Requirement analysis took 100 milliseconds. */
/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /usr/local/lib/tmc.ct ---- */

/* Routines for 'calc'.

   template file:      /usr/local/lib/tmc.ct
   datastructure file: calc.ds
   tm version:         36
   tm kernel version:  2.0-beta3
 */

#ifndef FIRSTROOM
#define FIRSTROOM 0
#endif

static long newcnt_statement_list = 0;
static long frecnt_statement_list = 0;

static long newcnt_ExprConst = 0;
static long frecnt_ExprConst = 0;
static long newcnt_ExprNegate = 0;
static long frecnt_ExprNegate = 0;
static long newcnt_ExprPlus = 0;
static long frecnt_ExprPlus = 0;
static long newcnt_ExprSymbol = 0;
static long frecnt_ExprSymbol = 0;
static long newcnt_ExprTimes = 0;
static long frecnt_ExprTimes = 0;
static long newcnt_statement = 0;
static long frecnt_statement = 0;

static char tm_srcfile[] = __FILE__;

static char tm_allocfreed[] = "%-20s: %6ld allocated, %6ld freed.%s\n";

#ifndef FATAL
#define FATAL(msg) tm_fatal(tm_srcfile,__LINE__,msg)
#endif

/* Error strings. */
static char tm_badcons[] = "bad constructor for '%s': '%s'";
static char tm_badeof[] = "unexpected end of file";

#ifndef FATALTAG
#define FATALTAG(tag) tm_badtag(tm_srcfile,__LINE__,tag)
#endif

/**************************************************
 *    set array room routines                     *
 **************************************************/

/* Announce that you will need setroom for 'rm' elements in
 * statement_list 'l'.
 */
static statement_list setroom_statement_list( statement_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( statement *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( statement *, l->arr, rm * sizeof(*(l->arr)) );
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
#undef new_statement
#define new_statement(lhs,rhs) real_new_statement(lhs,rhs,_f,_l)
#undef new_statement_list
#define new_statement_list() real_new_statement_list(_f,_l)
#endif

#ifdef LOGNEW
statement_list real_new_statement_list( const char *_f, const int _l )
#else
statement_list new_statement_list( void )
#endif
{
    statement_list nw;

    nw = TM_MALLOC( statement_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (statement *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( statement *, FIRSTROOM*sizeof(statement) );
    nw->room = FIRSTROOM;
#endif
    newcnt_statement_list++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

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

#ifdef LOGNEW
statement real_new_statement( tmstring p_lhs, expr p_rhs, const char *_f, const int _l )
#else
statement new_statement( tmstring p_lhs, expr p_rhs )
#endif
{
    statement nw;

    nw = TM_MALLOC( statement, sizeof(*nw) );
    nw->tag = TAGstatement;
    nw->lhs = p_lhs;
    nw->rhs = p_rhs;
    newcnt_statement++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/**************************************************
 *    Freeing routines                            *
 **************************************************/

/* Free an element 'e' of class type 'statement'. */
static void fre_statement( statement e )
{
    if( e == statementNIL ){
	return;
    }
    frecnt_statement++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of class type 'ExprConst'. */
static void fre_ExprConst( ExprConst e )
{
    if( e == ExprConstNIL ){
	return;
    }
    frecnt_ExprConst++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of class type 'ExprNegate'. */
static void fre_ExprNegate( ExprNegate e )
{
    if( e == ExprNegateNIL ){
	return;
    }
    frecnt_ExprNegate++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of class type 'ExprPlus'. */
static void fre_ExprPlus( ExprPlus e )
{
    if( e == ExprPlusNIL ){
	return;
    }
    frecnt_ExprPlus++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of class type 'ExprSymbol'. */
static void fre_ExprSymbol( ExprSymbol e )
{
    if( e == ExprSymbolNIL ){
	return;
    }
    frecnt_ExprSymbol++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of class type 'ExprTimes'. */
static void fre_ExprTimes( ExprTimes e )
{
    if( e == ExprTimesNIL ){
	return;
    }
    frecnt_ExprTimes++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free a list of statement elements 'l'. */
static void fre_statement_list( statement_list l )
{
    if( l == statement_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
    frecnt_statement_list++;
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
    TM_FREE( l );
}

/**************************************************
 *    Real append routines                        *
 **************************************************/


/* Append a statement element 'e' to list 'l', and return the new list. */
statement_list append_statement_list( statement_list l, statement e )
{
    if( l->sz >= l->room ){
	l = setroom_statement_list( l, 1+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/**************************************************
 *    Recursive freeing routines                  *
 **************************************************/


static void rfre_statement( statement );
static void rfre_ExprConst( ExprConst );
static void rfre_ExprNegate( ExprNegate );
static void rfre_ExprPlus( ExprPlus );
static void rfre_ExprSymbol( ExprSymbol );
static void rfre_ExprTimes( ExprTimes );

/* Recursively free an element 'e' of class type 'expr'
   and all elements in it.
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

/* Recursively free an element 'e' of class type 'statement'
   and all elements in it.
 */
static void rfre_statement( statement e )
{
    if( e == statementNIL ){
	return;
    }
    /* There are no subclasses. */
    rfre_tmstring( e->lhs );
    rfre_expr( e->rhs );
    fre_statement( e );
}

/* Recursively free an element 'e' of class type 'ExprConst'
   and all elements in it.
 */
static void rfre_ExprConst( ExprConst e )
{
    if( e == ExprConstNIL ){
	return;
    }
    /* There are no subclasses. */
    rfre_int( e->n );
    fre_ExprConst( e );
}

/* Recursively free an element 'e' of class type 'ExprNegate'
   and all elements in it.
 */
static void rfre_ExprNegate( ExprNegate e )
{
    if( e == ExprNegateNIL ){
	return;
    }
    /* There are no subclasses. */
    rfre_expr( e->x );
    fre_ExprNegate( e );
}

/* Recursively free an element 'e' of class type 'ExprPlus'
   and all elements in it.
 */
static void rfre_ExprPlus( ExprPlus e )
{
    if( e == ExprPlusNIL ){
	return;
    }
    /* There are no subclasses. */
    rfre_expr( e->a );
    rfre_expr( e->b );
    fre_ExprPlus( e );
}

/* Recursively free an element 'e' of class type 'ExprSymbol'
   and all elements in it.
 */
static void rfre_ExprSymbol( ExprSymbol e )
{
    if( e == ExprSymbolNIL ){
	return;
    }
    /* There are no subclasses. */
    rfre_tmstring( e->s );
    fre_ExprSymbol( e );
}

/* Recursively free an element 'e' of class type 'ExprTimes'
   and all elements in it.
 */
static void rfre_ExprTimes( ExprTimes e )
{
    if( e == ExprTimesNIL ){
	return;
    }
    /* There are no subclasses. */
    rfre_expr( e->a );
    rfre_expr( e->b );
    fre_ExprTimes( e );
}

/* Recursively free a list of elements 'e' of type statement. */
void rfre_statement_list( statement_list e )
{
    unsigned int ix;

    if( e == statement_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_statement( e->arr[ix] );
    }
    fre_statement_list( e );
}

/**************************************************
 *    print_<type> and print_<type>_list routines *
 **************************************************/


static void print_statement( TMPRINTSTATE *st, const statement );
static void print_expr( TMPRINTSTATE *st, const expr );
static void print_ExprConst( TMPRINTSTATE *st, const ExprConst );
static void print_ExprNegate( TMPRINTSTATE *st, const ExprNegate );
static void print_ExprPlus( TMPRINTSTATE *st, const ExprPlus );
static void print_ExprSymbol( TMPRINTSTATE *st, const ExprSymbol );
static void print_ExprTimes( TMPRINTSTATE *st, const ExprTimes );

/* Print an element 't' of class type 'statement'
 * using print optimizer.
 */
static void print_statement( TMPRINTSTATE *st, const statement t )
{
    if( t == statementNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_opencons( st );
    tm_printword( st, "statement" );
    print_tmstring( st, t->lhs );
    print_expr( st, t->rhs );
    tm_closecons( st );
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
	    FATALTAG( (int) t->tag );
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
    tm_opencons( st );
    tm_printword( st, "ExprConst" );
    print_int( st, t->n );
    tm_closecons( st );
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
    tm_opencons( st );
    tm_printword( st, "ExprNegate" );
    print_expr( st, t->x );
    tm_closecons( st );
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
    tm_opencons( st );
    tm_printword( st, "ExprPlus" );
    print_expr( st, t->a );
    print_expr( st, t->b );
    tm_closecons( st );
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
    tm_opencons( st );
    tm_printword( st, "ExprSymbol" );
    print_tmstring( st, t->s );
    tm_closecons( st );
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
    tm_opencons( st );
    tm_printword( st, "ExprTimes" );
    print_expr( st, t->a );
    print_expr( st, t->b );
    tm_closecons( st );
}

/* Print a list of elements 'l' of type 'statement'
   using print optimizer.
 */
void print_statement_list( TMPRINTSTATE *st, const statement_list l )
{
    unsigned int ix;

    if( l == statement_listNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_openlist( st );
    for( ix=0; ix<l->sz; ix++ ){
	print_statement( st, l->arr[ix] );
    }
    tm_closelist( st );
}

/**************************************************
 *    Scan routines.                              *
 **************************************************/

#ifdef LOGNEW
#define fscan_statement(f,ep) real_fscan_statement(f,ep,_f,_l)
#define fscan_expr(f,ep) real_fscan_expr(f,ep,_f,_l)
#undef fscan_statement_list
#define fscan_statement_list(f,lp) real_fscan_statement_list(f,lp,_f,_l)

static int real_fscan_statement( FILE *, statement *, const char *_f, const int _l );
static int real_fscan_expr( FILE *, expr *, const char *_f, const int _l );

#else

static int fscan_statement( FILE *, statement * );
static int fscan_expr( FILE *, expr * );

#endif

/* Read a class of type statement
   from file 'f' and allocate space for it.
   Set the pointer 'p' to point to that structure.
 */
#ifdef LOGNEW
static int real_fscan_statement( FILE *f, statement *p, const char *_f, const int _l )
#else
static int fscan_statement( FILE *f, statement *p )
#endif
{
    int n;
    int c;
    int err;
    char tm_word[13];	/* Largest constructor should fit in it.. */

#ifdef LOGNEW
    (void) _f;
    (void) _l;
#endif
    *p = statementNIL;
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
    if( tm_fscancons( f, tm_word, 13 ) ){
	return 1;
    }
    if( strcmp( tm_word, "statement" ) == 0 ){
	tmstring l_lhs;
	expr l_rhs;

	l_lhs = tmstringNIL;
	if( !err){
	    err = fscan_tmstring( f, &l_lhs );
	}
	l_rhs = exprNIL;
	if( !err){
	    err = fscan_expr( f, &l_rhs );
	}
	*p = new_statement( l_lhs, l_rhs );
    }
    else {
	(void) sprintf( tm_errmsg, tm_badcons, "statement", tm_word );
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
    int err;
    char tm_word[14];	/* Largest constructor should fit in it.. */

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
	if( !err){
	    err = fscan_expr( f, &l_a );
	}
	l_b = exprNIL;
	if( !err){
	    err = fscan_expr( f, &l_b );
	}
	*p =  (expr) new_ExprPlus( l_a, l_b );
    }
    else if( strcmp( tm_word, "ExprTimes" ) == 0 ){
	expr l_a;
	expr l_b;

	l_a = exprNIL;
	if( !err){
	    err = fscan_expr( f, &l_a );
	}
	l_b = exprNIL;
	if( !err){
	    err = fscan_expr( f, &l_b );
	}
	*p =  (expr) new_ExprTimes( l_a, l_b );
    }
    else if( strcmp( tm_word, "ExprNegate" ) == 0 ){
	expr l_x;

	l_x = exprNIL;
	if( !err){
	    err = fscan_expr( f, &l_x );
	}
	*p =  (expr) new_ExprNegate( l_x );
    }
    else if( strcmp( tm_word, "ExprConst" ) == 0 ){
	int l_n;

	l_n = intNIL;
	if( !err){
	    err = fscan_int( f, &l_n );
	}
	*p =  (expr) new_ExprConst( l_n );
    }
    else if( strcmp( tm_word, "ExprSymbol" ) == 0 ){
	tmstring l_s;

	l_s = tmstringNIL;
	if( !err){
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

/* Read an instance of a list of datastructure of type statement
   from file 'f' and allocate space for it. Set the pointer 'p' to
   point to that structure.
 */
#ifdef LOGNEW
int real_fscan_statement_list( FILE *f, statement_list *p, const char *_f, const int _l )
#else
int fscan_statement_list( FILE *f, statement_list *p )
#endif
{
    int c;
    int n;
    statement nw;
    int err = 0;

    *p = statement_listNIL;
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
    *p = new_statement_list();
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
	    err = fscan_statement( f, &nw );
	}
	*p = append_statement_list( *p, nw );
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
 *    Miscellaneous routines                      *
 **************************************************/
/* Print allocation and freeing statistics to file 'f'. */
void stat_calc( FILE *f )
{
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
	"statement",
	newcnt_statement,
	frecnt_statement,
	((newcnt_statement==frecnt_statement)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed, "statement_list",
	newcnt_statement_list,
	frecnt_statement_list,
	((newcnt_statement_list==frecnt_statement_list)? "": "<-")
    );
}

/* Return -1 if there is a structure that has freed more than allocated, or
 * else return 1 if there is a structure that has been freed less than
 * allocated, or else return 0.
 */
int get_balance_calc( void )
{
    int res;

    res = 0;
    /* Check for too many fre()s. */
    if( newcnt_statement_list<frecnt_statement_list ){
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
    if( newcnt_statement<frecnt_statement ){
        return -1;
    }
    /* Check for too many fre()s. */
    if( newcnt_statement_list>frecnt_statement_list ){
        res = 1;
    }
    if( newcnt_ExprConst>frecnt_ExprConst ){
        res = 1;
    }
    if( newcnt_ExprNegate>frecnt_ExprNegate ){
        res = 1;
    }
    if( newcnt_ExprPlus>frecnt_ExprPlus ){
        res = 1;
    }
    if( newcnt_ExprSymbol>frecnt_ExprSymbol ){
        res = 1;
    }
    if( newcnt_ExprTimes>frecnt_ExprTimes ){
        res = 1;
    }
    if( newcnt_statement>frecnt_statement ){
        res = 1;
    }
    return res;
}

/* ---- end of /usr/local/lib/tmc.ct ---- */
/* Code generation required 150 milliseconds. */
