/* File: subst.c
 *
 * Substitute known variables in expressions.
 */

#include <assert.h>
#include <tmc.h>

#include "calc.h"

/* ----------- Generated forward declarations start here ----------- */

/* Forward declarations. */
static command_list subst_command_list_walker( command_list e, command_list *lets );
static ExprPlus subst_ExprPlus_walker( ExprPlus e, command_list *lets );
static ExprTimes subst_ExprTimes_walker( ExprTimes e, command_list *lets );
static ExprNegate subst_ExprNegate_walker( ExprNegate e, command_list *lets );
static ExprSymbol subst_ExprSymbol_walker( ExprSymbol e, command_list *lets );
static expr subst_expr_walker( expr e, command_list *lets );
static command subst_command_walker( command e, command_list *lets );

/* ----------- Generated forward declarations end here ----------- */

static tmbool find_command( tmconststring nm, command_list l, unsigned int *pos )
{
    unsigned int ix;

    for( ix=0; ix<l->sz; ix++ ){
        if( strcmp( l->arr[ix]->lhs, nm ) == 0 ){
            *pos = ix;
            return TMTRUE;
        }
    }
    return TMFALSE;
}

static expr subst_ExprSymbol_action( ExprSymbol s, command_list *lets )
{
    unsigned int pos;
    expr res;

    s = (ExprSymbol) subst_ExprSymbol_walker( s, lets );
    if( find_command( s->s, *lets, &pos ) ){
        rfre_expr( (expr) s );
        res = rdup_expr( (*lets)->arr[pos]->rhs );
    }
    else {
        res = (expr) s;
    }
    return res;
}

/* First apply substitutions in the rhs of the command, then
 * add or replace the current assignment to the state.
 */
static command subst_command_action( command c, command_list *lets )
{
    unsigned int pos;

    c = (command) subst_command_walker( c, lets );
    if( find_command( c->lhs, *lets, &pos ) ){
        *lets = delete_command_list( *lets, pos );
    }
    *lets = append_command_list( *lets, rdup_command( c ) );
    return c;
}

/* ----------- Generated code starts here ----------- */

/* Given a list command_list, rewrite it. */
static command_list subst_command_list_walker( command_list e, command_list *lets )
{
    unsigned int ix;

    for( ix=0; ix<e->sz; ix++ ){
        e->arr[ix] = (command) subst_command_action( e->arr[ix], lets );
    }
    return e;
}

/* Given a class ExprPlus, rewrite it. */
static ExprPlus subst_ExprPlus_walker( ExprPlus e, command_list *lets )
{
    e->a = (expr) subst_expr_walker( e->a, lets );
    e->b = (expr) subst_expr_walker( e->b, lets );
    return e;
}

/* Given a class ExprTimes, rewrite it. */
static ExprTimes subst_ExprTimes_walker( ExprTimes e, command_list *lets )
{
    e->a = (expr) subst_expr_walker( e->a, lets );
    e->b = (expr) subst_expr_walker( e->b, lets );
    return e;
}

/* Given a class ExprNegate, rewrite it. */
static ExprNegate subst_ExprNegate_walker( ExprNegate e, command_list *lets )
{
    e->x = (expr) subst_expr_walker( e->x, lets );
    return e;
}

/* Given a class ExprSymbol, rewrite it. */
static ExprSymbol subst_ExprSymbol_walker( ExprSymbol e, command_list *lets )
{
    (void) lets;
    return e;
}

/* Given a class expr, rewrite it. */
static expr subst_expr_walker( expr e, command_list *lets )
{
    switch( e->tag ){
        case TAGExprPlus:
            e = (expr) subst_ExprPlus_walker( to_ExprPlus( e ), lets );
            break;

        case TAGExprTimes:
            e = (expr) subst_ExprTimes_walker( to_ExprTimes( e ), lets );
            break;

        case TAGExprNegate:
            e = (expr) subst_ExprNegate_walker( to_ExprNegate( e ), lets );
            break;

        case TAGExprSymbol:
            e = (expr) subst_ExprSymbol_action( to_ExprSymbol( e ), lets );
            break;

        default:
            break;

    }
    return e;
}

/* Given a class command, rewrite it. */
static command subst_command_walker( command e, command_list *lets )
{
    e->rhs = (expr) subst_expr_walker( e->rhs, lets );
    return e;
}


/* ----------- Generated code ends here ----------- */

int main( void )
{
    TMPRINTSTATE *st;
    int level;
    command_list sl;
    command_list context;
    command_list *lets = &context;

    tm_lineno = 1;
    if( fscan_command_list( stdin, &sl ) ){
        fprintf( stderr, "calcopt: %d: %s\n", tm_lineno, tm_errmsg );
        exit( 1 );
    }
    context = new_command_list();
    sl = (command_list) subst_command_list_walker( sl, lets );
    rfre_command_list( context );
    st = tm_setprint( stdout, 1, 75, 8, 0 );
    print_command_list( st, sl );
    level = tm_endprint( st );
    if( level != 0 ){
        fprintf( stderr, "Internal error: bracket level = %d\n", level );
        exit( 1 );
    }
    rfre_command_list( sl );
    if( get_balance_calc() != 0 || get_balance_tmstring() != 0 ){
        fprintf( stderr, "Tm object allocation not balanced\n" );
        stat_calc( stderr );
        stat_tmstring( stderr );
        report_lognew( stderr );
    }
    exit( 0 );
    return 0;
}
