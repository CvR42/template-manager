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
#include "tmc.h"

#define TESTARRAYSIZE 13000

/* The file handle for the input and output file. */
FILE *infile;
FILE *outfile;

static void bad( const char *msg )
{
   fprintf( stderr, "check error: %s\n", msg );
   exit( 1 );
}

/* testprintopt: test printopt routines */
static void testprintopt( TMPRINTSTATE *st )
{
    int k;
    int i;
    int j;

    tm_openlist( st );
    tm_closelist( st );
    tm_opentuple( st );
    tm_printword( st, "tuple1" );
    tm_printword( st, "24" );
    tm_closetuple( st );
    tm_opencons( st );
    tm_printword( st, "Cons1" );
    tm_closecons( st );
    for( k=0; k<12; k+=3 ){
	tm_opencons( st );
	tm_printword( st, "Cons2" );
	tm_opencons( st );
	tm_printword( st, "Cons3" );
	for( i=1; i<k; i++ ){
	    tm_openlist( st );
	    for( j=0; j<i; j++ ){
		tm_printword( st, "42" );
	    }
	    tm_closelist( st );
	}
	tm_closecons( st );
	tm_opentuple( st );
	tm_printword( st, "tuple" );
	for( i=1; i<k; i++ ){
	    tm_openlist( st );
	    for( j=0; j<i; j++ ){
		tm_printword( st, "42" );
	    }
	    tm_closelist( st );
	}
	tm_closetuple( st );
	tm_closecons( st );
    }
    tm_printword( st, "Top" );
    tm_printword( st, "level" );
    tm_printword( st, "tm_printword()." );
}

/* Test of tm_fscanopenbrac() and tm_fscanclosebrac().
 * Read open brackets and match with close brackets until
 * a group of 0 pairs is encountered. Write the brackets
 * to the output file with the tm_opencons( st ) and tm_closecons( st )
 * functions.
 */
static void testbrac( TMPRINTSTATE *st )
{
    int bracs;
    int i;

    do{
	bracs = tm_fscanopenbrac( infile );
	for( i=0; i<bracs; i++ ){
	    tm_opencons( st );
	    tm_printword( st, "Bractest" );
	    tm_printword( st, "42" );
	}
	if( tm_fscanclosebrac( infile, bracs ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	for( i=0; i<bracs; i++ ){
	    tm_closecons( st );
	}
    } while( bracs != 0 );
}

/* Test of tm_fscancons(). Read and write constructors until one
   with name "StopFscanCons" is encountered.
 */
static void testcons( TMPRINTSTATE *st )
{
    char buf[1000];

    tm_opencons( st );
    tm_printword( st, "Constest" );
    tm_openlist( st );
    do{
	if( tm_fscancons( infile, buf, 1000 ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
            exit( 1 );
	}
	tm_printword( st, buf );
    } while( strcmp( buf, "StopFscanCons" ) != 0 );
    tm_closelist( st );
    tm_closecons( st );
}

/* Test of print_ulong() and fscan_ulong(): read and write
   long's until one with value 42 is encountered.
 */
static void testulong( TMPRINTSTATE *st )
{
    ulong ul;

    tm_opencons( st );
    tm_printword( st, "Ulongtest" );
    do {
	if( fscan_ulong( infile, &ul ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_ulong( st, ul );
    } while( ul != 42 );
    tm_closecons( st );
}

/* Test of print_long() and fscan_long(): read and write
   long's until one with value 42 is encountered.
 */
static void testlong( TMPRINTSTATE *st )
{
    long l;

    tm_opencons( st );
    tm_printword( st, "Longtest" );
    do {
	if( fscan_long( infile, &l ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_long( st, l );
    } while( l != 42 );
    tm_closecons( st );
}

/* Test of print_sshrt() and fscan_sshrt(): read and write sshrt's until
   one with value -1 is encountered.
 */
static void testsshrt( TMPRINTSTATE *st )
{
    sshrt i;

    tm_opencons( st );
    tm_printword( st, "Sshrttest" );
    do {
	if( fscan_sshrt( infile, &i ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_sshrt( st, i );
    } while( i != -1 );
    tm_closecons( st );
}

/* Test of print_ushrt() and fscan_ushrt(): read and write
   unsigned's until one with value 42 is encountered.
 */
static void testushrt( TMPRINTSTATE *st )
{
    ushrt u;

    tm_opencons( st );
    tm_printword( st, "Ushrttest" );
    do {
	if( fscan_ushrt( infile, &u ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_ushrt( st, u );
    } while( u != 42 );
    tm_closecons( st );
}

/* Test of print_int() and fscan_int(): read and write int's until
   one with value -1 is encountered.
 */
static void testint( TMPRINTSTATE *st )
{
    int i;

    tm_opencons( st );
    tm_printword( st, "Inttest" );
    do {
	if( fscan_int( infile, &i ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_int( st, i );
    } while( i != -1 );
    tm_closecons( st );
}

/* Test of print_uint() and fscan_uint(): read and write
   unsigned's until one with value 42 is encountered.
 */
static void testuint( TMPRINTSTATE *st )
{
    uint u;

    tm_opencons( st );
    tm_printword( st, "Unsignedtest" );
    do {
	if( fscan_uint( infile, &u ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_uint( st, u );
    } while( u != 42 );
    tm_closecons( st );
}

/* Test of print_schar() and fscan_schar(): read and write schar's until
   one with value 'q' is encountered.
 */
static void testschar( TMPRINTSTATE *st )
{
    schar c;

    tm_opencons( st );
    tm_printword( st, "Schartest" );
    do {
	if( fscan_schar( infile, &c ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_schar( st, c );
    } while( c != 'q' );
    tm_closecons( st );
}

/* Test of print_uchar() and fscan_uchar(): read and write uchar's until
   one with value 'q' is encountered.
 */
static void testuchar( TMPRINTSTATE *st )
{
    uchar c;

    tm_opencons( st );
    tm_printword( st, "Uchartest" );
    do {
	if( fscan_uchar( infile, &c ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_uchar( st, c );
    } while( c != 'q' );
    tm_closecons( st );
}

/* test cmp_double() */
static void testdouble( void )
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
static void testfloat( void )
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

static void testtmstring( TMPRINTSTATE *st )
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
    tm_opencons( st );
    tm_printword( st, "Stringouttest" );
    print_tmstring( st, "" );
    print_tmstring( st, "Test" );
    tm_closecons( st );
    tm_opencons( st );
    tm_printword( st, "Stringintest" );
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
    tm_closecons( st );
}

/* Test the tmtext routines. */
static void test_tmtext( TMPRINTSTATE *st )
{
    tmtext t;
    tmtext t2;
    tmtext nw;
    int stop;
    int i;
    tmtext sbuf[10];
    tmstring s;

    for( i=0; i<10; i++ ){
	sbuf[i] = string_to_tmtext( "testing 1,2,3...." );
    }
    for( i=0; i<10; i++ ){
	fre_tmtext( sbuf[i] );
    }
    tm_opencons( st );
    tm_printword( st, "Textouttest" );
    t = new_tmtext();
    print_tmtext( st, t );
    rfre_tmtext( t );
    t = string_to_tmtext( "Test" );
    s = tmtext_to_tmstring( t );
    if( strcmp( s, "Test" ) != 0 ){
	bad( "tmtext_to_tmstring() or string_to_tmtext() failed" );
    }
    rfre_tmstring( s );
    t2 = rdup_tmtext( t );
    if( cmp_tmtext( t, t2 ) != 0 ){
	bad( "rdup_tmtext() failed" );
    }
    rfre_tmtext( t );
    t = t2;
    print_tmtext( st, t );
    rfre_tmtext( t );
    tm_closecons( st );
    tm_opencons( st );
    tm_printword( st, "Textintest" );
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
	rfre_tmtext( t );
    } while( stop == 0 );
    tm_closecons( st );
    t = new_tmtext();
    t = puts_tmtext( "testing", t );
    if( cmp_string_tmtext( "testing", t ) != 0 ){
	bad( "bad tmtext" );
    }
    nw = new_tmtext();
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
    rfre_tmtext( nw );
    nw = string_to_tmtext( "bla" );
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
    rfre_tmtext( nw );
    rfre_tmtext( t );
    t = string_to_tmtext( ", a, z, a, c, z, d, f, blabla" );
    rfre_tmtext( t );
}

static void testtmbool( TMPRINTSTATE *st )
{
    tmbool b;

    tm_opencons( st );
    tm_printword( st, "Tmboolouttest" );
    print_tmbool( st, TMTRUE );
    print_tmbool( st, TMFALSE );
    do {
	if( fscan_tmbool( infile, &b ) ){
	    fprintf( stderr, "*** Error: %s\n", tm_errmsg );
	}
	print_tmbool( st, b );
    } while( b );
    tm_closecons( st );
}

/* Test of fprint_uchar() */
static void ftestuchar( FILE *f )
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
static void ftestschar( FILE *f )
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
static void ftestsshrt( FILE *f )
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
static void ftestushrt( FILE *f )
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
static void ftestint( FILE *f )
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
static void ftestuint( FILE *f )
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
static void ftestlong( FILE *f )
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
static void ftestulong( FILE *f )
{
    fputs( "fprint_ulong: [", f );
    fprint_ulong( f, 12 );
    fputs( " ", f );
    fprint_ulong( f, 0 );
    fputs( " ", f );
    fprint_ulong( f, 123442 );
    fputs( "]\n", f );
}

static void ftesttmstring( FILE *f )
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

/* Test the tmsymbol handling routines. */
static void testtmsymbol( void )
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
    int ix;
    TMPRINTSTATE *st;
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
    testtmsymbol();
    tm_lineno = 1;
    st = tm_setprint( outfile, 4, 80, 8, 0 );
    testprintopt( st );
    testbrac( st );
    testcons( st );
    testschar( st );
    testuchar( st );
    testsshrt( st );
    testushrt( st );
    testint( st );
    testuint( st );
    testlong( st );
    testulong( st );
    testdouble();
    testfloat();
    testtmstring( st );
    test_tmtext( st );
    testtmbool( st );
    ftestschar( outfile );
    ftestuchar( outfile );
    ftestsshrt( outfile );
    ftestushrt( outfile );
    ftestint( outfile );
    ftestuint( outfile );
    ftestlong( outfile );
    ftestulong( outfile );
    ftesttmstring( outfile );
    lev = tm_endprint( st );
    fprintf( stderr, "bracket level: %d\n", lev );
    fprintf( stderr, "get_balance_tmstring(): %d\n", get_balance_tmstring() );
    fprintf( stderr, "get_balance_tmtext(): %d\n", get_balance_tmtext() );
    stat_tmstring( stderr );
    stat_tmtext( stderr );
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
    for( ix=0; ix<TESTARRAYSIZE; ix++ ){
	idlist[ix] = tm_new_logid( "testlognew", ix );
    }
    for( ix=50; ix<TESTARRAYSIZE; ix++ ){
	tm_fre_logid( idlist[ix] );
    }
    /* Notice that idlist[0] and idlist[49] are left pending. */
    for( ix=1; ix<49; ix++ ){
	tm_fre_logid( idlist[ix] );
    }
    report_lognew( stderr );
    flush_lognew();
    fflush( outfile );		/* Just to be sure.. */
    tm_fatal( __FILE__, __LINE__, "test of 'tm_fatal'" );
    exit( 0 );
    return 0;
}
