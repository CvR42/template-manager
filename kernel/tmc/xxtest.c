/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: XXXtest.c

   Test of 'XXX' modules: read a file for a given datastructure
   and write it out again in pretty-printed format.
 */

#include <stdio.h>
#include <tmc.h>
#include <stdlib.h>

#include "XXXcode.h"

#define CODEXXX

int main( void )
{
    toplevel_list ds;
    toplevel_list dscopy;
    toplevel_list l;
    toplevel e;
    int valid;
    int n;
    FILE *infile;
    FILE *outfile;
    TMPRINTSTATE *st;
    int lev;
    label lbl;
    thing t;
#ifdef CODEtmc
    expr x;
#endif

    lbl = new_label( 42 );
    t = (thing) new_Thing( 22 );
#ifdef CODEtmc
    x = (expr) new_exprPlus(
	(expr) new_exprConst( 42 ),
	(expr) new_exprConst( 5 )
    );
#endif
    ds = new_toplevel_list();
    ds = setroom_toplevel_list( ds, 42U );
#ifdef CODEalu
    if( ds->room<42U ){
        fprintf( stderr, "setroom_toplevel_list() fails\n" );
        fprintf( stderr, "actual size is %u\n", ds->sz );
        exit( EXIT_FAILURE );
    }
#endif
#ifdef CODEtmc
    if( ds->room<42U ){
        fprintf( stderr, "setroom_toplevel_list() fails\n" );
        fprintf( stderr, "actual size is %u\n", ds->sz );
        exit( EXIT_FAILURE );
    }
#endif
    rfre_toplevel_list( ds );
    ds = toplevel_listNIL;
    infile = fopen( "XXXtesti", "r" );
    if( infile == NULL ){
        fprintf( stderr, "Cannot open input file" );
        exit( EXIT_FAILURE );
    }
    outfile = fopen( "testout", "w" );
    if( outfile == NULL ){
        fprintf( stderr, "Cannot open output file" );
        exit( EXIT_FAILURE );
    }
    if( freopen( "testerr", "w", stderr ) == NULL ){
        fprintf( stderr, "Cannot redirect error file" );
        exit( EXIT_FAILURE );
    }
    tm_lineno = 1;
    if( fscan_toplevel_list( infile, &ds ) ){
	fprintf( stderr, "Read error at line XXXtesti(%d): %s\n", tm_lineno, tm_errmsg );
        exit( EXIT_FAILURE );
    }
    dscopy = rdup_toplevel_list( ds );
    rfre_toplevel_list( dscopy );	/* put something in caches */
    dscopy = rdup_toplevel_list( ds );
    if( cmp_toplevel_list( ds, dscopy ) != 0 ){
	fprintf( stderr, "cmp of copy and original does not yield 0??\n" );
	exit( EXIT_FAILURE );
    }
    if( !isequal_toplevel_list( ds, dscopy ) ){
	fprintf( stderr, "Copy not equal to original??\n" );
	exit( EXIT_FAILURE );
    }
    dscopy = reverse_toplevel_list( dscopy );
    if( cmp_toplevel_list( ds, dscopy ) == 0 ){
	fprintf( stderr, "Reversed copy equal to original??\n" );
	exit( EXIT_FAILURE );
    }
    dscopy = reverse_toplevel_list( dscopy );
    if( cmp_toplevel_list( ds, dscopy ) != 0 ){
	fprintf( stderr, "Doubly reversed copy not equal to original??\n" );
	exit( EXIT_FAILURE );
    }
#ifdef CODEtmc
    ds = insert_toplevel_list( ds, (unsigned int) 0, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEalu
    ds = insert_toplevel_list( ds, (unsigned int) 0, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEllu
    ds = insert_toplevel_list( ds, (unsigned int) 0, rdup_toplevel( ds ) );
#endif
    if( cmp_toplevel_list( ds, dscopy ) == 0 ){
	fprintf( stderr, "Insertion does not change comparison??\n" );
	exit( EXIT_FAILURE );
    }
#ifdef CODEtmc
    ds = insert_toplevel_list( ds, (unsigned int) 0, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEalu
    ds = insert_toplevel_list( ds, (unsigned int) 0, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEllu
    ds = insert_toplevel_list( ds, (unsigned int) 0, rdup_toplevel( ds ) );
#endif
#ifdef CODEtmc
    ds = insert_toplevel_list( ds, (unsigned int) 1, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEalu
    ds = insert_toplevel_list( ds, (unsigned int) 1, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEllu
    ds = insert_toplevel_list( ds, (unsigned int) 1, rdup_toplevel( ds ) );
#endif
#ifdef CODEtmc
    ds = insert_toplevel_list( ds, (unsigned int) 2, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEalu
    ds = insert_toplevel_list( ds, (unsigned int) 2, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEllu
    ds = insert_toplevel_list( ds, (unsigned int) 2, rdup_toplevel( ds ) );
#endif
    ds = delete_toplevel_list( ds, (unsigned int) 1 );
    ds = delete_toplevel_list( ds, (unsigned int) 0 );
    ds = extract_toplevel_list( ds, (unsigned int) 1, &e, &valid );
    if( !valid ){
	fprintf( stderr, "Extraction from position 1 invalid?\n" );
	exit( EXIT_FAILURE );
    }
    rfre_toplevel( e );
    e = toplevelNIL;
    ds = extract_toplevel_list( ds, (unsigned int) 0, &e, &valid );
    if( !valid ){
	fprintf( stderr, "Extraction from position 0 invalid?\n" );
	exit( EXIT_FAILURE );
    }
    rfre_toplevel( e );
    e = toplevelNIL;
    if( cmp_toplevel_list( ds, dscopy ) != 0 ){
	fprintf( stderr, "Deletions and extractions do not restore old ds??\n" );
	exit( EXIT_FAILURE );
    }
    ds = extract_toplevel_list( ds, 10000U, &e, &valid );
    if( valid ){
	fprintf( stderr, "Extraction from beyond the list size?\n" );
	exit( EXIT_FAILURE );
    }
    if( cmp_toplevel_list( ds, dscopy ) != 0 ){
	fprintf( stderr, "Out of bounds extraction affects datastructure?\n" );
	exit( EXIT_FAILURE );
    }
    ds = delete_toplevel_list( ds, 10000U );
    if( cmp_toplevel_list( ds, dscopy ) != 0 ){
	fprintf( stderr, "Out of bounds delete affects datastructure?\n" );
	exit( EXIT_FAILURE );
    }
#ifdef CODEtmc
    ds = insert_toplevel_list( ds, 0, to_toplevel( new_TopNone() ) );
    ds = insert_toplevel_list( ds, 0, to_toplevel( new_TopNone() ) );
    ds = insert_toplevel_list( ds, 0, to_toplevel( new_TopNone() ) );
#else
    ds = insert_toplevel_list( ds, 0, new_TopNone() );
    ds = insert_toplevel_list( ds, 0, new_TopNone() );
    ds = insert_toplevel_list( ds, 0, new_TopNone() );
#endif
    if( isequal_toplevel_list( ds, dscopy ) ){
	fprintf( stderr, "Inserts fail?\n" );
	exit( EXIT_FAILURE );
    }
    ds = deletelist_toplevel_list( ds, 0, 3U );
    if( !isequal_toplevel_list( ds, dscopy ) ){
	fprintf( stderr, "deletelist does not affect datastructure?\n" );
	exit( EXIT_FAILURE );
    }
#ifdef CODEtmc
    ds = append_toplevel_list( ds, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEalu
    ds = append_toplevel_list( ds, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEllu
    ds = append_toplevel_list( ds, rdup_toplevel( ds ) );
#endif
    if( cmp_toplevel_list( ds, dscopy ) == 0 ){
	fprintf( stderr, "Append does not change comparison??\n" );
	exit( EXIT_FAILURE );
    }
#ifdef CODEtmc
    ds = append_toplevel_list( ds, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEalu
    ds = append_toplevel_list( ds, rdup_toplevel( ds->arr[0] ) );
#endif
#ifdef CODEllu
    ds = append_toplevel_list( ds, rdup_toplevel( ds ) );
#endif
    ds = concat_toplevel_list( ds, dscopy );
    dscopy = toplevel_listNIL;
    ds = extractlist_toplevel_list( ds, 2, 5, &dscopy );
    ds = insertlist_toplevel_list( ds, 2, dscopy );
    /* 'dscopy' is not freed to test lognew routines. */
    dscopy = slice_toplevel_list( ds, 1, 1000 );
    l = rdup_toplevel_list( ds );
    for( n=0; n<100; n++ ){
	l = concat_toplevel_list( l, rdup_toplevel_list( ds ) );
    }
    rfre_toplevel_list( l );
    fprint_toplevel_list( outfile, dscopy );
    fprint_label( outfile, lbl );
    fprint_thing( outfile, t );
#ifdef CODEtmc
    fprint_expr( outfile, x );
#endif
    st = tm_setprint( outfile, 4, 78, 8, 0 );
    print_toplevel_list( st, ds );
    print_label( st, lbl );
    print_thing( st, t );
#ifdef CODEtmc
    print_expr( st, x );
    rfre_expr( x );
#endif
    lev = tm_endprint( st );
    fprintf( outfile, "bracket level: %d\n", lev );
    rfre_toplevel_list( ds );
    rfre_label( lbl );
    rfre_thing( t );
    fprintf( outfile, "get_balance_ds()=%d\n", get_balance_ds() );
    stat_ds( stderr );
    report_lognew( stderr );
    flush_lognew();
    (void) fclose( infile );
    (void) fclose( outfile );
    exit( EXIT_SUCCESS );
    /* UNREACHABLE */
    return 0;
}
