/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: tmc.h
 *
 * declaration of routines in tm library.
 */

#ifndef _TM_TMCDEFS

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
typedef unsigned int tmuint;
typedef unsigned long tmulong;

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _tmc_sym *tmsymbol;
typedef const struct _tmc_sym *const_tmsymbol;

typedef char *tmstring;
typedef char *tmword;
typedef const char *const_tmstring;
typedef const char *const_tmword;

struct str_Sstack {
    struct str_Sstack *next;
    struct str_sunit *ulist;
};

struct str_sunit {
    struct str_sunit *next;
    int tag;
};

struct str_tmprintstate {
    FILE *file;			/* output file */
    char *linebuf;
    int istep;			/* indent step */
    int width;			/* with of output */
    int tabwidth;		/* Width of a tab, or 0 if no tab. */
    unsigned int flags;		/* Some configuration flags */
    int braclev;		/* current bracket level */
    struct str_sunit *curlist;	/* current list of units */
    struct str_Sstack *stack;	/* stack of open constr. & lists */
};

typedef struct str_tmprintstate TMPRINTSTATE;

/* 'tmschar' functions */
#define tmscharNIL ('\0')
#define null_tmschar() tmscharNIL
#define rfre_tmschar(c)
#define fre_tmschar(c)
#define rdup_tmschar(c) (c)
#define cmp_tmschar(a,b) (a==b?0:(a<b?-1:1))
#define isequal_tmschar(a,b) (a==b)

/* 'tmuchar' functions */
#define tmucharNIL ('\0')
#define null_tmuchar() tmucharNIL
#define rfre_tmuchar(c)
#define fre_tmuchar(c)
#define rdup_tmuchar(c) (c)
#define cmp_tmuchar(a,b) (a==b?0:(a<b?-1:1))
#define isequal_tmuchar(a,b) (a==b))

/* 'tmsymbol' functions */
#define tmsymbolNIL (tmsymbol)0
#ifdef __cplusplus
// These functions are safer than the macros below, since they only accept
// tmsymbols.
inline tmsymbol rdup_tmsymbol( tmsymbol s ) { return s; }
inline void rfre_tmsymbol( tmsymbol ) {}
inline void fre_tmsymbol( tmsymbol ) { }
inline int cmp_tmsymbol(tmsymbol a, tmsymbol b) { return (a==b?0:(a<b?-1:1)); }
inline int isequal_tmsymbol(tmsymbol a, tmsymbol b) { return a==b; }
inline tmsymbol null_tmsymbol() { return tmsymbolNIL; }
#else
#define rdup_tmsymbol(s) (s)
#define rfre_tmsymbol(s)
#define fre_tmsymbol(s)
#define cmp_tmsymbol(a,b) (a==b?0:(a<b?-1:1))
#define isequal_tmsymbol(a,b) (a==b)
#define null_tmsymbol() tmsymbolNIL
#endif

/* 'double' functions */
#define rdup_double(d) (d)
#define fre_double(d)
#define rfre_double(d)
#define doubleNIL (0.0)
#define null_double() doubleNIL

/* 'float' functions */
#define rdup_float(d) (d)
#define fre_float(d)
#define rfre_float(d)
#define print_float(st,d) print_double(st,(double)d)
#define fprint_float(f,d) fprint_double(f,(double)d)
#define cmp_float(a,b) cmp_double((double) a,(double) b)
#define isequal_float(a,b) (a==b)
#define floatNIL (0.0)
#define null_float() floatNIL

/* 'tmshort' functions */
#define rdup_tmshort(i) (i)
#define fre_tmshort(i)
#define rfre_tmshort(i)
#define cmp_tmshort(a,b) ((a)-(b))
#define isequal_tmshort(a,b) ((a)==(b))
#define tmshortNIL (0)
#define null_tmshort() tmshortNIL

/* 'tmushort' functions */
#define rdup_tmushort(i) (i)
#define fre_tmushort(i)
#define rfre_tmushort(i)
#define cmp_tmushort(a,b) ((a)-(b))
#define isequal_tmushort(a,b) ((a)==(b))
#define tmushortNIL (0)
#define null_tmushort() tmushortNIL

/* 'int' functions */
#define rdup_int(i) (i)
#define fre_int(i)
#define rfre_int(i)
#define cmp_int(a,b) ((a)-(b))
#define isequal_int(a,b) ((a)==(b))
#define intNIL (0)
#define null_int() intNIL

/* 'tmuint' functions */
#define rdup_tmuint(i) (i)
#define fre_tmuint(i)
#define rfre_tmuint(i)
#define cmp_tmuint(a,b) ((a)-(b))
#define isequal_tmuint(a,b) ((a)==(b))
#define tmuintNIL (0)
#define null_tmuint() tmuintNIL

/* 'long' functions */
#define rdup_long(i) (i)
#define fre_long(i)
#define rfre_long(i)
#define cmp_long(a,b) ((a)>(b)?1:((a)<(b)?(-1):0))
#define isequal_long(a,b) ((a)==(b))
#define longNIL (0)
#define null_long() longNIL

/* 'tmulong' functions */
#define rdup_tmulong(i) (i)
#define fre_tmulong(i)
#define rfre_tmulong(i)
#define cmp_tmulong(a,b) ((a)>(b)?1:((a)<(b)?(-1):0))
#define isequal_tmulong(a,b) ((a)==(b))
#define tmulongNIL (0)
#define null_tmulong() tmulongNIL

/* 'tmword' functions */
#define cmp_tmword(a,b) strcmp(a,b)
#define isequal_tmword(a,b) (strcmp(a,b)==0)
#define tmwordNIL tmstringNIL
#define null_tmword() tmstringNIL
#define new_tmword new_tmstring
#define fre_tmword fre_tmstring
#define rdup_tmword rdup_tmstring
#define rfre_tmword rfre_tmstring
#if defined( LOGNEW )
#define fscan_tmword(f,p) fscan_tmword_lognew(f,p,__FILE__,__LINE__)
#else
#define fscan_tmword fscan_tmword_nolognew
#endif

/* 'tmstring' functions */
#define cmp_tmstring(a,b) strcmp(a,b)
#define isequal_tmstring(a,b) (strcmp(a,b)==0)
#define tmstringNIL ((tmstring)0)
#define null_tmstring() tmstringNIL
#ifndef __TM_LIBTMC_INTERN__
/* These shorthands should not be used in the library itself.
 * There should either be two versions, or one of the two
 * should be used explicitly.
 */
#if defined( LOGNEW )
#define new_tmstring(s) new_tmstring_lognew(s,__FILE__,__LINE__)
#define fscan_tmstring(f,p) fscan_tmstring_lognew(f,p,__FILE__,__LINE__)
#define fre_tmstring fre_tmstring_lognew
#define realloc_tmstring(s,sz) realloc_tmstring_lognew(s,sz,__FILE__,__LINE__)
#define create_tmstring(sz) create_tmstring_lognew(sz,__FILE__,__LINE__)
#define tmtext_to_tmstring(t) tmtext_to_tmstring_lognew(t,__FILE__,__LINE__)
#else
#define new_tmstring new_tmstring_nolognew
#define fre_tmstring fre_tmstring_nolognew
#define fscan_tmstring fscan_tmstring_nolognew
#define realloc_tmstring realloc_tmstring_nolognew
#define create_tmstring create_tmstring_nolognew
#define tmtext_to_tmstring tmtext_to_tmstring_nolognew
#endif
#if defined( LOGNEW )
#define new_tmtext() new_tmtext_lognew(__FILE__,__LINE__)
#define fscan_tmtext(f,p) fscan_tmtext_lognew(f,p,__FILE__,__LINE__)
#define string_to_tmtext(s) string_to_tmtext_lognew(s,__FILE__,__LINE__)
#define fre_tmtext fre_tmtext_lognew
#define slice_tmtext(t,from,to) slice_tmtext_lognew(t,from,to,__FILE__,__LINE__)
#define rdup_tmtext(t) rdup_tmtext_lognew(t,__FILE__,__LINE__)
#else
#define new_tmtext new_tmtext_nolognew
#define fscan_tmtext fscan_tmtext_nolognew
#define string_to_tmtext string_to_tmtext_nolognew
#define fre_tmtext fre_tmtext_nolognew
#define slice_tmtext slice_tmtext_nolognew
#define rdup_tmtext rdup_tmtext_nolognew
#endif
#endif
#define rdup_tmstring(s) new_tmstring(s)
#define rfre_tmstring fre_tmstring

/* 'tmtext' functions. */
typedef char *tmtextptr;

/* Structure for texts in memory. */
typedef struct str_tmtext {
    tmtextptr arr;
    long curpos;	/* Current read or write pointer. */
    long sz;
    long room;
    long int lognew_id;
} *tmtext;

typedef const struct str_tmtext *const_tmtext;

extern int cmp_tmtext( const const_tmtext ta, const const_tmtext tb );
#define tmtextNIL ((tmtext)0)
#define null_tmtext() tmtextNIL
extern tmtext rdup_tmtext_lognew( const tmtext t, const char *file, const int line );
extern tmtext rdup_tmtext_nolognew( const tmtext t );
#define rfre_tmtext fre_tmtext
extern void stat_tmtext( FILE *f );
extern int get_balance_tmtext( void );
extern void fre_tmtext_lognew( tmtext t );
extern void fre_tmtext_nolognew( tmtext t );
extern tmtext new_tmtext_lognew( const char *file, const int line );
extern tmtext new_tmtext_nolognew( void );
extern tmtext setroom_tmtext( tmtext t, const long rm );
extern tmtext delblock_tmtext( tmtext t, const long from, const long to );
extern tmtext replace_tmtext( tmtext t, const long from, const long to, const tmtext nw );
extern tmtext insert_tmtext( tmtext t, const long pos_parm, const tmtext nw );
extern int cmp_string_tmtext( const char *s, const tmtext t );
extern tmstring tmtext_to_tmstring_nolognew( const tmtext t );
extern tmstring tmtext_to_tmstring_lognew( const tmtext t, const char *file, const int line );
extern tmtext string_to_tmtext_lognew( const char *s, const char *file, const int line ); 
extern tmtext string_to_tmtext_nolognew( const char *s ); 
extern tmtext puts_tmtext( const char *s, tmtext t );
extern tmtext putc_tmtext( const char c, tmtext t );
extern void print_tmtext( TMPRINTSTATE *st, const tmtext t );
extern void fprint_tmtext( FILE *f, const tmtext t );
extern int fscan_tmtext_lognew( FILE *f, tmtext *s, const char *file, const int line );
extern int fscan_tmtext_nolognew( FILE *f, tmtext *s );
extern tmtext slice_tmtext_lognew( const tmtext t, const long from, const long to, const char *file, const int line );
extern tmtext slice_tmtext_nolognew( const tmtext t, const long from, const long to );

/* The functions below are undocumented. */
extern void copyblock_tmtext( tmtextptr d, const tmtextptr s, const long sz );
extern void insblock_tmtext( tmtext t, const long pos, const long sz );

/* 'tmbool' functions */
#define TMTRUESTR "True"
#define TMFALSESTR "False"
typedef enum en_tmbool { TMFALSE=0, TMTRUE=1 } tmbool;
#define new_tmbool(b) ((b)?TMTRUE:TMFALSE)
#define rdup_tmbool(b) (b)
#define fre_tmbool(b)
#define rfre_tmbool(b)
#define print_tmbool(st,b) tm_printword(st,(b)?TMTRUESTR:TMFALSESTR)
#define fprint_tmbool(f,b) fputs(((b)?TMTRUESTR:TMFALSESTR),f)
#define cmp_tmbool(a,b) ((int)a-(int)b)
#define isequal_tmbool(a,b) ((a)==(b))
#define tmboolNIL TMFALSE
#define null_tmbool() tmboolNIL

/* 'tmsymbol' functions */
extern tmsymbol find_tmsymbol( const char *name );
extern tmsymbol add_tmsymbol( const char *name );
extern tmsymbol gen_tmsymbol( const char *pre );
extern void flush_tmsymbol( void );
extern int fscan_tmsymbol( FILE *f, tmsymbol *s );
extern void print_tmsymbol( TMPRINTSTATE *st, const tmsymbol s );
extern void fprint_tmsymbol( FILE *f, const tmsymbol s );

typedef void *tm_neutralp;
extern tm_neutralp tm_malloc( size_t sz );
extern tm_neutralp tm_calloc( size_t n, size_t sz );
extern tm_neutralp tm_realloc( tm_neutralp p, size_t sz );

#ifdef __cplusplus
#define TM_MALLOC(t,n) (t) tm_malloc(n)
#define TM_CALLOC(t,sz,n) (t) tm_calloc(sz,n)
#define TM_REALLOC(t,p,n) (t) tm_realloc(p,n)
#else
#define TM_MALLOC(t,n) tm_malloc(n)
#define TM_CALLOC(t,sz,n) tm_calloc(sz,n)
#define TM_REALLOC(t,p,n) tm_realloc(p,n)
#endif
#define TM_FREE free

extern long int tm_new_logid( const char *file, const int line );
extern void tm_fre_logid( const long int id );
extern void tm_lognew( const tm_neutralp p, const char *file, const int line );
extern void tm_logfre( const tm_neutralp p );
extern void flush_lognew( void );
extern void report_lognew( FILE *f );

extern TMPRINTSTATE *tm_setprint(
    FILE *f,
    const int istep,
    const int width,
    const int tabwidth,
    const unsigned int flags
);
extern int tm_endprint( TMPRINTSTATE *st );
extern void tm_openlist( TMPRINTSTATE *st );
extern void tm_closelist( TMPRINTSTATE *st );
extern void tm_opencons( TMPRINTSTATE *st );
extern void tm_closecons( TMPRINTSTATE *st );
extern void tm_opentuple( TMPRINTSTATE *st );
extern void tm_closetuple( TMPRINTSTATE *st );
extern void tm_printword( TMPRINTSTATE *st, const char *w );

/* 'tmschar' functions. */
typedef signed char tmschar;
extern int fscan_tmschar( FILE *f, tmschar *c );
extern void print_tmschar( TMPRINTSTATE *st, const tmschar c );
extern void fprint_tmschar( FILE *f, const tmschar c );

/* 'tmuchar' functions. */
typedef unsigned char tmuchar;
extern int fscan_tmuchar( FILE *f, tmuchar *c );
extern void print_tmuchar( TMPRINTSTATE *st, const tmuchar c );
extern void fprint_tmuchar( FILE *f, const tmuchar c );

/* 'tmshort' functions. */
typedef short int tmshort;
extern int fscan_tmshort( FILE *f, tmshort *c );
extern void print_tmshort( TMPRINTSTATE *st, const tmshort c );
extern void fprint_tmshort( FILE *f, const tmshort c );

/* 'tmushort' functions. */
typedef unsigned short int tmushort;
extern int fscan_tmushort( FILE *f, tmushort *c );
extern void print_tmushort( TMPRINTSTATE *st, const tmushort c );
extern void fprint_tmushort( FILE *f, const tmushort c );

/* 'double' functions */
extern int fscan_double( FILE *f, double *d );
extern void print_double( TMPRINTSTATE *st, const double d );
extern void fprint_double( FILE *f, const double d );
extern int cmp_double( const double a, const double b );

/* 'float' functions */
extern int fscan_float( FILE *f, float *d );

/* 'int' functions */
extern int fscan_int( FILE *f, int *i );
extern void print_int( TMPRINTSTATE *st, const int i );
extern void fprint_int( FILE *f, const int i );

/* 'tmuint' functions */
extern int fscan_tmuint( FILE *f, tmuint *p );
extern void print_tmuint( TMPRINTSTATE *st, const tmuint u );
extern void fprint_tmuint( FILE *f, const tmuint u );

/* 'long' functions */
extern int fscan_long( FILE *f, long *i );
extern void print_long( TMPRINTSTATE *st, const long i );
extern void fprint_long( FILE *f, const long i );

/* 'tmulong' functions */
extern int fscan_tmulong( FILE *f, tmulong *p );
extern void print_tmulong( TMPRINTSTATE *st, const tmulong u );
extern void fprint_tmulong( FILE *f, const tmulong u );

/* 'tmword' functions */
extern int fscan_tmword_nolognew( FILE *f, tmword *s );
extern int fscan_tmword_lognew( FILE *f, tmword *p, const char *file, const int line );
extern void print_tmword( TMPRINTSTATE *st, const const_tmword s );
extern void fprint_tmword( FILE *f, const const_tmword s );

/* 'tmstring' functions */
extern tmstring realloc_tmstring_nolognew( tmstring s, const size_t sz );
extern tmstring realloc_tmstring_lognew( tmstring s, const size_t sz, const char *file, const int line );
extern tmstring create_tmstring_nolognew( const size_t sz );
extern tmstring create_tmstring_lognew( const size_t sz, const char *file, const int line );
extern tmstring new_tmstring_lognew( const char *s, const char *file, const int line );
extern void fre_tmstring_lognew( tmstring s );
extern int fscan_tmstring_lognew( FILE *f, tmstring *p, const char *file, const int line );
extern tmstring new_tmstring_nolognew( const char *s );
extern void fre_tmstring_nolognew( tmstring s );
extern int fscan_tmstring_nolognew( FILE *f, tmstring *p );
extern void print_tmstring( TMPRINTSTATE *st, const_tmstring s );
extern void fprint_tmstring( FILE *f, const_tmstring s );
extern void stat_tmstring( FILE *f );
extern int get_balance_tmstring( void );

/* 'tmtext' functions */
extern tmbool isequal_tmtext( const const_tmtext ta, const const_tmtext tb );

/* 'tmbool' functions */
extern int fscan_tmbool( FILE *f, tmbool *bp );

/* General low-level service functions */
extern int tm_fscanopenbrac( FILE *f );
extern int tm_fscanclosebrac( FILE *f, const int n );
extern int tm_fneedc( FILE *f, int c );
extern int tm_fscancons( FILE *f, char *s, const int sz );
extern int tm_fscanspace( FILE *f );
extern const char *tm_escapestring( const unsigned int code );
extern int tm_fscanescapedchar( FILE *f, int *code );

extern void tm_fatal( const char *file, const int line, const char *s );
extern void tm_badtag( const char *file, const int line, const int tag );
extern void tm_noroom( void );

/* Storage for a tmsymbol string */
struct _tmc_sym {
    struct _tmc_sym *next;		/* next in list */
    const_tmstring name;		/* pointer to the string */
#ifdef __cplusplus
    mutable tm_neutralp data;		/* any info for it. */
#else
    tm_neutralp data;			/* any info for it. */
#endif
};

/* the error message buffer of tm and its length */
extern char tm_errmsg[];
#define TM_ERRLEN 100
extern int tm_lineno;

#ifdef __cplusplus
} /* Closing bracket for 'extern "C" {' */
#endif

#define _TM_TMCDEFS 1
#endif
