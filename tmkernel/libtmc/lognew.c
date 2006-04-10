/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: newlog.c
   Log new_ and fre_ actions and their origin in the users' code.
 */

#include "config.h"
#include "tmc.h"

/* An entry in the pending pointer list. */
typedef struct str_ptrlog {
    tm_neutralp ptr;
    const char *file;
    int line;
} ptrlog;

/* One entry in the pending block list. The id of the block
 * is the index in the id array. Empty (unused) blocks are
 * indicated by line<0.
 */
typedef struct str_id {
    int line;
    union u_id {
	const char *filenm;	/* File name. */
	long int next;		/* Index of next free block if line<0 */
    } u;
} id;

static id *idlist = (id *)0;	/* The array of block info. */
static ptrlog *plist = (ptrlog *)0; 
static size_t plistsz = 0;	/* The index of the first free element in the list. */
static size_t plistroom = 0;	/* The number of elements in the array. */
static int plistofl = 0;	/* Overflow in the pointer list? */
static long int idsz = 0;	/* The index of the first free element in the array. */
static long int idroom = 0;	/* The number of elements in the array. */
static long int idfree = -1;	/* The linked list of free blocks. */
static long int idcnt = 0;	/* The number of pending blocks. */
static int idofl = 0;		/* Overflow in the id list? */

/***********************************************************
 *   pointer list                                          *
 ***********************************************************/

/* Given a pointer 'p', search for it in the list of pending pointers.
 * Return the position in the list if found, else return -1.
 */
static long search_plist( const tm_neutralp p )
{
    size_t ix;

    for( ix=0; ix<plistsz; ix++ ){
        if( plist[ix].ptr == p ){
            return ix;
        }
    }
    return -1;
}

static void print_plist( FILE *f )
{
    size_t ix;

    for( ix=0l; ix<plistsz; ix++ ){
	fprintf( f, "%s(%d) p=%p\n", plist[ix].file, plist[ix].line, plist[ix].ptr );
    }
}

/* Given a pointer 'p', record it as a new entry in the 'new' table. */
void tm_lognew( const tm_neutralp p, const char *file, const int line )
{
    size_t newroom;
    long pos;

    if( plistofl || p == (tm_neutralp) 0 ){
	return;
    }
    pos = search_plist( p );
    if( pos>=0 ){
	tm_fatal( "", 0, "lognew: pointer already registered" );
    }
    if( plistsz>=plistroom ){
	if( plistroom==0 ){
	    newroom = FIRSTLOGNEWSZ;
	    plist = TM_MALLOC( ptrlog *, newroom*sizeof( ptrlog ) );
	    plistroom = newroom;
	}
	else {
	    newroom = plistroom+plistroom;
	    plist = TM_REALLOC( ptrlog *, plist, newroom*sizeof( ptrlog ) );
	    plistroom = newroom;
	}
    }
    plist[plistsz].file = file;
    plist[plistsz].line = line;
    plist[plistsz].ptr = p;
    plistsz++;
}

/* Given a pointer 'p', delete its entry from the 'plist' table. */
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
 *   ID list                                               *
 ***********************************************************/

/* Maintain a table of pending tm blocks. The tm code should
 * register all allocated blocks to id_lognew(); They will
 * receive a unique long int to identify the block. When the
 * block is destroyed, this id is passed to tm_fre_logid() to
 * indicate its destruction.
 */

/* Register a new block */
long int tm_new_logid( const char *file, const int line )
{
    long int theid;
    size_t newroom;

    if( idfree>0 ){
	theid = idfree;
	idfree = idlist[theid].u.next;
    }
    else {
	if( idofl ){
	    return 0;
	}
	if( idsz>=idroom ){
	    if( idroom==0 ){
		newroom = FIRSTLOGNEWSZ;
		idlist = TM_MALLOC( id *, newroom*sizeof( id ) );
		idroom = newroom;
	    }
	    else {
		newroom = idroom+idroom;
		idlist = TM_REALLOC( id *, idlist, newroom*sizeof( id ) );
		idroom = newroom;
	    }
	}
	theid = idsz++;
    }
    idcnt++;
    idlist[theid].u.filenm = file;
    idlist[theid].line = line;
    return theid;
}

/* Remove the block with id 'i' from the list of pending blocks. */
void tm_fre_logid( const long int i )
{
    char buf[256];

   if( idofl ){
       return;
   }
   if( i<0l || i>idsz ){
	sprintf( buf, "Id out of range in tm_fre_logid(): %ld", i );
        tm_fatal( "", 0, buf );
   }
   if( idlist[i].line<0l ){
	sprintf( buf, "Free id in tm_fre_logid(): %ld", i );
        tm_fatal( "", 0, buf );
   }
   idcnt--;
   idlist[i].line = -1;
   idlist[i].u.next = idfree;
   idfree = i;
}

static void print_idlist( FILE *f )
{
    long int ix;
    long int prcnt;

    prcnt = 0l;
    for( ix=0l; ix<idsz; ix++ ){
	if( idlist[ix].line>=0l ){
	    fprintf( f, "%s(%d) id=%lu\n", idlist[ix].u.filenm, idlist[ix].line, (unsigned long) ix );
	    prcnt++;
	}
    }
    if( prcnt != idcnt ){
	fprintf(
	    f,
	    "Found %ld pending blocks instead of %ld.\n",
	    prcnt,
	    idcnt
	);
    }
}

/***********************************************************
 *   flushing and statistics                               *
 ***********************************************************/

/* Print the remaining entries in the new log to file 'f'. */
void report_lognew( FILE *f )
{
    if( plistsz>0 || idcnt>0 ){
	fputs( "lognew: pending blocks:\n", f );
    }
    if( plistofl ){
	fputs( "lognew: pointer list overflow.\n", f );
    }
    else {
	print_plist( f );
    }
    if( idofl ){
	fputs( "lognew: id list overflow.\n", f );
    }
    else {
	print_idlist( f );
    }
}

/* Flush the log. */
void flush_lognew( void )
{
    idcnt = 0;
    idroom = 0;
    idsz = 0;
    idfree = -1;
    idofl = 0;
    if( idlist != 0 ){
	TM_FREE( idlist );
    }
    if( plist != 0 ){
	TM_FREE( plist );
    }
    idlist = (id *)0;
    plist = (ptrlog *)0;
    plistsz = 0;
    plistroom = 0;
    plistofl = 0;
}
