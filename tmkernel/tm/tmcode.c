/* file: tmcode.c */

#include "config.h"

/* Standard UNIX libraries */
#include <stdio.h>

/* Standard tm library */
#include <tmc.h>

/* Local definitions */
#include "tmdefs.h"

#include "tmcode.h"
#include "tmstring.h"
#include "global.h"
#include "misc.h"

/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /usr/local/lib/calu.ct ---- */

/* Routines for 'tm'.

   template file:      /usr/local/lib/calu.ct
   datastructure file: tm.ds
   tm version:         35
   tm kernel version:  *** development -- not for distribution ***
 */

#ifndef FIRSTROOM
#define FIRSTROOM 0
#endif

#ifdef STAT
static long newcnt_alternative_list = 0;
static long frecnt_alternative_list = 0;
static long newcnt_classComponent_list = 0;
static long frecnt_classComponent_list = 0;
static long newcnt_constructor_list = 0;
static long frecnt_constructor_list = 0;
static long newcnt_ds_list = 0;
static long frecnt_ds_list = 0;
static long newcnt_field_list = 0;
static long frecnt_field_list = 0;
static long newcnt_macro_list = 0;
static long frecnt_macro_list = 0;
static long newcnt_tmstring_list = 0;
static long frecnt_tmstring_list = 0;
static long newcnt_tplelm_list = 0;
static long frecnt_tplelm_list = 0;
static long newcnt_var_list = 0;
static long frecnt_var_list = 0;

static long newcnt_alternative = 0;
static long frecnt_alternative = 0;
static long newcnt_CCSuper = 0;
static long frecnt_CCSuper = 0;
static long newcnt_CCFields = 0;
static long frecnt_CCFields = 0;
static long newcnt_CCAlternatives = 0;
static long frecnt_CCAlternatives = 0;
static long newcnt_CCSublist = 0;
static long frecnt_CCSublist = 0;
static long newcnt_constructor = 0;
static long frecnt_constructor = 0;
static long newcnt_DsCons = 0;
static long frecnt_DsCons = 0;
static long newcnt_DsTuple = 0;
static long frecnt_DsTuple = 0;
static long newcnt_DsClass = 0;
static long frecnt_DsClass = 0;
static long newcnt_field = 0;
static long frecnt_field = 0;
static long newcnt_macro = 0;
static long frecnt_macro = 0;
static long newcnt_Plain = 0;
static long frecnt_Plain = 0;
static long newcnt_Foreach = 0;
static long frecnt_Foreach = 0;
static long newcnt_While = 0;
static long frecnt_While = 0;
static long newcnt_If = 0;
static long frecnt_If = 0;
static long newcnt_Set = 0;
static long frecnt_Set = 0;
static long newcnt_Append = 0;
static long frecnt_Append = 0;
static long newcnt_Error = 0;
static long frecnt_Error = 0;
static long newcnt_Exit = 0;
static long frecnt_Exit = 0;
static long newcnt_ExpandInherits = 0;
static long frecnt_ExpandInherits = 0;
static long newcnt_Redirect = 0;
static long frecnt_Redirect = 0;
static long newcnt_Include = 0;
static long frecnt_Include = 0;
static long newcnt_Macro = 0;
static long frecnt_Macro = 0;
static long newcnt_Call = 0;
static long frecnt_Call = 0;
static long newcnt_Return = 0;
static long frecnt_Return = 0;
static long newcnt_Insert = 0;
static long frecnt_Insert = 0;
static long newcnt_var = 0;
static long frecnt_var = 0;
#endif


/* Caching variables.
 *
 * For each type or type list array of CACHESZ elements is maintained that
 * is filled by the fre_<type>() routines. If possible new_<type>() or
 * new_<cons>() uses these elements.
 *
 * All cacheix_<type> variables maintain the index of the first
 * free element in the array.
 */
#ifndef CACHESZ
#define CACHESZ 5
#endif

#ifdef USECACHE
#undef USECACHE
#endif

#if CACHESZ==0
#else
#define USECACHE
#endif

#ifdef USECACHE
static short int cacheix_alternative_list = 0;
static alternative_list cache_alternative_list[CACHESZ]; 
static short int cacheix_classComponent_list = 0;
static classComponent_list cache_classComponent_list[CACHESZ]; 
static short int cacheix_constructor_list = 0;
static constructor_list cache_constructor_list[CACHESZ]; 
static short int cacheix_ds_list = 0;
static ds_list cache_ds_list[CACHESZ]; 
static short int cacheix_field_list = 0;
static field_list cache_field_list[CACHESZ]; 
static short int cacheix_macro_list = 0;
static macro_list cache_macro_list[CACHESZ]; 
static short int cacheix_tmstring_list = 0;
static tmstring_list cache_tmstring_list[CACHESZ]; 
static short int cacheix_tplelm_list = 0;
static tplelm_list cache_tplelm_list[CACHESZ]; 
static short int cacheix_var_list = 0;
static var_list cache_var_list[CACHESZ]; 
static short int cacheix_alternative = 0;
static alternative cache_alternative[CACHESZ];
static short int cacheix_classComponent = 0;
static classComponent cache_classComponent[CACHESZ];
static short int cacheix_constructor = 0;
static constructor cache_constructor[CACHESZ];
static short int cacheix_ds = 0;
static ds cache_ds[CACHESZ];
static short int cacheix_field = 0;
static field cache_field[CACHESZ];
static short int cacheix_macro = 0;
static macro cache_macro[CACHESZ];
static short int cacheix_tplelm = 0;
static tplelm cache_tplelm[CACHESZ];
static short int cacheix_var = 0;
static var cache_var[CACHESZ];
#endif

static char tm_srcfile[] = __FILE__;

#ifdef STAT
static char tm_allocfreed[] = "%-20s: %6ld allocated, %6ld freed.%s\n";
#endif

#ifndef FATAL
#define FATAL(msg) tm_fatal(tm_srcfile,__LINE__,msg)
#endif

/* Error strings. */
static char tm_nilptr[] = "NIL pointer";

#ifndef FATALTAG
#define FATALTAG(tag) tm_badtag(tm_srcfile,__LINE__,tag)
#endif

/**************************************************
 *    set array room routines                     *
 **************************************************/

/* Announce that you will need setroom for 'rm' elements in
 * alternative_list 'l'.
 */
static alternative_list setroom_alternative_list( alternative_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( alternative *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( alternative *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need setroom for 'rm' elements in
 * classComponent_list 'l'.
 */
static classComponent_list setroom_classComponent_list( classComponent_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( classComponent *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( classComponent *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need setroom for 'rm' elements in
 * constructor_list 'l'.
 */
static constructor_list setroom_constructor_list( constructor_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( constructor *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( constructor *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need setroom for 'rm' elements in
 * ds_list 'l'.
 */
static ds_list setroom_ds_list( ds_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( ds *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( ds *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need setroom for 'rm' elements in
 * field_list 'l'.
 */
static field_list setroom_field_list( field_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( field *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( field *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need setroom for 'rm' elements in
 * macro_list 'l'.
 */
static macro_list setroom_macro_list( macro_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( macro *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( macro *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need setroom for 'rm' elements in
 * tmstring_list 'l'.
 */
static tmstring_list setroom_tmstring_list( tmstring_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( tmstring *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( tmstring *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need setroom for 'rm' elements in
 * tplelm_list 'l'.
 */
static tplelm_list setroom_tplelm_list( tplelm_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( tplelm *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( tplelm *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need setroom for 'rm' elements in
 * var_list 'l'.
 */
static var_list setroom_var_list( var_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( var *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( var *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/**************************************************
 *    Allocation routines                         *
 **************************************************/

#ifdef LOGNEW
#undef new_alternative
#define new_alternative(label,component) real_new_alternative(label,component,_f,_l)
#undef new_CCSuper
#undef new_CCFields
#undef new_CCAlternatives
#undef new_CCSublist
#define new_CCSuper(super) real_new_CCSuper(super,_f,_l)
#define new_CCFields(fields) real_new_CCFields(fields,_f,_l)
#define new_CCAlternatives(alternatives) real_new_CCAlternatives(alternatives,_f,_l)
#define new_CCSublist(components) real_new_CCSublist(components,_f,_l)
#undef new_constructor
#define new_constructor(name,fields) real_new_constructor(name,fields,_f,_l)
#undef new_DsCons
#undef new_DsTuple
#undef new_DsClass
#define new_DsCons(name,inherits,constructors) real_new_DsCons(name,inherits,constructors,_f,_l)
#define new_DsTuple(name,inherits,fields) real_new_DsTuple(name,inherits,fields,_f,_l)
#define new_DsClass(name,virtual,inherits,fields) real_new_DsClass(name,virtual,inherits,fields,_f,_l)
#undef new_field
#define new_field(level,name,type) real_new_field(level,name,type,_f,_l)
#undef new_macro
#define new_macro(lvl,name,orgfile,fpl,body) real_new_macro(lvl,name,orgfile,fpl,body,_f,_l)
#undef new_Plain
#undef new_Foreach
#undef new_While
#undef new_If
#undef new_Set
#undef new_Append
#undef new_Error
#undef new_Exit
#undef new_ExpandInherits
#undef new_Redirect
#undef new_Include
#undef new_Macro
#undef new_Call
#undef new_Return
#undef new_Insert
#define new_Plain(lno,plainline) real_new_Plain(lno,plainline,_f,_l)
#define new_Foreach(lno,felist,felines) real_new_Foreach(lno,felist,felines,_f,_l)
#define new_While(lno,whilecond,whilelines) real_new_While(lno,whilecond,whilelines,_f,_l)
#define new_If(lno,ifcond,ifthen,ifelse) real_new_If(lno,ifcond,ifthen,ifelse,_f,_l)
#define new_Set(lno,setline) real_new_Set(lno,setline,_f,_l)
#define new_Append(lno,appline) real_new_Append(lno,appline,_f,_l)
#define new_Error(lno,errstr) real_new_Error(lno,errstr,_f,_l)
#define new_Exit(lno,str) real_new_Exit(lno,str,_f,_l)
#define new_ExpandInherits(lno,types) real_new_ExpandInherits(lno,types,_f,_l)
#define new_Redirect(lno,fname,body) real_new_Redirect(lno,fname,body,_f,_l)
#define new_Include(lno,fname) real_new_Include(lno,fname,_f,_l)
#define new_Macro(lno,formpar,macbody) real_new_Macro(lno,formpar,macbody,_f,_l)
#define new_Call(lno,callline) real_new_Call(lno,callline,_f,_l)
#define new_Return(lno,retval) real_new_Return(lno,retval,_f,_l)
#define new_Insert(lno,fname) real_new_Insert(lno,fname,_f,_l)
#undef new_var
#define new_var(lvl,name,val) real_new_var(lvl,name,val,_f,_l)
#undef new_alternative_list
#define new_alternative_list() real_new_alternative_list(_f,_l)
#undef new_classComponent_list
#define new_classComponent_list() real_new_classComponent_list(_f,_l)
#undef new_constructor_list
#define new_constructor_list() real_new_constructor_list(_f,_l)
#undef new_ds_list
#define new_ds_list() real_new_ds_list(_f,_l)
#undef new_field_list
#define new_field_list() real_new_field_list(_f,_l)
#undef new_macro_list
#define new_macro_list() real_new_macro_list(_f,_l)
#undef new_tmstring_list
#define new_tmstring_list() real_new_tmstring_list(_f,_l)
#undef new_tplelm_list
#define new_tplelm_list() real_new_tplelm_list(_f,_l)
#undef new_var_list
#define new_var_list() real_new_var_list(_f,_l)
#endif

#ifdef LOGNEW
alternative_list real_new_alternative_list( const char *_f, const int _l )
#else
alternative_list new_alternative_list( void )
#endif
{
    alternative_list nw;

#ifdef USECACHE
    if( cacheix_alternative_list > 0 ){
	nw = cache_alternative_list[--cacheix_alternative_list];
    }
    else {
#endif
	nw = TM_MALLOC( alternative_list, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (alternative *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( alternative *, FIRSTROOM*sizeof(alternative) );
    nw->room = FIRSTROOM;
#endif
#ifdef STAT
    newcnt_alternative_list++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
classComponent_list real_new_classComponent_list( const char *_f, const int _l )
#else
classComponent_list new_classComponent_list( void )
#endif
{
    classComponent_list nw;

#ifdef USECACHE
    if( cacheix_classComponent_list > 0 ){
	nw = cache_classComponent_list[--cacheix_classComponent_list];
    }
    else {
#endif
	nw = TM_MALLOC( classComponent_list, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (classComponent *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( classComponent *, FIRSTROOM*sizeof(classComponent) );
    nw->room = FIRSTROOM;
#endif
#ifdef STAT
    newcnt_classComponent_list++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
constructor_list real_new_constructor_list( const char *_f, const int _l )
#else
constructor_list new_constructor_list( void )
#endif
{
    constructor_list nw;

#ifdef USECACHE
    if( cacheix_constructor_list > 0 ){
	nw = cache_constructor_list[--cacheix_constructor_list];
    }
    else {
#endif
	nw = TM_MALLOC( constructor_list, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (constructor *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( constructor *, FIRSTROOM*sizeof(constructor) );
    nw->room = FIRSTROOM;
#endif
#ifdef STAT
    newcnt_constructor_list++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
ds_list real_new_ds_list( const char *_f, const int _l )
#else
ds_list new_ds_list( void )
#endif
{
    ds_list nw;

#ifdef USECACHE
    if( cacheix_ds_list > 0 ){
	nw = cache_ds_list[--cacheix_ds_list];
    }
    else {
#endif
	nw = TM_MALLOC( ds_list, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (ds *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( ds *, FIRSTROOM*sizeof(ds) );
    nw->room = FIRSTROOM;
#endif
#ifdef STAT
    newcnt_ds_list++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
field_list real_new_field_list( const char *_f, const int _l )
#else
field_list new_field_list( void )
#endif
{
    field_list nw;

#ifdef USECACHE
    if( cacheix_field_list > 0 ){
	nw = cache_field_list[--cacheix_field_list];
    }
    else {
#endif
	nw = TM_MALLOC( field_list, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (field *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( field *, FIRSTROOM*sizeof(field) );
    nw->room = FIRSTROOM;
#endif
#ifdef STAT
    newcnt_field_list++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
macro_list real_new_macro_list( const char *_f, const int _l )
#else
macro_list new_macro_list( void )
#endif
{
    macro_list nw;

#ifdef USECACHE
    if( cacheix_macro_list > 0 ){
	nw = cache_macro_list[--cacheix_macro_list];
    }
    else {
#endif
	nw = TM_MALLOC( macro_list, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (macro *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( macro *, FIRSTROOM*sizeof(macro) );
    nw->room = FIRSTROOM;
#endif
#ifdef STAT
    newcnt_macro_list++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tmstring_list real_new_tmstring_list( const char *_f, const int _l )
#else
tmstring_list new_tmstring_list( void )
#endif
{
    tmstring_list nw;

#ifdef USECACHE
    if( cacheix_tmstring_list > 0 ){
	nw = cache_tmstring_list[--cacheix_tmstring_list];
    }
    else {
#endif
	nw = TM_MALLOC( tmstring_list, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (tmstring *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( tmstring *, FIRSTROOM*sizeof(tmstring) );
    nw->room = FIRSTROOM;
#endif
#ifdef STAT
    newcnt_tmstring_list++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm_list real_new_tplelm_list( const char *_f, const int _l )
#else
tplelm_list new_tplelm_list( void )
#endif
{
    tplelm_list nw;

#ifdef USECACHE
    if( cacheix_tplelm_list > 0 ){
	nw = cache_tplelm_list[--cacheix_tplelm_list];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm_list, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (tplelm *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( tplelm *, FIRSTROOM*sizeof(tplelm) );
    nw->room = FIRSTROOM;
#endif
#ifdef STAT
    newcnt_tplelm_list++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
var_list real_new_var_list( const char *_f, const int _l )
#else
var_list new_var_list( void )
#endif
{
    var_list nw;

#ifdef USECACHE
    if( cacheix_var_list > 0 ){
	nw = cache_var_list[--cacheix_var_list];
    }
    else {
#endif
	nw = TM_MALLOC( var_list, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (var *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( var *, FIRSTROOM*sizeof(var) );
    nw->room = FIRSTROOM;
#endif
#ifdef STAT
    newcnt_var_list++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
alternative real_new_alternative( tmstring p_label, classComponent p_component, const char *_f, const int _l )
#else
alternative new_alternative( tmstring p_label, classComponent p_component )
#endif
{
    alternative nw;

#ifdef USECACHE
    if( cacheix_alternative > 0 ){
	nw = cache_alternative[--cacheix_alternative];
    }
    else {
#endif
	nw = TM_MALLOC( alternative, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->label = p_label;
    nw->component = p_component;
#ifdef STAT
    newcnt_alternative++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
classComponent real_new_CCSuper( tmstring p_super, const char *_f, const int _l )
#else
classComponent new_CCSuper( tmstring p_super )
#endif
{
    classComponent nw;

#ifdef USECACHE
    if( cacheix_classComponent > 0 ){
	nw = cache_classComponent[--cacheix_classComponent];
    }
    else {
#endif
	nw = TM_MALLOC( classComponent, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGCCSuper;
    nw->CCSuper.super = p_super;
#ifdef STAT
    newcnt_CCSuper++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
classComponent real_new_CCFields( field_list p_fields, const char *_f, const int _l )
#else
classComponent new_CCFields( field_list p_fields )
#endif
{
    classComponent nw;

#ifdef USECACHE
    if( cacheix_classComponent > 0 ){
	nw = cache_classComponent[--cacheix_classComponent];
    }
    else {
#endif
	nw = TM_MALLOC( classComponent, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGCCFields;
    nw->CCFields.fields = p_fields;
#ifdef STAT
    newcnt_CCFields++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
classComponent real_new_CCAlternatives( alternative_list p_alternatives, const char *_f, const int _l )
#else
classComponent new_CCAlternatives( alternative_list p_alternatives )
#endif
{
    classComponent nw;

#ifdef USECACHE
    if( cacheix_classComponent > 0 ){
	nw = cache_classComponent[--cacheix_classComponent];
    }
    else {
#endif
	nw = TM_MALLOC( classComponent, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGCCAlternatives;
    nw->CCAlternatives.alternatives = p_alternatives;
#ifdef STAT
    newcnt_CCAlternatives++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
classComponent real_new_CCSublist( classComponent_list p_components, const char *_f, const int _l )
#else
classComponent new_CCSublist( classComponent_list p_components )
#endif
{
    classComponent nw;

#ifdef USECACHE
    if( cacheix_classComponent > 0 ){
	nw = cache_classComponent[--cacheix_classComponent];
    }
    else {
#endif
	nw = TM_MALLOC( classComponent, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGCCSublist;
    nw->CCSublist.components = p_components;
#ifdef STAT
    newcnt_CCSublist++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
constructor real_new_constructor( tmstring p_name, field_list p_fields, const char *_f, const int _l )
#else
constructor new_constructor( tmstring p_name, field_list p_fields )
#endif
{
    constructor nw;

#ifdef USECACHE
    if( cacheix_constructor > 0 ){
	nw = cache_constructor[--cacheix_constructor];
    }
    else {
#endif
	nw = TM_MALLOC( constructor, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->name = p_name;
    nw->fields = p_fields;
#ifdef STAT
    newcnt_constructor++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
ds real_new_DsCons( tmstring p_name, tmstring_list p_inherits, constructor_list p_constructors, const char *_f, const int _l )
#else
ds new_DsCons( tmstring p_name, tmstring_list p_inherits, constructor_list p_constructors )
#endif
{
    ds nw;

#ifdef USECACHE
    if( cacheix_ds > 0 ){
	nw = cache_ds[--cacheix_ds];
    }
    else {
#endif
	nw = TM_MALLOC( ds, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGDsCons;
    nw->DsCons.name = p_name;
    nw->DsCons.inherits = p_inherits;
    nw->DsCons.constructors = p_constructors;
#ifdef STAT
    newcnt_DsCons++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
ds real_new_DsTuple( tmstring p_name, tmstring_list p_inherits, field_list p_fields, const char *_f, const int _l )
#else
ds new_DsTuple( tmstring p_name, tmstring_list p_inherits, field_list p_fields )
#endif
{
    ds nw;

#ifdef USECACHE
    if( cacheix_ds > 0 ){
	nw = cache_ds[--cacheix_ds];
    }
    else {
#endif
	nw = TM_MALLOC( ds, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGDsTuple;
    nw->DsTuple.name = p_name;
    nw->DsTuple.inherits = p_inherits;
    nw->DsTuple.fields = p_fields;
#ifdef STAT
    newcnt_DsTuple++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
ds real_new_DsClass( tmstring p_name, tmbool p_virtual, tmstring_list p_inherits, field_list p_fields, const char *_f, const int _l )
#else
ds new_DsClass( tmstring p_name, tmbool p_virtual, tmstring_list p_inherits, field_list p_fields )
#endif
{
    ds nw;

#ifdef USECACHE
    if( cacheix_ds > 0 ){
	nw = cache_ds[--cacheix_ds];
    }
    else {
#endif
	nw = TM_MALLOC( ds, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGDsClass;
    nw->DsClass.name = p_name;
    nw->DsClass.virtual = p_virtual;
    nw->DsClass.inherits = p_inherits;
    nw->DsClass.fields = p_fields;
#ifdef STAT
    newcnt_DsClass++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
field real_new_field( int p_level, tmstring p_name, tmstring p_type, const char *_f, const int _l )
#else
field new_field( int p_level, tmstring p_name, tmstring p_type )
#endif
{
    field nw;

#ifdef USECACHE
    if( cacheix_field > 0 ){
	nw = cache_field[--cacheix_field];
    }
    else {
#endif
	nw = TM_MALLOC( field, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->level = p_level;
    nw->name = p_name;
    nw->type = p_type;
#ifdef STAT
    newcnt_field++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
macro real_new_macro( uint p_lvl, tmstring p_name, tmstring p_orgfile, tmstring_list p_fpl, tplelm_list p_body, const char *_f, const int _l )
#else
macro new_macro( uint p_lvl, tmstring p_name, tmstring p_orgfile, tmstring_list p_fpl, tplelm_list p_body )
#endif
{
    macro nw;

#ifdef USECACHE
    if( cacheix_macro > 0 ){
	nw = cache_macro[--cacheix_macro];
    }
    else {
#endif
	nw = TM_MALLOC( macro, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->lvl = p_lvl;
    nw->name = p_name;
    nw->orgfile = p_orgfile;
    nw->fpl = p_fpl;
    nw->body = p_body;
#ifdef STAT
    newcnt_macro++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Plain( int p_lno, tmstring p_plainline, const char *_f, const int _l )
#else
tplelm new_Plain( int p_lno, tmstring p_plainline )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGPlain;
    nw->Plain.lno = p_lno;
    nw->Plain.plainline = p_plainline;
#ifdef STAT
    newcnt_Plain++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Foreach( int p_lno, tmstring p_felist, tplelm_list p_felines, const char *_f, const int _l )
#else
tplelm new_Foreach( int p_lno, tmstring p_felist, tplelm_list p_felines )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGForeach;
    nw->Foreach.lno = p_lno;
    nw->Foreach.felist = p_felist;
    nw->Foreach.felines = p_felines;
#ifdef STAT
    newcnt_Foreach++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_While( int p_lno, tmstring p_whilecond, tplelm_list p_whilelines, const char *_f, const int _l )
#else
tplelm new_While( int p_lno, tmstring p_whilecond, tplelm_list p_whilelines )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGWhile;
    nw->While.lno = p_lno;
    nw->While.whilecond = p_whilecond;
    nw->While.whilelines = p_whilelines;
#ifdef STAT
    newcnt_While++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_If( int p_lno, tmstring p_ifcond, tplelm_list p_ifthen, tplelm_list p_ifelse, const char *_f, const int _l )
#else
tplelm new_If( int p_lno, tmstring p_ifcond, tplelm_list p_ifthen, tplelm_list p_ifelse )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGIf;
    nw->If.lno = p_lno;
    nw->If.ifcond = p_ifcond;
    nw->If.ifthen = p_ifthen;
    nw->If.ifelse = p_ifelse;
#ifdef STAT
    newcnt_If++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Set( int p_lno, tmstring p_setline, const char *_f, const int _l )
#else
tplelm new_Set( int p_lno, tmstring p_setline )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGSet;
    nw->Set.lno = p_lno;
    nw->Set.setline = p_setline;
#ifdef STAT
    newcnt_Set++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Append( int p_lno, tmstring p_appline, const char *_f, const int _l )
#else
tplelm new_Append( int p_lno, tmstring p_appline )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGAppend;
    nw->Append.lno = p_lno;
    nw->Append.appline = p_appline;
#ifdef STAT
    newcnt_Append++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Error( int p_lno, tmstring p_errstr, const char *_f, const int _l )
#else
tplelm new_Error( int p_lno, tmstring p_errstr )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGError;
    nw->Error.lno = p_lno;
    nw->Error.errstr = p_errstr;
#ifdef STAT
    newcnt_Error++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Exit( int p_lno, tmstring p_str, const char *_f, const int _l )
#else
tplelm new_Exit( int p_lno, tmstring p_str )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGExit;
    nw->Exit.lno = p_lno;
    nw->Exit.str = p_str;
#ifdef STAT
    newcnt_Exit++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_ExpandInherits( int p_lno, tmstring p_types, const char *_f, const int _l )
#else
tplelm new_ExpandInherits( int p_lno, tmstring p_types )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGExpandInherits;
    nw->ExpandInherits.lno = p_lno;
    nw->ExpandInherits.types = p_types;
#ifdef STAT
    newcnt_ExpandInherits++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Redirect( int p_lno, tmstring p_fname, tplelm_list p_body, const char *_f, const int _l )
#else
tplelm new_Redirect( int p_lno, tmstring p_fname, tplelm_list p_body )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGRedirect;
    nw->Redirect.lno = p_lno;
    nw->Redirect.fname = p_fname;
    nw->Redirect.body = p_body;
#ifdef STAT
    newcnt_Redirect++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Include( int p_lno, tmstring p_fname, const char *_f, const int _l )
#else
tplelm new_Include( int p_lno, tmstring p_fname )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGInclude;
    nw->Include.lno = p_lno;
    nw->Include.fname = p_fname;
#ifdef STAT
    newcnt_Include++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Macro( int p_lno, tmstring p_formpar, tplelm_list p_macbody, const char *_f, const int _l )
#else
tplelm new_Macro( int p_lno, tmstring p_formpar, tplelm_list p_macbody )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGMacro;
    nw->Macro.lno = p_lno;
    nw->Macro.formpar = p_formpar;
    nw->Macro.macbody = p_macbody;
#ifdef STAT
    newcnt_Macro++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Call( int p_lno, tmstring p_callline, const char *_f, const int _l )
#else
tplelm new_Call( int p_lno, tmstring p_callline )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGCall;
    nw->Call.lno = p_lno;
    nw->Call.callline = p_callline;
#ifdef STAT
    newcnt_Call++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Return( int p_lno, tmstring p_retval, const char *_f, const int _l )
#else
tplelm new_Return( int p_lno, tmstring p_retval )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGReturn;
    nw->Return.lno = p_lno;
    nw->Return.retval = p_retval;
#ifdef STAT
    newcnt_Return++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Insert( int p_lno, tmstring p_fname, const char *_f, const int _l )
#else
tplelm new_Insert( int p_lno, tmstring p_fname )
#endif
{
    tplelm nw;

#ifdef USECACHE
    if( cacheix_tplelm > 0 ){
	nw = cache_tplelm[--cacheix_tplelm];
    }
    else {
#endif
	nw = TM_MALLOC( tplelm, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->tag = TAGInsert;
    nw->Insert.lno = p_lno;
    nw->Insert.fname = p_fname;
#ifdef STAT
    newcnt_Insert++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
var real_new_var( uint p_lvl, tmstring p_name, tmstring p_val, const char *_f, const int _l )
#else
var new_var( uint p_lvl, tmstring p_name, tmstring p_val )
#endif
{
    var nw;

#ifdef USECACHE
    if( cacheix_var > 0 ){
	nw = cache_var[--cacheix_var];
    }
    else {
#endif
	nw = TM_MALLOC( var, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->lvl = p_lvl;
    nw->name = p_name;
    nw->val = p_val;
#ifdef STAT
    newcnt_var++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/**************************************************
 *    Freeing routines                            *
 **************************************************/

/* Free an element 'e' of type 'alternative'. */
static void fre_alternative( alternative e )
{
    if( e == alternativeNIL ){
	return;
    }
#ifdef STAT
    frecnt_alternative++;
#endif
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
#ifdef USECACHE
    if( cacheix_alternative<CACHESZ ){
	cache_alternative[cacheix_alternative++] = e;
	return;
    }
#endif
    TM_FREE( e );
}

/* Free an element 'e' of type 'classComponent'. */
static void fre_classComponent( classComponent e )
{
    if( e == classComponentNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
#ifdef STAT
    switch( e->tag ){
	case TAGCCSuper:
	    frecnt_CCSuper++;
	    break;

	case TAGCCFields:
	    frecnt_CCFields++;
	    break;

	case TAGCCAlternatives:
	    frecnt_CCAlternatives++;
	    break;

	case TAGCCSublist:
	    frecnt_CCSublist++;
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
#endif
#ifdef USECACHE
    if( cacheix_classComponent<CACHESZ ){
	cache_classComponent[cacheix_classComponent++] = e;
	return;
    }
#endif
    TM_FREE( e );
}

/* Free an element 'e' of type 'constructor'. */
static void fre_constructor( constructor e )
{
    if( e == constructorNIL ){
	return;
    }
#ifdef STAT
    frecnt_constructor++;
#endif
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
#ifdef USECACHE
    if( cacheix_constructor<CACHESZ ){
	cache_constructor[cacheix_constructor++] = e;
	return;
    }
#endif
    TM_FREE( e );
}

/* Free an element 'e' of type 'ds'. */
static void fre_ds( ds e )
{
    if( e == dsNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
#ifdef STAT
    switch( e->tag ){
	case TAGDsCons:
	    frecnt_DsCons++;
	    break;

	case TAGDsTuple:
	    frecnt_DsTuple++;
	    break;

	case TAGDsClass:
	    frecnt_DsClass++;
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
#endif
#ifdef USECACHE
    if( cacheix_ds<CACHESZ ){
	cache_ds[cacheix_ds++] = e;
	return;
    }
#endif
    TM_FREE( e );
}

/* Free an element 'e' of type 'field'. */
static void fre_field( field e )
{
    if( e == fieldNIL ){
	return;
    }
#ifdef STAT
    frecnt_field++;
#endif
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
#ifdef USECACHE
    if( cacheix_field<CACHESZ ){
	cache_field[cacheix_field++] = e;
	return;
    }
#endif
    TM_FREE( e );
}

/* Free an element 'e' of type 'macro'. */
static void fre_macro( macro e )
{
    if( e == macroNIL ){
	return;
    }
#ifdef STAT
    frecnt_macro++;
#endif
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
#ifdef USECACHE
    if( cacheix_macro<CACHESZ ){
	cache_macro[cacheix_macro++] = e;
	return;
    }
#endif
    TM_FREE( e );
}

/* Free an element 'e' of type 'tplelm'. */
static void fre_tplelm( tplelm e )
{
    if( e == tplelmNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
#ifdef STAT
    switch( e->tag ){
	case TAGPlain:
	    frecnt_Plain++;
	    break;

	case TAGForeach:
	    frecnt_Foreach++;
	    break;

	case TAGWhile:
	    frecnt_While++;
	    break;

	case TAGIf:
	    frecnt_If++;
	    break;

	case TAGSet:
	    frecnt_Set++;
	    break;

	case TAGAppend:
	    frecnt_Append++;
	    break;

	case TAGError:
	    frecnt_Error++;
	    break;

	case TAGExit:
	    frecnt_Exit++;
	    break;

	case TAGExpandInherits:
	    frecnt_ExpandInherits++;
	    break;

	case TAGRedirect:
	    frecnt_Redirect++;
	    break;

	case TAGInclude:
	    frecnt_Include++;
	    break;

	case TAGMacro:
	    frecnt_Macro++;
	    break;

	case TAGCall:
	    frecnt_Call++;
	    break;

	case TAGReturn:
	    frecnt_Return++;
	    break;

	case TAGInsert:
	    frecnt_Insert++;
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
#endif
#ifdef USECACHE
    if( cacheix_tplelm<CACHESZ ){
	cache_tplelm[cacheix_tplelm++] = e;
	return;
    }
#endif
    TM_FREE( e );
}

/* Free an element 'e' of type 'var'. */
static void fre_var( var e )
{
    if( e == varNIL ){
	return;
    }
#ifdef STAT
    frecnt_var++;
#endif
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
#ifdef USECACHE
    if( cacheix_var<CACHESZ ){
	cache_var[cacheix_var++] = e;
	return;
    }
#endif
    TM_FREE( e );
}

/* Free a list of alternative elements 'l'. */
static void fre_alternative_list( alternative_list l )
{
    if( l == alternative_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
#ifdef STAT
    frecnt_alternative_list++;
#endif
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
#ifdef USECACHE
    if( cacheix_alternative_list<CACHESZ ){
	cache_alternative_list[cacheix_alternative_list++] = l;
	return;
    }
#endif
    TM_FREE( l );
}

/* Free a list of classComponent elements 'l'. */
static void fre_classComponent_list( classComponent_list l )
{
    if( l == classComponent_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
#ifdef STAT
    frecnt_classComponent_list++;
#endif
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
#ifdef USECACHE
    if( cacheix_classComponent_list<CACHESZ ){
	cache_classComponent_list[cacheix_classComponent_list++] = l;
	return;
    }
#endif
    TM_FREE( l );
}

/* Free a list of constructor elements 'l'. */
static void fre_constructor_list( constructor_list l )
{
    if( l == constructor_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
#ifdef STAT
    frecnt_constructor_list++;
#endif
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
#ifdef USECACHE
    if( cacheix_constructor_list<CACHESZ ){
	cache_constructor_list[cacheix_constructor_list++] = l;
	return;
    }
#endif
    TM_FREE( l );
}

/* Free a list of ds elements 'l'. */
static void fre_ds_list( ds_list l )
{
    if( l == ds_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
#ifdef STAT
    frecnt_ds_list++;
#endif
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
#ifdef USECACHE
    if( cacheix_ds_list<CACHESZ ){
	cache_ds_list[cacheix_ds_list++] = l;
	return;
    }
#endif
    TM_FREE( l );
}

/* Free a list of field elements 'l'. */
static void fre_field_list( field_list l )
{
    if( l == field_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
#ifdef STAT
    frecnt_field_list++;
#endif
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
#ifdef USECACHE
    if( cacheix_field_list<CACHESZ ){
	cache_field_list[cacheix_field_list++] = l;
	return;
    }
#endif
    TM_FREE( l );
}

/* Free a list of macro elements 'l'. */
static void fre_macro_list( macro_list l )
{
    if( l == macro_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
#ifdef STAT
    frecnt_macro_list++;
#endif
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
#ifdef USECACHE
    if( cacheix_macro_list<CACHESZ ){
	cache_macro_list[cacheix_macro_list++] = l;
	return;
    }
#endif
    TM_FREE( l );
}

/* Free a list of tmstring elements 'l'. */
static void fre_tmstring_list( tmstring_list l )
{
    if( l == tmstring_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
#ifdef STAT
    frecnt_tmstring_list++;
#endif
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
#ifdef USECACHE
    if( cacheix_tmstring_list<CACHESZ ){
	cache_tmstring_list[cacheix_tmstring_list++] = l;
	return;
    }
#endif
    TM_FREE( l );
}

/* Free a list of tplelm elements 'l'. */
static void fre_tplelm_list( tplelm_list l )
{
    if( l == tplelm_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
#ifdef STAT
    frecnt_tplelm_list++;
#endif
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
#ifdef USECACHE
    if( cacheix_tplelm_list<CACHESZ ){
	cache_tplelm_list[cacheix_tplelm_list++] = l;
	return;
    }
#endif
    TM_FREE( l );
}

/* Free a list of var elements 'l'. */
static void fre_var_list( var_list l )
{
    if( l == var_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
#ifdef STAT
    frecnt_var_list++;
#endif
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
#ifdef USECACHE
    if( cacheix_var_list<CACHESZ ){
	cache_var_list[cacheix_var_list++] = l;
	return;
    }
#endif
    TM_FREE( l );
}

/**************************************************
 *    Real append routines                        *
 **************************************************/


/* Append a alternative element 'e' to list 'l', and return the new list. */
alternative_list append_alternative_list( alternative_list l, alternative e )
{
    if( l->sz >= l->room ){
	l = setroom_alternative_list( l, 1+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a classComponent element 'e' to list 'l', and return the new list. */
classComponent_list append_classComponent_list( classComponent_list l, classComponent e )
{
    if( l->sz >= l->room ){
	l = setroom_classComponent_list( l, 1+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a constructor element 'e' to list 'l', and return the new list. */
constructor_list append_constructor_list( constructor_list l, constructor e )
{
    if( l->sz >= l->room ){
	l = setroom_constructor_list( l, 1+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a ds element 'e' to list 'l', and return the new list. */
ds_list append_ds_list( ds_list l, ds e )
{
    if( l->sz >= l->room ){
	l = setroom_ds_list( l, 1+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a field element 'e' to list 'l', and return the new list. */
field_list append_field_list( field_list l, field e )
{
    if( l->sz >= l->room ){
	l = setroom_field_list( l, 1+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a tmstring element 'e' to list 'l', and return the new list. */
tmstring_list append_tmstring_list( tmstring_list l, tmstring e )
{
    if( l->sz >= l->room ){
	l = setroom_tmstring_list( l, 1+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a tplelm element 'e' to list 'l', and return the new list. */
tplelm_list append_tplelm_list( tplelm_list l, tplelm e )
{
    if( l->sz >= l->room ){
	l = setroom_tplelm_list( l, 1+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/**************************************************
 *    insert_<type>_list routines                 *
 **************************************************/

/* Insert a macro element 'e' to into list 'l' at position 'pos'. */
macro_list insert_macro_list( macro_list l, const unsigned int pos, macro e )
{
    unsigned int ix;
    macro *arr;
    unsigned int the_pos = pos;

    if( l == macro_listNIL ){
	FATAL( tm_nilptr );
    }
    if( l->sz >= l->room ){
	l = setroom_macro_list( l, 1+(l->sz)+(l->sz) );
    }
    if( the_pos>l->sz ){
	the_pos = l->sz;
    }
    arr = l->arr;
    for( ix=l->sz; ix>the_pos; ix-- ){
	arr[ix] = arr[ix-1];
    }
    l->sz++;
    arr[the_pos] = e;
    return l;
}

/* Insert a tmstring element 'e' to into list 'l' at position 'pos'. */
tmstring_list insert_tmstring_list( tmstring_list l, const unsigned int pos, tmstring e )
{
    unsigned int ix;
    tmstring *arr;
    unsigned int the_pos = pos;

    if( l == tmstring_listNIL ){
	FATAL( tm_nilptr );
    }
    if( l->sz >= l->room ){
	l = setroom_tmstring_list( l, 1+(l->sz)+(l->sz) );
    }
    if( the_pos>l->sz ){
	the_pos = l->sz;
    }
    arr = l->arr;
    for( ix=l->sz; ix>the_pos; ix-- ){
	arr[ix] = arr[ix-1];
    }
    l->sz++;
    arr[the_pos] = e;
    return l;
}

/* Insert a var element 'e' to into list 'l' at position 'pos'. */
var_list insert_var_list( var_list l, const unsigned int pos, var e )
{
    unsigned int ix;
    var *arr;
    unsigned int the_pos = pos;

    if( l == var_listNIL ){
	FATAL( tm_nilptr );
    }
    if( l->sz >= l->room ){
	l = setroom_var_list( l, 1+(l->sz)+(l->sz) );
    }
    if( the_pos>l->sz ){
	the_pos = l->sz;
    }
    arr = l->arr;
    for( ix=l->sz; ix>the_pos; ix-- ){
	arr[ix] = arr[ix-1];
    }
    l->sz++;
    arr[the_pos] = e;
    return l;
}

/**********************************************
 *    concatenate routines                    *
 **********************************************/

/* Concatenate ds list 'lb' after ds list 'la'.
   The list descriptor of list 'lb' is freed,
   since its contents has been moved to 'la'.
 */
ds_list concat_ds_list( ds_list la, ds_list lb )
{
    unsigned int cnt;
    ds *sp;
    ds *dp;

    la = setroom_ds_list( la, la->sz+lb->sz );
    cnt = lb->sz;
    sp = lb->arr;
    dp = &la->arr[la->sz];
    while( cnt!=0 ){
	*dp++ = *sp++;
	cnt--;
    }
    la->sz += lb->sz;
    fre_ds_list( lb );
    return la;
}

/* Concatenate field list 'lb' after field list 'la'.
   The list descriptor of list 'lb' is freed,
   since its contents has been moved to 'la'.
 */
field_list concat_field_list( field_list la, field_list lb )
{
    unsigned int cnt;
    field *sp;
    field *dp;

    la = setroom_field_list( la, la->sz+lb->sz );
    cnt = lb->sz;
    sp = lb->arr;
    dp = &la->arr[la->sz];
    while( cnt!=0 ){
	*dp++ = *sp++;
	cnt--;
    }
    la->sz += lb->sz;
    fre_field_list( lb );
    return la;
}

/**************************************************
 *    Recursive freeing routines                  *
 **************************************************/

static void rfre_constructor_list( constructor_list );

static void rfre_alternative( alternative );
static void rfre_field( field );
static void rfre_var( var );

/* Recursively free an element 'e' of type 'ds'
   and all elements in it.
 */
void rfre_ds( ds e )
{
    if( e == dsNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsCons:
	    rfre_tmstring( e->DsCons.name );
	    rfre_tmstring_list( e->DsCons.inherits );
	    rfre_constructor_list( e->DsCons.constructors );
	    break;

	case TAGDsTuple:
	    rfre_tmstring( e->DsTuple.name );
	    rfre_tmstring_list( e->DsTuple.inherits );
	    rfre_field_list( e->DsTuple.fields );
	    break;

	case TAGDsClass:
	    rfre_tmstring( e->DsClass.name );
	    rfre_tmbool( e->DsClass.virtual );
	    rfre_tmstring_list( e->DsClass.inherits );
	    rfre_field_list( e->DsClass.fields );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
    fre_ds( e );
}

/* Recursively free an element 'e' of type 'classComponent'
   and all elements in it.
 */
void rfre_classComponent( classComponent e )
{
    if( e == classComponentNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCCSuper:
	    rfre_tmstring( e->CCSuper.super );
	    break;

	case TAGCCFields:
	    rfre_field_list( e->CCFields.fields );
	    break;

	case TAGCCAlternatives:
	    rfre_alternative_list( e->CCAlternatives.alternatives );
	    break;

	case TAGCCSublist:
	    rfre_classComponent_list( e->CCSublist.components );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
    fre_classComponent( e );
}

/* Recursively free an element 'e' of type 'alternative'
   and all elements in it.
 */
static void rfre_alternative( alternative e )
{
    if( e == alternativeNIL ){
	return;
    }
    rfre_tmstring( e->label );
    rfre_classComponent( e->component );
    fre_alternative( e );
}

/* Recursively free an element 'e' of type 'constructor'
   and all elements in it.
 */
void rfre_constructor( constructor e )
{
    if( e == constructorNIL ){
	return;
    }
    rfre_tmstring( e->name );
    rfre_field_list( e->fields );
    fre_constructor( e );
}

/* Recursively free an element 'e' of type 'field'
   and all elements in it.
 */
static void rfre_field( field e )
{
    if( e == fieldNIL ){
	return;
    }
    rfre_int( e->level );
    rfre_tmstring( e->name );
    rfre_tmstring( e->type );
    fre_field( e );
}

/* Recursively free an element 'e' of type 'macro'
   and all elements in it.
 */
void rfre_macro( macro e )
{
    if( e == macroNIL ){
	return;
    }
    rfre_uint( e->lvl );
    rfre_tmstring( e->name );
    rfre_tmstring( e->orgfile );
    rfre_tmstring_list( e->fpl );
    rfre_tplelm_list( e->body );
    fre_macro( e );
}

/* Recursively free an element 'e' of type 'var'
   and all elements in it.
 */
static void rfre_var( var e )
{
    if( e == varNIL ){
	return;
    }
    rfre_uint( e->lvl );
    rfre_tmstring( e->name );
    rfre_tmstring( e->val );
    fre_var( e );
}

/* Recursively free an element 'e' of type 'tplelm'
   and all elements in it.
 */
void rfre_tplelm( tplelm e )
{
    if( e == tplelmNIL ){
	return;
    }
    switch( e->tag ){
	case TAGPlain:
	    rfre_int( e->Plain.lno );
	    rfre_tmstring( e->Plain.plainline );
	    break;

	case TAGForeach:
	    rfre_int( e->Foreach.lno );
	    rfre_tmstring( e->Foreach.felist );
	    rfre_tplelm_list( e->Foreach.felines );
	    break;

	case TAGWhile:
	    rfre_int( e->While.lno );
	    rfre_tmstring( e->While.whilecond );
	    rfre_tplelm_list( e->While.whilelines );
	    break;

	case TAGIf:
	    rfre_int( e->If.lno );
	    rfre_tmstring( e->If.ifcond );
	    rfre_tplelm_list( e->If.ifthen );
	    rfre_tplelm_list( e->If.ifelse );
	    break;

	case TAGSet:
	    rfre_int( e->Set.lno );
	    rfre_tmstring( e->Set.setline );
	    break;

	case TAGAppend:
	    rfre_int( e->Append.lno );
	    rfre_tmstring( e->Append.appline );
	    break;

	case TAGError:
	    rfre_int( e->Error.lno );
	    rfre_tmstring( e->Error.errstr );
	    break;

	case TAGExit:
	    rfre_int( e->Exit.lno );
	    rfre_tmstring( e->Exit.str );
	    break;

	case TAGExpandInherits:
	    rfre_int( e->ExpandInherits.lno );
	    rfre_tmstring( e->ExpandInherits.types );
	    break;

	case TAGRedirect:
	    rfre_int( e->Redirect.lno );
	    rfre_tmstring( e->Redirect.fname );
	    rfre_tplelm_list( e->Redirect.body );
	    break;

	case TAGInclude:
	    rfre_int( e->Include.lno );
	    rfre_tmstring( e->Include.fname );
	    break;

	case TAGMacro:
	    rfre_int( e->Macro.lno );
	    rfre_tmstring( e->Macro.formpar );
	    rfre_tplelm_list( e->Macro.macbody );
	    break;

	case TAGCall:
	    rfre_int( e->Call.lno );
	    rfre_tmstring( e->Call.callline );
	    break;

	case TAGReturn:
	    rfre_int( e->Return.lno );
	    rfre_tmstring( e->Return.retval );
	    break;

	case TAGInsert:
	    rfre_int( e->Insert.lno );
	    rfre_tmstring( e->Insert.fname );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
    fre_tplelm( e );
}

/* Recursively free a list of elements 'e' of type alternative. */
void rfre_alternative_list( alternative_list e )
{
    unsigned int ix;

    if( e == alternative_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_alternative( e->arr[ix] );
    }
    fre_alternative_list( e );
}

/* Recursively free a list of elements 'e' of type classComponent. */
void rfre_classComponent_list( classComponent_list e )
{
    unsigned int ix;

    if( e == classComponent_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_classComponent( e->arr[ix] );
    }
    fre_classComponent_list( e );
}

/* Recursively free a list of elements 'e' of type constructor. */
static void rfre_constructor_list( constructor_list e )
{
    unsigned int ix;

    if( e == constructor_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_constructor( e->arr[ix] );
    }
    fre_constructor_list( e );
}

/* Recursively free a list of elements 'e' of type ds. */
void rfre_ds_list( ds_list e )
{
    unsigned int ix;

    if( e == ds_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_ds( e->arr[ix] );
    }
    fre_ds_list( e );
}

/* Recursively free a list of elements 'e' of type field. */
void rfre_field_list( field_list e )
{
    unsigned int ix;

    if( e == field_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_field( e->arr[ix] );
    }
    fre_field_list( e );
}

/* Recursively free a list of elements 'e' of type macro. */
void rfre_macro_list( macro_list e )
{
    unsigned int ix;

    if( e == macro_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_macro( e->arr[ix] );
    }
    fre_macro_list( e );
}

/* Recursively free a list of elements 'e' of type tmstring. */
void rfre_tmstring_list( tmstring_list e )
{
    unsigned int ix;

    if( e == tmstring_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_tmstring( e->arr[ix] );
    }
    fre_tmstring_list( e );
}

/* Recursively free a list of elements 'e' of type tplelm. */
void rfre_tplelm_list( tplelm_list e )
{
    unsigned int ix;

    if( e == tplelm_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_tplelm( e->arr[ix] );
    }
    fre_tplelm_list( e );
}

/* Recursively free a list of elements 'e' of type var. */
void rfre_var_list( var_list e )
{
    unsigned int ix;

    if( e == var_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_var( e->arr[ix] );
    }
    fre_var_list( e );
}

/**************************************************
 *    print_<type> and print_<type>_list routines *
 **************************************************/

static void print_constructor_list( TMPRINTSTATE *st, const constructor_list );
static void print_field_list( TMPRINTSTATE *st, const field_list );

static void print_ds( TMPRINTSTATE *st, const ds );
static void print_constructor( TMPRINTSTATE *st, const constructor );
static void print_field( TMPRINTSTATE *st, const field );

/* Print an element 't' of type 'ds'
   using print optimizer.
 */
static void print_ds( TMPRINTSTATE *st, const ds t )
{
    if( t == dsNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_opencons( st );
    switch( t->tag ){
	case TAGDsCons:
	    tm_printword( st, "DsCons" );
	    print_tmstring( st, t->DsCons.name );
	    print_tmstring_list( st, t->DsCons.inherits );
	    print_constructor_list( st, t->DsCons.constructors );
	    break;

	case TAGDsTuple:
	    tm_printword( st, "DsTuple" );
	    print_tmstring( st, t->DsTuple.name );
	    print_tmstring_list( st, t->DsTuple.inherits );
	    print_field_list( st, t->DsTuple.fields );
	    break;

	case TAGDsClass:
	    tm_printword( st, "DsClass" );
	    print_tmstring( st, t->DsClass.name );
	    print_tmbool( st, t->DsClass.virtual );
	    print_tmstring_list( st, t->DsClass.inherits );
	    print_field_list( st, t->DsClass.fields );
	    break;

	default:
	    FATALTAG( (int) t->tag );
    }
    tm_closecons( st );
}

/* Print an element 't' of type 'constructor'
   using print optimizer.
 */
static void print_constructor( TMPRINTSTATE *st, const constructor t )
{
    if( t == constructorNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_opentuple( st );
    print_tmstring( st, t->name );
    print_field_list( st, t->fields );
    tm_closetuple( st );
}

/* Print an element 't' of type 'field'
   using print optimizer.
 */
static void print_field( TMPRINTSTATE *st, const field t )
{
    if( t == fieldNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_opentuple( st );
    print_int( st, t->level );
    print_tmstring( st, t->name );
    print_tmstring( st, t->type );
    tm_closetuple( st );
}

/* Print a list of elements 'l' of type 'constructor'
   using print optimizer.
 */
static void print_constructor_list( TMPRINTSTATE *st, const constructor_list l )
{
    unsigned int ix;

    if( l == constructor_listNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_openlist( st );
    for( ix=0; ix<l->sz; ix++ ){
	print_constructor( st, l->arr[ix] );
    }
    tm_closelist( st );
}

/* Print a list of elements 'l' of type 'ds'
   using print optimizer.
 */
void print_ds_list( TMPRINTSTATE *st, const ds_list l )
{
    unsigned int ix;

    if( l == ds_listNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_openlist( st );
    for( ix=0; ix<l->sz; ix++ ){
	print_ds( st, l->arr[ix] );
    }
    tm_closelist( st );
}

/* Print a list of elements 'l' of type 'field'
   using print optimizer.
 */
static void print_field_list( TMPRINTSTATE *st, const field_list l )
{
    unsigned int ix;

    if( l == field_listNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_openlist( st );
    for( ix=0; ix<l->sz; ix++ ){
	print_field( st, l->arr[ix] );
    }
    tm_closelist( st );
}

/* Print a list of elements 'l' of type 'tmstring'
   using print optimizer.
 */
void print_tmstring_list( TMPRINTSTATE *st, const tmstring_list l )
{
    unsigned int ix;

    if( l == tmstring_listNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_openlist( st );
    for( ix=0; ix<l->sz; ix++ ){
	print_tmstring( st, l->arr[ix] );
    }
    tm_closelist( st );
}

/**************************************************
 *    Duplication routines                        *
 **************************************************/

#ifdef LOGNEW
#undef rdup_ds
#define rdup_ds(e) real_rdup_ds(e,_f,_l)
#undef rdup_constructor
#define rdup_constructor(e) real_rdup_constructor(e,_f,_l)
#define rdup_field(e) real_rdup_field(e,_f,_l)
#define rdup_tplelm(e) real_rdup_tplelm(e,_f,_l)
#undef rdup_constructor_list
#define rdup_constructor_list(l) real_rdup_constructor_list(l,_f,_l)
#undef rdup_field_list
#define rdup_field_list(l) real_rdup_field_list(l,_f,_l)
#undef rdup_tmstring_list
#define rdup_tmstring_list(l) real_rdup_tmstring_list(l,_f,_l)
#undef rdup_tplelm_list
#define rdup_tplelm_list(l) real_rdup_tplelm_list(l,_f,_l)

static field real_rdup_field( const field, const char *_f, const int _l );
static tplelm real_rdup_tplelm( const tplelm, const char *_f, const int _l );

#else

static field rdup_field( const field );
static tplelm rdup_tplelm( const tplelm );

#endif
/* Recursively duplicate a ds element 'e'. */
#ifdef LOGNEW
ds real_rdup_ds( const ds e, const char *_f, const int _l )
#else
ds rdup_ds( const ds e )
#endif
{
    if( e == dsNIL ){
	return dsNIL;
    }
    switch( e->tag ){
	case TAGDsCons:
	{
	    tmstring i_name;
	    tmstring_list i_inherits;
	    constructor_list i_constructors;

	    i_name = rdup_tmstring( e->DsCons.name );
	    i_inherits = rdup_tmstring_list( e->DsCons.inherits );
	    i_constructors = rdup_constructor_list( e->DsCons.constructors );
	    return new_DsCons( i_name, i_inherits, i_constructors );
	}

	case TAGDsTuple:
	{
	    tmstring i_name;
	    tmstring_list i_inherits;
	    field_list i_fields;

	    i_name = rdup_tmstring( e->DsTuple.name );
	    i_inherits = rdup_tmstring_list( e->DsTuple.inherits );
	    i_fields = rdup_field_list( e->DsTuple.fields );
	    return new_DsTuple( i_name, i_inherits, i_fields );
	}

	case TAGDsClass:
	{
	    tmstring i_name;
	    tmbool i_virtual;
	    tmstring_list i_inherits;
	    field_list i_fields;

	    i_name = rdup_tmstring( e->DsClass.name );
	    i_virtual = rdup_tmbool( e->DsClass.virtual );
	    i_inherits = rdup_tmstring_list( e->DsClass.inherits );
	    i_fields = rdup_field_list( e->DsClass.fields );
	    return new_DsClass( i_name, i_virtual, i_inherits, i_fields );
	}

	default:
	    FATALTAG( (int) e->tag );
    }
    return dsNIL;
}

/* Recursively duplicate a constructor element 'e'. */
#ifdef LOGNEW
constructor real_rdup_constructor( const constructor e, const char *_f, const int _l )
#else
constructor rdup_constructor( const constructor e )
#endif
{
    tmstring i_name;
    field_list i_fields;

    if( e == constructorNIL ){
	return constructorNIL;
    }
    i_name = rdup_tmstring( e->name );
    i_fields = rdup_field_list( e->fields );
    return new_constructor( i_name, i_fields );
}

/* Recursively duplicate a field element 'e'. */
#ifdef LOGNEW
static field real_rdup_field( const field e, const char *_f, const int _l )
#else
static field rdup_field( const field e )
#endif
{
    int i_level;
    tmstring i_name;
    tmstring i_type;

    if( e == fieldNIL ){
	return fieldNIL;
    }
    i_level = rdup_int( e->level );
    i_name = rdup_tmstring( e->name );
    i_type = rdup_tmstring( e->type );
    return new_field( i_level, i_name, i_type );
}

/* Recursively duplicate a tplelm element 'e'. */
#ifdef LOGNEW
static tplelm real_rdup_tplelm( const tplelm e, const char *_f, const int _l )
#else
static tplelm rdup_tplelm( const tplelm e )
#endif
{
    if( e == tplelmNIL ){
	return tplelmNIL;
    }
    switch( e->tag ){
	case TAGPlain:
	{
	    int i_lno;
	    tmstring i_plainline;

	    i_lno = rdup_int( e->Plain.lno );
	    i_plainline = rdup_tmstring( e->Plain.plainline );
	    return new_Plain( i_lno, i_plainline );
	}

	case TAGForeach:
	{
	    int i_lno;
	    tmstring i_felist;
	    tplelm_list i_felines;

	    i_lno = rdup_int( e->Foreach.lno );
	    i_felist = rdup_tmstring( e->Foreach.felist );
	    i_felines = rdup_tplelm_list( e->Foreach.felines );
	    return new_Foreach( i_lno, i_felist, i_felines );
	}

	case TAGWhile:
	{
	    int i_lno;
	    tmstring i_whilecond;
	    tplelm_list i_whilelines;

	    i_lno = rdup_int( e->While.lno );
	    i_whilecond = rdup_tmstring( e->While.whilecond );
	    i_whilelines = rdup_tplelm_list( e->While.whilelines );
	    return new_While( i_lno, i_whilecond, i_whilelines );
	}

	case TAGIf:
	{
	    int i_lno;
	    tmstring i_ifcond;
	    tplelm_list i_ifthen;
	    tplelm_list i_ifelse;

	    i_lno = rdup_int( e->If.lno );
	    i_ifcond = rdup_tmstring( e->If.ifcond );
	    i_ifthen = rdup_tplelm_list( e->If.ifthen );
	    i_ifelse = rdup_tplelm_list( e->If.ifelse );
	    return new_If( i_lno, i_ifcond, i_ifthen, i_ifelse );
	}

	case TAGSet:
	{
	    int i_lno;
	    tmstring i_setline;

	    i_lno = rdup_int( e->Set.lno );
	    i_setline = rdup_tmstring( e->Set.setline );
	    return new_Set( i_lno, i_setline );
	}

	case TAGAppend:
	{
	    int i_lno;
	    tmstring i_appline;

	    i_lno = rdup_int( e->Append.lno );
	    i_appline = rdup_tmstring( e->Append.appline );
	    return new_Append( i_lno, i_appline );
	}

	case TAGError:
	{
	    int i_lno;
	    tmstring i_errstr;

	    i_lno = rdup_int( e->Error.lno );
	    i_errstr = rdup_tmstring( e->Error.errstr );
	    return new_Error( i_lno, i_errstr );
	}

	case TAGExit:
	{
	    int i_lno;
	    tmstring i_str;

	    i_lno = rdup_int( e->Exit.lno );
	    i_str = rdup_tmstring( e->Exit.str );
	    return new_Exit( i_lno, i_str );
	}

	case TAGExpandInherits:
	{
	    int i_lno;
	    tmstring i_types;

	    i_lno = rdup_int( e->ExpandInherits.lno );
	    i_types = rdup_tmstring( e->ExpandInherits.types );
	    return new_ExpandInherits( i_lno, i_types );
	}

	case TAGRedirect:
	{
	    int i_lno;
	    tmstring i_fname;
	    tplelm_list i_body;

	    i_lno = rdup_int( e->Redirect.lno );
	    i_fname = rdup_tmstring( e->Redirect.fname );
	    i_body = rdup_tplelm_list( e->Redirect.body );
	    return new_Redirect( i_lno, i_fname, i_body );
	}

	case TAGInclude:
	{
	    int i_lno;
	    tmstring i_fname;

	    i_lno = rdup_int( e->Include.lno );
	    i_fname = rdup_tmstring( e->Include.fname );
	    return new_Include( i_lno, i_fname );
	}

	case TAGMacro:
	{
	    int i_lno;
	    tmstring i_formpar;
	    tplelm_list i_macbody;

	    i_lno = rdup_int( e->Macro.lno );
	    i_formpar = rdup_tmstring( e->Macro.formpar );
	    i_macbody = rdup_tplelm_list( e->Macro.macbody );
	    return new_Macro( i_lno, i_formpar, i_macbody );
	}

	case TAGCall:
	{
	    int i_lno;
	    tmstring i_callline;

	    i_lno = rdup_int( e->Call.lno );
	    i_callline = rdup_tmstring( e->Call.callline );
	    return new_Call( i_lno, i_callline );
	}

	case TAGReturn:
	{
	    int i_lno;
	    tmstring i_retval;

	    i_lno = rdup_int( e->Return.lno );
	    i_retval = rdup_tmstring( e->Return.retval );
	    return new_Return( i_lno, i_retval );
	}

	case TAGInsert:
	{
	    int i_lno;
	    tmstring i_fname;

	    i_lno = rdup_int( e->Insert.lno );
	    i_fname = rdup_tmstring( e->Insert.fname );
	    return new_Insert( i_lno, i_fname );
	}

	default:
	    FATALTAG( (int) e->tag );
    }
    return tplelmNIL;
}

/* Recursively duplicate constructor list 'l'. */
#ifdef LOGNEW
constructor_list real_rdup_constructor_list( const constructor_list l, const char *_f, const int _l )
#else
constructor_list rdup_constructor_list( const constructor_list l )
#endif
{
    unsigned int ix;
    constructor_list nw;
    constructor *ar;
    constructor *or;

    if( l == constructor_listNIL ){
	return constructor_listNIL;
    }
    nw = setroom_constructor_list( new_constructor_list(), l->sz );
    ar = nw->arr;
    or = l->arr;
    for( ix=0; ix<l->sz; ix++ ){
	*ar++ = rdup_constructor( *or++ );
    }
    nw->sz = l->sz;
    return nw;
}

/* Recursively duplicate field list 'l'. */
#ifdef LOGNEW
field_list real_rdup_field_list( const field_list l, const char *_f, const int _l )
#else
field_list rdup_field_list( const field_list l )
#endif
{
    unsigned int ix;
    field_list nw;
    field *ar;
    field *or;

    if( l == field_listNIL ){
	return field_listNIL;
    }
    nw = setroom_field_list( new_field_list(), l->sz );
    ar = nw->arr;
    or = l->arr;
    for( ix=0; ix<l->sz; ix++ ){
	*ar++ = rdup_field( *or++ );
    }
    nw->sz = l->sz;
    return nw;
}

/* Recursively duplicate tmstring list 'l'. */
#ifdef LOGNEW
tmstring_list real_rdup_tmstring_list( const tmstring_list l, const char *_f, const int _l )
#else
tmstring_list rdup_tmstring_list( const tmstring_list l )
#endif
{
    unsigned int ix;
    tmstring_list nw;
    tmstring *ar;
    tmstring *or;

    if( l == tmstring_listNIL ){
	return tmstring_listNIL;
    }
    nw = setroom_tmstring_list( new_tmstring_list(), l->sz );
    ar = nw->arr;
    or = l->arr;
    for( ix=0; ix<l->sz; ix++ ){
	*ar++ = rdup_tmstring( *or++ );
    }
    nw->sz = l->sz;
    return nw;
}

/* Recursively duplicate tplelm list 'l'. */
#ifdef LOGNEW
tplelm_list real_rdup_tplelm_list( const tplelm_list l, const char *_f, const int _l )
#else
tplelm_list rdup_tplelm_list( const tplelm_list l )
#endif
{
    unsigned int ix;
    tplelm_list nw;
    tplelm *ar;
    tplelm *or;

    if( l == tplelm_listNIL ){
	return tplelm_listNIL;
    }
    nw = setroom_tplelm_list( new_tplelm_list(), l->sz );
    ar = nw->arr;
    or = l->arr;
    for( ix=0; ix<l->sz; ix++ ){
	*ar++ = rdup_tplelm( *or++ );
    }
    nw->sz = l->sz;
    return nw;
}

/**************************************************
 *    delete_<type>_list routines                 *
 **************************************************/


/* Delete 'ds' element at position 'pos' in list 'l'. */
ds_list delete_ds_list( ds_list l, const unsigned int pos )
{
    unsigned int ix;

    if( l == ds_listNIL ){
	FATAL( tm_nilptr );
    }
    if( pos >= l->sz ){
	return l;
    }
    rfre_ds( l->arr[pos] );
    l->sz--;
    for( ix=pos; ix<l->sz; ix++ ){
	l->arr[ix] = l->arr[ix+1];
    }
    return l;
}

/* Delete 'macro' element at position 'pos' in list 'l'. */
macro_list delete_macro_list( macro_list l, const unsigned int pos )
{
    unsigned int ix;

    if( l == macro_listNIL ){
	FATAL( tm_nilptr );
    }
    if( pos >= l->sz ){
	return l;
    }
    rfre_macro( l->arr[pos] );
    l->sz--;
    for( ix=pos; ix<l->sz; ix++ ){
	l->arr[ix] = l->arr[ix+1];
    }
    return l;
}

/* Delete 'tmstring' element at position 'pos' in list 'l'. */
tmstring_list delete_tmstring_list( tmstring_list l, const unsigned int pos )
{
    unsigned int ix;

    if( l == tmstring_listNIL ){
	FATAL( tm_nilptr );
    }
    if( pos >= l->sz ){
	return l;
    }
    rfre_tmstring( l->arr[pos] );
    l->sz--;
    for( ix=pos; ix<l->sz; ix++ ){
	l->arr[ix] = l->arr[ix+1];
    }
    return l;
}

/* Delete 'var' element at position 'pos' in list 'l'. */
var_list delete_var_list( var_list l, const unsigned int pos )
{
    unsigned int ix;

    if( l == var_listNIL ){
	FATAL( tm_nilptr );
    }
    if( pos >= l->sz ){
	return l;
    }
    rfre_var( l->arr[pos] );
    l->sz--;
    for( ix=pos; ix<l->sz; ix++ ){
	l->arr[ix] = l->arr[ix+1];
    }
    return l;
}

/**************************************************
 *    Miscellaneous routines                      *
 **************************************************/
/* Flush the allocation caches. */
void flush_tm()
{
#ifdef USECACHE
    short int ix;

    for( ix=0; ix<cacheix_alternative_list; ix++ ){
	TM_FREE( cache_alternative_list[ix] );
    }
    cacheix_alternative_list = 0;
    for( ix=0; ix<cacheix_classComponent_list; ix++ ){
	TM_FREE( cache_classComponent_list[ix] );
    }
    cacheix_classComponent_list = 0;
    for( ix=0; ix<cacheix_constructor_list; ix++ ){
	TM_FREE( cache_constructor_list[ix] );
    }
    cacheix_constructor_list = 0;
    for( ix=0; ix<cacheix_ds_list; ix++ ){
	TM_FREE( cache_ds_list[ix] );
    }
    cacheix_ds_list = 0;
    for( ix=0; ix<cacheix_field_list; ix++ ){
	TM_FREE( cache_field_list[ix] );
    }
    cacheix_field_list = 0;
    for( ix=0; ix<cacheix_macro_list; ix++ ){
	TM_FREE( cache_macro_list[ix] );
    }
    cacheix_macro_list = 0;
    for( ix=0; ix<cacheix_tmstring_list; ix++ ){
	TM_FREE( cache_tmstring_list[ix] );
    }
    cacheix_tmstring_list = 0;
    for( ix=0; ix<cacheix_tplelm_list; ix++ ){
	TM_FREE( cache_tplelm_list[ix] );
    }
    cacheix_tplelm_list = 0;
    for( ix=0; ix<cacheix_var_list; ix++ ){
	TM_FREE( cache_var_list[ix] );
    }
    cacheix_var_list = 0;
    for( ix=0; ix<cacheix_alternative; ix++ ){
	TM_FREE( cache_alternative[ix] );
    }
    cacheix_alternative = 0;
    for( ix=0; ix<cacheix_classComponent; ix++ ){
	TM_FREE( cache_classComponent[ix] );
    }
    cacheix_classComponent = 0;
    for( ix=0; ix<cacheix_constructor; ix++ ){
	TM_FREE( cache_constructor[ix] );
    }
    cacheix_constructor = 0;
    for( ix=0; ix<cacheix_ds; ix++ ){
	TM_FREE( cache_ds[ix] );
    }
    cacheix_ds = 0;
    for( ix=0; ix<cacheix_field; ix++ ){
	TM_FREE( cache_field[ix] );
    }
    cacheix_field = 0;
    for( ix=0; ix<cacheix_macro; ix++ ){
	TM_FREE( cache_macro[ix] );
    }
    cacheix_macro = 0;
    for( ix=0; ix<cacheix_tplelm; ix++ ){
	TM_FREE( cache_tplelm[ix] );
    }
    cacheix_tplelm = 0;
    for( ix=0; ix<cacheix_var; ix++ ){
	TM_FREE( cache_var[ix] );
    }
    cacheix_var = 0;
#endif
}

/* Print allocation and freeing statistics to file 'f'. */
void stat_tm( FILE *f )
{
#ifdef STAT
    fprintf(
	f,
	tm_allocfreed,
	"alternative",
	newcnt_alternative,
	frecnt_alternative,
	((newcnt_alternative==frecnt_alternative)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"CCSuper",
	newcnt_CCSuper,
	frecnt_CCSuper,
	((newcnt_CCSuper==frecnt_CCSuper)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"CCFields",
	newcnt_CCFields,
	frecnt_CCFields,
	((newcnt_CCFields==frecnt_CCFields)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"CCAlternatives",
	newcnt_CCAlternatives,
	frecnt_CCAlternatives,
	((newcnt_CCAlternatives==frecnt_CCAlternatives)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"CCSublist",
	newcnt_CCSublist,
	frecnt_CCSublist,
	((newcnt_CCSublist==frecnt_CCSublist)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"constructor",
	newcnt_constructor,
	frecnt_constructor,
	((newcnt_constructor==frecnt_constructor)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"DsCons",
	newcnt_DsCons,
	frecnt_DsCons,
	((newcnt_DsCons==frecnt_DsCons)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"DsTuple",
	newcnt_DsTuple,
	frecnt_DsTuple,
	((newcnt_DsTuple==frecnt_DsTuple)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"DsClass",
	newcnt_DsClass,
	frecnt_DsClass,
	((newcnt_DsClass==frecnt_DsClass)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"field",
	newcnt_field,
	frecnt_field,
	((newcnt_field==frecnt_field)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"macro",
	newcnt_macro,
	frecnt_macro,
	((newcnt_macro==frecnt_macro)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Plain",
	newcnt_Plain,
	frecnt_Plain,
	((newcnt_Plain==frecnt_Plain)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Foreach",
	newcnt_Foreach,
	frecnt_Foreach,
	((newcnt_Foreach==frecnt_Foreach)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"While",
	newcnt_While,
	frecnt_While,
	((newcnt_While==frecnt_While)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"If",
	newcnt_If,
	frecnt_If,
	((newcnt_If==frecnt_If)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Set",
	newcnt_Set,
	frecnt_Set,
	((newcnt_Set==frecnt_Set)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Append",
	newcnt_Append,
	frecnt_Append,
	((newcnt_Append==frecnt_Append)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Error",
	newcnt_Error,
	frecnt_Error,
	((newcnt_Error==frecnt_Error)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Exit",
	newcnt_Exit,
	frecnt_Exit,
	((newcnt_Exit==frecnt_Exit)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"ExpandInherits",
	newcnt_ExpandInherits,
	frecnt_ExpandInherits,
	((newcnt_ExpandInherits==frecnt_ExpandInherits)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Redirect",
	newcnt_Redirect,
	frecnt_Redirect,
	((newcnt_Redirect==frecnt_Redirect)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Include",
	newcnt_Include,
	frecnt_Include,
	((newcnt_Include==frecnt_Include)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Macro",
	newcnt_Macro,
	frecnt_Macro,
	((newcnt_Macro==frecnt_Macro)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Call",
	newcnt_Call,
	frecnt_Call,
	((newcnt_Call==frecnt_Call)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Return",
	newcnt_Return,
	frecnt_Return,
	((newcnt_Return==frecnt_Return)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Insert",
	newcnt_Insert,
	frecnt_Insert,
	((newcnt_Insert==frecnt_Insert)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"var",
	newcnt_var,
	frecnt_var,
	((newcnt_var==frecnt_var)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed, "alternative_list",
	newcnt_alternative_list,
	frecnt_alternative_list,
	((newcnt_alternative_list==frecnt_alternative_list)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed, "classComponent_list",
	newcnt_classComponent_list,
	frecnt_classComponent_list,
	((newcnt_classComponent_list==frecnt_classComponent_list)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed, "constructor_list",
	newcnt_constructor_list,
	frecnt_constructor_list,
	((newcnt_constructor_list==frecnt_constructor_list)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed, "ds_list",
	newcnt_ds_list,
	frecnt_ds_list,
	((newcnt_ds_list==frecnt_ds_list)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed, "field_list",
	newcnt_field_list,
	frecnt_field_list,
	((newcnt_field_list==frecnt_field_list)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed, "macro_list",
	newcnt_macro_list,
	frecnt_macro_list,
	((newcnt_macro_list==frecnt_macro_list)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed, "tmstring_list",
	newcnt_tmstring_list,
	frecnt_tmstring_list,
	((newcnt_tmstring_list==frecnt_tmstring_list)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed, "tplelm_list",
	newcnt_tplelm_list,
	frecnt_tplelm_list,
	((newcnt_tplelm_list==frecnt_tplelm_list)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed, "var_list",
	newcnt_var_list,
	frecnt_var_list,
	((newcnt_var_list==frecnt_var_list)? "": "<-")
    );
#else
    (void) f; /* to prevent 'f unused' from compiler and lint */
#endif
}

/* ---- end of /usr/local/lib/calu.ct ---- */
