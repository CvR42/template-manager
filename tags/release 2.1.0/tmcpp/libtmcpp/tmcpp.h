// file: tmcpp.h
//
// declaration of routines in tm library.

#ifndef _TM_TMCDEFS

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
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

// allocid memory leak tracking tools
// tm_report_allocid is a dummy function. Provide your own, and
// put a breakpoint in it.
extern void tm_report_allocid( const unsigned long id );
extern void tm_register_new_allocid( const unsigned long id );
extern void tm_register_free_allocid( const unsigned long id );
extern unsigned long int tm_allocid_next;
extern void tm_list_pending_ids( FILE *f );

typedef class _tmc_sym *tmsymbol;

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

class TmPrintState {
private:
    FILE *file;			// output file
    char *linebuf;
    int istep;			// indent step
    int width;			// with of output
    int tabwidth;		// Width of a tab, or 0 if no tab.
    unsigned int flags;		// Some configuration flags
    int braclev;		// current bracket level
    struct str_sunit *curlist;	// current list of units
    struct str_Sstack *stack;	// stack of open constr. & lists

private:
    void pushLevel();
    void popLevel();
    void doIndent( const int n );
    void vertPrintConstructor( struct str_sunit * c, const int lev );
    void vertPrintList( struct str_sunit * c, const int lev );
    void vertPrintTuple( struct str_sunit * c, const int lev );
    void vertPrintSunit( struct str_sunit * l, const int lev );
    tmstring horPrintList( struct str_sunit * l );
    tmstring horPrintConstructor( struct str_sunit *l );
    tmstring horPrintTuple( struct str_sunit *l );

public:
    TmPrintState(
	FILE *f,
	const int istep = 4,
	const int width = 74,
	const int tabwidth = 8,
	const unsigned int flags=0
    );
    virtual ~TmPrintState();
    virtual void destroy() { delete this; }
    inline int getLevel() const { return braclev; }
    void openList();
    void closeList();
    void openConstructor();
    void closeConstructor();
    void openTuple();
    void closeTuple();
    void printWord( const char *w );
};

// 'schar' functions
#define scharNIL ('\0')

// 'uchar' functions
#define ucharNIL ('\0')

// 'tmsymbol' functions
#define tmsymbolNIL (tmsymbol)0

// 'double' functions
#define doubleNIL (0.0)

// 'float' functions
#define print_float(st,d) print_double(st,(double)d)
#define fprint_float(f,d) fprint_double(f,(double)d)
#define floatNIL (0.0)

// 'sshrt' functions
#define sshrtNIL (0)

// 'ushrt' functions
#define ushrtNIL (0)

// 'int' functions
inline int compare( const int a, const int b ) { return ((a)-(b)); }
#define intNIL (0)

// 'uint' functions
inline int compare( const uint a, const uint b ) { return ((a)>(b)?1:((a)<(b)?(-1):0)); }
#define uintNIL (0)

// 'long' functions
inline int compare( const long a, const long b ) { return ((a)>(b)?1:((a)<(b)?(-1):0)); }
#define longNIL (0)

// 'ulong' functions
inline int compare( const ulong a, const ulong b ) { return ((a)>(b)?1:((a)<(b)?(-1):0)); }
#define ulongNIL (0)

// 'tmword' functions
#define tmwordNIL tmstringNIL
#define new_tmword new_tmstring
#define fre_tmword fre_tmstring
#define rfre_tmword fre_tmstring

// 'tmstring' functions
inline int compare( const tmstring a, const tmstring b ) { return strcmp(a,b); }
#define tmstringNIL ((tmstring)0)


// Structure for texts in memory.
class tmtext {
public:
    typedef long size_type;

private:
    static unsigned long newcount;
    static unsigned long freecount;
    size_type room;

public:
    char *arr;
    size_type curpos;	// Current read or write pointer.
    size_type sz;

private:
    unsigned long __id;

private:
    static void copyblock( char *d, const char *s, const size_type sz );
    void insblock( const size_type pos, const size_type sz );
    void settext( const tmtext &c );
    void setstring( const char *s );

#ifdef LOGNEW
    inline void allocid_admin()
    {
	__id = tm_allocid_next++;
	tm_register_new_allocid( __id );
        tm_report_allocid( __id );
    }
#else
    inline void allocid_admin() {}
#endif

public:
    inline size_type size() const { return sz; }
    inline size_type capacity() const { return room; }

    tmtext( const size_type sz=32 ): room(0), arr(0), curpos(0), sz(0), __id(0) {
	reserve( sz );
	allocid_admin();
	newcount++;
    }
    tmtext( const tmtext &c ): room(0), arr(0), curpos(0), sz(0), __id(0) {
	settext(c);
	allocid_admin();
	newcount++;
    }
    tmtext( const char *s ): room(0), arr(0), curpos(0), sz(0), __id(0) {
	append( s );
	curpos = 0;
	allocid_admin();
	newcount++;
    }
#ifdef LOGNEW
    virtual ~tmtext() { tm_register_free_allocid( __id ); free( arr ); freecount++; }
#else
    virtual ~tmtext() { free( arr ); freecount++; }
#endif
    inline static void reportAllocId( FILE *f ) { (void) f; }

    void reserve( const size_type rm );
    virtual tmtext *clone() const { return new tmtext( *this ); }
    tmtext *insert( const size_type pos, const tmtext *nw );
    tmtext *insert( const size_type pos, const char *s );
    tmtext *insert( const size_type pos, const char c );
    tmtext *append( const tmtext *nw );
    tmtext *append( const char *s );
    tmtext *append( const char c );
    tmtext *erase( const size_type from, const size_type to = LONG_MAX );
    inline tmtext *erase() { sz=0; curpos=0; return this; }
    virtual void destroy() { delete this; }
    tmtext *slice( const size_type from, const size_type to ) const;
    tmtext *replace( const size_type from, const size_type to, const tmtext *nw );
    tmtext *replace( const size_type from, const size_type to, const tmtext *nw, const size_type nw_from, const size_type nw_to );
    static void stat( FILE *f );
    static int get_balance();
    const char *c_str() { reserve( sz+1 ); arr[sz] = 0; return arr; }
};

extern int compare( const tmtext &, const tmtext & );

#define tmtextNIL ((tmtext *)0)
extern int cmp_string_tmtext( const char *s, const tmtext *t );
extern tmstring tmtext_to_tmstring_nolognew( const tmtext *t );
extern tmstring tmtext_to_tmstring_lognew( const tmtext *t, const char *file, const int line );
extern tmtext *puts_tmtext( const char *s, tmtext *t );
extern tmtext *putc_tmtext( const char c, tmtext *t );
extern void print_tmtext( TmPrintState *st, const tmtext *t );
extern void fprint_tmtext( FILE *f, const tmtext *t );
extern int fscan_tmtext( FILE *f, tmtext **s );

// The functions below are undocumented.

// 'bool' functions
#define new_bool(b) ((b)!=0)
#define print_bool(st,b) (st->printWord((b)?"true":"false"))
#define fprint_bool(f,b) fputs(((b)?"true":"false"),f)
inline int compare( const bool a, const bool b ) { return ((int)a-(int)b); }
#define boolNIL false

// 'tmsymbol' functions
extern tmsymbol find_tmsymbol( const char *name );
extern tmsymbol add_tmsymbol( const char *name );
extern tmsymbol gen_tmsymbol( const char *pre );
extern void flush_tmsymbol();
extern int fscan_tmsymbol( FILE *f, tmsymbol *s );
extern void print_tmsymbol( TmPrintState *st, const tmsymbol s );
extern void fprint_tmsymbol( FILE *f, const tmsymbol s );
inline int compare( const tmsymbol a, const tmsymbol b ) { return (a==b?0:(a<b?-1:1)); }

typedef void *tm_neutralp;
extern tm_neutralp tm_malloc( size_t sz );
extern tm_neutralp tm_calloc( size_t n, size_t sz );
extern tm_neutralp tm_realloc( tm_neutralp p, size_t sz );

// 'schar' functions.
typedef signed char schar;
extern int fscan_schar( FILE *f, schar *c );
extern void print_schar( TmPrintState *st, const schar c );
extern void fprint_schar( FILE *f, const schar c );
inline int compare( const schar a, const schar b ) { return (a==b?0:(a<b?-1:1)); }

// 'uchar' functions.
#if !defined( _AIX ) || !defined( _ALL_SOURCE )
typedef unsigned char uchar;
#endif
extern int fscan_uchar( FILE *f, uchar *c );
extern void print_uchar( TmPrintState *st, const uchar c );
extern void fprint_uchar( FILE *f, const uchar c );
inline int compare( const uchar a, const uchar b ) { return (a==b?0:(a<b?-1:1)); }

// 'sshrt' functions.
typedef short int sshrt;
extern int fscan_sshrt( FILE *f, sshrt *c );
extern void print_sshrt( TmPrintState *st, const sshrt c );
extern void fprint_sshrt( FILE *f, const sshrt c );
inline int compare( const sshrt a, const sshrt b ) { return (a==b?0:(a<b?-1:1)); };

// 'ushrt' functions.
typedef unsigned short int ushrt;
extern int fscan_ushrt( FILE *f, ushrt *c );
extern void print_ushrt( TmPrintState *st, const ushrt c );
extern void fprint_ushrt( FILE *f, const ushrt c );
inline int compare( const ushrt a, const ushrt b ) { return (a==b?0:(a<b?-1:1)); };

// 'double' functions
extern int fscan_double( FILE *f, double *d );
extern void print_double( TmPrintState *st, const double d );
extern void fprint_double( FILE *f, const double d );
extern int compare( const double a, const double b );

// 'float' functions
extern int fscan_float( FILE *f, float *d );
inline int compare( const float a, const float b ) { return (a==b?0:(a<b?-1:1)); }

// 'int' functions
extern int fscan_int( FILE *f, int *i );
extern void print_int( TmPrintState *st, const int i );
extern void fprint_int( FILE *f, const int i );

// 'uint' functions
extern int fscan_uint( FILE *f, uint *p );
extern void print_uint( TmPrintState *st, const uint u );
extern void fprint_uint( FILE *f, const uint u );

// 'long' functions
extern int fscan_long( FILE *f, long *i );
extern void print_long( TmPrintState *st, const long i );
extern void fprint_long( FILE *f, const long i );

// 'ulong' functions
extern int fscan_ulong( FILE *f, ulong *p );
extern void print_ulong( TmPrintState *st, const ulong u );
extern void fprint_ulong( FILE *f, const ulong u );

// 'tmword' functions
extern int fscan_tmword( FILE *f, tmword *s );
extern void print_tmword( TmPrintState *st, const tmconstword s );
extern void fprint_tmword( FILE *f, const tmconstword s );

// 'tmstring' functions
extern tmstring realloc_tmstring_nolognew( tmstring s, const size_t sz );
extern tmstring realloc_tmstring_lognew( tmstring s, const size_t sz, const char *file, const int line );
extern tmstring realloc_tmstring( tmstring s, const size_t sz );
extern tmstring create_tmstring_nolognew( const size_t sz );
extern tmstring create_tmstring_lognew( const size_t sz, const char *file, const int line );
extern tmstring new_tmstring_nolognew( const char *s );
extern tmstring new_tmstring_lognew( const char *s, const char *file, const int line );
extern void fre_tmstring_lognew( tmstring s );
extern void fre_tmstring_nolognew( tmstring s );
extern int fscan_tmstring_nolognew( FILE *f, tmstring *p );
extern int fscan_tmstring_lognew( FILE *f, tmstring *s, const char *file, const int line );
extern void print_tmstring( TmPrintState *st, tmconststring s );
extern void fprint_tmstring( FILE *f, tmconststring s );
extern void stat_tmstring( FILE *f );
extern int get_balance_tmstring();
#define rfre_tmstring fre_tmstring
#define rdup_tmstring new_tmstring

#ifdef LOGNEW
#define tmtext_to_tmstring(s) tmtext_to_tmstring_lognew(s,__FILE__,__LINE__)
#define realloc_tmstring(s,n) realloc_tmstring_lognew(s,n,__FILE__,__LINE__)
#define new_tmstring(s) new_tmstring_lognew(s,__FILE__,__LINE__)
#define fscan_tmstring(f,p) fscan_tmstring_lognew(f,p,__FILE__,__LINE__)
#define create_tmstring(n) create_tmstring_lognew(n,__FILE__,__LINE__)
#define fre_tmstring fre_tmstring_lognew
#else
#define tmtext_to_tmstring(s) tmtext_to_tmstring_nolognew(s)
#define realloc_tmstring(s,n) realloc_tmstring_nolognew(s,n)
#define new_tmstring(s) new_tmstring_nolognew(s)
#define fscan_tmstring(f,p) fscan_tmstring_nolognew(f,p)
#define create_tmstring(n) create_tmstring_nolognew(n)
#define fre_tmstring fre_tmstring_nolognew
#endif

// 'bool' functions
extern int fscan_bool( FILE *f, bool *bp );

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

// Storage for a symbol string
class _tmc_sym {
public:
    class _tmc_sym *next;		// Next in list
    tmconststring name;			// Pointer to the string
    tm_neutralp data;			// Any info for it.
};

// the error message buffer of Tm and its length
extern char tm_errmsg[];
#define TM_ERRLEN 100
extern int tm_lineno;

// Lognew interface
extern void tm_lognew( const tm_neutralp p, const char *file, const int line );
extern void tm_logfre( const tm_neutralp p );
extern void report_lognew( FILE *f );
extern void flush_lognew();

#define _TM_TMCDEFS 1
#endif
