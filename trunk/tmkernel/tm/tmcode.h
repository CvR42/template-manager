/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /home/gargamel/reeuwijk/i586/lib/calu.ht ---- */
/* Definition C datastructures (Version for array list).

   template file:      /home/gargamel/reeuwijk/i586/lib/calu.ht
   datastructure file: tm.ds
   tm version:         35
   tm kernel version:  1.2
 */

/* forward reference typedefs for all types.
 * C does not like the use of undefined types, but does not
 * mind the use of pointers to (yet) undefined types.
 */
typedef struct str_constructor_list *constructor_list;
typedef struct str_ds_list *ds_list;
typedef struct str_field_list *field_list;
typedef struct str_macro_list *macro_list;
typedef struct str_tmstring_list *tmstring_list;
typedef struct str_tplelm_list *tplelm_list;
typedef struct str_var_list *var_list;
typedef struct str_ds *ds;
typedef struct str_constructor *constructor;
typedef struct str_field *field;
typedef struct str_macro *macro;
typedef struct str_var *var;
typedef struct str_tplelm *tplelm;

#define dsNIL (ds)0
#define constructorNIL (constructor)0
#define fieldNIL (field)0
#define macroNIL (macro)0
#define varNIL (var)0
#define tplelmNIL (tplelm)0
#define constructor_listNIL (constructor_list)0
#define ds_listNIL (ds_list)0
#define field_listNIL (field_list)0
#define macro_listNIL (macro_list)0
#define tmstring_listNIL (tmstring_list)0
#define tplelm_listNIL (tplelm_list)0
#define var_listNIL (var_list)0

#define DsCons u.ue_DsCons
#define DsTuple u.ue_DsTuple

typedef enum en_tags_ds {
    TAGDsCons, TAGDsTuple
} tags_ds;

#define Plain u.ue_Plain
#define Foreach u.ue_Foreach
#define While u.ue_While
#define If u.ue_If
#define Set u.ue_Set
#define Append u.ue_Append
#define Error u.ue_Error
#define Exit u.ue_Exit
#define ExpandInherits u.ue_ExpandInherits
#define Redirect u.ue_Redirect
#define Include u.ue_Include
#define Macro u.ue_Macro
#define Call u.ue_Call
#define Return u.ue_Return
#define Insert u.ue_Insert

typedef enum en_tags_tplelm {
    TAGPlain, TAGForeach, TAGWhile, TAGIf, TAGSet, TAGAppend, TAGError, TAGExit, TAGExpandInherits, TAGRedirect, TAGInclude, TAGMacro, TAGCall, TAGReturn, TAGInsert
} tags_tplelm;


/* Structure for constructor DsCons */
typedef struct str_DsCons {
    tmstring ctypename;
    tmstring_list cinherits;
    constructor_list conslist;
} C_DsCons;

/* Structure for constructor DsTuple */
typedef struct str_DsTuple {
    tmstring ttypename;
    tmstring_list tinherits;
    field_list tuplefields;
} C_DsTuple;

struct str_ds {
    tags_ds tag;
    union uni_ds {
	C_DsCons ue_DsCons;
	C_DsTuple ue_DsTuple;
    } u;
#ifdef LOGNEW
    long int lognew_id;
#endif
};

struct str_constructor {
    tmstring name;
    field_list fields;
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

struct str_var {
    uint lvl;
    tmstring name;
    tmstring val;
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

/* Structure for constructor Append */
typedef struct str_Append {
    int lno;
    tmstring appline;
} C_Append;

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

/* Structure for constructor ExpandInherits */
typedef struct str_ExpandInherits {
    int lno;
    tmstring types;
} C_ExpandInherits;

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

struct str_tplelm {
    tags_tplelm tag;
    union uni_tplelm {
	C_Plain ue_Plain;
	C_Foreach ue_Foreach;
	C_While ue_While;
	C_If ue_If;
	C_Set ue_Set;
	C_Append ue_Append;
	C_Error ue_Error;
	C_Exit ue_Exit;
	C_ExpandInherits ue_ExpandInherits;
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

struct str_constructor_list {
    unsigned int sz;
    unsigned int room;
    constructor *arr;
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
#define new_constructor(name,fields) real_new_constructor(name,fields,__FILE__,__LINE__)
#define new_DsCons(ctypename,cinherits,conslist) real_new_DsCons(ctypename,cinherits,conslist,__FILE__,__LINE__)
#define new_DsTuple(ttypename,tinherits,tuplefields) real_new_DsTuple(ttypename,tinherits,tuplefields,__FILE__,__LINE__)
#define new_field(level,name,type) real_new_field(level,name,type,__FILE__,__LINE__)
#define new_macro(lvl,name,orgfile,fpl,body) real_new_macro(lvl,name,orgfile,fpl,body,__FILE__,__LINE__)
#define new_Plain(lno,plainline) real_new_Plain(lno,plainline,__FILE__,__LINE__)
#define new_Foreach(lno,felist,felines) real_new_Foreach(lno,felist,felines,__FILE__,__LINE__)
#define new_While(lno,whilecond,whilelines) real_new_While(lno,whilecond,whilelines,__FILE__,__LINE__)
#define new_If(lno,ifcond,ifthen,ifelse) real_new_If(lno,ifcond,ifthen,ifelse,__FILE__,__LINE__)
#define new_Set(lno,setline) real_new_Set(lno,setline,__FILE__,__LINE__)
#define new_Append(lno,appline) real_new_Append(lno,appline,__FILE__,__LINE__)
#define new_Error(lno,errstr) real_new_Error(lno,errstr,__FILE__,__LINE__)
#define new_Exit(lno,str) real_new_Exit(lno,str,__FILE__,__LINE__)
#define new_ExpandInherits(lno,types) real_new_ExpandInherits(lno,types,__FILE__,__LINE__)
#define new_Redirect(lno,fname,body) real_new_Redirect(lno,fname,body,__FILE__,__LINE__)
#define new_Include(lno,fname) real_new_Include(lno,fname,__FILE__,__LINE__)
#define new_Macro(lno,formpar,macbody) real_new_Macro(lno,formpar,macbody,__FILE__,__LINE__)
#define new_Call(lno,callline) real_new_Call(lno,callline,__FILE__,__LINE__)
#define new_Return(lno,retval) real_new_Return(lno,retval,__FILE__,__LINE__)
#define new_Insert(lno,fname) real_new_Insert(lno,fname,__FILE__,__LINE__)
#define new_var(lvl,name,val) real_new_var(lvl,name,val,__FILE__,__LINE__)
#define new_constructor_list() real_new_constructor_list(__FILE__,__LINE__)
#define new_ds_list() real_new_ds_list(__FILE__,__LINE__)
#define new_field_list() real_new_field_list(__FILE__,__LINE__)
#define new_macro_list() real_new_macro_list(__FILE__,__LINE__)
#define new_tmstring_list() real_new_tmstring_list(__FILE__,__LINE__)
#define new_tplelm_list() real_new_tplelm_list(__FILE__,__LINE__)
#define new_var_list() real_new_var_list(__FILE__,__LINE__)
#define rdup_constructor(e) real_rdup_constructor(e,__FILE__,__LINE__)
#define rdup_ds(e) real_rdup_ds(e,__FILE__,__LINE__)
#define rdup_constructor_list(e) real_rdup_constructor_list(e,__FILE__,__LINE__)
#define rdup_field_list(e) real_rdup_field_list(e,__FILE__,__LINE__)
#define rdup_tmstring_list(e) real_rdup_tmstring_list(e,__FILE__,__LINE__)
#define rdup_tplelm_list(e) real_rdup_tplelm_list(e,__FILE__,__LINE__)
#endif

#ifdef LOGNEW
extern constructor real_new_constructor( tmstring, field_list, const char *_f, const int _l );
#else
extern constructor new_constructor( tmstring, field_list );
#endif
#ifdef LOGNEW
extern ds real_new_DsCons( tmstring, tmstring_list, constructor_list, const char *, const int );
#else
extern ds new_DsCons( tmstring, tmstring_list, constructor_list );
#endif
#ifdef LOGNEW
extern ds real_new_DsTuple( tmstring, tmstring_list, field_list, const char *, const int );
#else
extern ds new_DsTuple( tmstring, tmstring_list, field_list );
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
extern tplelm real_new_Append( int, tmstring, const char *, const int );
#else
extern tplelm new_Append( int, tmstring );
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
extern tplelm real_new_ExpandInherits( int, tmstring, const char *, const int );
#else
extern tplelm new_ExpandInherits( int, tmstring );
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
extern constructor_list real_new_constructor_list( const char *file, const int line );
extern ds_list real_new_ds_list( const char *file, const int line );
extern field_list real_new_field_list( const char *file, const int line );
extern macro_list real_new_macro_list( const char *file, const int line );
extern tmstring_list real_new_tmstring_list( const char *file, const int line );
extern tplelm_list real_new_tplelm_list( const char *file, const int line );
extern var_list real_new_var_list( const char *file, const int line );
#else
extern constructor_list new_constructor_list( void );
extern ds_list new_ds_list( void );
extern field_list new_field_list( void );
extern macro_list new_macro_list( void );
extern tmstring_list new_tmstring_list( void );
extern tplelm_list new_tplelm_list( void );
extern var_list new_var_list( void );
#endif
extern constructor_list append_constructor_list( constructor_list, constructor );
extern ds_list append_ds_list( ds_list, ds );
extern field_list append_field_list( field_list, field );
extern tmstring_list append_tmstring_list( tmstring_list, tmstring );
extern tplelm_list append_tplelm_list( tplelm_list, tplelm );
extern macro_list insert_macro_list( macro_list, const unsigned int, macro  );
extern tmstring_list insert_tmstring_list( tmstring_list, const unsigned int, tmstring  );
extern var_list insert_var_list( var_list, const unsigned int, var  );
extern ds_list delete_ds_list( ds_list, const unsigned int );
extern macro_list delete_macro_list( macro_list, const unsigned int );
extern tmstring_list delete_tmstring_list( tmstring_list, const unsigned int );
extern var_list delete_var_list( var_list, const unsigned int );
extern field_list concat_field_list( field_list, field_list );
extern void rfre_ds_list( ds_list );
extern void rfre_field_list( field_list );
extern void rfre_macro_list( macro_list );
extern void rfre_tmstring_list( tmstring_list );
extern void rfre_tplelm_list( tplelm_list );
extern void rfre_var_list( var_list );
extern void rfre_constructor( constructor );
extern void rfre_ds( ds );
extern void rfre_macro( macro );
extern void rfre_tplelm( tplelm );
extern void print_ds_list( TMPRINTSTATE *st, const ds_list );
extern void print_tmstring_list( TMPRINTSTATE *st, const tmstring_list );
#ifdef LOGNEW
#else
#endif
#ifdef LOGNEW
extern constructor real_rdup_constructor( const constructor, const char *_f, const int _l );
extern ds real_rdup_ds( const ds, const char *_f, const int _l );
extern constructor_list real_rdup_constructor_list( const constructor_list, const char *_f, const int _l );
extern field_list real_rdup_field_list( const field_list, const char *_f, const int _l );
extern tmstring_list real_rdup_tmstring_list( const tmstring_list, const char *_f, const int _l );
extern tplelm_list real_rdup_tplelm_list( const tplelm_list, const char *_f, const int _l );
#else
extern constructor rdup_constructor( const constructor );
extern ds rdup_ds( const ds );
extern constructor_list rdup_constructor_list( const constructor_list );
extern field_list rdup_field_list( const field_list );
extern tmstring_list rdup_tmstring_list( const tmstring_list );
extern tplelm_list rdup_tplelm_list( const tplelm_list );
#endif
#ifdef LOGNEW
#else
#endif
extern void flush_tm( void );
extern void stat_tm( FILE * );
/* ---- end of /home/gargamel/reeuwijk/i586/lib/calu.ht ---- */
