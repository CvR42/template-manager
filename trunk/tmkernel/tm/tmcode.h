/* Requirement analysis took 360 milliseconds. */
/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /usr/local/lib/tmc.ht ---- */
/* External definitions (Version for array list).

   template file:      /usr/local/lib/tmc.ht
   datastructure file: tm.ds
   tm version:         36
   tm kernel version:  2.0-beta11
 */

/* data structures */

/* forward reference typedefs for all types.
 * C does not like the use of undefined types, but does not
 * mind the use of pointers to (yet) undefined types.
 */
typedef struct str_alternative_list *alternative_list;
typedef struct str_classComponent_list *classComponent_list;
typedef struct str_ds_list *ds_list;
typedef struct str_field_list *field_list;
typedef struct str_macro_list *macro_list;
typedef struct str_switchcase_list *switchcase_list;
typedef struct str_tmstring_list *tmstring_list;
typedef struct str_tplelm_list *tplelm_list;
typedef struct str_var_list *var_list;
typedef struct str_Append *Append;
typedef struct str_Appendfile *Appendfile;
typedef struct str_CCAlternatives *CCAlternatives;
typedef struct str_CCFields *CCFields;
typedef struct str_CCSublist *CCSublist;
typedef struct str_CCSuper *CCSuper;
typedef struct str_Call *Call;
typedef struct str_Case *Case;
typedef struct str_Default *Default;
typedef struct str_DsAlias *DsAlias;
typedef struct str_DsClass *DsClass;
typedef struct str_DsConstructor *DsConstructor;
typedef struct str_DsConstructorBase *DsConstructorBase;
typedef struct str_DsTuple *DsTuple;
typedef struct str_Error *Error;
typedef struct str_Exit *Exit;
typedef struct str_Foreach *Foreach;
typedef struct str_GlobalAppend *GlobalAppend;
typedef struct str_GlobalSet *GlobalSet;
typedef struct str_If *If;
typedef struct str_Include *Include;
typedef struct str_Insert *Insert;
typedef struct str_Macro *Macro;
typedef struct str_Plain *Plain;
typedef struct str_Redirect *Redirect;
typedef struct str_Rename *Rename;
typedef struct str_Return *Return;
typedef struct str_Set *Set;
typedef struct str_Switch *Switch;
typedef struct str_While *While;
typedef struct str_field *field;
typedef struct str_macro *macro;
typedef struct str_switchcase *switchcase;
typedef struct str_var *var;
typedef struct str_classComponent *classComponent;
typedef struct str_alternative *alternative;
typedef struct str_ds *ds;
typedef struct str_tplelm *tplelm;

#define alternative_listNIL (alternative_list)0
#define classComponent_listNIL (classComponent_list)0
#define ds_listNIL (ds_list)0
#define field_listNIL (field_list)0
#define macro_listNIL (macro_list)0
#define switchcase_listNIL (switchcase_list)0
#define tmstring_listNIL (tmstring_list)0
#define tplelm_listNIL (tplelm_list)0
#define var_listNIL (var_list)0
#define AppendNIL (Append)0
#define AppendfileNIL (Appendfile)0
#define CCAlternativesNIL (CCAlternatives)0
#define CCFieldsNIL (CCFields)0
#define CCSublistNIL (CCSublist)0
#define CCSuperNIL (CCSuper)0
#define CallNIL (Call)0
#define CaseNIL (Case)0
#define DefaultNIL (Default)0
#define DsAliasNIL (DsAlias)0
#define DsClassNIL (DsClass)0
#define DsConstructorNIL (DsConstructor)0
#define DsConstructorBaseNIL (DsConstructorBase)0
#define DsTupleNIL (DsTuple)0
#define ErrorNIL (Error)0
#define ExitNIL (Exit)0
#define ForeachNIL (Foreach)0
#define GlobalAppendNIL (GlobalAppend)0
#define GlobalSetNIL (GlobalSet)0
#define IfNIL (If)0
#define IncludeNIL (Include)0
#define InsertNIL (Insert)0
#define MacroNIL (Macro)0
#define PlainNIL (Plain)0
#define RedirectNIL (Redirect)0
#define RenameNIL (Rename)0
#define ReturnNIL (Return)0
#define SetNIL (Set)0
#define SwitchNIL (Switch)0
#define WhileNIL (While)0
#define alternativeNIL (alternative)0
#define fieldNIL (field)0
#define macroNIL (macro)0
#define switchcaseNIL (switchcase)0
#define varNIL (var)0
#define classComponentNIL (classComponent)0
#define dsNIL (ds)0
#define tplelmNIL (tplelm)0

typedef enum en_tags_classComponent {
    TAGCCSuper, TAGCCFields, TAGCCAlternatives, TAGCCSublist
} tags_classComponent;

typedef enum en_tags_ds {
    TAGDsConstructorBase, TAGDsTuple, TAGDsClass, TAGDsConstructor, TAGDsAlias
} tags_ds;

typedef enum en_tags_tplelm {
    TAGPlain, TAGForeach, TAGWhile, TAGIf, TAGSwitch, TAGSet, TAGRename, TAGGlobalSet, TAGAppend, TAGGlobalAppend, TAGError, TAGExit, TAGRedirect, TAGAppendfile, TAGMacro, TAGCall, TAGReturn, TAGInclude, TAGInsert, TAGCase, TAGDefault
} tags_tplelm;


#ifdef __cplusplus
/* Structure for tuple 'alternative'. */
struct str_alternative {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmstring label;
    classComponent component;
};

/* Structure for tuple 'field'. */
struct str_field {
#ifdef LOGNEW
    long int lognew_id;
#endif
    int level;
    tmstring name;
    tmstring type;
};

/* Structure for tuple 'macro'. */
struct str_macro {
#ifdef LOGNEW
    long int lognew_id;
#endif
    uint lvl;
    tmstring name;
    tmstring orgfile;
    tmstring_list fpl;
    tplelm_list body;
};

/* Structure for tuple 'switchcase'. */
struct str_switchcase {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmstring cases;
    tplelm_list action;
};

/* Structure for tuple 'var'. */
struct str_var {
#ifdef LOGNEW
    long int lognew_id;
#endif
    uint lvl;
    tmstring name;
    tmstring val;
};

/* Structure for class 'classComponent'. */
class str_classComponent {
public:
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_classComponent tag;
};

/* Structure for class 'CCAlternatives'. */
class str_CCAlternatives: public str_classComponent {
public:
    alternative_list alternatives;
};

/* Structure for class 'CCFields'. */
class str_CCFields: public str_classComponent {
public:
    field_list fields;
};

/* Structure for class 'CCSublist'. */
class str_CCSublist: public str_classComponent {
public:
    classComponent_list components;
};

/* Structure for class 'CCSuper'. */
class str_CCSuper: public str_classComponent {
public:
    tmstring super;
};

/* Structure for class 'ds'. */
class str_ds {
public:
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    tmstring name;
    tmstring_list inherits;
};

/* Structure for class 'DsAlias'. */
class str_DsAlias: public str_ds {
public:
    tmstring target;
};

/* Structure for class 'DsClass'. */
class str_DsClass: public str_ds {
public:
    field_list fields;
    tmbool virtual;
};

/* Structure for class 'DsConstructor'. */
class str_DsConstructor: public str_ds {
public:
    field_list fields;
};

/* Structure for class 'DsConstructorBase'. */
class str_DsConstructorBase: public str_ds {
public:
    tmstring_list constructors;
};

/* Structure for class 'DsTuple'. */
class str_DsTuple: public str_ds {
public:
    field_list fields;
};

/* Structure for class 'tplelm'. */
class str_tplelm {
public:
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
};

/* Structure for class 'Append'. */
class str_Append: public str_tplelm {
public:
    tmstring line;
};

/* Structure for class 'Appendfile'. */
class str_Appendfile: public str_tplelm {
public:
    tmstring fname;
    tplelm_list body;
};

/* Structure for class 'Call'. */
class str_Call: public str_tplelm {
public:
    tmstring line;
};

/* Structure for class 'Case'. */
class str_Case: public str_tplelm {
public:
    tmstring val;
};

/* Structure for class 'Default'. */
class str_Default: public str_tplelm {
public:
};

/* Structure for class 'Error'. */
class str_Error: public str_tplelm {
public:
    tmstring str;
};

/* Structure for class 'Exit'. */
class str_Exit: public str_tplelm {
public:
    tmstring str;
};

/* Structure for class 'Foreach'. */
class str_Foreach: public str_tplelm {
public:
    tmstring felist;
    tplelm_list body;
};

/* Structure for class 'GlobalAppend'. */
class str_GlobalAppend: public str_tplelm {
public:
    tmstring line;
};

/* Structure for class 'GlobalSet'. */
class str_GlobalSet: public str_tplelm {
public:
    tmstring line;
};

/* Structure for class 'If'. */
class str_If: public str_tplelm {
public:
    tmstring cond;
    tplelm_list ifthen;
    tplelm_list ifelse;
};

/* Structure for class 'Include'. */
class str_Include: public str_tplelm {
public:
    tmstring fname;
};

/* Structure for class 'Insert'. */
class str_Insert: public str_tplelm {
public:
    tmstring fname;
};

/* Structure for class 'Macro'. */
class str_Macro: public str_tplelm {
public:
    tmstring formals;
    tplelm_list body;
};

/* Structure for class 'Plain'. */
class str_Plain: public str_tplelm {
public:
    tmstring line;
};

/* Structure for class 'Redirect'. */
class str_Redirect: public str_tplelm {
public:
    tmstring fname;
    tplelm_list body;
};

/* Structure for class 'Rename'. */
class str_Rename: public str_tplelm {
public:
    tmstring line;
};

/* Structure for class 'Return'. */
class str_Return: public str_tplelm {
public:
    tmstring retval;
};

/* Structure for class 'Set'. */
class str_Set: public str_tplelm {
public:
    tmstring line;
};

/* Structure for class 'Switch'. */
class str_Switch: public str_tplelm {
public:
    tmstring val;
    switchcase_list cases;
    tplelm_list deflt;
};

/* Structure for class 'While'. */
class str_While: public str_tplelm {
public:
    tmstring cond;
    tplelm_list body;
};

#else
/* Structure for class 'Append'. */
struct str_Append {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring line;
};

/* Structure for class 'Appendfile'. */
struct str_Appendfile {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring fname;
    tplelm_list body;
};

/* Structure for class 'CCAlternatives'. */
struct str_CCAlternatives {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_classComponent tag;
    alternative_list alternatives;
};

/* Structure for class 'CCFields'. */
struct str_CCFields {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_classComponent tag;
    field_list fields;
};

/* Structure for class 'CCSublist'. */
struct str_CCSublist {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_classComponent tag;
    classComponent_list components;
};

/* Structure for class 'CCSuper'. */
struct str_CCSuper {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_classComponent tag;
    tmstring super;
};

/* Structure for class 'Call'. */
struct str_Call {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring line;
};

/* Structure for class 'Case'. */
struct str_Case {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring val;
};

/* Structure for class 'Default'. */
struct str_Default {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
};

/* Structure for class 'DsAlias'. */
struct str_DsAlias {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    tmstring name;
    tmstring_list inherits;
    tmstring target;
};

/* Structure for class 'DsClass'. */
struct str_DsClass {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    tmstring name;
    tmstring_list inherits;
    field_list fields;
    tmbool virtual;
};

/* Structure for class 'DsConstructor'. */
struct str_DsConstructor {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    tmstring name;
    tmstring_list inherits;
    field_list fields;
};

/* Structure for class 'DsConstructorBase'. */
struct str_DsConstructorBase {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    tmstring name;
    tmstring_list inherits;
    tmstring_list constructors;
};

/* Structure for class 'DsTuple'. */
struct str_DsTuple {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    tmstring name;
    tmstring_list inherits;
    field_list fields;
};

/* Structure for class 'Error'. */
struct str_Error {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring str;
};

/* Structure for class 'Exit'. */
struct str_Exit {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring str;
};

/* Structure for class 'Foreach'. */
struct str_Foreach {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring felist;
    tplelm_list body;
};

/* Structure for class 'GlobalAppend'. */
struct str_GlobalAppend {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring line;
};

/* Structure for class 'GlobalSet'. */
struct str_GlobalSet {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring line;
};

/* Structure for class 'If'. */
struct str_If {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring cond;
    tplelm_list ifthen;
    tplelm_list ifelse;
};

/* Structure for class 'Include'. */
struct str_Include {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring fname;
};

/* Structure for class 'Insert'. */
struct str_Insert {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring fname;
};

/* Structure for class 'Macro'. */
struct str_Macro {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring formals;
    tplelm_list body;
};

/* Structure for class 'Plain'. */
struct str_Plain {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring line;
};

/* Structure for class 'Redirect'. */
struct str_Redirect {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring fname;
    tplelm_list body;
};

/* Structure for class 'Rename'. */
struct str_Rename {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring line;
};

/* Structure for class 'Return'. */
struct str_Return {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring retval;
};

/* Structure for class 'Set'. */
struct str_Set {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring line;
};

/* Structure for class 'Switch'. */
struct str_Switch {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring val;
    switchcase_list cases;
    tplelm_list deflt;
};

/* Structure for class 'While'. */
struct str_While {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring cond;
    tplelm_list body;
};

/* Structure for tuple 'field'. */
struct str_field {
#ifdef LOGNEW
    long int lognew_id;
#endif
    int level;
    tmstring name;
    tmstring type;
};

/* Structure for tuple 'macro'. */
struct str_macro {
#ifdef LOGNEW
    long int lognew_id;
#endif
    uint lvl;
    tmstring name;
    tmstring orgfile;
    tmstring_list fpl;
    tplelm_list body;
};

/* Structure for tuple 'switchcase'. */
struct str_switchcase {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmstring cases;
    tplelm_list action;
};

/* Structure for tuple 'var'. */
struct str_var {
#ifdef LOGNEW
    long int lognew_id;
#endif
    uint lvl;
    tmstring name;
    tmstring val;
};

/* Structure for class 'classComponent'. */
struct str_classComponent {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_classComponent tag;
};

/* Structure for tuple 'alternative'. */
struct str_alternative {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmstring label;
    classComponent component;
};

/* Structure for class 'ds'. */
struct str_ds {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    tmstring name;
    tmstring_list inherits;
};

/* Structure for class 'tplelm'. */
struct str_tplelm {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
};

#endif

struct str_alternative_list {
    unsigned int sz;
    unsigned int room;
    alternative *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_classComponent_list {
    unsigned int sz;
    unsigned int room;
    classComponent *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_ds_list {
    unsigned int sz;
    unsigned int room;
    ds *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_field_list {
    unsigned int sz;
    unsigned int room;
    field *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_macro_list {
    unsigned int sz;
    unsigned int room;
    macro *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_switchcase_list {
    unsigned int sz;
    unsigned int room;
    switchcase *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_tmstring_list {
    unsigned int sz;
    unsigned int room;
    tmstring *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_tplelm_list {
    unsigned int sz;
    unsigned int room;
    tplelm *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_var_list {
    unsigned int sz;
    unsigned int room;
    var *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

/* Type casting macros. */
#define to_Append(e) ((Append)e)
#define to_Appendfile(e) ((Appendfile)e)
#define to_CCAlternatives(e) ((CCAlternatives)e)
#define to_CCFields(e) ((CCFields)e)
#define to_CCSublist(e) ((CCSublist)e)
#define to_CCSuper(e) ((CCSuper)e)
#define to_Call(e) ((Call)e)
#define to_Case(e) ((Case)e)
#define to_Default(e) ((Default)e)
#define to_DsAlias(e) ((DsAlias)e)
#define to_DsClass(e) ((DsClass)e)
#define to_DsConstructor(e) ((DsConstructor)e)
#define to_DsConstructorBase(e) ((DsConstructorBase)e)
#define to_DsTuple(e) ((DsTuple)e)
#define to_Error(e) ((Error)e)
#define to_Exit(e) ((Exit)e)
#define to_Foreach(e) ((Foreach)e)
#define to_GlobalAppend(e) ((GlobalAppend)e)
#define to_GlobalSet(e) ((GlobalSet)e)
#define to_If(e) ((If)e)
#define to_Include(e) ((Include)e)
#define to_Insert(e) ((Insert)e)
#define to_Macro(e) ((Macro)e)
#define to_Plain(e) ((Plain)e)
#define to_Redirect(e) ((Redirect)e)
#define to_Rename(e) ((Rename)e)
#define to_Return(e) ((Return)e)
#define to_Set(e) ((Set)e)
#define to_Switch(e) ((Switch)e)
#define to_While(e) ((While)e)
#define to_alternative(e) ((alternative)e)
#define to_field(e) ((field)e)
#define to_macro(e) ((macro)e)
#define to_switchcase(e) ((switchcase)e)
#define to_var(e) ((var)e)
#define to_classComponent(e) ((classComponent)e)
#define to_ds(e) ((ds)e)
#define to_tplelm(e) ((tplelm)e)

/* new_<type> routines */
#ifdef LOGNEW
#define new_Append(lno,line) real_new_Append(lno,line,__FILE__,__LINE__)
#define new_Appendfile(lno,fname,body) real_new_Appendfile(lno,fname,body,__FILE__,__LINE__)
#define new_CCAlternatives(alternatives) real_new_CCAlternatives(alternatives,__FILE__,__LINE__)
#define new_CCFields(fields) real_new_CCFields(fields,__FILE__,__LINE__)
#define new_CCSublist(components) real_new_CCSublist(components,__FILE__,__LINE__)
#define new_CCSuper(super) real_new_CCSuper(super,__FILE__,__LINE__)
#define new_Call(lno,line) real_new_Call(lno,line,__FILE__,__LINE__)
#define new_Case(lno,val) real_new_Case(lno,val,__FILE__,__LINE__)
#define new_Default(lno) real_new_Default(lno,__FILE__,__LINE__)
#define new_DsAlias(name,inherits,target) real_new_DsAlias(name,inherits,target,__FILE__,__LINE__)
#define new_DsClass(name,inherits,fields,virtual) real_new_DsClass(name,inherits,fields,virtual,__FILE__,__LINE__)
#define new_DsConstructor(name,inherits,fields) real_new_DsConstructor(name,inherits,fields,__FILE__,__LINE__)
#define new_DsConstructorBase(name,inherits,constructors) real_new_DsConstructorBase(name,inherits,constructors,__FILE__,__LINE__)
#define new_DsTuple(name,inherits,fields) real_new_DsTuple(name,inherits,fields,__FILE__,__LINE__)
#define new_Error(lno,str) real_new_Error(lno,str,__FILE__,__LINE__)
#define new_Exit(lno,str) real_new_Exit(lno,str,__FILE__,__LINE__)
#define new_Foreach(lno,felist,body) real_new_Foreach(lno,felist,body,__FILE__,__LINE__)
#define new_GlobalAppend(lno,line) real_new_GlobalAppend(lno,line,__FILE__,__LINE__)
#define new_GlobalSet(lno,line) real_new_GlobalSet(lno,line,__FILE__,__LINE__)
#define new_If(lno,cond,ifthen,ifelse) real_new_If(lno,cond,ifthen,ifelse,__FILE__,__LINE__)
#define new_Include(lno,fname) real_new_Include(lno,fname,__FILE__,__LINE__)
#define new_Insert(lno,fname) real_new_Insert(lno,fname,__FILE__,__LINE__)
#define new_Macro(lno,formals,body) real_new_Macro(lno,formals,body,__FILE__,__LINE__)
#define new_Plain(lno,line) real_new_Plain(lno,line,__FILE__,__LINE__)
#define new_Redirect(lno,fname,body) real_new_Redirect(lno,fname,body,__FILE__,__LINE__)
#define new_Rename(lno,line) real_new_Rename(lno,line,__FILE__,__LINE__)
#define new_Return(lno,retval) real_new_Return(lno,retval,__FILE__,__LINE__)
#define new_Set(lno,line) real_new_Set(lno,line,__FILE__,__LINE__)
#define new_Switch(lno,val,cases,deflt) real_new_Switch(lno,val,cases,deflt,__FILE__,__LINE__)
#define new_While(lno,cond,body) real_new_While(lno,cond,body,__FILE__,__LINE__)
#define new_alternative(label,component) real_new_alternative(label,component,__FILE__,__LINE__)
#define new_field(level,name,type) real_new_field(level,name,type,__FILE__,__LINE__)
#define new_macro(lvl,name,orgfile,fpl,body) real_new_macro(lvl,name,orgfile,fpl,body,__FILE__,__LINE__)
#define new_switchcase(cases,action) real_new_switchcase(cases,action,__FILE__,__LINE__)
#define new_var(lvl,name,val) real_new_var(lvl,name,val,__FILE__,__LINE__)
#define new_alternative_list() real_new_alternative_list(__FILE__,__LINE__)
#define new_classComponent_list() real_new_classComponent_list(__FILE__,__LINE__)
#define new_ds_list() real_new_ds_list(__FILE__,__LINE__)
#define new_field_list() real_new_field_list(__FILE__,__LINE__)
#define new_macro_list() real_new_macro_list(__FILE__,__LINE__)
#define new_switchcase_list() real_new_switchcase_list(__FILE__,__LINE__)
#define new_tmstring_list() real_new_tmstring_list(__FILE__,__LINE__)
#define new_tplelm_list() real_new_tplelm_list(__FILE__,__LINE__)
#define new_var_list() real_new_var_list(__FILE__,__LINE__)
#define rdup_ds(e) real_rdup_ds(e,__FILE__,__LINE__)
#define rdup_tplelm(e) real_rdup_tplelm(e,__FILE__,__LINE__)
#define rdup_field_list(e) real_rdup_field_list(e,__FILE__,__LINE__)
#define rdup_tmstring_list(e) real_rdup_tmstring_list(e,__FILE__,__LINE__)
#define rdup_tplelm_list(e) real_rdup_tplelm_list(e,__FILE__,__LINE__)
#endif

#ifdef LOGNEW
extern Append real_new_Append( int, tmstring, const char *, const int );
extern Appendfile real_new_Appendfile( int, tmstring, tplelm_list, const char *, const int );
extern CCAlternatives real_new_CCAlternatives( alternative_list, const char *, const int );
extern CCFields real_new_CCFields( field_list, const char *, const int );
extern CCSublist real_new_CCSublist( classComponent_list, const char *, const int );
extern CCSuper real_new_CCSuper( tmstring, const char *, const int );
extern Call real_new_Call( int, tmstring, const char *, const int );
extern Case real_new_Case( int, tmstring, const char *, const int );
extern Default real_new_Default( int, const char *, const int );
extern DsAlias real_new_DsAlias( tmstring, tmstring_list, tmstring, const char *, const int );
extern DsClass real_new_DsClass( tmstring, tmstring_list, field_list, tmbool, const char *, const int );
extern DsConstructor real_new_DsConstructor( tmstring, tmstring_list, field_list, const char *, const int );
extern DsConstructorBase real_new_DsConstructorBase( tmstring, tmstring_list, tmstring_list, const char *, const int );
extern DsTuple real_new_DsTuple( tmstring, tmstring_list, field_list, const char *, const int );
extern Error real_new_Error( int, tmstring, const char *, const int );
extern Exit real_new_Exit( int, tmstring, const char *, const int );
extern Foreach real_new_Foreach( int, tmstring, tplelm_list, const char *, const int );
extern GlobalAppend real_new_GlobalAppend( int, tmstring, const char *, const int );
extern GlobalSet real_new_GlobalSet( int, tmstring, const char *, const int );
extern If real_new_If( int, tmstring, tplelm_list, tplelm_list, const char *, const int );
extern Include real_new_Include( int, tmstring, const char *, const int );
extern Insert real_new_Insert( int, tmstring, const char *, const int );
extern Macro real_new_Macro( int, tmstring, tplelm_list, const char *, const int );
extern Plain real_new_Plain( int, tmstring, const char *, const int );
extern Redirect real_new_Redirect( int, tmstring, tplelm_list, const char *, const int );
extern Rename real_new_Rename( int, tmstring, const char *, const int );
extern Return real_new_Return( int, tmstring, const char *, const int );
extern Set real_new_Set( int, tmstring, const char *, const int );
extern Switch real_new_Switch( int, tmstring, switchcase_list, tplelm_list, const char *, const int );
extern While real_new_While( int, tmstring, tplelm_list, const char *, const int );
extern alternative real_new_alternative( tmstring, classComponent, const char *, const int );
extern field real_new_field( int, tmstring, tmstring, const char *, const int );
extern macro real_new_macro( uint, tmstring, tmstring, tmstring_list, tplelm_list, const char *, const int );
extern switchcase real_new_switchcase( tmstring, tplelm_list, const char *, const int );
extern var real_new_var( uint, tmstring, tmstring, const char *, const int );
extern alternative_list real_new_alternative_list( const char *file, const int line );
extern classComponent_list real_new_classComponent_list( const char *file, const int line );
extern ds_list real_new_ds_list( const char *file, const int line );
extern field_list real_new_field_list( const char *file, const int line );
extern macro_list real_new_macro_list( const char *file, const int line );
extern switchcase_list real_new_switchcase_list( const char *file, const int line );
extern tmstring_list real_new_tmstring_list( const char *file, const int line );
extern tplelm_list real_new_tplelm_list( const char *file, const int line );
extern var_list real_new_var_list( const char *file, const int line );
#else
extern Append new_Append( int, tmstring );
extern Appendfile new_Appendfile( int, tmstring, tplelm_list );
extern CCAlternatives new_CCAlternatives( alternative_list );
extern CCFields new_CCFields( field_list );
extern CCSublist new_CCSublist( classComponent_list );
extern CCSuper new_CCSuper( tmstring );
extern Call new_Call( int, tmstring );
extern Case new_Case( int, tmstring );
extern Default new_Default( int );
extern DsAlias new_DsAlias( tmstring, tmstring_list, tmstring );
extern DsClass new_DsClass( tmstring, tmstring_list, field_list, tmbool );
extern DsConstructor new_DsConstructor( tmstring, tmstring_list, field_list );
extern DsConstructorBase new_DsConstructorBase( tmstring, tmstring_list, tmstring_list );
extern DsTuple new_DsTuple( tmstring, tmstring_list, field_list );
extern Error new_Error( int, tmstring );
extern Exit new_Exit( int, tmstring );
extern Foreach new_Foreach( int, tmstring, tplelm_list );
extern GlobalAppend new_GlobalAppend( int, tmstring );
extern GlobalSet new_GlobalSet( int, tmstring );
extern If new_If( int, tmstring, tplelm_list, tplelm_list );
extern Include new_Include( int, tmstring );
extern Insert new_Insert( int, tmstring );
extern Macro new_Macro( int, tmstring, tplelm_list );
extern Plain new_Plain( int, tmstring );
extern Redirect new_Redirect( int, tmstring, tplelm_list );
extern Rename new_Rename( int, tmstring );
extern Return new_Return( int, tmstring );
extern Set new_Set( int, tmstring );
extern Switch new_Switch( int, tmstring, switchcase_list, tplelm_list );
extern While new_While( int, tmstring, tplelm_list );
extern alternative new_alternative( tmstring, classComponent );
extern field new_field( int, tmstring, tmstring );
extern macro new_macro( uint, tmstring, tmstring, tmstring_list, tplelm_list );
extern switchcase new_switchcase( tmstring, tplelm_list );
extern var new_var( uint, tmstring, tmstring );
extern alternative_list new_alternative_list( void );
extern classComponent_list new_classComponent_list( void );
extern ds_list new_ds_list( void );
extern field_list new_field_list( void );
extern macro_list new_macro_list( void );
extern switchcase_list new_switchcase_list( void );
extern tmstring_list new_tmstring_list( void );
extern tplelm_list new_tplelm_list( void );
extern var_list new_var_list( void );
#endif
extern alternative_list append_alternative_list( alternative_list, alternative );
extern classComponent_list append_classComponent_list( classComponent_list, classComponent );
extern ds_list append_ds_list( ds_list, ds );
extern field_list append_field_list( field_list, field );
extern switchcase_list append_switchcase_list( switchcase_list, switchcase );
extern tmstring_list append_tmstring_list( tmstring_list, tmstring );
extern tplelm_list append_tplelm_list( tplelm_list, tplelm );
extern var_list append_var_list( var_list, var );
extern macro_list insert_macro_list( macro_list, const unsigned int, macro  );
extern tmstring_list insert_tmstring_list( tmstring_list, const unsigned int, tmstring  );
extern var_list insert_var_list( var_list, const unsigned int, var  );
extern ds_list delete_ds_list( ds_list, const unsigned int );
extern macro_list delete_macro_list( macro_list, const unsigned int );
extern tmstring_list delete_tmstring_list( tmstring_list, const unsigned int );
extern var_list delete_var_list( var_list, const unsigned int );
extern tmstring_list extract_tmstring_list( tmstring_list, const unsigned int, tmstring *, int * );
extern ds_list concat_ds_list( ds_list, ds_list );
extern field_list concat_field_list( field_list, field_list );
extern tmstring_list concat_tmstring_list( tmstring_list, tmstring_list );
extern void rfre_alternative_list( alternative_list );
extern void rfre_classComponent_list( classComponent_list );
extern void rfre_ds_list( ds_list );
extern void rfre_field_list( field_list );
extern void rfre_macro_list( macro_list );
extern void rfre_tmstring_list( tmstring_list );
extern void rfre_tplelm_list( tplelm_list );
extern void rfre_var_list( var_list );
extern void rfre_classComponent( classComponent );
extern void rfre_ds( ds );
extern void rfre_macro( macro );
extern void rfre_tplelm( tplelm );
extern void print_ds_list( TMPRINTSTATE *, const ds_list );
extern void print_tmstring_list( TMPRINTSTATE *, const tmstring_list );
#ifdef LOGNEW
extern ds real_rdup_ds( const ds, const char *_f, const int _l );
extern tplelm real_rdup_tplelm( const tplelm, const char *_f, const int _l );
extern field_list real_rdup_field_list( const field_list, const char *_f, const int _l );
extern tmstring_list real_rdup_tmstring_list( const tmstring_list, const char *_f, const int _l );
extern tplelm_list real_rdup_tplelm_list( const tplelm_list, const char *_f, const int _l );
#else
extern ds rdup_ds( const ds );
extern tplelm rdup_tplelm( const tplelm );
extern field_list rdup_field_list( const field_list );
extern tmstring_list rdup_tmstring_list( const tmstring_list );
extern tplelm_list rdup_tplelm_list( const tplelm_list );
#endif
extern void stat_tm( FILE * );
extern int get_balance_tm( void );
/* ---- end of /usr/local/lib/tmc.ht ---- */
/* Code generation required 580 milliseconds. */
