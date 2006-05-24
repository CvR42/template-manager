/* File: $Id$
 *
 * Symbol table manager.
 */

#include "config.h"
#include "tmc.h"

static tmbool gensymworking = TMFALSE;
static tmbool initdone = TMFALSE;

typedef /*@only@*/ /*@null@*/ struct _tmc_sym *null_tmsymbol;

/* This is the table of symbol strings. Each used symbol string should
 * occur here exactly once, so that a compare on equal names is
 * simplified to comparing the pointers to the strings. This is
 * ensured by the routines 'add_tmsymbol()' and 'gen_tmsymbol()'.
 */
static null_tmsymbol symtab[SYMHASHWIDTH];

/* For each hash value of a possible gensym prefix, keep track of a
 * counter. This prevents the gensym counter from having to start
 * from 0 every time.
 */
static unsigned int gencount[SYMHASHWIDTH];

/* Initalize tmsymbol routines. */
static void init_tmsymbol( void )
{
    int i;

    for( i=0; i<SYMHASHWIDTH; i++ ){
	symtab[i] = tmsymbolNIL;
	gencount[i] = 0;
    }
    initdone = TMTRUE;
}

/* The hashing function:
 * Return a value in the range 0..SYMHASHWIDTH-1.
 */
static unsigned int hash( const char *s )
{
    unsigned int sum = 0;

    while( *s != '\0' ){
	sum = (5U*sum)+(unsigned int) (*s++);
	while( sum>=SYMHASHWIDTH ){
	    sum -= (SYMHASHWIDTH-1);
	}
    }
    return sum;
}

/* Make a new storage space for a tmsymbol. */
static /*@only@*/ tmsymbol new_tmsymbol( tmsymbol l, /*@only@*/ tmstring s )
{
    tmsymbol nw = TM_MALLOC( tmsymbol, sizeof( *nw )  );

    nw->next = l;
    nw->name = s;
    nw->data = (tm_neutralp) 0;
    return nw;
}

/* Try to locate string 'name' in the given list 'list'.

   If the name occurs in the list, a pointer to the entry is returned,
   else tmsymbolNIL is returned.
 */
static /*@null@*/ /*@dependent@*/ tmsymbol dofind_tmsymbol( const char *name, tmsymbol list )
{
    while( list != tmsymbolNIL ){
	if( strcmp( list->name, name ) == 0 ){
	    return list;
	}
	list = list->next;
    }
    return tmsymbolNIL;
}

/* Search the symbol table for the given tmsymbol.
   If the name occurs in the table, a pointer to the entry is returned,
   else tmsymbolNIL is returned.
 */
tmsymbol find_tmsymbol( const char *name )
{
    tmsymbol entry;
    unsigned int hashval;

    if( !initdone ){
	init_tmsymbol();
    }
    hashval = hash( name );
    entry = dofind_tmsymbol( name, symtab[hashval] );
    return entry;
}

/* Add string 'name' to the symbol table.
   If the name already occurs in the table, a pointer to the old
   entry is returned, else a new entry is added, and a pointer to this
   new entry is returned.

   This routine must ensure that for all tmsymbols with the same name,
   the same pointer is returned.
 */
tmsymbol add_tmsymbol( const char *name )
{
    tmsymbol entry;
    unsigned int hashval;
    tmstring nwstr;

    if( !initdone ){
	init_tmsymbol();
    }
    if( gensymworking ){
	fprintf(
	    stderr,
	    "You can't add tmsymbols after using gen_tmsymbol() (name = '%s')\n",
	    name
	);
	exit( EXIT_FAILURE );
    }
    hashval = hash( name );
    entry = dofind_tmsymbol( name, symtab[hashval] );
    if( entry != tmsymbolNIL ){
	return entry;
    }
    nwstr = new_tmstring_nolognew( name );
    entry = new_tmsymbol( symtab[hashval], nwstr );
    symtab[hashval] = entry;
    return entry;
}

/* given a prefix 'pre', generate a new tmsymbol with an unique name.

   This is done by systematically generating names of the form
   <pre><number> until a name is found that doesn't occur in the
   list.

   To ensure that the tmsymbol remains unique, the flag 'gensymworking'
   is set after the first tmsymbol has been generated.  After that it is
   an error to add new tmsymbols to the table using 'add_tmsymbol()'.
 */
tmsymbol gen_tmsymbol( const char *pre )
{
    unsigned int hashval;
    tmstring name;
    tmsymbol entry;
    unsigned int gensymnum;
    unsigned int prehash;
    tmbool found = TMFALSE;

    if( !initdone ){
	init_tmsymbol();
    }
    name = create_tmstring_nolognew( strlen( pre ) + 30 );
    prehash = hash( pre );
    gensymnum = gencount[prehash];
    do {
	sprintf( name, "%s%x", pre, gensymnum++ );
	hashval = hash( name );
	found = (dofind_tmsymbol( name, symtab[hashval] ) == tmsymbolNIL);
    } while( !found );
    entry = new_tmsymbol( symtab[hashval], name );
    symtab[hashval] = entry;
    gencount[prehash] = gensymnum;
    return entry;
}

void flush_tmsymbol()
{
    int i;

    for( i=0; i<SYMHASHWIDTH; i++ ){
	tmsymbol s = symtab[i];

	while( s != tmsymbolNIL ){
	    tmsymbol n = s->next;

	    /* The cast breaks the `const' declaration of the name, but is
	     * necessary to delete the string.
	     */
	    fre_tmstring_nolognew( (tmstring) s->name );
	    TM_FREE( s );
	    s = n;
	}
	symtab[i] = tmsymbolNIL;
	gencount[i] = 0;
    }
    gensymworking = TMFALSE;
}
