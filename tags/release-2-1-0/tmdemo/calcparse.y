%{
#include <tmc.h>

#include "calc.h"

static command_list result;

static void yyerror( const char *s )
{
    fprintf( stderr, "%s\n", s );
    exit( 1 );
}

%}

%union {
    expr			_expr;
    command			_command;
    command_list		_commandList;
    tmstring			_identifier;
    int				_literal;
}

%start program

%token <_identifier>		IDENTIFIER
%token <_literal>		LITERAL

%type	<_expr>			expr
%type	<_command>		command
%type	<_commandList>	commandList

%left '+' '-'
%left '*'

%%

program:
    commandList
	{ result = $1; }
;

commandList:
    /* empty */
	{ $$ = new_command_list(); }
|
    commandList command
	{ $$ = append_command_list( $1, $2 ); }
;

command:
    IDENTIFIER '=' expr ';'
	{ $$ = new_command( $1, $3 ); }
;

expr:
    expr '+' expr
	{ $$ = (expr) new_ExprPlus( $1, $3 ); }
|
    expr '-' expr
	{ $$ = (expr) new_ExprPlus( $1, (expr) new_ExprNegate( $3 ) ); }
|
    expr '*' expr
	{ $$ = (expr) new_ExprTimes( $1, $3 ); }
|
    '-' expr
	{ $$ = (expr) new_ExprNegate( $2 ); }
|
    LITERAL
	{ $$ = (expr) new_ExprConst( $1 ); }
|
    IDENTIFIER
	{ $$ = (expr) new_ExprSymbol( $1 ); }
|
    '(' expr ')'
	{ $$ = $2; }
;

%%

int main( void )
{
    TMPRINTSTATE *st;
    int level;

    if( yyparse() ){
	exit( 1 );
    }
    st = tm_setprint( stdout, 1, 75, 8, 0 );
    print_command_list( st, result );
    level = tm_endprint( st );
    if( level != 0 ){
	fprintf( stderr, "Internal error: bracket level = %d\n", level );
	exit( 1 );
    }
    rfre_command_list( result );
    if( get_balance_calc() != 0 || get_balance_tmstring() != 0 ){
        fprintf( stderr, "Tm object allocation not balanced\n" );
        stat_calc( stderr );
        stat_tmstring( stderr );
        report_lognew( stderr );
    }
    exit( 0 );
    return 0;
}
