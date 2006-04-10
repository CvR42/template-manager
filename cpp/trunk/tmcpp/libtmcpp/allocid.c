// file: allocid.c
// Log new_ and fre_ actions.

#include "config.h"
#include "tmcpp.h"

#include <vector>
using namespace std;

unsigned long tm_allocid_next = 0;

static vector<bool> flags = vector<bool>( 10 );

void tm_register_new_allocid( const unsigned long id )
{
    while( id>=flags.size() ){
	flags.resize( 1+id+flags.size(), false );
    }
    flags[id] = true;
}

void tm_register_free_allocid( const unsigned long id )
{
    if( id<flags.size() ){
	flags[id] = false;
    }
}

void tm_list_pending_ids( FILE *f )
{
    bool first = false;
    int n = 0;
    for( unsigned long ix = 0; ix!=flags.size(); ix++ ){
	if( flags[ix] ){
	    if( first ){
		fputs( "The following blocks are still pending:\n", f );
		first = false;
	    }
	    fprintf( f, "%10lu ", ix );
	    n++;
	    if( n>5 ){
		n = 0;
		fputs( "\n", f );
	    }
	}
    }
    if( n != 0 ){
	fputs( "\n", f );
    }
}
