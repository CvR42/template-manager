// Tm - an interface code generator.
// Author: C. van Reeuwijk.
//
// All rights reserved.

// file: test.c
//
// Test of 'tmcpp' modules: read a file for a given datastructure
// and write it out again in pretty-printed format.

#include "config.h"
#include <stdio.h>
#include <tmcpp.h>
#include <stdlib.h>

#include "cppcode.h"

// Test a list of a value type
static void test_valuetype_list( FILE *infile, FILE *outfile )
{
    int_list *l = new int_list( 22 );
    l->append( 2 );
    l->append( 3 );
    l->append( 7 );
    l->erase( 1 );
    int_list *lc = l->clone();
    if( cmp_int_list( l, lc ) != 0 ){
	fprintf( stderr, "Duplicate of int list is not the same\n" );
        fprintf( stderr, "Original: " );
	fprint_int_list( stderr, l );
        fprintf( stderr, "Copy: " );
	fprint_int_list( stderr, lc );
	exit( 1 );
    }
    if( l->arr[0] != 2 ){
	fprintf( stderr, "l[0] has unexpected value %d\n", l->arr[0] );
	exit( 1 );
    }
    if( l->arr[1] != 7 ){
	fprintf( stderr, "l[1] has unexpected value %d\n", l->arr[1] );
	exit( 1 );
    }
    l->concat( lc );
    lc = l->slice( 1, 2 );
    lc->reverse();
    fprint_int_list( outfile, l );
    TMPRINTSTATE *st = tm_setprint( outfile, 4, 78, 8, 0 );
    print_int_list( st, l );
    int lev = tm_endprint( st );
    fprintf( outfile, "bracket level: %d\n", lev );
    {
	int n;
	int ok;

        ok = l->extract( 0, &n );
	if( !ok ){
	    fprintf( stderr, "could not extract from int list\n" );
	    exit( 1 );
	}
	if( n != 2 ){
	    fprintf( stderr, "extracted int has unexpected value %d\n", n );
	    exit( 1 );
	}
	l->concat( lc );
	lc = l->extractlist( 1, 3 );
    }
    l->destroy();
    lc->destroy();
    {
	int_list *lb;
	if( fscan_int_list( infile, &lb ) ){
	    fprintf(
		stderr,
		"Read error at line testin(%d): %s\n",
		tm_lineno,
		tm_errmsg
	    );
	    exit( 1 );
	}
	lb->destroy();
    }
}

int main( void )
{
    toplevel_list *l;
    toplevel *e;
    bool valid;
    FILE *infile;
    FILE *outfile;
    TMPRINTSTATE *st;

    tm_lineno = 1;
    label *lbl = new label( 42 );
    thing *t = new Thing( 22 );
    expr *x = new exprPlus( new exprConst( 42 ), new exprConst( 5 ) );
    toplevel_list *ds = new toplevel_list( 42 );
    if( ds->room<42 ){
        fprintf( stderr, "toplevel_list::reserve() fails\n" );
        fprintf( stderr, "actual size is %u\n", ds->size() );
        exit( 1 );
    }
    ds->destroy();
    infile = fopen( "testin", "r" );
    if( infile == NULL ){
        fprintf( stderr, "Cannot open input file\n" );
        exit( 1 );
    }
    outfile = fopen( "testout", "w" );
    if( outfile == NULL ){
        fprintf( stderr, "Cannot open output file\n" );
        exit( 1 );
    }
    if( freopen( "testerr", "w", stderr ) == NULL ){
        fprintf( stderr, "Cannot redirect error file\n" );
        exit( 1 );
    }
    test_valuetype_list( infile, outfile );
    if( fscan_toplevel_list( infile, &ds ) ){
	fprintf( stderr, "Read error at line testin(%d): %s\n", tm_lineno, tm_errmsg );
        exit( 1 );
    }
    toplevel_list *dscopy = ds->clone();
    dscopy->destroy();
    dscopy = ds->clone();
    if( cmp_toplevel_list( ds, dscopy ) != 0 ){
	fprintf( stderr, "Copy not equal to original??\n" );
	exit( 1 );
    }
    dscopy->reverse();
    if( cmp_toplevel_list( ds, dscopy ) == 0 ){
	fprintf( stderr, "Reversed copy equal to original??\n" );
	exit( 1 );
    }
    dscopy->reverse();
    if( cmp_toplevel_list( ds, dscopy ) != 0 ){
	fprintf( stderr, "Doubly reversed copy not equal to original??\n" );
	exit( 1 );
    }
    ds->insert( (unsigned int) 0, ds->arr[0]->clone() );
    if( cmp_toplevel_list( ds, dscopy ) == 0 ){
	fprintf( stderr, "Insertion does not change comparison??\n" );
	exit( 1 );
    }
    ds->insert( (unsigned int) 0, ds->arr[0]->clone() );
    ds->insert( (unsigned int) 1, ds->arr[0]->clone() );
    ds->insert( (unsigned int) 2, ds->arr[0]->clone() );
    ds->erase( 1 );
    ds->erase( 0 );
    valid = ds->extract( 1u, &e );
    if( !valid ){
	fprintf( stderr, "Extraction from position 1 invalid?\n" );
	exit( 1 );
    }
    e->destroy();
    valid = ds->extract( 0u, &e );
    if( !valid ){
	fprintf( stderr, "Extraction from position 0 invalid?\n" );
	exit( 1 );
    }
    e->destroy();
    if( cmp_toplevel_list( ds, dscopy ) != 0 ){
	fprintf( stderr, "Deletions and extractions do not restore old ds??\n" );
	exit( 1 );
    }
    valid = ds->extract( 10000, &e );
    if( valid ){
	fprintf( stderr, "Extraction from beyond the list size?\n" );
	exit( 1 );
    }
    if( cmp_toplevel_list( ds, dscopy ) != 0 ){
	fprintf( stderr, "Out of bounds extraction affects datastructure?\n" );
	exit( 1 );
    }
    ds->erase( 10000 );
    if( cmp_toplevel_list( ds, dscopy ) != 0 ){
	fprintf( stderr, "Out of bounds erase affects datastructure?\n" );
	exit( 1 );
    }
    ds->append( ds->arr[0]->clone() );
    if( cmp_toplevel_list( ds, dscopy ) == 0 ){
	fprintf( stderr, "Append does not change comparison??\n" );
	exit( 1 );
    }
    ds->append( ds->arr[0]->clone() );
    ds->concat( dscopy );
    dscopy = ds->extractlist( 2, 5 );
    ds->insertlist( 2, dscopy );
    // 'dscopy' is not freed to test lognew routines.
    dscopy = ds->slice( 1, 1000 );
    l = ds->clone();
    for( int n=0; n<100; n++ ){
	l->concat( ds->clone() );
    }
    l->destroy();
    fprint_toplevel_list( outfile, dscopy );
    fprint_label( outfile, lbl );
    fprint_thing( outfile, t );
    fprint_expr( outfile, x );
    st = tm_setprint( outfile, 4, 78, 8, 0 );
    print_toplevel_list( st, ds );
    print_label( st, lbl );
    print_thing( st, t );
    print_expr( st, x );
    x->destroy();
    int lev = tm_endprint( st );
    fprintf( outfile, "bracket level: %d\n", lev );
    ds->destroy();
    lbl->destroy();
    t->destroy();
    fprintf( outfile, "get_balance_ds()=%d\n", get_balance_ds() );
    stat_ds( stderr );
    fclose( infile );
    fclose( outfile );
    exit( 0 );
    return 0;
}
