
/* Requirement analysis took 100 milliseconds. */
/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /usr/local/lib/tmc.ht ---- */
/* External definitions (Version for array list).

   template file:      /usr/local/lib/tmc.ht
   datastructure file: calc.ds
   tm version:         36
   tm kernel version:  2.0-beta19
 */

/* data structures */

/* forward reference typedefs for all types.
 * C does not like the use of undefined types, but does not
 * mind the use of pointers to (yet) undefined types.
 */
typedef struct str_command_list *command_list;
typedef struct str_expr *expr;
typedef struct str_ExprConst *ExprConst;
typedef struct str_ExprNegate *ExprNegate;
typedef struct str_ExprPlus *ExprPlus;
typedef struct str_ExprSymbol *ExprSymbol;
typedef struct str_ExprTimes *ExprTimes;
typedef struct str_command *command;

#define command_listNIL (command_list)0
#define ExprConstNIL (ExprConst)0
#define ExprNegateNIL (ExprNegate)0
#define ExprPlusNIL (ExprPlus)0
#define ExprSymbolNIL (ExprSymbol)0
#define ExprTimesNIL (ExprTimes)0
#define commandNIL (command)0
#define exprNIL (expr)0

typedef enum en_tags_command {
    TAGcommand
} tags_command;

typedef enum en_tags_expr {
    TAGExprPlus, TAGExprTimes, TAGExprNegate, TAGExprConst, TAGExprSymbol
} tags_expr;


#ifdef __cplusplus
/* Structure for class 'command'. */
class str_command {
public:
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_command tag;
    tmstring lhs;
    expr rhs;
};

/* Structure for class 'expr'. */
class str_expr {
public:
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
};

/* Structure for class 'ExprConst'. */
class str_ExprConst: public str_expr {
public:
    int n;
};

/* Structure for class 'ExprNegate'. */
class str_ExprNegate: public str_expr {
public:
    expr x;
};

/* Structure for class 'ExprPlus'. */
class str_ExprPlus: public str_expr {
public:
    expr a;
    expr b;
};

/* Structure for class 'ExprSymbol'. */
class str_ExprSymbol: public str_expr {
public:
    tmstring s;
};

/* Structure for class 'ExprTimes'. */
class str_ExprTimes: public str_expr {
public:
    expr a;
    expr b;
};

#else
/* Structure for class 'expr'. */
struct str_expr {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
};

/* Structure for class 'ExprConst'. */
struct str_ExprConst {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
    int n;
};

/* Structure for class 'ExprNegate'. */
struct str_ExprNegate {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
    expr x;
};

/* Structure for class 'ExprPlus'. */
struct str_ExprPlus {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
    expr a;
    expr b;
};

/* Structure for class 'ExprSymbol'. */
struct str_ExprSymbol {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
    tmstring s;
};

/* Structure for class 'ExprTimes'. */
struct str_ExprTimes {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_expr tag;
    expr a;
    expr b;
};

/* Structure for class 'command'. */
struct str_command {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_command tag;
    tmstring lhs;
    expr rhs;
};

#endif

struct str_command_list {
    unsigned int sz;
    unsigned int room;
    command *arr;
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
#define to_command(e) ((command)e)
#define to_expr(e) ((expr)e)

/* new_<type> routines */
#ifdef LOGNEW
#define new_ExprConst(n) real_new_ExprConst(n,__FILE__,__LINE__)
#define new_ExprNegate(x) real_new_ExprNegate(x,__FILE__,__LINE__)
#define new_ExprPlus(a,b) real_new_ExprPlus(a,b,__FILE__,__LINE__)
#define new_ExprSymbol(s) real_new_ExprSymbol(s,__FILE__,__LINE__)
#define new_ExprTimes(a,b) real_new_ExprTimes(a,b,__FILE__,__LINE__)
#define new_command(lhs,rhs) real_new_command(lhs,rhs,__FILE__,__LINE__)
#define new_command_list() real_new_command_list(__FILE__,__LINE__)
#define rdup_command(e) real_rdup_command(e,__FILE__,__LINE__)
#define rdup_expr(e) real_rdup_expr(e,__FILE__,__LINE__)
#define fscan_command_list(f,l) real_fscan_command_list(f,l,__FILE__,__LINE__)
#endif

#ifdef LOGNEW
extern ExprConst real_new_ExprConst( int, const char *, const int );
extern ExprNegate real_new_ExprNegate( expr, const char *, const int );
extern ExprPlus real_new_ExprPlus( expr, expr, const char *, const int );
extern ExprSymbol real_new_ExprSymbol( tmstring, const char *, const int );
extern ExprTimes real_new_ExprTimes( expr, expr, const char *, const int );
extern command real_new_command( tmstring, expr, const char *, const int );
extern command_list real_new_command_list( const char *file, const int line );
#else
extern ExprConst new_ExprConst( int );
extern ExprNegate new_ExprNegate( expr );
extern ExprPlus new_ExprPlus( expr, expr );
extern ExprSymbol new_ExprSymbol( tmstring );
extern ExprTimes new_ExprTimes( expr, expr );
extern command new_command( tmstring, expr );
extern command_list new_command_list( void );
#endif
extern command_list append_command_list( command_list, command );
extern command_list delete_command_list( command_list, const unsigned int );
extern void rfre_command_list( command_list );
extern void rfre_expr( expr );
extern void print_command_list( TMPRINTSTATE *, const command_list );
#ifdef LOGNEW
extern command real_rdup_command( const command, const char *_f, const int _l );
extern expr real_rdup_expr( const expr, const char *_f, const int _l );
#else
extern command rdup_command( const command );
extern expr rdup_expr( const expr );
#endif
#ifdef LOGNEW
extern int real_fscan_command_list( FILE *, command_list *, const char *, const int );
#else
extern int fscan_command_list( FILE *, command_list * );
#endif
extern void stat_calc( FILE * );
extern int get_balance_calc( void );
/* ---- end of /usr/local/lib/tmc.ht ---- */
/* Code generation required 130 milliseconds. */
