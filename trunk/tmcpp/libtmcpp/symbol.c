/*LINTLIBRARY*/
/* File: tmsymbol.c

   Symbol table manager.
 */

#include "config.h"
#include "tmcpp.h"

static tmbool gensymworking = TMFALSE;
static tmbool initdone = TMFALSE;

/* This is the table of symbol strings. Each used symbol string should
   occur here exactly once, so that a compare on equal names is
   simplified to comparing the pointers to the strings. This is
   ensured by the routines 'add_tmsymbol()' and 'gen_tmsymbol()'.
 */
tmsymbol symtab[SYMHASHWIDTH];
static int symtabcnt[SYMHASHWIDTH];

/* initalize tmsymbol routines */
static void init_tmsymbol( void )
{
    int i;

    for( i=0; i<SYMHASHWIDTH; i++ ){
	symtab[i] = tmsymbolNIL;
	symtabcnt[i] = 0;
    }
    initdone = TMTRUE;
}

/* The hashing function:
   Return a value in the range 0..SYMHASHWIDTH-1.
 */
static unsigned int hash( const char *s )
{
    unsigned int sum;

    sum = 0;
    while( *s != '\0' ){
	sum = (5*sum)+(*s++);
	while( sum>=SYMHASHWIDTH ){
	    sum -= (SYMHASHWIDTH-1);
	}
    }
    return sum;
}

/* Make a nw storage space for a tmsymbol. */
static tmsymbol newtmsymbol( tmsymbol l, tmstring s )
{
    tmsymbol nw;

    nw = TM_MALLOC( tmsymbol, sizeof( *nw )  );
    nw->next = l;
    nw->name = s;
    nw->data = (tm_neutralp) 0;
    return nw;
}

/* Try to locate string 'name' in the given list 'list'.

   If the name occurs in the list, a pointer to the entry is returned,
   else tmsymbolNIL is returned.
 */
static tmsymbol dofind_tmsymbol( const char *name, tmsymbol list )
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
   entry is returned, else a nw entry is added, and a pointer to this
   nw entry is returned.

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
	exit( 1 );
    }
    hashval = hash( name );
    entry = dofind_tmsymbol( name, symtab[hashval] );
    if( entry != tmsymbolNIL ){
	return entry;
    }
    nwstr = new_tmstring( name );
    entry = newtmsymbol( symtab[hashval], nwstr );
    symtab[hashval] = entry;
    symtabcnt[hashval]++;
    return entry;
}

/* given a prefix 'pre', generate a nw tmsymbol with an unique name.

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
    unsigned long int gensymnum;

    if( !initdone ){
	init_tmsymbol();
    }
    name = new_tmstring( "" );
    name = realloc_tmstring( name, strlen( pre ) + 30 );
    gensymnum = 0;
    for(;;){
	sprintf( name, "%s%lx", pre, gensymnum++ );
	hashval = hash( name );
	if( dofind_tmsymbol( name, symtab[hashval] ) == tmsymbolNIL ){
	    break;
	}
    }
    entry = newtmsymbol( symtab[hashval], name );
    symtab[hashval] = entry;
    symtabcnt[hashval]++;
    return entry;
}

void flush_tmsymbol( void )
{

    for( int i=0; i<SYMHASHWIDTH; i++ ){
	tmsymbol s = symtab[i];
	while( s != tmsymbolNIL ){
	    tmsymbol n = s->next;
	    fre_tmstring( (tmstring) s->name );
	    TM_FREE( s );
	    s = n;
	}
	symtab[i] = tmsymbolNIL;
    }
    gensymworking = TMFALSE;
}
