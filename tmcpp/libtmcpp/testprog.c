/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: testprog.c
 *
 * Test of library programs.
 */

#include "config.h"
#include "tmcpp.h"

#define TESTARRAYSIZE 13000

/* The file handle for the input and output file. */
FILE *infile;
FILE *outfile;

static void bad( const char *msg )
{
   fprintf( stderr, "check error: %s\n", msg );
   exit( 1 );
}

// test_printopt: test printopt routines
static void test_printopt( TmPrintState *st )
{
    int k;
    int i;
    int j;

    st->openList();
    st->closeList();
    st->openTuple();
    st->printWord( "tuple1" );
    st->printWord( "24" );
    st->closeTuple();
    st->openConstructor();
    st->printWord( "Cons1" );
    st->closeConstructor();
    for( k=0; k<12; k+=3 ){
	st->openConstructor();
	st->printWord( "Cons2" );
	st->openConstructor();
	st->printWord( "Cons3" );
	for( i=1; i<k; i++ ){
	    st->openList();
	    for( j=0; j<i; j++ ){
		st->printWord( "42" );
	    }
	    st->closeList();
	}
	st->closeConstructor();
	st->openTuple();
	st->printWord( "tuple" );
	for( i=1; i<k; i++ ){
	    st->openList();
	    for( j=0; j<i; j++ ){
		st->printWord( "42" );
	    }
	    st->closeList();
	}
	st->closeTuple();
	st->closeConstructor();
    }
    st->printWord( "Top" );
    st->printWord( "level" );
    st->printWord( "tm_printword()." );
}

/* Test of tm_fscanopenbrac() and tm_fscanclosebrac().
 * Read open brackets and match with close brackets until
 * a group of 0 pairs is encountered. Write the brackets
 * to the output file with the st->openConstructor() and st->closeConstructor()
 * functions.
 */
static void test_brac( TmPrintState *st )
{
    int bracs;
    int i;

    do{
	bracs = tm_fscanopenbrac( infile );
	for( i=0; i<bracs; i++ ){
	    st->openConstructor();
	    st->printWord( "Bractest" );
	    st->printWord( "42" );
	}
	if( tm_fscanclosebrac( infile, bracs ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	for( i=0; i<bracs; i++ ){
	    st->closeConstructor();
	}
    } while( bracs != 0 );
}

/* Test of tm_fscancons(). Read and write constructors until one
   with name "StopFscanCons" is encountered.
 */
static void test_cons( TmPrintState *st )
{
    char buf[1000];

    st->openConstructor();
    st->printWord( "Constest" );
    st->openList();
    do{
	if( tm_fscancons( infile, buf, 1000 ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
            exit( 1 );
	}
	st->printWord( buf );
    } while( strcmp( buf, "StopFscanCons" ) != 0 );
    st->closeList();
    st->closeConstructor();
}

/* Test of print_ulong() and fscan_ulong(): read and write
   long's until one with value 42 is encountered.
 */
static void test_ulong( TmPrintState *st )
{
    ulong ul;

    st->openConstructor();
    st->printWord( "Ulongtest" );
    do {
	if( fscan_ulong( infile, &ul ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_ulong( st, ul );
    } while( ul != 42 );
    st->closeConstructor();
}

/* Test of print_long() and fscan_long(): read and write
   long's until one with value 42 is encountered.
 */
static void test_long( TmPrintState *st )
{
    long l;

    st->openConstructor();
    st->printWord( "Longtest" );
    do {
	if( fscan_long( infile, &l ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_long( st, l );
    } while( l != 42 );
    st->closeConstructor();
}

/* Test of print_sshrt() and fscan_sshrt(): read and write sshrt's until
   one with value -1 is encountered.
 */
static void test_sshrt( TmPrintState *st )
{
    sshrt i;

    st->openConstructor();
    st->printWord( "Sshrttest" );
    do {
	if( fscan_sshrt( infile, &i ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_sshrt( st, i );
    } while( i != -1 );
    st->closeConstructor();
}

/* Test of print_ushrt() and fscan_ushrt(): read and write
   unsigned's until one with value 42 is encountered.
 */
static void test_ushrt( TmPrintState *st )
{
    ushrt u;

    st->openConstructor();
    st->printWord( "Ushrttest" );
    do {
	if( fscan_ushrt( infile, &u ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_ushrt( st, u );
    } while( u != 42 );
    st->closeConstructor();
}

/* Test of print_int() and fscan_int(): read and write int's until
   one with value -1 is encountered.
 */
static void test_int( TmPrintState *st )
{
    int i;

    st->openConstructor();
    st->printWord( "Inttest" );
    do {
	if( fscan_int( infile, &i ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_int( st, i );
    } while( i != -1 );
    st->closeConstructor();
}

/* Test of print_uint() and fscan_uint(): read and write
   unsigned's until one with value 42 is encountered.
 */
static void test_uint( TmPrintState *st )
{
    uint u;

    st->openConstructor();
    st->printWord( "Unsignedtest" );
    do {
	if( fscan_uint( infile, &u ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_uint( st, u );
    } while( u != 42 );
    st->closeConstructor();
}

/* Test of print_schar() and fscan_schar(): read and write schar's until
   one with value 'q' is encountered.
 */
static void test_schar( TmPrintState *st )
{
    schar c;

    st->openConstructor();
    st->printWord( "Schartest" );
    do {
	if( fscan_schar( infile, &c ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_schar( st, c );
    } while( c != 'q' );
    st->closeConstructor();
}

/* Test of print_uchar() and fscan_uchar(): read and write uchar's until
   one with value 'q' is encountered.
 */
static void test_uchar( TmPrintState *st )
{
    uchar c;

    st->openConstructor();
    st->printWord( "Uchartest" );
    do {
	if( fscan_uchar( infile, &c ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_uchar( st, c );
    } while( c != 'q' );
    st->closeConstructor();
}

/* test cmp_double() */
static void test_double( void )
{
    int res;
    double a = 1.2e3;

    res = cmp_double( (double) 1.0, (double) -1.0 );
    if( res <= 0 ){
	fprintf(
	    stderr,
	    "*** Error: cmp_double( (double) 1.0, (double) -1.0 ) = %d\n",
	    res
	);
    }
    res = cmp_double( (double) -42.0, (double) -1.0 );
    if( res >= 0 ){
	fprintf(
	    stderr,
	    "*** Error: cmp_double( (double) -42.0, (double) -1.0 ) = %d\n",
	    res
	);
    }
    res = cmp_double( a, a );
    if( res != 0 ){
	fprintf(
	    stderr,
	    "*** Error: cmp_double( a , a ) = %d\n",
	    res
	);
    }
}

/* test cmp_float() */
static void test_float( void )
{
    int res;
    float a = 1.2e3;

    res = cmp_float( (float) 1.0, (float) -1.0 );
    if( res <= 0 ){
	fprintf(
	    stderr,
	    "*** Error: cmp_float( (float) 1.0, (float) -1.0 ) = %d\n",
	    res
	);
    }
    res = cmp_float( (float) -42.0, (float) -1.0 );
    if( res >= 0 ){
	fprintf(
	    stderr,
	    "*** Error: cmp_float( (float) -42.0, (float) -1.0 ) = %d\n",
	    res
	);
    }
    res = cmp_float( a, a );
    if( res != 0 ){
	fprintf(
	    stderr,
	    "*** Error: cmp_float( a , a ) = %d\n",
	    res
	);
    }
}

static void test_tmstring( TmPrintState *st )
{
    tmstring s;
    int stop;
    int i;
    tmstring sbuf[10];

    for( i=0; i<10; i++ ){
	sbuf[i] = new_tmstring( "testing 1,2,3...." );
    }
    for( i=0; i<10; i++ ){
	fre_tmstring( sbuf[i] );
    }
    st->openConstructor();
    st->printWord( "Stringouttest" );
    print_tmstring( st, "" );
    print_tmstring( st, "Test" );
    st->closeConstructor();
    st->openConstructor();
    st->printWord( "Stringintest" );
    stop = 0;
    do {
	if( fscan_tmstring( infile, &s ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	    fflush( stderr );
	}
	print_tmstring( st, s );
	if( s != tmstringNIL && strcmp( s, "STOP"  ) == 0 ){
	    stop = 1;
	}
	fre_tmstring( s );
    } while( stop == 0 );
    st->closeConstructor();
}

static void test_tmword( TmPrintState *st )
{
    tmword s;
    int stop;

    st->openConstructor();
    st->printWord( "Wordouttest" );
    print_tmword( st, "Test" );
    st->closeConstructor();
    st->openConstructor();
    st->printWord( "Wordintest" );
    stop = 0;
    do {
	if( fscan_tmword( infile, &s ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	    fflush( stderr );
	}
	print_tmword( st, s );
	if( s != tmwordNIL && strcmp( s, "STOP"  ) == 0 ){
	    stop = 1;
	}
	fre_tmword( s );
    } while( stop == 0 );
    st->closeConstructor();
}

/* Test the tmtext routines. */
static void test_tmtext( TmPrintState *st )
{
    tmtext *t;
    tmtext *t2;
    tmtext *nw;
    int stop;
    tmtext *sbuf[10];

    for( int i=0; i<10; i++ ){
	sbuf[i] = new tmtext( "testing 1,2,3...." );
    }
    for( int i=0; i<10; i++ ){
	sbuf[i]->destroy();
    }
    st->openConstructor();
    st->printWord( "Textouttest" );
    t = new tmtext();
    print_tmtext( st, t );
    t->destroy();
    t = new tmtext( "Test" );
    if( t->sz != 4 ){
	bad( "tmtext::tmtext( char * ) results in text with the wrong size" );
    }
    if( t->curpos != 0 ){
	bad( "tmtext::tmtext( char * ) does not put curpos on 0" );
    }
    if( t->room<t->sz ){
	bad( "tmtext::tmtext( char * ) room smaller than size?" );
    }
    if( t->arr[0] != 'T' || t->arr[1] != 'e' || t->arr[2] != 's' || t->arr[3] != 't' ){
	bad( "tmtext::tmtext( char * ) results in the wrong text" );
    }
    tmstring s = tmtext_to_tmstring( t );
    if( strcmp( s, "Test" ) != 0 ){
	fprintf( stderr, "s: '%s'\n", s );
	bad( "tmtext_to_tmstring() failed" );
    }
    rfre_tmstring( s );
    t2 = t->clone();
    if( cmp_tmtext( t, t2 ) != 0 ){
	bad( "tmtext::clone() failed" );
    }
    t->destroy();
    t = t2;
    print_tmtext( st, t );
    st->closeConstructor();
    t->destroy();
    st->openConstructor();
    st->printWord( "Textintest" );
    stop = 0;
    do {
	if( fscan_tmtext( infile, &t ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	    fflush( stderr );
	}
	print_tmtext( st, t );
	if( t != tmtextNIL && cmp_string_tmtext( "STOP", t  ) == 0 ){
	    stop = 1;
	}
	t->destroy();
    } while( stop == 0 );
    st->closeConstructor();
    t = new tmtext();
    t = puts_tmtext( "testing", t );
    if( cmp_string_tmtext( "testing", t ) != 0 ){
	bad( "bad tmtext" );
    }
    nw = new tmtext();
    nw = putc_tmtext( 't', nw );
    nw = putc_tmtext( 's', nw );
    t = replace_tmtext( t, 2, 4, nw );
    if( cmp_string_tmtext( "tetsing", t ) != 0 ){
	bad( "tmtext not replaced" );
    }
    t = replace_tmtext( t, 0, 1, nw );
    if( cmp_string_tmtext( "tsetsing", t ) != 0 ){
	bad( "tmtext not replaced" );
    }
    t = replace_tmtext( t, 0, 0, nw );
    if( cmp_string_tmtext( "tstsetsing", t ) != 0 ){
	bad( "tmtext not replaced" );
    }
    t = replace_tmtext( t, 0, 4, nw );
    if( cmp_string_tmtext( "tsetsing", t ) != 0 ){
	bad( "tmtext not replaced" );
    }
    t = replace_tmtext( t, 6, 8, nw );
    if( cmp_string_tmtext( "tsetsits", t ) != 0 ){
	bad( "tmtext not replaced" );
    }
    t = replace_tmtext( t, 1, 5, nw );
    if( cmp_string_tmtext( "ttsits", t ) != 0 ){
	bad( "tmtext not replaced" );
    }
    t = delblock_tmtext( t, 0, 1 );
    if( cmp_string_tmtext( "tsits", t ) != 0 ){
	bad( "tmtext block not deleted" );
    }
    nw->destroy();
    nw = new tmtext( "bla" );
    t = insert_tmtext( t, 0, nw );
    if( cmp_string_tmtext( "blatsits", t ) != 0 ){
	bad( "tmtext badly inserted" );
    }
    t = insert_tmtext( t, 0, nw );
    if( cmp_string_tmtext( "blablatsits", t ) != 0 ){
	bad( "tmtext badly inserted" );
    }
    t = insert_tmtext( t, 2, nw );
    if( cmp_string_tmtext( "blblaablatsits", t ) != 0 ){
	bad( "tmtext badly inserted" );
    }
    t = insert_tmtext( t, 1000, nw );
    if( cmp_string_tmtext( "blblaablatsitsbla", t ) != 0 ){
	bad( "tmtext badly inserted" );
    }
    nw->destroy();
    t->destroy();
    t = new tmtext( ", a, z, a, c, z, d, f, blabla" );
    t->destroy();
}

static void test_tmbool( TmPrintState *st )
{
    tmbool b;

    st->openConstructor();
    st->printWord( "Tmboolouttest" );
    print_tmbool( st, TMTRUE );
    print_tmbool( st, TMFALSE );
    do {
	if( fscan_tmbool( infile, &b ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_tmbool( st, b );
    } while( b );
    st->closeConstructor();
}

/* Test of fprint_uchar() */
static void ftest_uchar( FILE *f )
{
    fputs( "fprint_uchar: [", f );
    fprint_uchar( f, 'a' );
    fputs( " ", f );
    fprint_uchar( f, ' ' );
    fputs( " ", f );
    fprint_uchar( f, (uchar) 129 );
    fputs( " ", f );
    fprint_uchar( f, '\0' );
    fputs( "]\n", f );
}

/* Test of fprint_schar() */
static void ftest_schar( FILE *f )
{
    fputs( "fprint_schar: [", f );
    fprint_schar( f, 'a' );
    fputs( " ", f );
    fprint_schar( f, ' ' );
    fputs( " ", f );
    fprint_schar( f, (schar) -2 );
    fputs( " ", f );
    fprint_schar( f, (schar) 129 );
    fputs( " ", f );
    fprint_schar( f, '\0' );
    fputs( "]\n", f );
}

/* Test of fprint_sshrt() */
static void ftest_sshrt( FILE *f )
{
    fputs( "fprint_sshrt: [", f );
    fprint_sshrt( f, 12 );
    fputs( " ", f );
    fprint_sshrt( f, 0 );
    fputs( " ", f );
    fprint_sshrt( f, -42 );
    fputs( "]\n", f );
}

/* Test of fprint_uint() */
static void ftest_ushrt( FILE *f )
{
    fputs( "fprint_ushrt: [", f );
    fprint_ushrt( f, 12 );
    fputs( " ", f );
    fprint_ushrt( f, 0 );
    fputs( " ", f );
    fprint_ushrt( f, 42 );
    fputs( "]\n", f );
}

/* Test of fprint_int() */
static void ftest_int( FILE *f )
{
    fputs( "fprint_int: [", f );
    fprint_int( f, 12 );
    fputs( " ", f );
    fprint_int( f, 0 );
    fputs( " ", f );
    fprint_int( f, -42 );
    fputs( "]\n", f );
}

/* Test of fprint_uint() */
static void ftest_uint( FILE *f )
{
    fputs( "fprint_uint: [", f );
    fprint_uint( f, 12 );
    fputs( " ", f );
    fprint_uint( f, 0 );
    fputs( " ", f );
    fprint_uint( f, 42 );
    fputs( "]\n", f );
}

/* Test of fprint_long() */
static void ftest_long( FILE *f )
{
    fputs( "fprint_long: [", f );
    fprint_long( f, 12 );
    fputs( " ", f );
    fprint_long( f, 0 );
    fputs( " ", f );
    fprint_long( f, -123442 );
    fputs( "]\n", f );
}

/* Test of fprint_ulong() */
static void ftest_ulong( FILE *f )
{
    fputs( "fprint_ulong: [", f );
    fprint_ulong( f, 12 );
    fputs( " ", f );
    fprint_ulong( f, 0 );
    fputs( " ", f );
    fprint_ulong( f, 123442 );
    fputs( "]\n", f );
}

static void ftest_tmstring( FILE *f )
{
    fputs( "fprint_tmstring: [", f );
    fprint_tmstring( f, "blabla" );
    fputs( " ", f );
    fprint_tmstring( f,  "" );
    fputs( " ", f );
    fprint_tmstring( f,  "reutel" );
    fputs( " ", f );
    fprint_tmstring( f,  tmstringNIL );
    fputs( "]\n", f );
}

static void ftest_tmword( FILE *f )
{
    fputs( "fprint_tmword: [", f );
    fprint_tmword( f, "blabla" );
    fputs( " ", f );
    fprint_tmword( f,  "reutel" );
    fputs( " ", f );
    fprint_tmword( f,  tmwordNIL );
    fputs( "]\n", f );
}

/* Test the tmsymbol handling routines. */
static void test_tmsymbol( void )
{
    tmsymbol a;
    tmsymbol b;
    tmsymbol t;
    tmsymbol g1;
    tmsymbol g2;

    a = add_tmsymbol( "a" );
    b = add_tmsymbol( "a" );
    if( a != b ){
	bad( "equal tmsymbols do not compare equal" );
    }
    b = add_tmsymbol( "b" );
    if( a == b ){
	bad( "unequal tmsymbols compare equal" );
    }
    g1 = gen_tmsymbol( "base" );
    if( g1 == a || g1 == b ){
	bad( "gensym tmsymbol is equal to existing tmsymbol" );
    }
    t = find_tmsymbol( "a" );
    if( t == tmsymbolNIL ){
	bad( "tmsymbol not found back" );
    }
    if( t != a ){
	bad( "wrong tmsymbol found" );
    }
    t = find_tmsymbol( "is not there" );
    if( t != tmsymbolNIL ){
	fprintf( stderr, "tmsymbol '%s'", t->name );
	bad( "non-existing tmsymbol found" );
    }
    g2 = gen_tmsymbol( "base" );
    if( g2 == a || g2 == b || g2 == g1 ){
	bad( "gensym tmsymbol is equal to existing tmsymbol" );
    }
    flush_tmsymbol();
}

#ifdef __MSDOS__
long huge idlist[TESTARRAYSIZE];
#else
long idlist[TESTARRAYSIZE];
#endif

int main( void )
{
    tmstring str;
    tmstring scstr;
    int lev;

    infile = fopen( "testin", "r" );
    if( infile == NULL ){
	bad( "cannot open input file" );
    }
    outfile = fopen( "testout", "w" );
    if( outfile == NULL ){
	bad( "cannot open output file" );
    }
    if( freopen( "testerr", "w", stderr ) == NULL ){
	bad( "cannot redirect stderr" );
    }
    test_tmsymbol();
    tm_lineno = 1;
    TmPrintState *st = new TmPrintState( outfile, 4, 80, 8, 0 );
    test_printopt( st );
    test_brac( st );
    test_cons( st );
    test_schar( st );
    test_uchar( st );
    test_sshrt( st );
    test_ushrt( st );
    test_int( st );
    test_uint( st );
    test_long( st );
    test_ulong( st );
    test_double();
    test_float();
    test_tmstring( st );
    test_tmword( st );
    test_tmtext( st );
    test_tmbool( st );
    ftest_schar( outfile );
    ftest_uchar( outfile );
    ftest_sshrt( outfile );
    ftest_ushrt( outfile );
    ftest_int( outfile );
    ftest_uint( outfile );
    ftest_long( outfile );
    ftest_ulong( outfile );
    ftest_tmstring( outfile );
    ftest_tmword( outfile );
    lev = st->getLevel();
    st->destroy();
    fprintf( stderr, "bracket level: %d\n", lev );
    fprintf( stderr, "get_balance_tmstring(): %d\n", get_balance_tmstring() );
    fprintf( stderr, "tmtext::get_balance(): %d\n", tmtext::get_balance() );
    stat_tmstring( stderr );
    tmtext::stat( stderr );
    fprintf( outfile, "tm_lineno=%d\n", tm_lineno );
    str = new_tmstring( "bla" );
    fre_tmstring( str );
    if( fscan_tmstring( infile, &scstr ) ){
	fprintf( stderr, "*** Error: %s\n", tm_errmsg );
    }
    str = new_tmstring( "bla" );
    str = realloc_tmstring( str, strlen( str )*4 );
    (void) str;
    str = create_tmstring( 23 );
    (void) str;
    fflush( outfile );		/* Just to be sure.. */
    tm_fatal( __FILE__, __LINE__, "test of 'tm_fatal'" );
    exit( 0 );
    return 0;
}
