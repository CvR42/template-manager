/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /usr/local/lib/calu.ht ---- */
/* External definitions (Version for array list).

   template file:      /usr/local/lib/calu.ht
   datastructure file: tm.ds
   tm version:         36
   tm kernel version:  *** development -- not for distribution ***
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
typedef struct str_tmstring_list *tmstring_list;
typedef struct str_tplelm_list *tplelm_list;
typedef struct str_var_list *var_list;
typedef struct str_classComponent *classComponent;
typedef struct str_alternative *alternative;
typedef struct str_ds *ds;
typedef struct str_field *field;
typedef struct str_macro *macro;
typedef struct str_tplelm *tplelm;
typedef struct str_var *var;

#define alternativeNIL (alternative)0
#define classComponentNIL (classComponent)0
#define dsNIL (ds)0
#define fieldNIL (field)0
#define macroNIL (macro)0
#define tplelmNIL (tplelm)0
#define varNIL (var)0
#define alternative_listNIL (alternative_list)0
#define classComponent_listNIL (classComponent_list)0
#define ds_listNIL (ds_list)0
#define field_listNIL (field_list)0
#define macro_listNIL (macro_list)0
#define tmstring_listNIL (tmstring_list)0
#define tplelm_listNIL (tplelm_list)0
#define var_listNIL (var_list)0

#define CCSuper u.ue_CCSuper
#define CCFields u.ue_CCFields
#define CCAlternatives u.ue_CCAlternatives
#define CCSublist u.ue_CCSublist
#define DsCons u.ue_DsCons
#define DsTuple u.ue_DsTuple
#define DsClass u.ue_DsClass
#define DsConstructor u.ue_DsConstructor
#define Plain u.ue_Plain
#define Foreach u.ue_Foreach
#define While u.ue_While
#define If u.ue_If
#define Set u.ue_Set
#define GlobalSet u.ue_GlobalSet
#define Append u.ue_Append
#define GlobalAppend u.ue_GlobalAppend
#define Error u.ue_Error
#define Exit u.ue_Exit
#define Redirect u.ue_Redirect
#define Include u.ue_Include
#define Macro u.ue_Macro
#define Call u.ue_Call
#define Return u.ue_Return
#define Insert u.ue_Insert

typedef enum en_tags_classComponent {
    TAGCCSuper, TAGCCFields, TAGCCAlternatives, TAGCCSublist
} tags_classComponent;

typedef enum en_tags_ds {
    TAGDsCons, TAGDsTuple, TAGDsClass, TAGDsConstructor
} tags_ds;

typedef enum en_tags_tplelm {
    TAGPlain, TAGForeach, TAGWhile, TAGIf, TAGSet, TAGGlobalSet, TAGAppend, TAGGlobalAppend, TAGError, TAGExit, TAGRedirect, TAGInclude, TAGMacro, TAGCall, TAGReturn, TAGInsert
} tags_tplelm;


/* Structure for constructor CCSuper */
typedef struct str_CCSuper {
    tmstring super;
} C_CCSuper;

/* Structure for constructor CCFields */
typedef struct str_CCFields {
    field_list fields;
} C_CCFields;

/* Structure for constructor CCAlternatives */
typedef struct str_CCAlternatives {
    alternative_list alternatives;
} C_CCAlternatives;

/* Structure for constructor CCSublist */
typedef struct str_CCSublist {
    classComponent_list components;
} C_CCSublist;

/* Constructor type classComponent */
struct str_classComponent {
    tags_classComponent tag;
    union uni_classComponent {
	C_CCSuper ue_CCSuper;
	C_CCFields ue_CCFields;
	C_CCAlternatives ue_CCAlternatives;
	C_CCSublist ue_CCSublist;
    } u;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_alternative {
    tmstring label;
    classComponent component;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

/* Structure for constructor DsCons */
typedef struct str_DsCons {
    tmstring name;
    tmstring_list inherits;
    tmstring_list constructors;
} C_DsCons;

/* Structure for constructor DsTuple */
typedef struct str_DsTuple {
    tmstring name;
    tmstring_list inherits;
    field_list fields;
} C_DsTuple;

/* Structure for constructor DsClass */
typedef struct str_DsClass {
    tmstring name;
    tmstring_list inherits;
    field_list fields;
    tmbool virtual;
} C_DsClass;

/* Structure for constructor DsConstructor */
typedef struct str_DsConstructor {
    tmstring name;
    tmstring_list inherits;
    field_list fields;
} C_DsConstructor;

/* Constructor type ds */
struct str_ds {
    tags_ds tag;
    union uni_ds {
	C_DsCons ue_DsCons;
	C_DsTuple ue_DsTuple;
	C_DsClass ue_DsClass;
	C_DsConstructor ue_DsConstructor;
    } u;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_field {
    int level;
    tmstring name;
    tmstring type;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_macro {
    uint lvl;
    tmstring name;
    tmstring orgfile;
    tmstring_list fpl;
    tplelm_list body;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

/* Structure for constructor Plain */
typedef struct str_Plain {
    int lno;
    tmstring plainline;
} C_Plain;

/* Structure for constructor Foreach */
typedef struct str_Foreach {
    int lno;
    tmstring felist;
    tplelm_list felines;
} C_Foreach;

/* Structure for constructor While */
typedef struct str_While {
    int lno;
    tmstring whilecond;
    tplelm_list whilelines;
} C_While;

/* Structure for constructor If */
typedef struct str_If {
    int lno;
    tmstring ifcond;
    tplelm_list ifthen;
    tplelm_list ifelse;
} C_If;

/* Structure for constructor Set */
typedef struct str_Set {
    int lno;
    tmstring setline;
} C_Set;

/* Structure for constructor GlobalSet */
typedef struct str_GlobalSet {
    int lno;
    tmstring setline;
} C_GlobalSet;

/* Structure for constructor Append */
typedef struct str_Append {
    int lno;
    tmstring appline;
} C_Append;

/* Structure for constructor GlobalAppend */
typedef struct str_GlobalAppend {
    int lno;
    tmstring appline;
} C_GlobalAppend;

/* Structure for constructor Error */
typedef struct str_Error {
    int lno;
    tmstring errstr;
} C_Error;

/* Structure for constructor Exit */
typedef struct str_Exit {
    int lno;
    tmstring str;
} C_Exit;

/* Structure for constructor Redirect */
typedef struct str_Redirect {
    int lno;
    tmstring fname;
    tplelm_list body;
} C_Redirect;

/* Structure for constructor Include */
typedef struct str_Include {
    int lno;
    tmstring fname;
} C_Include;

/* Structure for constructor Macro */
typedef struct str_Macro {
    int lno;
    tmstring formpar;
    tplelm_list macbody;
} C_Macro;

/* Structure for constructor Call */
typedef struct str_Call {
    int lno;
    tmstring callline;
} C_Call;

/* Structure for constructor Return */
typedef struct str_Return {
    int lno;
    tmstring retval;
} C_Return;

/* Structure for constructor Insert */
typedef struct str_Insert {
    int lno;
    tmstring fname;
} C_Insert;

/* Constructor type tplelm */
struct str_tplelm {
    tags_tplelm tag;
    union uni_tplelm {
	C_Plain ue_Plain;
	C_Foreach ue_Foreach;
	C_While ue_While;
	C_If ue_If;
	C_Set ue_Set;
	C_GlobalSet ue_GlobalSet;
	C_Append ue_Append;
	C_GlobalAppend ue_GlobalAppend;
	C_Error ue_Error;
	C_Exit ue_Exit;
	C_Redirect ue_Redirect;
	C_Include ue_Include;
	C_Macro ue_Macro;
	C_Call ue_Call;
	C_Return ue_Return;
	C_Insert ue_Insert;
    } u;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_var {
    uint lvl;
    tmstring name;
    tmstring val;
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


#ifdef LOGNEW
#define new_alternative(label,component) real_new_alternative(label,component,__FILE__,__LINE__)
#define new_CCSuper(super) real_new_CCSuper(super,__FILE__,__LINE__)
#define new_CCFields(fields) real_new_CCFields(fields,__FILE__,__LINE__)
#define new_CCAlternatives(alternatives) real_new_CCAlternatives(alternatives,__FILE__,__LINE__)
#define new_CCSublist(components) real_new_CCSublist(components,__FILE__,__LINE__)
#define new_DsCons(name,inherits,constructors) real_new_DsCons(name,inherits,constructors,__FILE__,__LINE__)
#define new_DsTuple(name,inherits,fields) real_new_DsTuple(name,inherits,fields,__FILE__,__LINE__)
#define new_DsClass(name,inherits,fields,virtual) real_new_DsClass(name,inherits,fields,virtual,__FILE__,__LINE__)
#define new_DsConstructor(name,inherits,fields) real_new_DsConstructor(name,inherits,fields,__FILE__,__LINE__)
#define new_field(level,name,type) real_new_field(level,name,type,__FILE__,__LINE__)
#define new_macro(lvl,name,orgfile,fpl,body) real_new_macro(lvl,name,orgfile,fpl,body,__FILE__,__LINE__)
#define new_Plain(lno,plainline) real_new_Plain(lno,plainline,__FILE__,__LINE__)
#define new_Foreach(lno,felist,felines) real_new_Foreach(lno,felist,felines,__FILE__,__LINE__)
#define new_While(lno,whilecond,whilelines) real_new_While(lno,whilecond,whilelines,__FILE__,__LINE__)
#define new_If(lno,ifcond,ifthen,ifelse) real_new_If(lno,ifcond,ifthen,ifelse,__FILE__,__LINE__)
#define new_Set(lno,setline) real_new_Set(lno,setline,__FILE__,__LINE__)
#define new_GlobalSet(lno,setline) real_new_GlobalSet(lno,setline,__FILE__,__LINE__)
#define new_Append(lno,appline) real_new_Append(lno,appline,__FILE__,__LINE__)
#define new_GlobalAppend(lno,appline) real_new_GlobalAppend(lno,appline,__FILE__,__LINE__)
#define new_Error(lno,errstr) real_new_Error(lno,errstr,__FILE__,__LINE__)
#define new_Exit(lno,str) real_new_Exit(lno,str,__FILE__,__LINE__)
#define new_Redirect(lno,fname,body) real_new_Redirect(lno,fname,body,__FILE__,__LINE__)
#define new_Include(lno,fname) real_new_Include(lno,fname,__FILE__,__LINE__)
#define new_Macro(lno,formpar,macbody) real_new_Macro(lno,formpar,macbody,__FILE__,__LINE__)
#define new_Call(lno,callline) real_new_Call(lno,callline,__FILE__,__LINE__)
#define new_Return(lno,retval) real_new_Return(lno,retval,__FILE__,__LINE__)
#define new_Insert(lno,fname) real_new_Insert(lno,fname,__FILE__,__LINE__)
#define new_var(lvl,name,val) real_new_var(lvl,name,val,__FILE__,__LINE__)
#define new_alternative_list() real_new_alternative_list(__FILE__,__LINE__)
#define new_classComponent_list() real_new_classComponent_list(__FILE__,__LINE__)
#define new_ds_list() real_new_ds_list(__FILE__,__LINE__)
#define new_field_list() real_new_field_list(__FILE__,__LINE__)
#define new_macro_list() real_new_macro_list(__FILE__,__LINE__)
#define new_tmstring_list() real_new_tmstring_list(__FILE__,__LINE__)
#define new_tplelm_list() real_new_tplelm_list(__FILE__,__LINE__)
#define new_var_list() real_new_var_list(__FILE__,__LINE__)
#define rdup_ds(e) real_rdup_ds(e,__FILE__,__LINE__)
#define rdup_field_list(e) real_rdup_field_list(e,__FILE__,__LINE__)
#define rdup_tmstring_list(e) real_rdup_tmstring_list(e,__FILE__,__LINE__)
#define rdup_tplelm_list(e) real_rdup_tplelm_list(e,__FILE__,__LINE__)
#endif

#ifdef LOGNEW
extern alternative real_new_alternative( tmstring, classComponent, const char *_f, const int _l );
#else
extern alternative new_alternative( tmstring, classComponent );
#endif
#ifdef LOGNEW
extern classComponent real_new_CCSuper( tmstring, const char *, const int );
#else
extern classComponent new_CCSuper( tmstring );
#endif
#ifdef LOGNEW
extern classComponent real_new_CCFields( field_list, const char *, const int );
#else
extern classComponent new_CCFields( field_list );
#endif
#ifdef LOGNEW
extern classComponent real_new_CCAlternatives( alternative_list, const char *, const int );
#else
extern classComponent new_CCAlternatives( alternative_list );
#endif
#ifdef LOGNEW
extern classComponent real_new_CCSublist( classComponent_list, const char *, const int );
#else
extern classComponent new_CCSublist( classComponent_list );
#endif
#ifdef LOGNEW
extern ds real_new_DsCons( tmstring, tmstring_list, tmstring_list, const char *, const int );
#else
extern ds new_DsCons( tmstring, tmstring_list, tmstring_list );
#endif
#ifdef LOGNEW
extern ds real_new_DsTuple( tmstring, tmstring_list, field_list, const char *, const int );
#else
extern ds new_DsTuple( tmstring, tmstring_list, field_list );
#endif
#ifdef LOGNEW
extern ds real_new_DsClass( tmstring, tmstring_list, field_list, tmbool, const char *, const int );
#else
extern ds new_DsClass( tmstring, tmstring_list, field_list, tmbool );
#endif
#ifdef LOGNEW
extern ds real_new_DsConstructor( tmstring, tmstring_list, field_list, const char *, const int );
#else
extern ds new_DsConstructor( tmstring, tmstring_list, field_list );
#endif
#ifdef LOGNEW
extern field real_new_field( int, tmstring, tmstring, const char *_f, const int _l );
#else
extern field new_field( int, tmstring, tmstring );
#endif
#ifdef LOGNEW
extern macro real_new_macro( uint, tmstring, tmstring, tmstring_list, tplelm_list, const char *_f, const int _l );
#else
extern macro new_macro( uint, tmstring, tmstring, tmstring_list, tplelm_list );
#endif
#ifdef LOGNEW
extern tplelm real_new_Plain( int, tmstring, const char *, const int );
#else
extern tplelm new_Plain( int, tmstring );
#endif
#ifdef LOGNEW
extern tplelm real_new_Foreach( int, tmstring, tplelm_list, const char *, const int );
#else
extern tplelm new_Foreach( int, tmstring, tplelm_list );
#endif
#ifdef LOGNEW
extern tplelm real_new_While( int, tmstring, tplelm_list, const char *, const int );
#else
extern tplelm new_While( int, tmstring, tplelm_list );
#endif
#ifdef LOGNEW
extern tplelm real_new_If( int, tmstring, tplelm_list, tplelm_list, const char *, const int );
#else
extern tplelm new_If( int, tmstring, tplelm_list, tplelm_list );
#endif
#ifdef LOGNEW
extern tplelm real_new_Set( int, tmstring, const char *, const int );
#else
extern tplelm new_Set( int, tmstring );
#endif
#ifdef LOGNEW
extern tplelm real_new_GlobalSet( int, tmstring, const char *, const int );
#else
extern tplelm new_GlobalSet( int, tmstring );
#endif
#ifdef LOGNEW
extern tplelm real_new_Append( int, tmstring, const char *, const int );
#else
extern tplelm new_Append( int, tmstring );
#endif
#ifdef LOGNEW
extern tplelm real_new_GlobalAppend( int, tmstring, const char *, const int );
#else
extern tplelm new_GlobalAppend( int, tmstring );
#endif
#ifdef LOGNEW
extern tplelm real_new_Error( int, tmstring, const char *, const int );
#else
extern tplelm new_Error( int, tmstring );
#endif
#ifdef LOGNEW
extern tplelm real_new_Exit( int, tmstring, const char *, const int );
#else
extern tplelm new_Exit( int, tmstring );
#endif
#ifdef LOGNEW
extern tplelm real_new_Redirect( int, tmstring, tplelm_list, const char *, const int );
#else
extern tplelm new_Redirect( int, tmstring, tplelm_list );
#endif
#ifdef LOGNEW
extern tplelm real_new_Include( int, tmstring, const char *, const int );
#else
extern tplelm new_Include( int, tmstring );
#endif
#ifdef LOGNEW
extern tplelm real_new_Macro( int, tmstring, tplelm_list, const char *, const int );
#else
extern tplelm new_Macro( int, tmstring, tplelm_list );
#endif
#ifdef LOGNEW
extern tplelm real_new_Call( int, tmstring, const char *, const int );
#else
extern tplelm new_Call( int, tmstring );
#endif
#ifdef LOGNEW
extern tplelm real_new_Return( int, tmstring, const char *, const int );
#else
extern tplelm new_Return( int, tmstring );
#endif
#ifdef LOGNEW
extern tplelm real_new_Insert( int, tmstring, const char *, const int );
#else
extern tplelm new_Insert( int, tmstring );
#endif
#ifdef LOGNEW
extern var real_new_var( uint, tmstring, tmstring, const char *_f, const int _l );
#else
extern var new_var( uint, tmstring, tmstring );
#endif
#ifdef LOGNEW
extern alternative_list real_new_alternative_list( const char *file, const int line );
extern classComponent_list real_new_classComponent_list( const char *file, const int line );
extern ds_list real_new_ds_list( const char *file, const int line );
extern field_list real_new_field_list( const char *file, const int line );
extern macro_list real_new_macro_list( const char *file, const int line );
extern tmstring_list real_new_tmstring_list( const char *file, const int line );
extern tplelm_list real_new_tplelm_list( const char *file, const int line );
extern var_list real_new_var_list( const char *file, const int line );
#else
extern alternative_list new_alternative_list( void );
extern classComponent_list new_classComponent_list( void );
extern ds_list new_ds_list( void );
extern field_list new_field_list( void );
extern macro_list new_macro_list( void );
extern tmstring_list new_tmstring_list( void );
extern tplelm_list new_tplelm_list( void );
extern var_list new_var_list( void );
#endif
extern alternative_list append_alternative_list( alternative_list, alternative );
extern classComponent_list append_classComponent_list( classComponent_list, classComponent );
extern ds_list append_ds_list( ds_list, ds );
extern field_list append_field_list( field_list, field );
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
#else
#endif
#ifdef LOGNEW
extern ds real_rdup_ds( const ds, const char *_f, const int _l );
extern field_list real_rdup_field_list( const field_list, const char *_f, const int _l );
extern tmstring_list real_rdup_tmstring_list( const tmstring_list, const char *_f, const int _l );
extern tplelm_list real_rdup_tplelm_list( const tplelm_list, const char *_f, const int _l );
#else
extern ds rdup_ds( const ds );
extern field_list rdup_field_list( const field_list );
extern tmstring_list rdup_tmstring_list( const tmstring_list );
extern tplelm_list rdup_tplelm_list( const tplelm_list );
#endif
#ifdef LOGNEW
#else
#endif
extern void flush_tm( void );
extern void stat_tm( FILE * );
extern int get_balance_tm( void );
/* ---- end of /usr/local/lib/calu.ht ---- */
