
/* Requirement analysis took 90 milliseconds. */
/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /usr/local/lib/tmc.ht ---- */
/* External definitions (Version for array list).

   template file:      /usr/local/lib/tmc.ht
   datastructure file: calc.ds
   tm version:         36
   tm kernel version:  2.0-beta4
 */

/* data structures */

/* forward reference typedefs for all types.
 * C does not like the use of undefined types, but does not
 * mind the use of pointers to (yet) undefined types.
 */
typedef struct str_statement_list *statement_list;
typedef struct str_ExprConst *ExprConst;
typedef struct str_ExprSymbol *ExprSymbol;
typedef struct str_expr *expr;
typedef struct str_ExprNegate *ExprNegate;
typedef struct str_ExprPlus *ExprPlus;
typedef struct str_ExprTimes *ExprTimes;
typedef struct str_statement *statement;

#define statement_listNIL (statement_list)0
#define ExprConstNIL (ExprConst)0
#define ExprNegateNIL (ExprNegate)0
#define ExprPlusNIL (ExprPlus)0
#define ExprSymbolNIL (ExprSymbol)0
#define ExprTimesNIL (ExprTimes)0
#define statementNIL (statement)0
#define exprNIL (expr)0

typedef enum en_tags_expr {
    TAGExprPlus, TAGExprTimes, TAGExprNegate, TAGExprConst, TAGExprSymbol
} tags_expr;

typedef enum en_tags_statement {
    TAGstatement
} tags_statement;


/* Structure for class ExprConst. */
struct str_ExprConst {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
    int n;
};

/* Structure for class ExprSymbol. */
struct str_ExprSymbol {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
    tmstring s;
};

/* Structure for class expr. */
struct str_expr {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
};

/* Structure for class ExprNegate. */
struct str_ExprNegate {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
    expr x;
};

/* Structure for class ExprPlus. */
struct str_ExprPlus {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
    expr a;
    expr b;
};

/* Structure for class ExprTimes. */
struct str_ExprTimes {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
    expr a;
    expr b;
};

/* Structure for class statement. */
struct str_statement {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_statement tag;
    tmstring lhs;
    expr rhs;
};


struct str_statement_list {
    unsigned int sz;
    unsigned int room;
    statement *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

/* Type casting macros. */
#define to_ExprConst(e) ((ExprConst)e)
#define to_ExprNegate(e) ((ExprNegate)e)
#define to_ExprPlus(e) ((ExprPlus)e)
#define to_ExprSymbol(e) ((ExprSymbol)e)
#define to_ExprTimes(e) ((ExprTimes)e)
#define to_statement(e) ((statement)e)
#define to_expr(e) ((expr)e)

/* new_<type> routines */
#ifdef LOGNEW
#define new_ExprConst(n) real_new_ExprConst(n,__FILE__,__LINE__)
#define new_ExprNegate(x) real_new_ExprNegate(x,__FILE__,__LINE__)
#define new_ExprPlus(a,b) real_new_ExprPlus(a,b,__FILE__,__LINE__)
#define new_ExprSymbol(s) real_new_ExprSymbol(s,__FILE__,__LINE__)
#define new_ExprTimes(a,b) real_new_ExprTimes(a,b,__FILE__,__LINE__)
#define new_statement(lhs,rhs) real_new_statement(lhs,rhs,__FILE__,__LINE__)
#define new_statement_list() real_new_statement_list(__FILE__,__LINE__)
#define fscan_statement_list(f,l) real_fscan_statement_list(f,l,__FILE__,__LINE__)
#endif

#ifdef LOGNEW
extern ExprConst real_new_ExprConst( int, const char *, const int );
extern ExprNegate real_new_ExprNegate( expr, const char *, const int );
extern ExprPlus real_new_ExprPlus( expr, expr, const char *, const int );
extern ExprSymbol real_new_ExprSymbol( tmstring, const char *, const int );
extern ExprTimes real_new_ExprTimes( expr, expr, const char *, const int );
extern statement real_new_statement( tmstring, expr, const char *, const int );
extern statement_list real_new_statement_list( const char *file, const int line );
#else
extern ExprConst new_ExprConst( int );
extern ExprNegate new_ExprNegate( expr );
extern ExprPlus new_ExprPlus( expr, expr );
extern ExprSymbol new_ExprSymbol( tmstring );
extern ExprTimes new_ExprTimes( expr, expr );
extern statement new_statement( tmstring, expr );
extern statement_list new_statement_list( void );
#endif
extern statement_list append_statement_list( statement_list, statement );
extern void rfre_statement_list( statement_list );
extern void rfre_expr( expr );
extern void print_statement_list( TMPRINTSTATE *, const statement_list );
#ifdef LOGNEW
extern int real_fscan_statement_list( FILE *, statement_list *, const char *, const int );
#else
extern int fscan_statement_list( FILE *, statement_list * );
#endif
extern void stat_calc( FILE * );
extern int get_balance_calc( void );
/* ---- end of /usr/local/lib/tmc.ht ---- */
/* Code generation required 120 milliseconds. */
