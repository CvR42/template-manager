%{
#include <stdlib.h>
#include <tmc.h>

#include "calc.h"
#include "tokens.h"

#ifdef LINUX
#define yywrap() (1)
#endif

%}
%option noyywrap
%option input
%option nounput

white_space	[ \t\f\n]
letter		[A-Za-z_]
identifier	{letter}({letter}|[0-9])*
number		[0-9]+

%%

{white_space}+	{}
{number}	{
		    yylval._literal = atoi( yytext );
		    return LITERAL;
		}
{identifier}	{
		    yylval._identifier = new_tmstring( yytext );
		    return IDENTIFIER;
		}
.		{ return *yytext; }

%%
