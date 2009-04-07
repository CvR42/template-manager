/* File $Id$
 *
 * Variable and macro management.
 */

/* standard UNIX libraries */
#include <stdio.h>
#include <time.h>

/* Tm library definitions */
#include <tmc.h>

/* local definitions */
#include "tmdefs.h"

#include "tmcode.h"
#include "tmstring.h"
#include "misc.h"
#include "error.h"
#include "var.h"
#include "global.h"
#include "refex.h"

/******************************************************
 *    hashing parameters                              *    
 ******************************************************/

/* NOTE: The remainder of the code assumes HASHWIDTH is a power of 2. */
#define HASHBITS 6U
#define HASHWIDTH (1U<<HASHBITS)
#define HASHMASK (HASHWIDTH-1)

/******************************************************
 *    Datastructures                                  *    
 ******************************************************/

static variable_list variables[HASHWIDTH];
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
	 v = (v ^ (unsigned int) *s);
	 v<<=1;
	 if( (v & HASHWIDTH) != 0 ) v++;
	 v &= HASHMASK;
	 s++;
    }
    return v;
}

/******************************************************
 *    macro management                                *
 ******************************************************/

/* Search in current context level 'lvl' for macro with name 'nm'.
   Return pointer to variable, or variableNIL if not found.
 */
static tmbool findlocmacro(
    const char *nm,
    unsigned int *hvp,
    unsigned int *ixp
)
{
    macro_list l;
    unsigned int hv;
    unsigned int ix;

    hv = hashval( nm );
    l = macros[hv];
    for( ix=0; ix<l->sz; ix++ ){
        const_macro m = l->arr[ix];

	if( m->lvl==ctxlvl && strcmp( nm, m->name ) == 0 ){
	    *hvp = hv;
	    *ixp = ix;
	    return TRUE;
	}
    }
    return FALSE;
}

/* Search in all contexts for variable with name 'nm'. Return pointer to
   struct macro of variable, or variableNIL if not found.
 */
const_macro findmacro( const char *nm )
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

const char *match_macros( const char *pat, tmstring_list *matches )
{
    const char *errm = ref_comp( pat );
    unsigned int hv;

    if( errm != NULL ){
	return errm;
    }
    for( hv=0; hv<HASHWIDTH; hv++ ){
	unsigned int ix;
	const macro_list l = macros[hv];

	for( ix=0; ix<l->sz; ix++ ){
	    const macro m = l->arr[ix];

	    if( ref_exec( m->name ) ){
		*matches = append_tmstring_list(
		    *matches,
		    rdup_tmstring( m->name )
		);
	    }
	}
    }
    return NULL;
}

const char *match_vars( const char *pat, tmstring_list *matches )
{
    const char *errm = ref_comp( pat );
    unsigned int hv;

    if( errm != NULL ){
	return errm;
    }
    for( hv=0; hv<HASHWIDTH; hv++ ){
	unsigned int ix;
	const_variable_list l = variables[hv];

	for( ix=0; ix<l->sz; ix++ ){
	    const_variable m = l->arr[ix];

	    if( ref_exec( m->name ) ){
		*matches = append_tmstring_list(
		    *matches,
		    rdup_tmstring( m->name )
		);
	    }
	}
    }
    return NULL;
}

/* Add a new macro to the known macros. If macro a macro of that name
 * exists, overwrite it, else create a new one.
 */
void setmacro(
    const char *nm,
    const_origin org,
    const_tmstring_list pl,
    const_tplelm_list body
)
{
    unsigned int hv;
    macro nwmacro;
    tmbool found;
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
        rdup_origin( org ),
	ctxlvl,
	rdup_tmstring( nm ),
	rdup_tmstring_list( pl ),
	rdup_tplelm_list( body )
    );
    macros[hv] = insert_macro_list( macros[hv], 0, nwmacro ); 
}

/******************************************************
 *    variable management                             *
 ******************************************************/

/* Search in current context level 'lvl' for variable with name 'nm'.
   Return pointer to struct variable of variable, or variableNIL if not found.
 */
static /*@observer@*//*@null@*/ variable findlocvar( const char *nm )
{
    variable_list l;
    unsigned int hv;
    variable v;
    unsigned int ix;

    hv = hashval( nm );
    l = variables[hv];
    for( ix=0; ix<l->sz; ix++ ){
	v = l->arr[ix];
	if( v->lvl==ctxlvl && strcmp( nm, v->name ) == 0 ){
	    return v;
	}
    }
    return variableNIL;
}

/* Search in all contexts for variable with name 'nm'. Return pointer to
   struct variable of variable, or variableNIL if not found.
 */
static /*@observer@*//*@null@*/ variable findvar( const char *nm )
{
    variable_list l;
    unsigned int hv;
    unsigned int ix;
    variable v;

    hv = hashval( nm );
    l = variables[hv];
    for( ix=0; ix<l->sz; ix++ ){
	v = l->arr[ix];
	if( strcmp( nm, v->name ) == 0 ) return v;
    }
    return variableNIL;
}

/* Add a variable 'nm' with value 'v' to the known variables.
   If variable 'nm' exists, overwrite old value, else create a
   new variable with the given value.
 */
void setvar( const char *nm, const char *v )
{
    unsigned int hv;
    variable nwvar;

    if( vartr ){
	if( nm[0] == '\r' ){
	    fprintf( tracestream, "set return value to '%s' (ctx=%u)\n", v, ctxlvl );
	}
	else {
	    fprintf( tracestream, "set: %s = '%s' (ctx=%u)\n", nm, v, ctxlvl );
	}
    }
    nwvar = findlocvar( nm );
    if( nwvar != variableNIL ){
	fre_tmstring( nwvar->val );
	nwvar->val = new_tmstring( v );
	return;
    }
    hv = hashval( nm );
    nwvar = new_variable( ctxlvl, new_tmstring( nm ), new_tmstring( v ) );
    variables[hv] = insert_variable_list( variables[hv], 0, nwvar ); 
}

/* Given the hash value of a variable, and the name of the variable,
 * remove this variable from all contexts.
 */
static void zapvar( const unsigned int hv, const char *nm )
{
    variable_list vl;
    unsigned int ix;

    vl = variables[hv];
    ix = 0;
    while( ix<vl->sz ){
	if( strcmp( vl->arr[ix]->name, nm ) == 0 ){
	    vl = delete_variable_list( vl, ix );
	}
	else {
	    ix++;
	}
    }
    variables[hv] = vl;
}

/* Add a variable 'nm' with value 'v' to the known variables.
 * Zap old variables in all contexts, and put this one in the topmost
 * context.
 */
void globalsetvar( const char *nm, const char *v )
{
    unsigned int hv;
    variable nwvar;

    if( vartr ){
	fprintf( tracestream, "global set: %s = '%s'\n", nm, v );
    }
    nwvar = findlocvar( nm );
    if( nwvar != variableNIL ){
	fre_tmstring( nwvar->val );
	nwvar->val = new_tmstring( v );
	return;
    }
    hv = hashval( nm );
    zapvar( hv, nm );
    nwvar = new_variable( 0, new_tmstring( nm ), new_tmstring( v ) );
    variables[hv] = append_variable_list( variables[hv], nwvar ); 
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

    for( hv=0; hv<HASHWIDTH; hv++ ){
        variable_list vl;
        macro_list ml;
        unsigned int ix;

	vl = variables[hv];
	ix = 0;
	while( ix<vl->sz ){
	    if( vl->arr[ix]->lvl>=ctxlvl ){
		vl = delete_variable_list( vl, ix );
	    }
	    else {
		ix++;
	    }
	}
	variables[hv] = vl;
	ml = macros[hv];
	ix = 0;
	while( ix<ml->sz ){
	    if( ml->arr[ix]->lvl>=ctxlvl ){
		ml = delete_macro_list( ml, ix );
	    }
	    else {
		ix++;
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
const_tmstring getvar( const char *nm )
{
    const_variable v = findvar( nm );

    if( v != variableNIL ){
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
    const_variable v = findlocvar( RETVALNAME );

    if( v != variableNIL ){
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

/* Initialize 'variable' routines. */
void init_var(void )
{
    unsigned int i;

    for( i=0; i<HASHWIDTH; i++ ){
	variables[i] = new_variable_list();
    }
    ctxlvl = 0;
    for( i=0; i<HASHWIDTH; i++ ){
	macros[i] = new_macro_list();
    }
}

/* Terminate 'variable' routines. */
void end_var( void )
{
    unsigned int i;

    if( ctxlvl!=0 ){
	fprintf(
	    stderr,
	    "Warning: still %u context levels pending!\n",
	    ctxlvl
	);
    }
    for( i=0; i<HASHWIDTH; i++ ){
	rfre_variable_list( variables[i] );
    }
    for( i=0; i<HASHWIDTH; i++ ){
	rfre_macro_list( macros[i] );
    }
}
