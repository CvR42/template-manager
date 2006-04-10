// file: lognew.c
//
// Log pointer allocation and freeing; only used for tmstring
// Administration for other types is in alloclog.c

#include "config.h"
#include "tmcpp.h"

#define FIRSTLOGNEWSZ 100

/* An entry in the pending pointer list. */
typedef struct str_ptrlog {
    tm_neutralp ptr;
    const char *file;
    int line;
} ptrlog;

static ptrlog *plist = (ptrlog *)0; 
static size_t plistsz = 0;	/* The index of the first free element in the list. */
static size_t plistroom = 0;	/* The number of elements in the array. */
static int plistofl = 0;	/* Overflow in the pointer list? */

// Given a pointer 'p', search for it in the list of pending pointers.
// Return the position in the list if found, else return -1.
static long search_plist( const tm_neutralp p )
{
    for( size_t ix=0; ix<plistsz; ix++ ){
        if( plist[ix].ptr == p ){
            return ix;
        }
    }
    return -1;
}

static void print_plist( FILE *f )
{
    for( size_t ix=0l; ix<plistsz; ix++ ){
	fprintf( f, "%s(%d)\n", plist[ix].file, plist[ix].line );
    }
}

// Given a pointer 'p', record it as a new entry in the 'new' table.
void tm_lognew( const tm_neutralp p, const char *file, const int line )
{
    size_t newroom;

    if( plistofl || p == (tm_neutralp) 0 ){
	return;
    }
    long pos = search_plist( p );
    if( pos>=0 ){
	tm_fatal( "", 0, "lognew: pointer already registered" );
    }
    if( plistsz>=plistroom ){
	if( plistroom==0 ){
	    newroom = FIRSTLOGNEWSZ;
	    plist = (ptrlog *) tm_malloc( newroom*sizeof( ptrlog ) );
	    plistroom = newroom;
	}
	else {
	    newroom = plistroom+plistroom;
	    plist = (ptrlog *) tm_realloc( plist, newroom*sizeof( ptrlog ) );
	    plistroom = newroom;
	}
    }
    plist[plistsz].file = file;
    plist[plistsz].line = line;
    plist[plistsz].ptr = p;
    plistsz++;
}

// Given a pointer 'p', delete its entry from the 'plist' table.
void tm_logfre( const tm_neutralp p )
{
    long pos;		/* Position of the entry in the table. */

    if( plistofl || p == (tm_neutralp) 0 ){
	return;
    }
    pos = search_plist( p );
    if( pos>=0 ){
        /* Remove the pointer from the table. To compact the table
         * the entry at the end of the table is moved into this slot,
         * and the table size is decremented.
         */
        plistsz--;
        plist[pos] = plist[plistsz];
    }
    /* Else the pointer was not found in the log, this is strange,
     * but we'll assume that someone forgot to register it.
     */
}

/***********************************************************
 *   flushing and statistics                               *
 ***********************************************************/

// Print the remaining entries in the new log to file 'f'.
void report_lognew( FILE *f )
{
    if( plistsz>0 ){
	fputs( "lognew: pending blocks:\n", f );
    }
    if( plistofl ){
	fputs( "lognew: pointer list overflow.\n", f );
    }
    else {
	print_plist( f );
    }
}

// Flush the log.
void flush_lognew()
{
    free( plist );
    plist = (ptrlog *)0;
    plistsz = 0;
    plistroom = 0;
    plistofl = 0;
}
