#include <stdio.h>
#include <tmc.h>

#include "calc.h"

/* Small utility function to get the value of an ExprConst. */
static int get_const( expr x )
{
    if( x->tag != TAGExprConst ){
	fprintf( stderr, "Internal error: not a const\n" );
	exit( 1 );
    }
    return to_ExprConst(x)->n;
}

static expr optimize_expr( expr x )
{
    switch( x->tag ){
	case TAGExprPlus:
	{
	    ExprPlus px = to_ExprPlus( x );

	    px->a = optimize_expr( px->a );
	    px->b = optimize_expr( px->b );
	    if( px->a->tag == TAGExprConst && px->b->tag == TAGExprConst ){
		int sum = get_const( px->a )+get_const( px->b );

		rfre_expr( x );
		x = (expr) new_ExprConst( sum );
	    }
	    break;
	}

	case TAGExprTimes:
	{
	    ExprTimes px = to_ExprTimes( x );

	    px->a = optimize_expr( px->a );
	    px->b = optimize_expr( px->b );
	    if( px->a->tag == TAGExprConst && px->b->tag == TAGExprConst ){
		int prod = get_const( px->a )*get_const( px->b );

		rfre_expr( x );
		x = (expr) new_ExprConst( prod );
	    }
	    break;
	}

	case TAGExprNegate:
	{
	    ExprNegate px = to_ExprNegate( x );

	    px->x = optimize_expr( px->x );
	    if( px->x->tag == TAGExprConst ){
		int nx = -get_const( px->x );

		rfre_expr( x );
		x = (expr) new_ExprConst( nx );
	    }
	    break;
	}

	case TAGExprConst:
	case TAGExprSymbol:
	    break;
    }
    return x;
}

static statement optimize_statement( statement s )
{
    s->rhs = optimize_expr( s->rhs );
    return s;
}

static statement_list optimize_statement_list( statement_list sl )
{
    unsigned int ix;

    for( ix=0; ix<sl->sz; ix++ ){
	sl->arr[ix] = optimize_statement( sl->arr[ix] );
    }
    return sl;
}

int main( void )
{
    TMPRINTSTATE *st;
    int level;
    statement_list sl;

    tm_lineno = 1;
    if( fscan_statement_list( stdin, &sl ) ){
	fprintf( stderr, "calcopt: %d: %s\n", tm_lineno, tm_errmsg );
	exit( 1 );
    }
    sl = optimize_statement_list( sl );
    st = tm_setprint( stdout, 1, 75, 8, 0 );
    print_statement_list( st, sl );
    level = tm_endprint( st );
    if( level != 0 ){
	fprintf( stderr, "Internal error: bracket level = %d\n", level );
	exit( 1 );
    }
    rfre_statement_list( sl );
    if( get_balance_calc() != 0 || get_balance_tmstring() != 0 ){
        fprintf( stderr, "Tm object allocation not balanced\n" );
        stat_calc( stderr );
        stat_tmstring( stderr );
        report_lognew( stderr );
    }
    exit( 0 );
    return 0;
}
