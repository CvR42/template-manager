/* Requirement analysis took 14 milliseconds. */
/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /Users/reeuwijk/lab/lib/tmc.ht ---- */
/* External definitions (Version for array list).

   template file:      /Users/reeuwijk/lab/lib/tmc.ht
   datastructure file: tm.ds
   tm version:         36
   tm kernel version:  *** development -- not for distribution ***
 */

/* data structures */

/* forward reference typedefs for all types.
 * C does not like the use of undefined types, but does not
 * mind the use of pointers to (yet) undefined types.
 */
typedef struct str_Field_list *Field_list;
typedef const struct str_Field_list *const_Field_list;
typedef struct str_Switchcase_list *Switchcase_list;
typedef const struct str_Switchcase_list *const_Switchcase_list;
typedef struct str_Type_list *Type_list;
typedef const struct str_Type_list *const_Type_list;
typedef struct str_alternative_list *alternative_list;
typedef const struct str_alternative_list *const_alternative_list;
typedef struct str_classComponent_list *classComponent_list;
typedef const struct str_classComponent_list *const_classComponent_list;
typedef struct str_ds_list *ds_list;
typedef const struct str_ds_list *const_ds_list;
typedef struct str_macro_list *macro_list;
typedef const struct str_macro_list *const_macro_list;
typedef struct str_tmstring_list *tmstring_list;
typedef const struct str_tmstring_list *const_tmstring_list;
typedef struct str_tmsymbol_list *tmsymbol_list;
typedef const struct str_tmsymbol_list *const_tmsymbol_list;
typedef struct str_tplelm_list *tplelm_list;
typedef const struct str_tplelm_list *const_tplelm_list;
typedef struct str_variable_list *variable_list;
typedef const struct str_variable_list *const_variable_list;
typedef struct str_Switchcase *Switchcase;
typedef const struct str_Switchcase *const_Switchcase;
typedef struct str_Type *Type;
typedef const struct str_Type *const_Type;
typedef struct str_origin *origin;
typedef const struct str_origin *const_origin;
typedef struct str_macro *macro;
typedef const struct str_macro *const_macro;
typedef struct str_origsymbol *origsymbol;
typedef const struct str_origsymbol *const_origsymbol;
typedef struct str_Field *Field;
typedef const struct str_Field *const_Field;
typedef struct str_variable *variable;
typedef const struct str_variable *const_variable;
typedef struct str_classComponent *classComponent;
typedef const struct str_classComponent *const_classComponent;
typedef struct str_CCAlternatives *CCAlternatives;
typedef const struct str_CCAlternatives *const_CCAlternatives;
typedef struct str_CCFields *CCFields;
typedef const struct str_CCFields *const_CCFields;
typedef struct str_CCSublist *CCSublist;
typedef const struct str_CCSublist *const_CCSublist;
typedef struct str_CCSuper *CCSuper;
typedef const struct str_CCSuper *const_CCSuper;
typedef struct str_alternative *alternative;
typedef const struct str_alternative *const_alternative;
typedef struct str_ds *ds;
typedef const struct str_ds *const_ds;
typedef struct str_DsAlias *DsAlias;
typedef const struct str_DsAlias *const_DsAlias;
typedef struct str_DsClass *DsClass;
typedef const struct str_DsClass *const_DsClass;
typedef struct str_DsConstructor *DsConstructor;
typedef const struct str_DsConstructor *const_DsConstructor;
typedef struct str_DsConstructorBase *DsConstructorBase;
typedef const struct str_DsConstructorBase *const_DsConstructorBase;
typedef struct str_DsInclude *DsInclude;
typedef const struct str_DsInclude *const_DsInclude;
typedef struct str_DsTuple *DsTuple;
typedef const struct str_DsTuple *const_DsTuple;
typedef struct str_tplelm *tplelm;
typedef const struct str_tplelm *const_tplelm;
typedef struct str_Append *Append;
typedef const struct str_Append *const_Append;
typedef struct str_Appendfile *Appendfile;
typedef const struct str_Appendfile *const_Appendfile;
typedef struct str_Call *Call;
typedef const struct str_Call *const_Call;
typedef struct str_Case *Case;
typedef const struct str_Case *const_Case;
typedef struct str_Default *Default;
typedef const struct str_Default *const_Default;
typedef struct str_DeleteType *DeleteType;
typedef const struct str_DeleteType *const_DeleteType;
typedef struct str_Error *Error;
typedef const struct str_Error *const_Error;
typedef struct str_Exit *Exit;
typedef const struct str_Exit *const_Exit;
typedef struct str_For *For;
typedef const struct str_For *const_For;
typedef struct str_Foreach *Foreach;
typedef const struct str_Foreach *const_Foreach;
typedef struct str_GlobalAppend *GlobalAppend;
typedef const struct str_GlobalAppend *const_GlobalAppend;
typedef struct str_GlobalSet *GlobalSet;
typedef const struct str_GlobalSet *const_GlobalSet;
typedef struct str_GlobalSplit *GlobalSplit;
typedef const struct str_GlobalSplit *const_GlobalSplit;
typedef struct str_If *If;
typedef const struct str_If *const_If;
typedef struct str_Include *Include;
typedef const struct str_Include *const_Include;
typedef struct str_Insert *Insert;
typedef const struct str_Insert *const_Insert;
typedef struct str_Macro *Macro;
typedef const struct str_Macro *const_Macro;
typedef struct str_Plain *Plain;
typedef const struct str_Plain *const_Plain;
typedef struct str_Redirect *Redirect;
typedef const struct str_Redirect *const_Redirect;
typedef struct str_Rename *Rename;
typedef const struct str_Rename *const_Rename;
typedef struct str_Return *Return;
typedef const struct str_Return *const_Return;
typedef struct str_Set *Set;
typedef const struct str_Set *const_Set;
typedef struct str_Split *Split;
typedef const struct str_Split *const_Split;
typedef struct str_Switch *Switch;
typedef const struct str_Switch *const_Switch;
typedef struct str_While *While;
typedef const struct str_While *const_While;

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
#define DsIncludeNIL (DsInclude)0
#define DsTupleNIL (DsTuple)0
#define ErrorNIL (Error)0
#define ExitNIL (Exit)0
#define FieldNIL (Field)0
#define ForNIL (For)0
#define ForeachNIL (Foreach)0
#define GlobalAppendNIL (GlobalAppend)0
#define GlobalSetNIL (GlobalSet)0
#define GlobalSplitNIL (GlobalSplit)0
#define IfNIL (If)0
#define IncludeNIL (Include)0
#define InsertNIL (Insert)0
#define MacroNIL (Macro)0
#define PlainNIL (Plain)0
#define RedirectNIL (Redirect)0
#define RenameNIL (Rename)0
#define ReturnNIL (Return)0
#define SetNIL (Set)0
#define SplitNIL (Split)0
#define SwitchNIL (Switch)0
#define SwitchcaseNIL (Switchcase)0
#define TypeNIL (Type)0
#define WhileNIL (While)0
#define alternativeNIL (alternative)0
#define macroNIL (macro)0
#define originNIL (origin)0
#define origsymbolNIL (origsymbol)0
#define variableNIL (variable)0
#define classComponentNIL (classComponent)0
#define dsNIL (ds)0
#define tplelmNIL (tplelm)0
#define Field_listNIL (Field_list)0
#define Switchcase_listNIL (Switchcase_list)0
#define Type_listNIL (Type_list)0
#define alternative_listNIL (alternative_list)0
#define classComponent_listNIL (classComponent_list)0
#define ds_listNIL (ds_list)0
#define macro_listNIL (macro_list)0
#define tmstring_listNIL (tmstring_list)0
#define tmsymbol_listNIL (tmsymbol_list)0
#define tplelm_listNIL (tplelm_list)0
#define variable_listNIL (variable_list)0

typedef enum en_tags_classComponent {
    TAGCCSuper,
    TAGCCFields,
    TAGCCAlternatives,
    TAGCCSublist
} tags_classComponent;

typedef enum en_tags_ds {
    TAGDsInclude,
    TAGDsConstructorBase,
    TAGDsTuple,
    TAGDsClass,
    TAGDsConstructor,
    TAGDsAlias
} tags_ds;

typedef enum en_tags_tplelm {
    TAGPlain,
    TAGFor,
    TAGForeach,
    TAGWhile,
    TAGIf,
    TAGSwitch,
    TAGSet,
    TAGSplit,
    TAGRename,
    TAGGlobalSet,
    TAGGlobalSplit,
    TAGAppend,
    TAGGlobalAppend,
    TAGDeleteType,
    TAGError,
    TAGExit,
    TAGRedirect,
    TAGAppendfile,
    TAGMacro,
    TAGCall,
    TAGReturn,
    TAGInclude,
    TAGInsert,
    TAGCase,
    TAGDefault
} tags_tplelm;



#ifdef __cplusplus
/* Structure for tuple 'Field'. */
struct str_Field {
#ifdef LOGNEW
    long int lognew_id;
#endif
    origsymbol name;
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
    tmuint level;
    tmsymbol basetype;
};

/* Structure for tuple 'alternative'. */
struct str_alternative {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmsymbol label;
    classComponent component;
};

/* Structure for tuple 'macro'. */
struct str_macro {
#ifdef LOGNEW
    long int lognew_id;
#endif
    origin org;
    tmuint lvl;
    tmstring name;
    tmstring_list fpl;
    tplelm_list body;
};

/* Structure for tuple 'origin'. */
struct str_origin {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmsymbol file;
    tmuint line;
};

/* Structure for tuple 'origsymbol'. */
struct str_origsymbol {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmsymbol sym;
    origin org;
};

/* Structure for tuple 'variable'. */
struct str_variable {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmuint lvl;
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
    tmsymbol super;
};

/* Structure for class 'ds'. */
class str_ds {
public:
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    origsymbol name;
    tmsymbol_list inherits;
    tmsymbol_list inheritors;
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
    tmsymbol_list constructors;
};

/* Structure for class 'DsInclude'. */
class str_DsInclude: public str_ds {
public:
    tmstring fnm;
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
    origin org;
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

/* Structure for class 'For'. */
class str_For: public str_tplelm {
public:
    tmstring parms;
    tplelm_list body;
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

/* Structure for class 'GlobalSplit'. */
class str_GlobalSplit: public str_tplelm {
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

/* Structure for class 'Split'. */
class str_Split: public str_tplelm {
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
    tmuint level;
    tmsymbol basetype;
};

/* Structure for tuple 'origin'. */
struct str_origin {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmsymbol file;
    tmuint line;
};

/* Structure for tuple 'macro'. */
struct str_macro {
#ifdef LOGNEW
    long int lognew_id;
#endif
    origin org;
    tmuint lvl;
    tmstring name;
    tmstring_list fpl;
    tplelm_list body;
};

/* Structure for tuple 'origsymbol'. */
struct str_origsymbol {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmsymbol sym;
    origin org;
};

/* Structure for tuple 'Field'. */
struct str_Field {
#ifdef LOGNEW
    long int lognew_id;
#endif
    origsymbol name;
    Type type;
};

/* Structure for tuple 'variable'. */
struct str_variable {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmuint lvl;
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
    tmsymbol super;
};

/* Structure for tuple 'alternative'. */
struct str_alternative {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tmsymbol label;
    classComponent component;
};

/* Structure for class 'ds'. */
struct str_ds {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    origsymbol name;
    tmsymbol_list inherits;
    tmsymbol_list inheritors;
};

/* Structure for class 'DsAlias'. */
struct str_DsAlias {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    origsymbol name;
    tmsymbol_list inherits;
    tmsymbol_list inheritors;
    Type type;
};

/* Structure for class 'DsClass'. */
struct str_DsClass {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    origsymbol name;
    tmsymbol_list inherits;
    tmsymbol_list inheritors;
    Field_list fields;
    tmbool isvirtual;
};

/* Structure for class 'DsConstructor'. */
struct str_DsConstructor {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    origsymbol name;
    tmsymbol_list inherits;
    tmsymbol_list inheritors;
    Field_list fields;
};

/* Structure for class 'DsConstructorBase'. */
struct str_DsConstructorBase {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    origsymbol name;
    tmsymbol_list inherits;
    tmsymbol_list inheritors;
    tmsymbol_list constructors;
};

/* Structure for class 'DsInclude'. */
struct str_DsInclude {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    origsymbol name;
    tmsymbol_list inherits;
    tmsymbol_list inheritors;
    tmstring fnm;
};

/* Structure for class 'DsTuple'. */
struct str_DsTuple {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_ds tag;
    origsymbol name;
    tmsymbol_list inherits;
    tmsymbol_list inheritors;
    Field_list fields;
};

/* Structure for class 'tplelm'. */
struct str_tplelm {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
};

/* Structure for class 'Append'. */
struct str_Append {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring line;
};

/* Structure for class 'Appendfile'. */
struct str_Appendfile {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring fname;
    tplelm_list body;
};

/* Structure for class 'Call'. */
struct str_Call {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring line;
};

/* Structure for class 'Case'. */
struct str_Case {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring val;
};

/* Structure for class 'Default'. */
struct str_Default {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
};

/* Structure for class 'DeleteType'. */
struct str_DeleteType {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring line;
};

/* Structure for class 'Error'. */
struct str_Error {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring str;
};

/* Structure for class 'Exit'. */
struct str_Exit {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring str;
};

/* Structure for class 'For'. */
struct str_For {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring parms;
    tplelm_list body;
};

/* Structure for class 'Foreach'. */
struct str_Foreach {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring felist;
    tplelm_list body;
};

/* Structure for class 'GlobalAppend'. */
struct str_GlobalAppend {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring line;
};

/* Structure for class 'GlobalSet'. */
struct str_GlobalSet {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring line;
};

/* Structure for class 'GlobalSplit'. */
struct str_GlobalSplit {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring line;
};

/* Structure for class 'If'. */
struct str_If {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
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
    origin org;
    tmstring fname;
};

/* Structure for class 'Insert'. */
struct str_Insert {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring fname;
};

/* Structure for class 'Macro'. */
struct str_Macro {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring formals;
    tplelm_list body;
};

/* Structure for class 'Plain'. */
struct str_Plain {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring line;
};

/* Structure for class 'Redirect'. */
struct str_Redirect {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring fname;
    tplelm_list body;
};

/* Structure for class 'Rename'. */
struct str_Rename {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring line;
};

/* Structure for class 'Return'. */
struct str_Return {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring retval;
};

/* Structure for class 'Set'. */
struct str_Set {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring line;
};

/* Structure for class 'Split'. */
struct str_Split {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
    tmstring line;
};

/* Structure for class 'Switch'. */
struct str_Switch {
#ifdef LOGNEW
    long int lognew_id;
#endif
    tags_tplelm tag;
    origin org;
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
    origin org;
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

struct str_tmsymbol_list {
    unsigned int sz;
    unsigned int room;
    tmsymbol *arr;
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

struct str_variable_list {
    unsigned int sz;
    unsigned int room;
    variable *arr;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

/* Type casting macros. */
#ifdef TMC_CHECKED_CAST
#define to_Append(e) ((e)->tag==TAGAppend?((Append)e):(Append)tm_badcast(__FILE__,__LINE__))
#define to_const_Append(e) ((e)->tag==TAGAppend?((const_Append)e):(const_Append)tm_badcast(__FILE__,__LINE__))
#define to_Appendfile(e) ((e)->tag==TAGAppendfile?((Appendfile)e):(Appendfile)tm_badcast(__FILE__,__LINE__))
#define to_const_Appendfile(e) ((e)->tag==TAGAppendfile?((const_Appendfile)e):(const_Appendfile)tm_badcast(__FILE__,__LINE__))
#define to_CCAlternatives(e) ((e)->tag==TAGCCAlternatives?((CCAlternatives)e):(CCAlternatives)tm_badcast(__FILE__,__LINE__))
#define to_const_CCAlternatives(e) ((e)->tag==TAGCCAlternatives?((const_CCAlternatives)e):(const_CCAlternatives)tm_badcast(__FILE__,__LINE__))
#define to_CCFields(e) ((e)->tag==TAGCCFields?((CCFields)e):(CCFields)tm_badcast(__FILE__,__LINE__))
#define to_const_CCFields(e) ((e)->tag==TAGCCFields?((const_CCFields)e):(const_CCFields)tm_badcast(__FILE__,__LINE__))
#define to_CCSublist(e) ((e)->tag==TAGCCSublist?((CCSublist)e):(CCSublist)tm_badcast(__FILE__,__LINE__))
#define to_const_CCSublist(e) ((e)->tag==TAGCCSublist?((const_CCSublist)e):(const_CCSublist)tm_badcast(__FILE__,__LINE__))
#define to_CCSuper(e) ((e)->tag==TAGCCSuper?((CCSuper)e):(CCSuper)tm_badcast(__FILE__,__LINE__))
#define to_const_CCSuper(e) ((e)->tag==TAGCCSuper?((const_CCSuper)e):(const_CCSuper)tm_badcast(__FILE__,__LINE__))
#define to_Call(e) ((e)->tag==TAGCall?((Call)e):(Call)tm_badcast(__FILE__,__LINE__))
#define to_const_Call(e) ((e)->tag==TAGCall?((const_Call)e):(const_Call)tm_badcast(__FILE__,__LINE__))
#define to_Case(e) ((e)->tag==TAGCase?((Case)e):(Case)tm_badcast(__FILE__,__LINE__))
#define to_const_Case(e) ((e)->tag==TAGCase?((const_Case)e):(const_Case)tm_badcast(__FILE__,__LINE__))
#define to_Default(e) ((e)->tag==TAGDefault?((Default)e):(Default)tm_badcast(__FILE__,__LINE__))
#define to_const_Default(e) ((e)->tag==TAGDefault?((const_Default)e):(const_Default)tm_badcast(__FILE__,__LINE__))
#define to_DeleteType(e) ((e)->tag==TAGDeleteType?((DeleteType)e):(DeleteType)tm_badcast(__FILE__,__LINE__))
#define to_const_DeleteType(e) ((e)->tag==TAGDeleteType?((const_DeleteType)e):(const_DeleteType)tm_badcast(__FILE__,__LINE__))
#define to_DsAlias(e) ((e)->tag==TAGDsAlias?((DsAlias)e):(DsAlias)tm_badcast(__FILE__,__LINE__))
#define to_const_DsAlias(e) ((e)->tag==TAGDsAlias?((const_DsAlias)e):(const_DsAlias)tm_badcast(__FILE__,__LINE__))
#define to_DsClass(e) ((e)->tag==TAGDsClass?((DsClass)e):(DsClass)tm_badcast(__FILE__,__LINE__))
#define to_const_DsClass(e) ((e)->tag==TAGDsClass?((const_DsClass)e):(const_DsClass)tm_badcast(__FILE__,__LINE__))
#define to_DsConstructor(e) ((e)->tag==TAGDsConstructor?((DsConstructor)e):(DsConstructor)tm_badcast(__FILE__,__LINE__))
#define to_const_DsConstructor(e) ((e)->tag==TAGDsConstructor?((const_DsConstructor)e):(const_DsConstructor)tm_badcast(__FILE__,__LINE__))
#define to_DsConstructorBase(e) ((e)->tag==TAGDsConstructorBase?((DsConstructorBase)e):(DsConstructorBase)tm_badcast(__FILE__,__LINE__))
#define to_const_DsConstructorBase(e) ((e)->tag==TAGDsConstructorBase?((const_DsConstructorBase)e):(const_DsConstructorBase)tm_badcast(__FILE__,__LINE__))
#define to_DsInclude(e) ((e)->tag==TAGDsInclude?((DsInclude)e):(DsInclude)tm_badcast(__FILE__,__LINE__))
#define to_const_DsInclude(e) ((e)->tag==TAGDsInclude?((const_DsInclude)e):(const_DsInclude)tm_badcast(__FILE__,__LINE__))
#define to_DsTuple(e) ((e)->tag==TAGDsTuple?((DsTuple)e):(DsTuple)tm_badcast(__FILE__,__LINE__))
#define to_const_DsTuple(e) ((e)->tag==TAGDsTuple?((const_DsTuple)e):(const_DsTuple)tm_badcast(__FILE__,__LINE__))
#define to_Error(e) ((e)->tag==TAGError?((Error)e):(Error)tm_badcast(__FILE__,__LINE__))
#define to_const_Error(e) ((e)->tag==TAGError?((const_Error)e):(const_Error)tm_badcast(__FILE__,__LINE__))
#define to_Exit(e) ((e)->tag==TAGExit?((Exit)e):(Exit)tm_badcast(__FILE__,__LINE__))
#define to_const_Exit(e) ((e)->tag==TAGExit?((const_Exit)e):(const_Exit)tm_badcast(__FILE__,__LINE__))
#define to_Field(e) ((Field)e)
#define to_const_Field(e) ((const_Field)e)
#define to_For(e) ((e)->tag==TAGFor?((For)e):(For)tm_badcast(__FILE__,__LINE__))
#define to_const_For(e) ((e)->tag==TAGFor?((const_For)e):(const_For)tm_badcast(__FILE__,__LINE__))
#define to_Foreach(e) ((e)->tag==TAGForeach?((Foreach)e):(Foreach)tm_badcast(__FILE__,__LINE__))
#define to_const_Foreach(e) ((e)->tag==TAGForeach?((const_Foreach)e):(const_Foreach)tm_badcast(__FILE__,__LINE__))
#define to_GlobalAppend(e) ((e)->tag==TAGGlobalAppend?((GlobalAppend)e):(GlobalAppend)tm_badcast(__FILE__,__LINE__))
#define to_const_GlobalAppend(e) ((e)->tag==TAGGlobalAppend?((const_GlobalAppend)e):(const_GlobalAppend)tm_badcast(__FILE__,__LINE__))
#define to_GlobalSet(e) ((e)->tag==TAGGlobalSet?((GlobalSet)e):(GlobalSet)tm_badcast(__FILE__,__LINE__))
#define to_const_GlobalSet(e) ((e)->tag==TAGGlobalSet?((const_GlobalSet)e):(const_GlobalSet)tm_badcast(__FILE__,__LINE__))
#define to_GlobalSplit(e) ((e)->tag==TAGGlobalSplit?((GlobalSplit)e):(GlobalSplit)tm_badcast(__FILE__,__LINE__))
#define to_const_GlobalSplit(e) ((e)->tag==TAGGlobalSplit?((const_GlobalSplit)e):(const_GlobalSplit)tm_badcast(__FILE__,__LINE__))
#define to_If(e) ((e)->tag==TAGIf?((If)e):(If)tm_badcast(__FILE__,__LINE__))
#define to_const_If(e) ((e)->tag==TAGIf?((const_If)e):(const_If)tm_badcast(__FILE__,__LINE__))
#define to_Include(e) ((e)->tag==TAGInclude?((Include)e):(Include)tm_badcast(__FILE__,__LINE__))
#define to_const_Include(e) ((e)->tag==TAGInclude?((const_Include)e):(const_Include)tm_badcast(__FILE__,__LINE__))
#define to_Insert(e) ((e)->tag==TAGInsert?((Insert)e):(Insert)tm_badcast(__FILE__,__LINE__))
#define to_const_Insert(e) ((e)->tag==TAGInsert?((const_Insert)e):(const_Insert)tm_badcast(__FILE__,__LINE__))
#define to_Macro(e) ((e)->tag==TAGMacro?((Macro)e):(Macro)tm_badcast(__FILE__,__LINE__))
#define to_const_Macro(e) ((e)->tag==TAGMacro?((const_Macro)e):(const_Macro)tm_badcast(__FILE__,__LINE__))
#define to_Plain(e) ((e)->tag==TAGPlain?((Plain)e):(Plain)tm_badcast(__FILE__,__LINE__))
#define to_const_Plain(e) ((e)->tag==TAGPlain?((const_Plain)e):(const_Plain)tm_badcast(__FILE__,__LINE__))
#define to_Redirect(e) ((e)->tag==TAGRedirect?((Redirect)e):(Redirect)tm_badcast(__FILE__,__LINE__))
#define to_const_Redirect(e) ((e)->tag==TAGRedirect?((const_Redirect)e):(const_Redirect)tm_badcast(__FILE__,__LINE__))
#define to_Rename(e) ((e)->tag==TAGRename?((Rename)e):(Rename)tm_badcast(__FILE__,__LINE__))
#define to_const_Rename(e) ((e)->tag==TAGRename?((const_Rename)e):(const_Rename)tm_badcast(__FILE__,__LINE__))
#define to_Return(e) ((e)->tag==TAGReturn?((Return)e):(Return)tm_badcast(__FILE__,__LINE__))
#define to_const_Return(e) ((e)->tag==TAGReturn?((const_Return)e):(const_Return)tm_badcast(__FILE__,__LINE__))
#define to_Set(e) ((e)->tag==TAGSet?((Set)e):(Set)tm_badcast(__FILE__,__LINE__))
#define to_const_Set(e) ((e)->tag==TAGSet?((const_Set)e):(const_Set)tm_badcast(__FILE__,__LINE__))
#define to_Split(e) ((e)->tag==TAGSplit?((Split)e):(Split)tm_badcast(__FILE__,__LINE__))
#define to_const_Split(e) ((e)->tag==TAGSplit?((const_Split)e):(const_Split)tm_badcast(__FILE__,__LINE__))
#define to_Switch(e) ((e)->tag==TAGSwitch?((Switch)e):(Switch)tm_badcast(__FILE__,__LINE__))
#define to_const_Switch(e) ((e)->tag==TAGSwitch?((const_Switch)e):(const_Switch)tm_badcast(__FILE__,__LINE__))
#define to_Switchcase(e) ((Switchcase)e)
#define to_const_Switchcase(e) ((const_Switchcase)e)
#define to_Type(e) ((Type)e)
#define to_const_Type(e) ((const_Type)e)
#define to_While(e) ((e)->tag==TAGWhile?((While)e):(While)tm_badcast(__FILE__,__LINE__))
#define to_const_While(e) ((e)->tag==TAGWhile?((const_While)e):(const_While)tm_badcast(__FILE__,__LINE__))
#define to_alternative(e) ((alternative)e)
#define to_const_alternative(e) ((const_alternative)e)
#define to_macro(e) ((macro)e)
#define to_const_macro(e) ((const_macro)e)
#define to_origin(e) ((origin)e)
#define to_const_origin(e) ((const_origin)e)
#define to_origsymbol(e) ((origsymbol)e)
#define to_const_origsymbol(e) ((const_origsymbol)e)
#define to_variable(e) ((variable)e)
#define to_const_variable(e) ((const_variable)e)
#define to_classComponent(e) ((classComponent)e)
#define to_const_classComponent(e) ((const_classComponent)e)
#define to_ds(e) ((ds)e)
#define to_const_ds(e) ((const_ds)e)
#define to_tplelm(e) ((tplelm)e)
#define to_const_tplelm(e) ((const_tplelm)e)
#else
#define to_Append(e) ((Append)e)
#define to_const_Append(e) ((const_Append)e)
#define to_Appendfile(e) ((Appendfile)e)
#define to_const_Appendfile(e) ((const_Appendfile)e)
#define to_CCAlternatives(e) ((CCAlternatives)e)
#define to_const_CCAlternatives(e) ((const_CCAlternatives)e)
#define to_CCFields(e) ((CCFields)e)
#define to_const_CCFields(e) ((const_CCFields)e)
#define to_CCSublist(e) ((CCSublist)e)
#define to_const_CCSublist(e) ((const_CCSublist)e)
#define to_CCSuper(e) ((CCSuper)e)
#define to_const_CCSuper(e) ((const_CCSuper)e)
#define to_Call(e) ((Call)e)
#define to_const_Call(e) ((const_Call)e)
#define to_Case(e) ((Case)e)
#define to_const_Case(e) ((const_Case)e)
#define to_Default(e) ((Default)e)
#define to_const_Default(e) ((const_Default)e)
#define to_DeleteType(e) ((DeleteType)e)
#define to_const_DeleteType(e) ((const_DeleteType)e)
#define to_DsAlias(e) ((DsAlias)e)
#define to_const_DsAlias(e) ((const_DsAlias)e)
#define to_DsClass(e) ((DsClass)e)
#define to_const_DsClass(e) ((const_DsClass)e)
#define to_DsConstructor(e) ((DsConstructor)e)
#define to_const_DsConstructor(e) ((const_DsConstructor)e)
#define to_DsConstructorBase(e) ((DsConstructorBase)e)
#define to_const_DsConstructorBase(e) ((const_DsConstructorBase)e)
#define to_DsInclude(e) ((DsInclude)e)
#define to_const_DsInclude(e) ((const_DsInclude)e)
#define to_DsTuple(e) ((DsTuple)e)
#define to_const_DsTuple(e) ((const_DsTuple)e)
#define to_Error(e) ((Error)e)
#define to_const_Error(e) ((const_Error)e)
#define to_Exit(e) ((Exit)e)
#define to_const_Exit(e) ((const_Exit)e)
#define to_Field(e) ((Field)e)
#define to_const_Field(e) ((const_Field)e)
#define to_For(e) ((For)e)
#define to_const_For(e) ((const_For)e)
#define to_Foreach(e) ((Foreach)e)
#define to_const_Foreach(e) ((const_Foreach)e)
#define to_GlobalAppend(e) ((GlobalAppend)e)
#define to_const_GlobalAppend(e) ((const_GlobalAppend)e)
#define to_GlobalSet(e) ((GlobalSet)e)
#define to_const_GlobalSet(e) ((const_GlobalSet)e)
#define to_GlobalSplit(e) ((GlobalSplit)e)
#define to_const_GlobalSplit(e) ((const_GlobalSplit)e)
#define to_If(e) ((If)e)
#define to_const_If(e) ((const_If)e)
#define to_Include(e) ((Include)e)
#define to_const_Include(e) ((const_Include)e)
#define to_Insert(e) ((Insert)e)
#define to_const_Insert(e) ((const_Insert)e)
#define to_Macro(e) ((Macro)e)
#define to_const_Macro(e) ((const_Macro)e)
#define to_Plain(e) ((Plain)e)
#define to_const_Plain(e) ((const_Plain)e)
#define to_Redirect(e) ((Redirect)e)
#define to_const_Redirect(e) ((const_Redirect)e)
#define to_Rename(e) ((Rename)e)
#define to_const_Rename(e) ((const_Rename)e)
#define to_Return(e) ((Return)e)
#define to_const_Return(e) ((const_Return)e)
#define to_Set(e) ((Set)e)
#define to_const_Set(e) ((const_Set)e)
#define to_Split(e) ((Split)e)
#define to_const_Split(e) ((const_Split)e)
#define to_Switch(e) ((Switch)e)
#define to_const_Switch(e) ((const_Switch)e)
#define to_Switchcase(e) ((Switchcase)e)
#define to_const_Switchcase(e) ((const_Switchcase)e)
#define to_Type(e) ((Type)e)
#define to_const_Type(e) ((const_Type)e)
#define to_While(e) ((While)e)
#define to_const_While(e) ((const_While)e)
#define to_alternative(e) ((alternative)e)
#define to_const_alternative(e) ((const_alternative)e)
#define to_macro(e) ((macro)e)
#define to_const_macro(e) ((const_macro)e)
#define to_origin(e) ((origin)e)
#define to_const_origin(e) ((const_origin)e)
#define to_origsymbol(e) ((origsymbol)e)
#define to_const_origsymbol(e) ((const_origsymbol)e)
#define to_variable(e) ((variable)e)
#define to_const_variable(e) ((const_variable)e)
#define to_classComponent(e) ((classComponent)e)
#define to_const_classComponent(e) ((const_classComponent)e)
#define to_ds(e) ((ds)e)
#define to_const_ds(e) ((const_ds)e)
#define to_tplelm(e) ((tplelm)e)
#define to_const_tplelm(e) ((const_tplelm)e)
#endif

#ifdef LOGNEW
#define new_Append(org,line) real_new_Append(org,line,__FILE__,__LINE__)
#define new_Appendfile(org,fname,body) real_new_Appendfile(org,fname,body,__FILE__,__LINE__)
#define new_CCAlternatives(alternatives) real_new_CCAlternatives(alternatives,__FILE__,__LINE__)
#define new_CCFields(fields) real_new_CCFields(fields,__FILE__,__LINE__)
#define new_CCSublist(components) real_new_CCSublist(components,__FILE__,__LINE__)
#define new_CCSuper(super) real_new_CCSuper(super,__FILE__,__LINE__)
#define new_Call(org,line) real_new_Call(org,line,__FILE__,__LINE__)
#define new_Case(org,val) real_new_Case(org,val,__FILE__,__LINE__)
#define new_Default(org) real_new_Default(org,__FILE__,__LINE__)
#define new_DeleteType(org,line) real_new_DeleteType(org,line,__FILE__,__LINE__)
#define new_DsAlias(name,inherits,inheritors,type) real_new_DsAlias(name,inherits,inheritors,type,__FILE__,__LINE__)
#define new_DsClass(name,inherits,inheritors,fields,isvirtual) real_new_DsClass(name,inherits,inheritors,fields,isvirtual,__FILE__,__LINE__)
#define new_DsConstructor(name,inherits,inheritors,fields) real_new_DsConstructor(name,inherits,inheritors,fields,__FILE__,__LINE__)
#define new_DsConstructorBase(name,inherits,inheritors,constructors) real_new_DsConstructorBase(name,inherits,inheritors,constructors,__FILE__,__LINE__)
#define new_DsInclude(name,inherits,inheritors,fnm) real_new_DsInclude(name,inherits,inheritors,fnm,__FILE__,__LINE__)
#define new_DsTuple(name,inherits,inheritors,fields) real_new_DsTuple(name,inherits,inheritors,fields,__FILE__,__LINE__)
#define new_Error(org,str) real_new_Error(org,str,__FILE__,__LINE__)
#define new_Exit(org,str) real_new_Exit(org,str,__FILE__,__LINE__)
#define new_Field(name,type) real_new_Field(name,type,__FILE__,__LINE__)
#define new_For(org,parms,body) real_new_For(org,parms,body,__FILE__,__LINE__)
#define new_Foreach(org,felist,body) real_new_Foreach(org,felist,body,__FILE__,__LINE__)
#define new_GlobalAppend(org,line) real_new_GlobalAppend(org,line,__FILE__,__LINE__)
#define new_GlobalSet(org,line) real_new_GlobalSet(org,line,__FILE__,__LINE__)
#define new_GlobalSplit(org,line) real_new_GlobalSplit(org,line,__FILE__,__LINE__)
#define new_If(org,cond,ifthen,ifelse) real_new_If(org,cond,ifthen,ifelse,__FILE__,__LINE__)
#define new_Include(org,fname) real_new_Include(org,fname,__FILE__,__LINE__)
#define new_Insert(org,fname) real_new_Insert(org,fname,__FILE__,__LINE__)
#define new_Macro(org,formals,body) real_new_Macro(org,formals,body,__FILE__,__LINE__)
#define new_Plain(org,line) real_new_Plain(org,line,__FILE__,__LINE__)
#define new_Redirect(org,fname,body) real_new_Redirect(org,fname,body,__FILE__,__LINE__)
#define new_Rename(org,line) real_new_Rename(org,line,__FILE__,__LINE__)
#define new_Return(org,retval) real_new_Return(org,retval,__FILE__,__LINE__)
#define new_Set(org,line) real_new_Set(org,line,__FILE__,__LINE__)
#define new_Split(org,line) real_new_Split(org,line,__FILE__,__LINE__)
#define new_Switch(org,val,cases,deflt) real_new_Switch(org,val,cases,deflt,__FILE__,__LINE__)
#define new_Switchcase(cases,action) real_new_Switchcase(cases,action,__FILE__,__LINE__)
#define new_Type(level,basetype) real_new_Type(level,basetype,__FILE__,__LINE__)
#define new_While(org,cond,body) real_new_While(org,cond,body,__FILE__,__LINE__)
#define new_alternative(label,component) real_new_alternative(label,component,__FILE__,__LINE__)
#define new_macro(org,lvl,name,fpl,body) real_new_macro(org,lvl,name,fpl,body,__FILE__,__LINE__)
#define new_origin(file,line) real_new_origin(file,line,__FILE__,__LINE__)
#define new_origsymbol(sym,org) real_new_origsymbol(sym,org,__FILE__,__LINE__)
#define new_variable(lvl,name,val) real_new_variable(lvl,name,val,__FILE__,__LINE__)
#define new_Field_list() real_new_Field_list(__FILE__,__LINE__)
#define new_Switchcase_list() real_new_Switchcase_list(__FILE__,__LINE__)
#define new_Type_list() real_new_Type_list(__FILE__,__LINE__)
#define new_alternative_list() real_new_alternative_list(__FILE__,__LINE__)
#define new_classComponent_list() real_new_classComponent_list(__FILE__,__LINE__)
#define new_ds_list() real_new_ds_list(__FILE__,__LINE__)
#define new_macro_list() real_new_macro_list(__FILE__,__LINE__)
#define new_tmstring_list() real_new_tmstring_list(__FILE__,__LINE__)
#define new_tmsymbol_list() real_new_tmsymbol_list(__FILE__,__LINE__)
#define new_tplelm_list() real_new_tplelm_list(__FILE__,__LINE__)
#define new_variable_list() real_new_variable_list(__FILE__,__LINE__)
#define rdup_Type(e) real_rdup_Type(e,__FILE__,__LINE__)
#define rdup_ds(e) real_rdup_ds(e,__FILE__,__LINE__)
#define rdup_origin(e) real_rdup_origin(e,__FILE__,__LINE__)
#define rdup_origsymbol(e) real_rdup_origsymbol(e,__FILE__,__LINE__)
#define rdup_tplelm(e) real_rdup_tplelm(e,__FILE__,__LINE__)
#define rdup_Field_list(e) real_rdup_Field_list(e,__FILE__,__LINE__)
#define rdup_tmstring_list(e) real_rdup_tmstring_list(e,__FILE__,__LINE__)
#define rdup_tmsymbol_list(e) real_rdup_tmsymbol_list(e,__FILE__,__LINE__)
#define rdup_tplelm_list(e) real_rdup_tplelm_list(e,__FILE__,__LINE__)
#define extractlist_tmstring_list(l,b,e,res) real_extractlist_tmstring_list(l,b,e,res,__FILE__,__LINE__)
#endif

#ifdef LOGNEW
extern  Append real_new_Append( origin, tmstring, const char *, int );
extern  Appendfile real_new_Appendfile( origin, tmstring, tplelm_list, const char *, int );
extern  CCAlternatives real_new_CCAlternatives( alternative_list, const char *, int );
extern  CCFields real_new_CCFields( Field_list, const char *, int );
extern  CCSublist real_new_CCSublist( classComponent_list, const char *, int );
extern  CCSuper real_new_CCSuper( tmsymbol, const char *, int );
extern  Call real_new_Call( origin, tmstring, const char *, int );
extern  Case real_new_Case( origin, tmstring, const char *, int );
extern  Default real_new_Default( origin, const char *, int );
extern  DeleteType real_new_DeleteType( origin, tmstring, const char *, int );
extern  DsAlias real_new_DsAlias( origsymbol, tmsymbol_list, tmsymbol_list, Type, const char *, int );
extern  DsClass real_new_DsClass( origsymbol, tmsymbol_list, tmsymbol_list, Field_list, tmbool, const char *, int );
extern  DsConstructor real_new_DsConstructor( origsymbol, tmsymbol_list, tmsymbol_list, Field_list, const char *, int );
extern  DsConstructorBase real_new_DsConstructorBase( origsymbol, tmsymbol_list, tmsymbol_list, tmsymbol_list, const char *, int );
extern  DsInclude real_new_DsInclude( origsymbol, tmsymbol_list, tmsymbol_list, tmstring, const char *, int );
extern  DsTuple real_new_DsTuple( origsymbol, tmsymbol_list, tmsymbol_list, Field_list, const char *, int );
extern  Error real_new_Error( origin, tmstring, const char *, int );
extern  Exit real_new_Exit( origin, tmstring, const char *, int );
extern  Field real_new_Field( origsymbol, Type, const char *, int );
extern  For real_new_For( origin, tmstring, tplelm_list, const char *, int );
extern  Foreach real_new_Foreach( origin, tmstring, tplelm_list, const char *, int );
extern  GlobalAppend real_new_GlobalAppend( origin, tmstring, const char *, int );
extern  GlobalSet real_new_GlobalSet( origin, tmstring, const char *, int );
extern  GlobalSplit real_new_GlobalSplit( origin, tmstring, const char *, int );
extern  If real_new_If( origin, tmstring, tplelm_list, tplelm_list, const char *, int );
extern  Include real_new_Include( origin, tmstring, const char *, int );
extern  Insert real_new_Insert( origin, tmstring, const char *, int );
extern  Macro real_new_Macro( origin, tmstring, tplelm_list, const char *, int );
extern  Plain real_new_Plain( origin, tmstring, const char *, int );
extern  Redirect real_new_Redirect( origin, tmstring, tplelm_list, const char *, int );
extern  Rename real_new_Rename( origin, tmstring, const char *, int );
extern  Return real_new_Return( origin, tmstring, const char *, int );
extern  Set real_new_Set( origin, tmstring, const char *, int );
extern  Split real_new_Split( origin, tmstring, const char *, int );
extern  Switch real_new_Switch( origin, tmstring, Switchcase_list, tplelm_list, const char *, int );
extern  Switchcase real_new_Switchcase( tmstring, tplelm_list, const char *, int );
extern  Type real_new_Type( tmuint, tmsymbol, const char *, int );
extern  While real_new_While( origin, tmstring, tplelm_list, const char *, int );
extern  alternative real_new_alternative( tmsymbol, classComponent, const char *, int );
extern  macro real_new_macro( origin, tmuint, tmstring, tmstring_list, tplelm_list, const char *, int );
extern  origin real_new_origin( tmsymbol, tmuint, const char *, int );
extern  origsymbol real_new_origsymbol( tmsymbol, origin, const char *, int );
extern  variable real_new_variable( tmuint, tmstring, tmstring, const char *, int );
extern  Field_list real_new_Field_list( const char *file, const int line );
extern  Switchcase_list real_new_Switchcase_list( const char *file, const int line );
extern  Type_list real_new_Type_list( const char *file, const int line );
extern  alternative_list real_new_alternative_list( const char *file, const int line );
extern  classComponent_list real_new_classComponent_list( const char *file, const int line );
extern  ds_list real_new_ds_list( const char *file, const int line );
extern  macro_list real_new_macro_list( const char *file, const int line );
extern  tmstring_list real_new_tmstring_list( const char *file, const int line );
extern  tmsymbol_list real_new_tmsymbol_list( const char *file, const int line );
extern  tplelm_list real_new_tplelm_list( const char *file, const int line );
extern  variable_list real_new_variable_list( const char *file, const int line );
#else
extern  Append new_Append( origin, tmstring );
extern  Appendfile new_Appendfile( origin, tmstring, tplelm_list );
extern  CCAlternatives new_CCAlternatives( alternative_list );
extern  CCFields new_CCFields( Field_list );
extern  CCSublist new_CCSublist( classComponent_list );
extern  CCSuper new_CCSuper( tmsymbol );
extern  Call new_Call( origin, tmstring );
extern  Case new_Case( origin, tmstring );
extern  Default new_Default( origin );
extern  DeleteType new_DeleteType( origin, tmstring );
extern  DsAlias new_DsAlias( origsymbol, tmsymbol_list, tmsymbol_list, Type );
extern  DsClass new_DsClass( origsymbol, tmsymbol_list, tmsymbol_list, Field_list, tmbool );
extern  DsConstructor new_DsConstructor( origsymbol, tmsymbol_list, tmsymbol_list, Field_list );
extern  DsConstructorBase new_DsConstructorBase( origsymbol, tmsymbol_list, tmsymbol_list, tmsymbol_list );
extern  DsInclude new_DsInclude( origsymbol, tmsymbol_list, tmsymbol_list, tmstring );
extern  DsTuple new_DsTuple( origsymbol, tmsymbol_list, tmsymbol_list, Field_list );
extern  Error new_Error( origin, tmstring );
extern  Exit new_Exit( origin, tmstring );
extern  Field new_Field( origsymbol, Type );
extern  For new_For( origin, tmstring, tplelm_list );
extern  Foreach new_Foreach( origin, tmstring, tplelm_list );
extern  GlobalAppend new_GlobalAppend( origin, tmstring );
extern  GlobalSet new_GlobalSet( origin, tmstring );
extern  GlobalSplit new_GlobalSplit( origin, tmstring );
extern  If new_If( origin, tmstring, tplelm_list, tplelm_list );
extern  Include new_Include( origin, tmstring );
extern  Insert new_Insert( origin, tmstring );
extern  Macro new_Macro( origin, tmstring, tplelm_list );
extern  Plain new_Plain( origin, tmstring );
extern  Redirect new_Redirect( origin, tmstring, tplelm_list );
extern  Rename new_Rename( origin, tmstring );
extern  Return new_Return( origin, tmstring );
extern  Set new_Set( origin, tmstring );
extern  Split new_Split( origin, tmstring );
extern  Switch new_Switch( origin, tmstring, Switchcase_list, tplelm_list );
extern  Switchcase new_Switchcase( tmstring, tplelm_list );
extern  Type new_Type( tmuint, tmsymbol );
extern  While new_While( origin, tmstring, tplelm_list );
extern  alternative new_alternative( tmsymbol, classComponent );
extern  macro new_macro( origin, tmuint, tmstring, tmstring_list, tplelm_list );
extern  origin new_origin( tmsymbol, tmuint );
extern  origsymbol new_origsymbol( tmsymbol, origin );
extern  variable new_variable( tmuint, tmstring, tmstring );
extern  Field_list new_Field_list( void );
extern  Switchcase_list new_Switchcase_list( void );
extern  Type_list new_Type_list( void );
extern  alternative_list new_alternative_list( void );
extern  classComponent_list new_classComponent_list( void );
extern  ds_list new_ds_list( void );
extern  macro_list new_macro_list( void );
extern  tmstring_list new_tmstring_list( void );
extern  tmsymbol_list new_tmsymbol_list( void );
extern  tplelm_list new_tplelm_list( void );
extern  variable_list new_variable_list( void );
#endif
extern  tmstring_list setroom_tmstring_list( tmstring_list, const unsigned int );
extern  tmsymbol_list setroom_tmsymbol_list( tmsymbol_list, const unsigned int );
extern Field_list append_Field_list( Field_list, Field );
extern Switchcase_list append_Switchcase_list( Switchcase_list, Switchcase );
extern Type_list append_Type_list( Type_list, Type );
extern alternative_list append_alternative_list( alternative_list, alternative );
extern classComponent_list append_classComponent_list( classComponent_list, classComponent );
extern ds_list append_ds_list( ds_list, ds );
extern tmstring_list append_tmstring_list( tmstring_list, tmstring );
extern tmsymbol_list append_tmsymbol_list( tmsymbol_list, tmsymbol );
extern tplelm_list append_tplelm_list( tplelm_list, tplelm );
extern variable_list append_variable_list( variable_list, variable );
extern  macro_list insert_macro_list( macro_list, unsigned int, macro  );
extern  tmstring_list insert_tmstring_list( tmstring_list, unsigned int, tmstring  );
extern  variable_list insert_variable_list( variable_list, unsigned int, variable  );
extern ds_list insertlist_ds_list( ds_list, unsigned int, ds_list  );
extern   ds_list delete_ds_list( ds_list, unsigned int );
extern   macro_list delete_macro_list( macro_list, unsigned int );
extern   tmstring_list delete_tmstring_list( tmstring_list, unsigned int );
extern   tmsymbol_list delete_tmsymbol_list( tmsymbol_list, unsigned int );
extern   variable_list delete_variable_list( variable_list, unsigned int );
extern tmstring_list extract_tmstring_list( tmstring_list, unsigned int, tmstring *, int * );
extern tmsymbol_list extract_tmsymbol_list( tmsymbol_list, unsigned int, tmsymbol *, int * );
#ifdef LOGNEW
extern tmstring_list real_extractlist_tmstring_list( tmstring_list, unsigned int, unsigned int, tmstring_list *, const char *, int );
#else
extern tmstring_list extractlist_tmstring_list( tmstring_list, unsigned int, unsigned int, tmstring_list * );
#endif
extern  Field_list concat_Field_list( Field_list, Field_list );
extern  ds_list concat_ds_list( ds_list, ds_list );
extern  tmsymbol_list concat_tmsymbol_list( tmsymbol_list, tmsymbol_list );
extern void rfre_Type_list( Type_list );
extern void rfre_alternative_list( alternative_list );
extern void rfre_classComponent_list( classComponent_list );
extern void rfre_ds_list( ds_list );
extern void rfre_macro_list( macro_list );
extern void rfre_tmstring_list( tmstring_list );
extern void rfre_tmsymbol_list( tmsymbol_list );
extern void rfre_tplelm_list( tplelm_list );
extern void rfre_variable_list( variable_list );
extern void rfre_Type( Type );
extern void rfre_classComponent( classComponent );
extern void rfre_ds( ds );
extern void rfre_origin( origin );
extern void print_ds_list( TMPRINTSTATE *st, const_ds_list l );
#ifdef LOGNEW
extern  Type real_rdup_Type( const_Type, const char *_f, int _l );
extern  ds real_rdup_ds( const_ds, const char *_f, int _l );
extern  origin real_rdup_origin( const_origin, const char *_f, int _l );
extern  origsymbol real_rdup_origsymbol( const_origsymbol, const char *_f, int _l );
extern  tplelm real_rdup_tplelm( const_tplelm, const char *_f, int _l );
extern  Field_list real_rdup_Field_list( const_Field_list, const char *_f, int _l );
extern  tmstring_list real_rdup_tmstring_list( const_tmstring_list, const char *_f, int _l );
extern  tmsymbol_list real_rdup_tmsymbol_list( const_tmsymbol_list, const char *_f, int _l );
extern  tplelm_list real_rdup_tplelm_list( const_tplelm_list, const char *_f, int _l );
#else
extern  Type rdup_Type( const_Type );
extern  ds rdup_ds( const_ds );
extern  origin rdup_origin( const_origin );
extern  origsymbol rdup_origsymbol( const_origsymbol );
extern  tplelm rdup_tplelm( const_tplelm );
extern Field_list rdup_Field_list( const_Field_list );
extern tmstring_list rdup_tmstring_list( const_tmstring_list );
extern tmsymbol_list rdup_tmsymbol_list( const_tmsymbol_list );
extern tplelm_list rdup_tplelm_list( const_tplelm_list );
#endif
extern void stat_tm( FILE *f );
extern int get_balance_tm( void );
/* ---- end of /Users/reeuwijk/lab/lib/tmc.ht ---- */
/* Code generation required 24 milliseconds. */
