/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: tmmisc.c
   Various low-level routines.
 */
#include "config.h"
#include <stdio.h>
#include <tmc.h>
#include "tmdefs.h"

#include "tmcode.h"
#include "misc.h"
#include "error.h"

/* Same as fopen, but give error message if file can't be opened */
FILE *ckfopen( const char *nm, const char *acc )
{
    FILE *hnd;

    hnd = fopen( nm, acc );
    if( NULL == hnd ){
	(void) strcpy( errarg, nm );
	sys_error( errno );
	exit( 1 );
    }
    return hnd;
}

/* Similar to freopen, but give error message if file can't be opened.
 * Therefore, file handle need not be returned.
 */
void ckfreopen( const char *nm, const char *acc, FILE *f )
{
    if( freopen( nm, acc, f ) == NULL ){
	(void) strcpy( errarg, nm );
	sys_error( errno );
	exit( 1 );
    }
}

/******************************************************
 *         DATASTRUCTURE SEARCH ROUTINES              *
 ******************************************************/

/* Given a type 't', return a pointer to its name tmstring. */
const tmstring get_type_name( const ds t )
{
    tmstring nm;

    nm = tmstringNIL;
    switch( t->tag ){
	case TAGDsCons:
	    nm = t->DsCons.name;
	    break;

	case TAGDsTuple:
	    nm = t->DsTuple.name;
	    break;

	case TAGDsClass:
	    nm = t->DsClass.name;
	    break;

    }
    return nm;
}

/* Given a list of types 'dl', search for type with name 't'.
 * Return the index of that type in the list, or dl->sz if not
 * found.
 */ 
unsigned int find_type_ix( const ds_list dl, const char *t )
{
    ds d;
    unsigned int ix;

    for( ix = 0; ix < dl->sz; ix++ ){
	d = dl->arr[ix];
	if( strcmp( get_type_name( d ), t ) == 0 ){
	    return ix;
	}
    }
    return dl->sz;
}

/* Given a list of constructors 'cl', search for constructor with name 'nm'.
 * Return the index of that constructor in the list, or cl->sz if not
 * found.
 */ 
unsigned int find_constructor_ix( const constructor_list cl, const char *nm )
{
    constructor c;
    unsigned int ix;

    for( ix = 0; ix < cl->sz; ix++ ){
	c = cl->arr[ix];
	if( strcmp( c->name, nm ) == 0 ){
	    return ix;
	}
    }
    return cl->sz;
}

/* Search for tmstring 's' in the list 'l' and return TRUE if
   found or FALSE otherwise.
 */
bool member_tmstring_list( const tmstring s, const tmstring_list l )
{
    unsigned int sno;

    for( sno=0; sno<l->sz; sno++ ){
	if( strcmp( l->arr[sno], s ) == 0 ){
	    return TRUE;
	}
    }
    return FALSE;
}

/* Ensure that there are no double names in each of the constructors of
 * constructor type with name 'nm' and constructors 'cons'.
 */
void ckconstructor( tmstring nm, constructor_list cons )
{
    constructor conx;
    field_list fields;
    unsigned int cix;	/* index in constructor list */
    unsigned int ix;	/* index of currently checked field */
    unsigned int six;	/* index for searching of fields/constr. */
    field fx;		/* checked field */
    field fy;		/* searched field */
    tmstring fnm;	/* name of currently checked field */
    tmstring connm;	/* name of current constructor */

    for( cix=0; cix<cons->sz; cix++ ){
	conx = cons->arr[cix];
	fields = conx->fields;
	connm = conx->name;
	for( ix=0; ix<fields->sz; ix++ ){
	    fx = fields->arr[ix];
	    fnm = fx->name;
	    for( six=ix+1; six<fields->sz; six++ ){
		fy = fields->arr[six];
		if( strcmp( fy->name, fnm ) == 0 ){
		    sprintf(
			errpos,
			"in type '%s', constructor '%s'",
			nm,
			connm
		    );
		    sprintf( errarg, "'%s'", fnm );
		    error( "double use of field name" );
		}
	    }
	}
    }
}
