/* File: $Id$
 *
 * Description of exported objects of lex.c
 */

typedef enum en_lextok {
    NONE, SEMI, BAR, NAME, COLON, COMMA, EQ, EQEQ, TILDEQ,
    ARROW, COLCOLEQ, INCLUDE, LSBRAC, RSBRAC, LRBRAC, RRBRAC,
    LCBRAC, RCBRAC,
    LEXEOF, STRING, PLUS
} lextok;

typedef union un_YYSTYPE {
    char *parstring;
    tmsymbol parsymbol;
} YYSTYPE;

extern YYSTYPE yylval;

#define LINESIZE 300

extern lextok yylex( void );
extern void set_lexfile( FILE *f, const char *nm );
extern void set_lex_debugging( tmbool flag );
extern void parserror( const char *msg );
extern origin make_origin( void );

extern void init_lex( void );
extern void end_lex( void );
extern void stat_lex( FILE *f );
