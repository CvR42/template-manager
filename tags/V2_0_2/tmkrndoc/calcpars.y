%{
#include <tmc.h>

#include "calc.h"

static statement_list result;

static void yyerror( const char *s )
{
    fprintf( stderr, "%s\n" );
    exit( 1 );
}

%}

/* use sort -b +2 */

%union {
    expr		_expr;
    statement		_statement;
    statement_list	_statementList;
    tmstring		_identifier;
    int			_literal;
}

%start program

%token <_identifier>	IDENTIFIER
%token <_literal>	LITERAL

%type	<_expr>			expr
%type	<_statement>		statement
%type	<_statementList>	statementList

%left '+' '-'
%left '*' '/' '%'

%%

program:
    statementList
	{ result = $1; }
;

statementList:
    /* empty */
	{ $$ = new_statement_list(); }
|
    statement
	{ $$ = append_statement_list( new_statement_list(), $1 ); }
|
    statementList ',' statement
	{ $$ = append_statement_list( $1, $3 ); }
;

statement:
    IDENTIFIER '=' expr ';'
	{ $$ = new_statement( $1, $3 ); }
;

expr:
    expr '+' expr
	{ $$ = new_ExprPlus( $1, $3 ); }
|
    expr '-' expr
	{ $$ = new_ExprMinus( $1, $3 ); }
|
    expr '*' expr
	{ $$ = new_ExprTimes( $1, $3 ); }
|
    expr '/' expr
	{ $$ = new_ExprDivide( $1, $3 ); }
|
    expr '%' expr
	{ $$ = new_ExprDivide( $1, $3 ); }
|
    '-' expr
	{ $$ = new_ExprNegate( $2 ); }
|
    LITERAL
	{ $$ = new_ExprConst( $1 ); }
|
    IDENTIFIER
	{ $$ = new_ExprSymbol( $1 ); }
|
    '(' expr ')'
	{ $$ = $2; }
;

%%

int main( int argc, char **argv )
{
    TMPRINTSTATE *st;
    int level;

    if( yyparse() ){
	exit( 1 );
    }
    st = tm_setprint( stdout, 1, 75, 8, 0 );
    print_statement_list( st, result );
    level = tm_endprint( st );
    if( level != 0 ){             
	fprintf( stderr, "Internal botch: bracket level = %d\n", level );
    }                
    if( get_balance_calc() != 0 || get_balance_tmstring() != 0 ){      
        fprintf( stderr, "Tm object allocation not balanced\n" );
        stat_calc( stderr );                    
        stat_tmstring( stderr );                            
        report_lognew( stderr );                                                
    }
    exit( 0 );
    return 0;
}
