/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File tmvar.c
 *
 * Variable and macro management.
 */

#include "config.h"

/* standard UNIX libraries */
#include <stdio.h>

/* tm library definitions */
#include <tmc.h>

/* local definitions */
#include "tmdefs.h"

#include "tmcode.h"
#include "tmstring.h"
#include "misc.h"
#include "error.h"
#include "var.h"
#include "global.h"

/******************************************************
 *    hashing parameters                              *    
 ******************************************************/

/* NOTE: The remainder of the code assumes HASHWIDTH is a power of 2. */
#define HASHBITS 6
#define HASHWIDTH (1<<HASHBITS)
#define HASHMASK (HASHWIDTH-1)

/******************************************************
 *    Datastructures                                  *    
 ******************************************************/

static var_list variables[HASHWIDTH];
static macro_list macros[HASHWIDTH];

static unsigned int ctxlvl;

/******************************************************
 *    hash function                                   *
 ******************************************************/

/* Hash function: map a 'normal' distribution of tmstrings on a
   evenly distributed number between 0..HASHWIDTH-1.
 */
static unsigned int hashval( const char *s )
{
    unsigned int v = 0;

    while( *s!= '\0' ){
	 v = (v ^ *s);
	 v<<=1;
	 if( v & HASHWIDTH ) v++;
	 v &= HASHMASK;
	 s++;
    }
    return v;
}

/******************************************************
 *    macro management                                *
 ******************************************************/

/* Search in current context level 'lvl' for macro with name 'nm'.
   Return pointer to variable, or varNIL if not found.
 */
static bool findlocmacro(
    const tmstring nm,
    unsigned int *hvp,
    unsigned int *ixp
)
{
    macro_list l;
    unsigned int hv;
    unsigned int ix;
    macro m;

    hv = hashval( nm );
    l = macros[hv];
    for( ix=0; ix<l->sz; ix++ ){
	m = l->arr[ix];
	if( m->lvl==ctxlvl && strcmp( nm, m->name ) == 0 ){
	    *hvp = hv;
	    *ixp = ix;
	    return TRUE;
	}
    }
    return FALSE;
}

/* Search in all contexts for variable with name 'nm'. Return pointer to
   struct macro of variable, or varNIL if not found.
 */
macro findmacro( const tmstring nm )
{
    macro_list l;
    unsigned int hv;
    unsigned int ix;
    macro m;

    hv = hashval( nm );
    l = macros[hv];
    for( ix=0; ix<l->sz; ix++ ){
	m = l->arr[ix];
	if( strcmp( nm, m->name ) == 0 ) return m;
    }
    return macroNIL;
}

/* Add a new macro to the known macros. If macro a macro of that name
 * exists, overwrite it, else create a new one.
 */
void setmacro(
    const tmstring nm,
    const tmstring fnm,
    const tmstring_list fpl,
    const tplelm_list body
)
{
    unsigned int hv;
    macro nwmacro;
    bool found;
    unsigned int ix;

    if( vartr ){
	fprintf( tracestream, "macro %s defined (ctx=%u)\n", nm, ctxlvl );
    }
    found = findlocmacro( nm, &hv, &ix );
    if( found ){
	macros[hv] = delete_macro_list( macros[hv], ix );
    }
    hv = hashval( nm );
    nwmacro = new_macro(
	ctxlvl,
	rdup_tmstring( nm ),
	rdup_tmstring( fnm ),
	rdup_tmstring_list( fpl ),
	rdup_tplelm_list( body )
    );
    macros[hv] = insert_macro_list( macros[hv], 0, nwmacro ); 
}

/******************************************************
 *    variable management                             *
 ******************************************************/

/* Search in current context level 'lvl' for variable with name 'nm'.
   Return pointer to struct var of variable, or varNIL if not found.
 */
static var findlocvar( const tmstring nm )
{
    var_list l;
    unsigned int hv;
    var v;
    unsigned int ix;

    hv = hashval( nm );
    l = variables[hv];
    for( ix=0; ix<l->sz; ix++ ){
	v = l->arr[ix];
	if( v->lvl==ctxlvl && strcmp( nm, v->name ) == 0 ){
	    return v;
	}
    }
    return varNIL;
}

/* Search in all contexts for variable with name 'nm'. Return pointer to
   struct var of variable, or varNIL if not found.
 */
static var findvar( const tmstring nm )
{
    var_list l;
    unsigned int hv;
    unsigned int ix;
    var v;

    hv = hashval( nm );
    l = variables[hv];
    for( ix=0; ix<l->sz; ix++ ){
	v = l->arr[ix];
	if( strcmp( nm, v->name ) == 0 ) return v;
    }
    return varNIL;
}

/* Add a variable 'nm' with value 'v' to the known variables.
   If variable 'nm' exists, overwrite old value, else create a
   new variable with the given value.
 */
void setvar( const tmstring nm, const tmstring v )
{
    unsigned int hv;
    var nwvar;

    if( vartr ){
	if( nm[0] == '\r' ){
	    fprintf( tracestream, "set return value to '%s' (ctx=%u)\n", v, ctxlvl );
	}
	else {
	    fprintf( tracestream, "set: %s = '%s' (ctx=%u)\n", nm, v, ctxlvl );
	}
    }
    nwvar = findlocvar( nm );
    if( nwvar != varNIL ){
	fre_tmstring( nwvar->val );
	nwvar->val = new_tmstring( v );
	return;
    }
    hv = hashval( nm );
    nwvar = new_var( ctxlvl, new_tmstring( nm ), new_tmstring( v ) );
    variables[hv] = insert_var_list( variables[hv], 0, nwvar ); 
}

/* Start a new variable context. */
void newvarctx( void )
{
    ctxlvl++;
    if( vartr ){
	fprintf( tracestream, "New context (ctx=%u)\n", ctxlvl );
    }
}

/* Drop a context. */
void flushvar( void )
{
    unsigned int hv;
    var_list vl;
    macro_list ml;
    unsigned int ix;

    for( hv=0; hv<HASHWIDTH; hv++ ){
	vl = variables[hv];
	for( ix=0; ix<vl->sz; ix++ ){
	    if( vl->arr[ix]->lvl>=ctxlvl ){
		vl = delete_var_list( vl, ix );
	    }
	}
	variables[hv] = vl;
	ml = macros[hv];
	for( ix=0; ix<ml->sz; ix++ ){
	    if( ml->arr[ix]->lvl>=ctxlvl ){
		ml = delete_macro_list( ml, ix );
	    }
	}
    }
    if( vartr ){
	fprintf( tracestream, "Dropped context %u\n", ctxlvl );
    }
    ctxlvl--;
}

/* Search for variable with name 'nm'. Return pointer to the value of
   'nm', or NULL of not found.
 */
tmstring getvar( const tmstring nm )
{
    var v;

    v = findvar( nm );
    if( v != varNIL ){
	if( vartr )
	    fprintf( tracestream, "found: %s = '%s' (ctx=%u)\n", nm, v->val, v->lvl );
	return v->val;
    }
    if( vartr ) fprintf( tracestream, "not found: %s\n", nm );
    return tmstringNIL;
}

/* Search locally for return variable. Return a copy of its value,
 * or an empty tmstring if not found.
 */
tmstring getretval( void )
{
    var v;

    v = findlocvar( RETVALNAME );
    if( v != varNIL ){
	if( vartr ){
	    fprintf(
		tracestream,
		"found retval: '%s' (ctx=%u)\n",
		v->val,
		v->lvl
	    );
	}
	return new_tmstring( v->val );
    }
    if( vartr ){
	fprintf( tracestream, "retval not found\n" );
    }
    return new_tmstring( "" );
}

/******************************************************
 *    initialization                                  *
 ******************************************************/

/* Initialize 'var' routines. */
void init_var(void )
{
    unsigned int i;

    for( i=0; i<HASHWIDTH; i++ ){
	variables[i] = new_var_list();
    }
    ctxlvl = 0;
    for( i=0; i<HASHWIDTH; i++ ){
	macros[i] = new_macro_list();
    }
}

/* Terminate 'var' routines. */
void end_var( void )
{
    unsigned int i;

    if( ctxlvl!=0 ){
	fprintf(
	    stderr,
	    "Warning: still %d context levels pending!\n",
	    ctxlvl
	);
    }
    for( i=0; i<HASHWIDTH; i++ ){
	rfre_var_list( variables[i] );
    }
    for( i=0; i<HASHWIDTH; i++ ){
	rfre_macro_list( macros[i] );
    }
}
