/* Requirement analysis took 400 milliseconds. */
/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /usr/local/lib/tmc.ht ---- */
/* External definitions (Version for array list).

   template file:      /usr/local/lib/tmc.ht
   datastructure file: tm.ds
   tm version:         36
   tm kernel version:  2.0-beta15
 */

/* data structures */

/* forward reference typedefs for all types.
 * C does not like the use of undefined types, but does not
 * mind the use of pointers to (yet) undefined types.
 */
typedef struct str_Field_list *Field_list;
typedef struct str_Switchcase_list *Switchcase_list;
typedef struct str_Type_list *Type_list;
typedef struct str_alternative_list *alternative_list;
typedef struct str_classComponent_list *classComponent_list;
typedef struct str_ds_list *ds_list;
typedef struct str_macro_list *macro_list;
typedef struct str_tmstring_list *tmstring_list;
typedef struct str_tplelm_list *tplelm_list;
typedef struct str_var_list *var_list;
typedef struct str_Switchcase *Switchcase;
typedef struct str_Type *Type;
typedef struct str_Field *Field;
typedef struct str_macro *macro;
typedef struct str_var *var;
typedef struct str_classComponent *classComponent;
typedef struct str_CCAlternatives *CCAlternatives;
typedef struct str_CCFields *CCFields;
typedef struct str_CCSublist *CCSublist;
typedef struct str_CCSuper *CCSuper;
typedef struct str_alternative *alternative;
typedef struct str_ds *ds;
typedef struct str_DsAlias *DsAlias;
typedef struct str_DsClass *DsClass;
typedef struct str_DsConstructor *DsConstructor;
typedef struct str_DsConstructorBase *DsConstructorBase;
typedef struct str_DsTuple *DsTuple;
typedef struct str_tplelm *tplelm;
typedef struct str_Append *Append;
typedef struct str_Appendfile *Appendfile;
typedef struct str_Call *Call;
typedef struct str_Case *Case;
typedef struct str_Default *Default;
typedef struct str_DeleteType *DeleteType;
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

#define Field_listNIL (Field_list)0
#define Switchcase_listNIL (Switchcase_list)0
#define Type_listNIL (Type_list)0
#define alternative_listNIL (alternative_list)0
#define classComponent_listNIL (classComponent_list)0
#define ds_listNIL (ds_list)0
#define macro_listNIL (macro_list)0
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
#define DeleteTypeNIL (DeleteType)0
#define DsAliasNIL (DsAlias)0
#define DsClassNIL (DsClass)0
#define DsConstructorNIL (DsConstructor)0
#define DsConstructorBaseNIL (DsConstructorBase)0
#define DsTupleNIL (DsTuple)0
#define ErrorNIL (Error)0
#define ExitNIL (Exit)0
#define FieldNIL (Field)0
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
#define SwitchcaseNIL (Switchcase)0
#define TypeNIL (Type)0
#define WhileNIL (While)0
#define alternativeNIL (alternative)0
#define macroNIL (macro)0
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
    TAGPlain, TAGForeach, TAGWhile, TAGIf, TAGSwitch, TAGSet, TAGRename, TAGGlobalSet, TAGAppend, TAGGlobalAppend, TAGDeleteType, TAGError, TAGExit, TAGRedirect, TAGAppendfile, TAGMacro, TAGCall, TAGReturn, TAGInclude, TAGInsert, TAGCase, TAGDefault
} tags_tplelm;


#ifdef __cplusplus
/* Structure for tuple 'Field'. */
struct str_Field {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmstring name;
    Type type;
};

/* Structure for tuple 'Switchcase'. */
struct str_Switchcase {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmstring cases;
    tplelm_list action;
};

/* Structure for tuple 'Type'. */
struct str_Type {
#ifdef LOGNEW
    long int lognew_id;
#endif
    uint level;
    tmstring basetype;
};

/* Structure for tuple 'alternative'. */
struct str_alternative {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmstring label;
    classComponent component;
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
    Field_list fields;
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
    Type type;
};

/* Structure for class 'DsClass'. */
class str_DsClass: public str_ds {
public:
    Field_list fields;
    tmbool isvirtual;
};

/* Structure for class 'DsConstructor'. */
class str_DsConstructor: public str_ds {
public:
    Field_list fields;
};

/* Structure for class 'DsConstructorBase'. */
class str_DsConstructorBase: public str_ds {
public:
    tmstring_list constructors;
};

/* Structure for class 'DsTuple'. */
class str_DsTuple: public str_ds {
public:
    Field_list fields;
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

/* Structure for class 'DeleteType'. */
class str_DeleteType: public str_tplelm {
public:
    tmstring line;
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
    Switchcase_list cases;
    tplelm_list deflt;
};

/* Structure for class 'While'. */
class str_While: public str_tplelm {
public:
    tmstring cond;
    tplelm_list body;
};

#else
/* Structure for tuple 'Switchcase'. */
struct str_Switchcase {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmstring cases;
    tplelm_list action;
};

/* Structure for tuple 'Type'. */
struct str_Type {
#ifdef LOGNEW
    long int lognew_id;
#endif
    uint level;
    tmstring basetype;
};

/* Structure for tuple 'Field'. */
struct str_Field {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmstring name;
    Type type;
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
    Field_list fields;
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

/* Structure for class 'DsAlias'. */
struct str_DsAlias {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    tmstring name;
    tmstring_list inherits;
    Type type;
};

/* Structure for class 'DsClass'. */
struct str_DsClass {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    tmstring name;
    tmstring_list inherits;
    Field_list fields;
    tmbool isvirtual;
};

/* Structure for class 'DsConstructor'. */
struct str_DsConstructor {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    tmstring name;
    tmstring_list inherits;
    Field_list fields;
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
    Field_list fields;
};

/* Structure for class 'tplelm'. */
struct str_tplelm {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
};

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

/* Structure for class 'DeleteType'. */
struct str_DeleteType {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    int lno;
    tmstring line;
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
    Switchcase_list cases;
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

#endif

struct str_Field_list {
    unsigned int sz;
    unsigned int room;
    Field *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_Switchcase_list {
    unsigned int sz;
    unsigned int room;
    Switchcase *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_Type_list {
    unsigned int sz;
    unsigned int room;
    Type *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

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

struct str_macro_list {
    unsigned int sz;
    unsigned int room;
    macro *arr;
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
#define to_DeleteType(e) ((DeleteType)e)
#define to_DsAlias(e) ((DsAlias)e)
#define to_DsClass(e) ((DsClass)e)
#define to_DsConstructor(e) ((DsConstructor)e)
#define to_DsConstructorBase(e) ((DsConstructorBase)e)
#define to_DsTuple(e) ((DsTuple)e)
#define to_Error(e) ((Error)e)
#define to_Exit(e) ((Exit)e)
#define to_Field(e) ((Field)e)
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
#define to_Switchcase(e) ((Switchcase)e)
#define to_Type(e) ((Type)e)
#define to_While(e) ((While)e)
#define to_alternative(e) ((alternative)e)
#define to_macro(e) ((macro)e)
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
#define new_DeleteType(lno,line) real_new_DeleteType(lno,line,__FILE__,__LINE__)
#define new_DsAlias(name,inherits,type) real_new_DsAlias(name,inherits,type,__FILE__,__LINE__)
#define new_DsClass(name,inherits,fields,isvirtual) real_new_DsClass(name,inherits,fields,isvirtual,__FILE__,__LINE__)
#define new_DsConstructor(name,inherits,fields) real_new_DsConstructor(name,inherits,fields,__FILE__,__LINE__)
#define new_DsConstructorBase(name,inherits,constructors) real_new_DsConstructorBase(name,inherits,constructors,__FILE__,__LINE__)
#define new_DsTuple(name,inherits,fields) real_new_DsTuple(name,inherits,fields,__FILE__,__LINE__)
#define new_Error(lno,str) real_new_Error(lno,str,__FILE__,__LINE__)
#define new_Exit(lno,str) real_new_Exit(lno,str,__FILE__,__LINE__)
#define new_Field(name,type) real_new_Field(name,type,__FILE__,__LINE__)
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
#define new_Switchcase(cases,action) real_new_Switchcase(cases,action,__FILE__,__LINE__)
#define new_Type(level,basetype) real_new_Type(level,basetype,__FILE__,__LINE__)
#define new_While(lno,cond,body) real_new_While(lno,cond,body,__FILE__,__LINE__)
#define new_alternative(label,component) real_new_alternative(label,component,__FILE__,__LINE__)
#define new_macro(lvl,name,orgfile,fpl,body) real_new_macro(lvl,name,orgfile,fpl,body,__FILE__,__LINE__)
#define new_var(lvl,name,val) real_new_var(lvl,name,val,__FILE__,__LINE__)
#define new_Field_list() real_new_Field_list(__FILE__,__LINE__)
#define new_Switchcase_list() real_new_Switchcase_list(__FILE__,__LINE__)
#define new_Type_list() real_new_Type_list(__FILE__,__LINE__)
#define new_alternative_list() real_new_alternative_list(__FILE__,__LINE__)
#define new_classComponent_list() real_new_classComponent_list(__FILE__,__LINE__)
#define new_ds_list() real_new_ds_list(__FILE__,__LINE__)
#define new_macro_list() real_new_macro_list(__FILE__,__LINE__)
#define new_tmstring_list() real_new_tmstring_list(__FILE__,__LINE__)
#define new_tplelm_list() real_new_tplelm_list(__FILE__,__LINE__)
#define new_var_list() real_new_var_list(__FILE__,__LINE__)
#define rdup_Type(e) real_rdup_Type(e,__FILE__,__LINE__)
#define rdup_ds(e) real_rdup_ds(e,__FILE__,__LINE__)
#define rdup_tplelm(e) real_rdup_tplelm(e,__FILE__,__LINE__)
#define rdup_Field_list(e) real_rdup_Field_list(e,__FILE__,__LINE__)
#define rdup_tmstring_list(e) real_rdup_tmstring_list(e,__FILE__,__LINE__)
#define rdup_tplelm_list(e) real_rdup_tplelm_list(e,__FILE__,__LINE__)
#endif

#ifdef LOGNEW
extern Append real_new_Append( int, tmstring, const char *, const int );
extern Appendfile real_new_Appendfile( int, tmstring, tplelm_list, const char *, const int );
extern CCAlternatives real_new_CCAlternatives( alternative_list, const char *, const int );
extern CCFields real_new_CCFields( Field_list, const char *, const int );
extern CCSublist real_new_CCSublist( classComponent_list, const char *, const int );
extern CCSuper real_new_CCSuper( tmstring, const char *, const int );
extern Call real_new_Call( int, tmstring, const char *, const int );
extern Case real_new_Case( int, tmstring, const char *, const int );
extern Default real_new_Default( int, const char *, const int );
extern DeleteType real_new_DeleteType( int, tmstring, const char *, const int );
extern DsAlias real_new_DsAlias( tmstring, tmstring_list, Type, const char *, const int );
extern DsClass real_new_DsClass( tmstring, tmstring_list, Field_list, tmbool, const char *, const int );
extern DsConstructor real_new_DsConstructor( tmstring, tmstring_list, Field_list, const char *, const int );
extern DsConstructorBase real_new_DsConstructorBase( tmstring, tmstring_list, tmstring_list, const char *, const int );
extern DsTuple real_new_DsTuple( tmstring, tmstring_list, Field_list, const char *, const int );
extern Error real_new_Error( int, tmstring, const char *, const int );
extern Exit real_new_Exit( int, tmstring, const char *, const int );
extern Field real_new_Field( tmstring, Type, const char *, const int );
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
extern Switch real_new_Switch( int, tmstring, Switchcase_list, tplelm_list, const char *, const int );
extern Switchcase real_new_Switchcase( tmstring, tplelm_list, const char *, const int );
extern Type real_new_Type( uint, tmstring, const char *, const int );
extern While real_new_While( int, tmstring, tplelm_list, const char *, const int );
extern alternative real_new_alternative( tmstring, classComponent, const char *, const int );
extern macro real_new_macro( uint, tmstring, tmstring, tmstring_list, tplelm_list, const char *, const int );
extern var real_new_var( uint, tmstring, tmstring, const char *, const int );
extern Field_list real_new_Field_list( const char *file, const int line );
extern Switchcase_list real_new_Switchcase_list( const char *file, const int line );
extern Type_list real_new_Type_list( const char *file, const int line );
extern alternative_list real_new_alternative_list( const char *file, const int line );
extern classComponent_list real_new_classComponent_list( const char *file, const int line );
extern ds_list real_new_ds_list( const char *file, const int line );
extern macro_list real_new_macro_list( const char *file, const int line );
extern tmstring_list real_new_tmstring_list( const char *file, const int line );
extern tplelm_list real_new_tplelm_list( const char *file, const int line );
extern var_list real_new_var_list( const char *file, const int line );
#else
extern Append new_Append( int, tmstring );
extern Appendfile new_Appendfile( int, tmstring, tplelm_list );
extern CCAlternatives new_CCAlternatives( alternative_list );
extern CCFields new_CCFields( Field_list );
extern CCSublist new_CCSublist( classComponent_list );
extern CCSuper new_CCSuper( tmstring );
extern Call new_Call( int, tmstring );
extern Case new_Case( int, tmstring );
extern Default new_Default( int );
extern DeleteType new_DeleteType( int, tmstring );
extern DsAlias new_DsAlias( tmstring, tmstring_list, Type );
extern DsClass new_DsClass( tmstring, tmstring_list, Field_list, tmbool );
extern DsConstructor new_DsConstructor( tmstring, tmstring_list, Field_list );
extern DsConstructorBase new_DsConstructorBase( tmstring, tmstring_list, tmstring_list );
extern DsTuple new_DsTuple( tmstring, tmstring_list, Field_list );
extern Error new_Error( int, tmstring );
extern Exit new_Exit( int, tmstring );
extern Field new_Field( tmstring, Type );
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
extern Switch new_Switch( int, tmstring, Switchcase_list, tplelm_list );
extern Switchcase new_Switchcase( tmstring, tplelm_list );
extern Type new_Type( uint, tmstring );
extern While new_While( int, tmstring, tplelm_list );
extern alternative new_alternative( tmstring, classComponent );
extern macro new_macro( uint, tmstring, tmstring, tmstring_list, tplelm_list );
extern var new_var( uint, tmstring, tmstring );
extern Field_list new_Field_list( void );
extern Switchcase_list new_Switchcase_list( void );
extern Type_list new_Type_list( void );
extern alternative_list new_alternative_list( void );
extern classComponent_list new_classComponent_list( void );
extern ds_list new_ds_list( void );
extern macro_list new_macro_list( void );
extern tmstring_list new_tmstring_list( void );
extern tplelm_list new_tplelm_list( void );
extern var_list new_var_list( void );
#endif
extern tmstring_list setroom_tmstring_list( tmstring_list, const unsigned int );
extern Field_list append_Field_list( Field_list, Field );
extern Switchcase_list append_Switchcase_list( Switchcase_list, Switchcase );
extern Type_list append_Type_list( Type_list, Type );
extern alternative_list append_alternative_list( alternative_list, alternative );
extern classComponent_list append_classComponent_list( classComponent_list, classComponent );
extern ds_list append_ds_list( ds_list, ds );
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
extern Field_list concat_Field_list( Field_list, Field_list );
extern ds_list concat_ds_list( ds_list, ds_list );
extern tmstring_list concat_tmstring_list( tmstring_list, tmstring_list );
extern void rfre_Field_list( Field_list );
extern void rfre_Type_list( Type_list );
extern void rfre_alternative_list( alternative_list );
extern void rfre_classComponent_list( classComponent_list );
extern void rfre_ds_list( ds_list );
extern void rfre_macro_list( macro_list );
extern void rfre_tmstring_list( tmstring_list );
extern void rfre_tplelm_list( tplelm_list );
extern void rfre_var_list( var_list );
extern void rfre_Type( Type );
extern void rfre_classComponent( classComponent );
extern void rfre_ds( ds );
extern void rfre_macro( macro );
extern void rfre_tplelm( tplelm );
extern void print_ds_list( TMPRINTSTATE *, const ds_list );
extern void print_tmstring_list( TMPRINTSTATE *, const tmstring_list );
#ifdef LOGNEW
extern Type real_rdup_Type( const Type, const char *_f, const int _l );
extern ds real_rdup_ds( const ds, const char *_f, const int _l );
extern tplelm real_rdup_tplelm( const tplelm, const char *_f, const int _l );
extern Field_list real_rdup_Field_list( const Field_list, const char *_f, const int _l );
extern tmstring_list real_rdup_tmstring_list( const tmstring_list, const char *_f, const int _l );
extern tplelm_list real_rdup_tplelm_list( const tplelm_list, const char *_f, const int _l );
#else
extern Type rdup_Type( const Type );
extern ds rdup_ds( const ds );
extern tplelm rdup_tplelm( const tplelm );
extern Field_list rdup_Field_list( const Field_list );
extern tmstring_list rdup_tmstring_list( const tmstring_list );
extern tplelm_list rdup_tplelm_list( const tplelm_list );
#endif
extern void stat_tm( FILE * );
extern int get_balance_tm( void );
/* ---- end of /usr/local/lib/tmc.ht ---- */
/* Code generation required 650 milliseconds. */
