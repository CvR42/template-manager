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
#ifdef __KERNEL_STRICT_NAMES
typedef unsigned int uint;
typedef unsigned long ulong;
#endif
#define GOT_UINT
#endif

#ifndef GOT_UINT
typedef unsigned int uint;
typedef unsigned long ulong;
#define GOT_UINT
#endif

typedef struct _tmc_sym *tmsymbol;

typedef char *tmstring;
typedef char *tmword;
typedef const char *tmconststring;
typedef const char *tmconstword;

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
#define rfre_schar(c)
#define fre_schar(c)
#define rdup_schar(c) (c)
#define cmp_schar(a,b) (a==b?0:(a<b?-1:1))

// 'uchar' functions
#define ucharNIL ('\0')
#define rfre_uchar(c)
#define fre_uchar(c)
#define rdup_uchar(c) (c)
#define cmp_uchar(a,b) (a==b?0:(a<b?-1:1))

// 'tmsymbol' functions
#define tmsymbolNIL (tmsymbol)0
#define rfre_tmsymbol(s)
#define fre_tmsymbol(s)
#define rdup_tmsymbol(s) (s)
#define cmp_tmsymbol(a,b) (a==b?0:(a<b?-1:1))

// 'double' functions
#define rdup_double(d) (d)
#define fre_double(d)
#define rfre_double(d)
#define doubleNIL (0.0)

// 'float' functions
#define rdup_float(d) (d)
#define fre_float(d)
#define rfre_float(d)
#define print_float(st,d) print_double(st,(double)d)
#define fprint_float(f,d) fprint_double(f,(double)d)
#define cmp_float(a,b) cmp_double((double) a,(double) b)
#define floatNIL (0.0)

// 'sshrt' functions
#define rdup_sshrt(i) (i)
#define fre_sshrt(i)
#define rfre_sshrt(i)
#define cmp_sshrt(a,b) ((a)-(b))
#define sshrtNIL (0)

// 'ushrt' functions
#define rdup_ushrt(i) (i)
#define fre_ushrt(i)
#define rfre_ushrt(i)
#define cmp_ushrt(a,b) ((a)-(b))
#define ushrtNIL (0)

/* 'int' functions */
#define rdup_int(i) (i)
#define fre_int(i)
#define rfre_int(i)
#define cmp_int(a,b) ((a)-(b))
#define intNIL (0)

/* 'uint' functions */
#define rdup_uint(i) (i)
#define fre_uint(i)
#define rfre_uint(i)
#define cmp_uint(a,b) ((a)-(b))
#define uintNIL (0)

/* 'long' functions */
#define rdup_long(i) (i)
#define fre_long(i)
#define rfre_long(i)
#define cmp_long(a,b) ((a)>(b)?1:((a)<(b)?(-1):0))
#define longNIL (0)

/* 'ulong' functions */
#define rdup_ulong(i) (i)
#define fre_ulong(i)
#define rfre_ulong(i)
#define cmp_ulong(a,b) ((a)>(b)?1:((a)<(b)?(-1):0))
#define ulongNIL (0)

/* 'tmword' functions */
#define cmp_tmword(a,b) strcmp(a,b)
#define tmwordNIL tmstringNIL
#define new_tmword new_tmstring
#define fre_tmword fre_tmstring
#define rdup_tmword rdup_tmstring
#define rfre_tmword rfre_tmstring

// 'tmstring' functions
#define cmp_tmstring(a,b) strcmp(a,b)
#define tmstringNIL ((tmstring)0)
#define rdup_tmstring(s) new_tmstring(s)
#define rfre_tmstring fre_tmstring


// Structure for texts in memory.
class tmtext {
private:
    static unsigned long newcount;
    static unsigned long freecount;

public:
    char *arr;
    mutable long curpos;	// Current read or write pointer.
    long sz;
    long room;

    tmtext( const long sz=32 );
    tmtext( const tmtext &c );
    tmtext( const char *s );
    virtual ~tmtext();
    void reserve( const long rm );
    virtual tmtext *clone() const { return new tmtext( *this ); }
    virtual void destroy() { delete this; }
    static void stat( FILE *f );
    static int get_balance();
};

extern int cmp_tmtext( const tmtext *ta, const tmtext *tb );
#define tmtextNIL ((tmtext *)0)
extern tmtext *delblock_tmtext( tmtext *t, const long from, const long to );
extern tmtext *replace_tmtext( tmtext *t, const long from, const long to, const tmtext *nw );
extern tmtext *insert_tmtext( tmtext *t, const long pos_parm, const tmtext *nw );
extern int cmp_string_tmtext( const char *s, const tmtext *t );
extern tmstring tmtext_to_tmstring( const tmtext *t );
extern tmtext *puts_tmtext( const char *s, tmtext *t );
extern tmtext *putc_tmtext( const char c, tmtext *t );
extern void print_tmtext( TMPRINTSTATE *st, const tmtext *t );
extern void fprint_tmtext( FILE *f, const tmtext *t );
extern int fscan_tmtext( FILE *f, tmtext **s );
extern tmtext *slice_tmtext( const tmtext *t, const long from, const long to );

/* The functions below are undocumented. */
extern void copyblock_tmtext( char *d, const char *s, const long sz );
extern void insblock_tmtext( tmtext *t, const long pos, const long sz );

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

/* 'tmsymbol' functions */
extern tmsymbol find_tmsymbol( const char *name );
extern tmsymbol add_tmsymbol( const char *name );
extern tmsymbol gen_tmsymbol( const char *pre );
extern void flush_tmsymbol();
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

// 'long' functions
extern int fscan_long( FILE *f, long *i );
extern void print_long( TMPRINTSTATE *st, const long i );
extern void fprint_long( FILE *f, const long i );

// 'ulong' functions
extern int fscan_ulong( FILE *f, ulong *p );
extern void print_ulong( TMPRINTSTATE *st, const ulong u );
extern void fprint_ulong( FILE *f, const ulong u );

// 'tmword' functions
extern int fscan_tmword( FILE *f, tmword *s );
extern void print_tmword( TMPRINTSTATE *st, const tmconstword s );
extern void fprint_tmword( FILE *f, const tmconstword s );

// 'tmstring' functions
extern tmstring realloc_tmstring( tmstring s, const size_t sz );
extern tmstring create_tmstring( const size_t sz );
extern tmstring new_tmstring( const char *s );
extern void fre_tmstring( tmstring s );
extern int fscan_tmstring( FILE *f, tmstring *p );
extern void print_tmstring( TMPRINTSTATE *st, tmconststring s );
extern void fprint_tmstring( FILE *f, tmconststring s );
extern void stat_tmstring( FILE *f );
extern int get_balance_tmstring();

// 'tmbool' functions
extern int fscan_tmbool( FILE *f, tmbool *bp );

// General low-level service functions
extern int tm_fscanopenbrac( FILE *f );
extern int tm_fscanclosebrac( FILE *f, const int n );
extern int tm_fneedc( FILE *f, int c );
extern int tm_fscancons( FILE *f, char *s, const int sz );
extern int tm_fscanspace( FILE *f );
extern const char *tm_escapestring( const unsigned int code );
extern int tm_fscanescapedchar( FILE *f, int *code );

extern void tm_fatal( const char *file, const int line, const char *s );
extern void tm_badtag( const char *file, const int line, const int tag );
extern void tm_noroom();

// Storage for a tmsymbol string
class _tmc_sym {
public:
    struct _tmc_sym *next;		/* next in list */
    tmconststring name;			/* pointer to the string */
    tm_neutralp data;			/* any info for it. */
};

// the error message buffer of tm and its length
extern char tm_errmsg[];
#define TM_ERRLEN 100
extern int tm_lineno;

class TmInt {
public:
    int n;

    inline TmInt( int nn ) { n = nn; }
    inline TmInt( TmInt &c ) { n = c.n; }
    inline virtual ~TmInt() {}
    inline TmInt print( TMPRINTSTATE * );
    inline TmInt fprint( FILE * );
};

#define _TM_TMCDEFS 1
#endif
