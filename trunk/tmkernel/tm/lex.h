/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: lex.h
   Description of exported objects of lex.c
 */

typedef enum en_lextok {
    NONE, SEMI, BAR, NAME, COLON, COMMA, EQEQ,
    COLCOLEQ, INCLUDE, LSBRAC, RSBRAC, LRBRAC, RRBRAC,
    LEXEOF, STRING, PLUS
} lextok;

typedef union un_YYSTYPE {
    ds pards;
    ds_list pardslist;
    constructor parcons;
    constructor_list parconslist;
    field parfield;
    field_list parfieldlist;
    char *parstring;
} YYSTYPE;

extern YYSTYPE yylval;

extern lextok yylex( void );
extern void init_lex( void );
extern void end_lex( void );
extern void stat_lex( FILE *f );

