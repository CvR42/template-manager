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
#if defined( _AIX ) && defined( _ALL_SOURCE )
#include <sys/types.h>
#define GOT_UINT
#endif
#if defined( __linux__ )
#include <linux/types.h>
#define GOT_UINT
#endif

#ifndef GOT_UINT
typedef unsigned int uint;
typedef unsigned long ulong;
#define GOT_UINT
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _tmc_sym *tmsymbol;

typedef char *tmstring;

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

/* 'schar' functions */
#define scharNIL ('\0')
#define null_schar() scharNIL
#define rfre_schar(c)
#define fre_schar(c)
#define rdup_schar(c) (c)
#define cmp_schar(a,b) (a==b?0:(a<b?-1:1))

/* 'uchar' functions */
#define ucharNIL ('\0')
#define null_uchar() ucharNIL
#define rfre_uchar(c)
#define fre_uchar(c)
#define rdup_uchar(c) (c)
#define cmp_uchar(a,b) (a==b?0:(a<b?-1:1))

/* 'tmsymbol' functions */
#define tmsymbolNIL (tmsymbol)0
#define null_tmsymbol() tmsymbolNIL
#define rfre_tmsymbol(s)
#define fre_tmsymbol(s)
#define rdup_tmsymbol(s) (s)
#define cmp_tmsymbol(a,b) (a==b?0:(a<b?-1:1))

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
#define floatNIL (0.0)
#define null_float() floatNIL

/* 'sshrt' functions */
#define rdup_sshrt(i) (i)
#define fre_sshrt(i)
#define rfre_sshrt(i)
#define cmp_sshrt(a,b) ((a)-(b))
#define sshrtNIL (0)
#define null_sshrt() sshrtNIL

/* 'ushrt' functions */
#define rdup_ushrt(i) (i)
#define fre_ushrt(i)
#define rfre_ushrt(i)
#define cmp_ushrt(a,b) ((a)-(b))
#define ushrtNIL (0)
#define null_ushrt() ushrtNIL

/* 'int' functions */
#define rdup_int(i) (i)
#define fre_int(i)
#define rfre_int(i)
#define cmp_int(a,b) ((a)-(b))
#define intNIL (0)
#define null_int() intNIL

/* 'uint' functions */
#define rdup_uint(i) (i)
#define fre_uint(i)
#define rfre_uint(i)
#define cmp_uint(a,b) ((a)-(b))
#define uintNIL (0)
#define null_uint() uintNIL

/* 'long' functions */
#define rdup_long(i) (i)
#define fre_long(i)
#define rfre_long(i)
#define cmp_long(a,b) ((a)>(b)?1:((a)<(b)?(-1):0))
#define longNIL (0)
#define null_long() longNIL

/* 'ulong' functions */
#define rdup_ulong(i) (i)
#define fre_ulong(i)
#define rfre_ulong(i)
#define cmp_ulong(a,b) ((a)>(b)?1:((a)<(b)?(-1):0))
#define ulongNIL (0)
#define null_ulong() ulongNIL

/* 'tmstring' functions */
#define cmp_tmstring(a,b) strcmp(a,b)
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
#define tmtext_to_tmstring(t) tmtext_to_tmstring_lognew(t,__FILE__,__LINE__)
#else
#define new_tmstring new_tmstring_nolognew
#define fre_tmstring fre_tmstring_nolognew
#define fscan_tmstring fscan_tmstring_nolognew
#define realloc_tmstring realloc_tmstring_nolognew
#define tmtext_to_tmstring tmtext_to_tmstring_nolognew
#endif
#ifdef LOGNEW
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

extern int cmp_tmtext( const tmtext ta, const tmtext tb );
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

/* 'schar' functions. */
typedef signed char schar;
extern int fscan_schar( FILE *f, schar *c );
extern void print_schar( TMPRINTSTATE *st, const schar c );
extern void fprint_schar( FILE *f, const schar c );

/* 'uchar' functions. */
#if !defined( _AIX ) || !defined( _ALL_SOURCE )
typedef unsigned char uchar;
#endif
extern int fscan_uchar( FILE *f, uchar *c );
extern void print_uchar( TMPRINTSTATE *st, const uchar c );
extern void fprint_uchar( FILE *f, const uchar c );

/* 'sshrt' functions. */
typedef short int sshrt;
extern int fscan_sshrt( FILE *f, sshrt *c );
extern void print_sshrt( TMPRINTSTATE *st, const sshrt c );
extern void fprint_sshrt( FILE *f, const sshrt c );

/* 'ushrt' functions. */
typedef unsigned short int ushrt;
extern int fscan_ushrt( FILE *f, ushrt *c );
extern void print_ushrt( TMPRINTSTATE *st, const ushrt c );
extern void fprint_ushrt( FILE *f, const ushrt c );

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

/* 'uint' functions */
extern int fscan_uint( FILE *f, uint *p );
extern void print_uint( TMPRINTSTATE *st, const uint u );
extern void fprint_uint( FILE *f, const uint u );

/* 'long' functions */
extern int fscan_long( FILE *f, long *i );
extern void print_long( TMPRINTSTATE *st, const long i );
extern void fprint_long( FILE *f, const long i );

/* 'ulong' functions */
extern int fscan_ulong( FILE *f, ulong *p );
extern void print_ulong( TMPRINTSTATE *st, const ulong u );
extern void fprint_ulong( FILE *f, const ulong u );

/* 'tmstring' functions */
extern tmstring realloc_tmstring_nolognew( tmstring s, const size_t sz );
extern tmstring realloc_tmstring_lognew( tmstring s, const size_t sz, const char *file, const int line );
extern tmstring new_tmstring_lognew( const char *s, const char *file, const int line );
extern void fre_tmstring_lognew( tmstring s );
extern int fscan_tmstring_lognew( FILE *f, tmstring *p, const char *file, const int line );
extern tmstring new_tmstring_nolognew( const char *s );
extern void fre_tmstring_nolognew( tmstring s );
extern int fscan_tmstring_nolognew( FILE *f, tmstring *p );
extern void print_tmstring( TMPRINTSTATE *st, const tmstring s );
extern void fprint_tmstring( FILE *f, const tmstring s );
extern void stat_tmstring( FILE *f );
extern int get_balance_tmstring( void );

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
    tmstring name;			/* pointer to the string */
    tm_neutralp data;			/* any info for it. */
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