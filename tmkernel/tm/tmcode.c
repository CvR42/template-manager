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

/* required:  new_alternative new_alternative_list new_classComponent new_classComponent_list new_ds new_ds_list new_field new_field_list new_macro new_macro_list new_switchcase new_switchcase_list new_tmstring_list new_tplelm new_tplelm_list new_var new_var_list */
/* required: . ds_alternative ds_alternative_list ds_classComponent ds_classComponent_list ds_ds ds_ds_list ds_field ds_field_list ds_macro ds_macro_list ds_switchcase ds_switchcase_list ds_tmstring_list ds_tplelm ds_tplelm_list ds_var ds_var_list */
/* required: .. ds_tmstring */
/* required: .. ds_int ds_tmbool ds_uint */
/* required:  rfre_alternative_list rfre_classComponent rfre_classComponent_list rfre_ds rfre_ds_list rfre_field_list rfre_macro rfre_macro_list rfre_tmstring_list rfre_tplelm rfre_tplelm_list rfre_var_list */
/* required: . rfre_alternative rfre_field rfre_tmstring rfre_var */
/* required: .. rfre_int rfre_uint */
/* required: ... fre_int fre_uint */
/* required: .. fre_alternative fre_field fre_tmstring fre_var */
/* required: . rfre_switchcase_list rfre_tmbool */
/* required: .. rfre_switchcase */
/* required: ... fre_switchcase */
/* required: .. fre_switchcase_list fre_tmbool */
/* required: . fre_alternative_list fre_classComponent fre_classComponent_list fre_ds fre_ds_list fre_field_list fre_macro fre_macro_list fre_tmstring_list fre_tplelm fre_tplelm_list fre_var_list */
/* required:  rdup_ds rdup_field_list rdup_tmstring_list rdup_tplelm rdup_tplelm_list */
/* required: . setroom_field_list setroom_tmstring_list setroom_tplelm_list */
/* required: . rdup_field rdup_tmstring */
/* required: .. new_tmstring */
/* required: .. rdup_int */
/* required: ... new_int */
/* required: . rdup_switchcase_list rdup_tmbool */
/* required: .. new_tmbool */
/* required: .. setroom_switchcase_list */
/* required: .. rdup_switchcase */
/* required:  print_ds_list print_tmstring_list */
/* required: . print_ds print_tmstring */
/* required: .. print_field_list print_tmbool */
/* required: ... print_field */
/* required: .... print_int */
/* required:  append_alternative_list append_classComponent_list append_ds_list append_field_list append_switchcase_list append_tmstring_list append_tplelm_list append_var_list */
/* required: . setroom_alternative_list setroom_classComponent_list setroom_ds_list setroom_var_list */
/* required:  concat_ds_list concat_field_list concat_tmstring_list */
/* required:  insert_macro_list insert_tmstring_list insert_var_list */
/* required: . setroom_macro_list */
/* required:  delete_ds_list delete_macro_list delete_tmstring_list delete_var_list */
/* required:  extract_tmstring_list */
/* Requirement analysis took 6080 milliseconds. */
/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /usr/local/lib/calu.ct ---- */

/* Routines for 'tm'.

   template file:      /usr/local/lib/calu.ct
   datastructure file: tm.ds
   tm version:         36
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
static long newcnt_ds_list = 0;
static long frecnt_ds_list = 0;
static long newcnt_field_list = 0;
static long frecnt_field_list = 0;
static long newcnt_macro_list = 0;
static long frecnt_macro_list = 0;
static long newcnt_switchcase_list = 0;
static long frecnt_switchcase_list = 0;
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
static long newcnt_DsConstructorBase = 0;
static long frecnt_DsConstructorBase = 0;
static long newcnt_DsTuple = 0;
static long frecnt_DsTuple = 0;
static long newcnt_DsClass = 0;
static long frecnt_DsClass = 0;
static long newcnt_DsConstructor = 0;
static long frecnt_DsConstructor = 0;
static long newcnt_field = 0;
static long frecnt_field = 0;
static long newcnt_macro = 0;
static long frecnt_macro = 0;
static long newcnt_switchcase = 0;
static long frecnt_switchcase = 0;
static long newcnt_Plain = 0;
static long frecnt_Plain = 0;
static long newcnt_Foreach = 0;
static long frecnt_Foreach = 0;
static long newcnt_While = 0;
static long frecnt_While = 0;
static long newcnt_If = 0;
static long frecnt_If = 0;
static long newcnt_Switch = 0;
static long frecnt_Switch = 0;
static long newcnt_Set = 0;
static long frecnt_Set = 0;
static long newcnt_GlobalSet = 0;
static long frecnt_GlobalSet = 0;
static long newcnt_Append = 0;
static long frecnt_Append = 0;
static long newcnt_GlobalAppend = 0;
static long frecnt_GlobalAppend = 0;
static long newcnt_Error = 0;
static long frecnt_Error = 0;
static long newcnt_Exit = 0;
static long frecnt_Exit = 0;
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
static long newcnt_Case = 0;
static long frecnt_Case = 0;
static long newcnt_Default = 0;
static long frecnt_Default = 0;
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
static short int cacheix_ds_list = 0;
static ds_list cache_ds_list[CACHESZ]; 
static short int cacheix_field_list = 0;
static field_list cache_field_list[CACHESZ]; 
static short int cacheix_macro_list = 0;
static macro_list cache_macro_list[CACHESZ]; 
static short int cacheix_switchcase_list = 0;
static switchcase_list cache_switchcase_list[CACHESZ]; 
static short int cacheix_tmstring_list = 0;
static tmstring_list cache_tmstring_list[CACHESZ]; 
static short int cacheix_tplelm_list = 0;
static tplelm_list cache_tplelm_list[CACHESZ]; 
static short int cacheix_var_list = 0;
static var_list cache_var_list[CACHESZ]; 
static short int cacheix_alternative = 0;
static alternative cache_alternative[CACHESZ];
static short int cacheix_field = 0;
static field cache_field[CACHESZ];
static short int cacheix_macro = 0;
static macro cache_macro[CACHESZ];
static short int cacheix_var = 0;
static var cache_var[CACHESZ];
static short int cacheix_switchcase = 0;
static switchcase cache_switchcase[CACHESZ];
static short int cacheix_ds = 0;
static ds cache_ds[CACHESZ];
static short int cacheix_classComponent = 0;
static classComponent cache_classComponent[CACHESZ];
static short int cacheix_tplelm = 0;
static tplelm cache_tplelm[CACHESZ];
#endif

static char tm_srcfile[] = __FILE__;

#ifdef STAT
static char tm_allocfreed[] = "%-20s: %6ld allocated, %6ld freed.%s\n";
#endif

#ifndef FATAL
#define FATAL(msg) tm_fatal(tm_srcfile,__LINE__,msg)
#endif

/* Possible error strings. */
static char tm_nilptr[] = "NIL pointer";

#ifndef FATALTAG
#define FATALTAG(tag) tm_badtag(tm_srcfile,__LINE__,(int) tag)
#endif

/**************************************************
 *    set array room routines                     *
 **************************************************/

/* Announce that you will need room for 'rm' elements in
    field_list 'l'.
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

/* Announce that you will need room for 'rm' elements in
    tmstring_list 'l'.
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

/* Announce that you will need room for 'rm' elements in
    tplelm_list 'l'.
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

/* Announce that you will need room for 'rm' elements in
    switchcase_list 'l'.
 */
static switchcase_list setroom_switchcase_list( switchcase_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->room==0 ){
	l->arr = TM_MALLOC( switchcase *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( switchcase *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need room for 'rm' elements in
    alternative_list 'l'.
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

/* Announce that you will need room for 'rm' elements in
    classComponent_list 'l'.
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

/* Announce that you will need room for 'rm' elements in
    ds_list 'l'.
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

/* Announce that you will need room for 'rm' elements in
    var_list 'l'.
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

/* Announce that you will need room for 'rm' elements in
    macro_list 'l'.
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
#undef new_DsConstructorBase
#undef new_DsTuple
#undef new_DsClass
#undef new_DsConstructor
#define new_DsConstructorBase(name,inherits,constructors) real_new_DsConstructorBase(name,inherits,constructors,_f,_l)
#define new_DsTuple(name,inherits,fields) real_new_DsTuple(name,inherits,fields,_f,_l)
#define new_DsClass(name,inherits,fields,virtual) real_new_DsClass(name,inherits,fields,virtual,_f,_l)
#define new_DsConstructor(name,inherits,fields) real_new_DsConstructor(name,inherits,fields,_f,_l)
#undef new_field
#define new_field(level,name,type) real_new_field(level,name,type,_f,_l)
#undef new_macro
#define new_macro(lvl,name,orgfile,fpl,body) real_new_macro(lvl,name,orgfile,fpl,body,_f,_l)
#undef new_switchcase
#define new_switchcase(cases,action) real_new_switchcase(cases,action,_f,_l)
#undef new_Plain
#undef new_Foreach
#undef new_While
#undef new_If
#undef new_Switch
#undef new_Set
#undef new_GlobalSet
#undef new_Append
#undef new_GlobalAppend
#undef new_Error
#undef new_Exit
#undef new_Redirect
#undef new_Include
#undef new_Macro
#undef new_Call
#undef new_Return
#undef new_Insert
#undef new_Case
#undef new_Default
#define new_Plain(lno,plainline) real_new_Plain(lno,plainline,_f,_l)
#define new_Foreach(lno,felist,felines) real_new_Foreach(lno,felist,felines,_f,_l)
#define new_While(lno,whilecond,whilelines) real_new_While(lno,whilecond,whilelines,_f,_l)
#define new_If(lno,ifcond,ifthen,ifelse) real_new_If(lno,ifcond,ifthen,ifelse,_f,_l)
#define new_Switch(lno,val,cases,deflt) real_new_Switch(lno,val,cases,deflt,_f,_l)
#define new_Set(lno,setline) real_new_Set(lno,setline,_f,_l)
#define new_GlobalSet(lno,setline) real_new_GlobalSet(lno,setline,_f,_l)
#define new_Append(lno,appline) real_new_Append(lno,appline,_f,_l)
#define new_GlobalAppend(lno,appline) real_new_GlobalAppend(lno,appline,_f,_l)
#define new_Error(lno,errstr) real_new_Error(lno,errstr,_f,_l)
#define new_Exit(lno,str) real_new_Exit(lno,str,_f,_l)
#define new_Redirect(lno,fname,body) real_new_Redirect(lno,fname,body,_f,_l)
#define new_Include(lno,fname) real_new_Include(lno,fname,_f,_l)
#define new_Macro(lno,formpar,macbody) real_new_Macro(lno,formpar,macbody,_f,_l)
#define new_Call(lno,callline) real_new_Call(lno,callline,_f,_l)
#define new_Return(lno,retval) real_new_Return(lno,retval,_f,_l)
#define new_Insert(lno,fname) real_new_Insert(lno,fname,_f,_l)
#define new_Case(lno,val) real_new_Case(lno,val,_f,_l)
#define new_Default(lno) real_new_Default(lno,_f,_l)
#undef new_var
#define new_var(lvl,name,val) real_new_var(lvl,name,val,_f,_l)
#undef new_alternative_list
#define new_alternative_list() real_new_alternative_list(_f,_l)
#undef new_classComponent_list
#define new_classComponent_list() real_new_classComponent_list(_f,_l)
#undef new_ds_list
#define new_ds_list() real_new_ds_list(_f,_l)
#undef new_field_list
#define new_field_list() real_new_field_list(_f,_l)
#undef new_macro_list
#define new_macro_list() real_new_macro_list(_f,_l)
#undef new_switchcase_list
#define new_switchcase_list() real_new_switchcase_list(_f,_l)
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
switchcase_list real_new_switchcase_list( const char *_f, const int _l )
#else
switchcase_list new_switchcase_list( void )
#endif
{
    switchcase_list nw;

#ifdef USECACHE
    if( cacheix_switchcase_list > 0 ){
	nw = cache_switchcase_list[--cacheix_switchcase_list];
    }
    else {
#endif
	nw = TM_MALLOC( switchcase_list, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (switchcase *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( switchcase *, FIRSTROOM*sizeof(switchcase) );
    nw->room = FIRSTROOM;
#endif
#ifdef STAT
    newcnt_switchcase_list++;
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
    to_CCSuper(nw)->super = p_super;
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
    to_CCFields(nw)->fields = p_fields;
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
    to_CCAlternatives(nw)->alternatives = p_alternatives;
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
    to_CCSublist(nw)->components = p_components;
#ifdef STAT
    newcnt_CCSublist++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
ds real_new_DsConstructorBase( tmstring p_name, tmstring_list p_inherits, tmstring_list p_constructors, const char *_f, const int _l )
#else
ds new_DsConstructorBase( tmstring p_name, tmstring_list p_inherits, tmstring_list p_constructors )
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
    nw->tag = TAGDsConstructorBase;
    to_DsConstructorBase(nw)->name = p_name;
    to_DsConstructorBase(nw)->inherits = p_inherits;
    to_DsConstructorBase(nw)->constructors = p_constructors;
#ifdef STAT
    newcnt_DsConstructorBase++;
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
    to_DsTuple(nw)->name = p_name;
    to_DsTuple(nw)->inherits = p_inherits;
    to_DsTuple(nw)->fields = p_fields;
#ifdef STAT
    newcnt_DsTuple++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
ds real_new_DsClass( tmstring p_name, tmstring_list p_inherits, field_list p_fields, tmbool p_virtual, const char *_f, const int _l )
#else
ds new_DsClass( tmstring p_name, tmstring_list p_inherits, field_list p_fields, tmbool p_virtual )
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
    to_DsClass(nw)->name = p_name;
    to_DsClass(nw)->inherits = p_inherits;
    to_DsClass(nw)->fields = p_fields;
    to_DsClass(nw)->virtual = p_virtual;
#ifdef STAT
    newcnt_DsClass++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
ds real_new_DsConstructor( tmstring p_name, tmstring_list p_inherits, field_list p_fields, const char *_f, const int _l )
#else
ds new_DsConstructor( tmstring p_name, tmstring_list p_inherits, field_list p_fields )
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
    nw->tag = TAGDsConstructor;
    to_DsConstructor(nw)->name = p_name;
    to_DsConstructor(nw)->inherits = p_inherits;
    to_DsConstructor(nw)->fields = p_fields;
#ifdef STAT
    newcnt_DsConstructor++;
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
switchcase real_new_switchcase( tmstring p_cases, tplelm_list p_action, const char *_f, const int _l )
#else
switchcase new_switchcase( tmstring p_cases, tplelm_list p_action )
#endif
{
    switchcase nw;

#ifdef USECACHE
    if( cacheix_switchcase > 0 ){
	nw = cache_switchcase[--cacheix_switchcase];
    }
    else {
#endif
	nw = TM_MALLOC( switchcase, sizeof(*nw) );
#ifdef USECACHE
    }
#endif
    nw->cases = p_cases;
    nw->action = p_action;
#ifdef STAT
    newcnt_switchcase++;
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
    to_Plain(nw)->lno = p_lno;
    to_Plain(nw)->plainline = p_plainline;
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
    to_Foreach(nw)->lno = p_lno;
    to_Foreach(nw)->felist = p_felist;
    to_Foreach(nw)->felines = p_felines;
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
    to_While(nw)->lno = p_lno;
    to_While(nw)->whilecond = p_whilecond;
    to_While(nw)->whilelines = p_whilelines;
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
    to_If(nw)->lno = p_lno;
    to_If(nw)->ifcond = p_ifcond;
    to_If(nw)->ifthen = p_ifthen;
    to_If(nw)->ifelse = p_ifelse;
#ifdef STAT
    newcnt_If++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Switch( int p_lno, tmstring p_val, switchcase_list p_cases, tplelm_list p_deflt, const char *_f, const int _l )
#else
tplelm new_Switch( int p_lno, tmstring p_val, switchcase_list p_cases, tplelm_list p_deflt )
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
    nw->tag = TAGSwitch;
    to_Switch(nw)->lno = p_lno;
    to_Switch(nw)->val = p_val;
    to_Switch(nw)->cases = p_cases;
    to_Switch(nw)->deflt = p_deflt;
#ifdef STAT
    newcnt_Switch++;
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
    to_Set(nw)->lno = p_lno;
    to_Set(nw)->setline = p_setline;
#ifdef STAT
    newcnt_Set++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_GlobalSet( int p_lno, tmstring p_setline, const char *_f, const int _l )
#else
tplelm new_GlobalSet( int p_lno, tmstring p_setline )
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
    nw->tag = TAGGlobalSet;
    to_GlobalSet(nw)->lno = p_lno;
    to_GlobalSet(nw)->setline = p_setline;
#ifdef STAT
    newcnt_GlobalSet++;
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
    to_Append(nw)->lno = p_lno;
    to_Append(nw)->appline = p_appline;
#ifdef STAT
    newcnt_Append++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_GlobalAppend( int p_lno, tmstring p_appline, const char *_f, const int _l )
#else
tplelm new_GlobalAppend( int p_lno, tmstring p_appline )
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
    nw->tag = TAGGlobalAppend;
    to_GlobalAppend(nw)->lno = p_lno;
    to_GlobalAppend(nw)->appline = p_appline;
#ifdef STAT
    newcnt_GlobalAppend++;
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
    to_Error(nw)->lno = p_lno;
    to_Error(nw)->errstr = p_errstr;
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
    to_Exit(nw)->lno = p_lno;
    to_Exit(nw)->str = p_str;
#ifdef STAT
    newcnt_Exit++;
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
    to_Redirect(nw)->lno = p_lno;
    to_Redirect(nw)->fname = p_fname;
    to_Redirect(nw)->body = p_body;
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
    to_Include(nw)->lno = p_lno;
    to_Include(nw)->fname = p_fname;
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
    to_Macro(nw)->lno = p_lno;
    to_Macro(nw)->formpar = p_formpar;
    to_Macro(nw)->macbody = p_macbody;
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
    to_Call(nw)->lno = p_lno;
    to_Call(nw)->callline = p_callline;
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
    to_Return(nw)->lno = p_lno;
    to_Return(nw)->retval = p_retval;
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
    to_Insert(nw)->lno = p_lno;
    to_Insert(nw)->fname = p_fname;
#ifdef STAT
    newcnt_Insert++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Case( int p_lno, tmstring p_val, const char *_f, const int _l )
#else
tplelm new_Case( int p_lno, tmstring p_val )
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
    nw->tag = TAGCase;
    to_Case(nw)->lno = p_lno;
    to_Case(nw)->val = p_val;
#ifdef STAT
    newcnt_Case++;
#endif
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
tplelm real_new_Default( int p_lno, const char *_f, const int _l )
#else
tplelm new_Default( int p_lno )
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
    nw->tag = TAGDefault;
    to_Default(nw)->lno = p_lno;
#ifdef STAT
    newcnt_Default++;
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

/* Free an element 'e' of type 'switchcase'. */
static void fre_switchcase( switchcase e )
{
    if( e == switchcaseNIL ){
	return;
    }
#ifdef STAT
    frecnt_switchcase++;
#endif
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
#ifdef USECACHE
    if( cacheix_switchcase<CACHESZ ){
	cache_switchcase[cacheix_switchcase++] = e;
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
	case TAGDsConstructorBase:
	    frecnt_DsConstructorBase++;
	    break;

	case TAGDsTuple:
	    frecnt_DsTuple++;
	    break;

	case TAGDsClass:
	    frecnt_DsClass++;
	    break;

	case TAGDsConstructor:
	    frecnt_DsConstructor++;
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

	case TAGSwitch:
	    frecnt_Switch++;
	    break;

	case TAGSet:
	    frecnt_Set++;
	    break;

	case TAGGlobalSet:
	    frecnt_GlobalSet++;
	    break;

	case TAGAppend:
	    frecnt_Append++;
	    break;

	case TAGGlobalAppend:
	    frecnt_GlobalAppend++;
	    break;

	case TAGError:
	    frecnt_Error++;
	    break;

	case TAGExit:
	    frecnt_Exit++;
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

	case TAGCase:
	    frecnt_Case++;
	    break;

	case TAGDefault:
	    frecnt_Default++;
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

/* Free a list of switchcase elements 'l'. */
static void fre_switchcase_list( switchcase_list l )
{
    if( l == switchcase_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
#ifdef STAT
    frecnt_switchcase_list++;
#endif
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
#ifdef USECACHE
    if( cacheix_switchcase_list<CACHESZ ){
	cache_switchcase_list[cacheix_switchcase_list++] = l;
	return;
    }
#endif
    TM_FREE( l );
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
 *    Append routines                             *
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

/* Append a switchcase element 'e' to list 'l', and return the new list. */
switchcase_list append_switchcase_list( switchcase_list l, switchcase e )
{
    if( l->sz >= l->room ){
	l = setroom_switchcase_list( l, 1+(l->sz)+(l->sz) );
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

/* Append a var element 'e' to list 'l', and return the new list. */
var_list append_var_list( var_list l, var e )
{
    if( l->sz >= l->room ){
	l = setroom_var_list( l, 1+(l->sz)+(l->sz) );
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
    macro *p;
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
    p = l->arr;
    for( ix=l->sz; ix>the_pos; ix-- ){
	p[ix] = p[ix-1];
    }
    l->sz++;
    p[the_pos] = e;
    return l;
}

/* Insert a tmstring element 'e' to into list 'l' at position 'pos'. */
tmstring_list insert_tmstring_list( tmstring_list l, const unsigned int pos, tmstring e )
{
    unsigned int ix;
    tmstring *p;
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
    p = l->arr;
    for( ix=l->sz; ix>the_pos; ix-- ){
	p[ix] = p[ix-1];
    }
    l->sz++;
    p[the_pos] = e;
    return l;
}

/* Insert a var element 'e' to into list 'l' at position 'pos'. */
var_list insert_var_list( var_list l, const unsigned int pos, var e )
{
    unsigned int ix;
    var *p;
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
    p = l->arr;
    for( ix=l->sz; ix>the_pos; ix-- ){
	p[ix] = p[ix-1];
    }
    l->sz++;
    p[the_pos] = e;
    return l;
}

/**************************************************
 *    Concatenate routines                        *
 **************************************************/

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

/* Concatenate tmstring list 'lb' after tmstring list 'la'.
   The list descriptor of list 'lb' is freed,
   since its contents has been moved to 'la'.
 */
tmstring_list concat_tmstring_list( tmstring_list la, tmstring_list lb )
{
    unsigned int cnt;
    tmstring *sp;
    tmstring *dp;

    la = setroom_tmstring_list( la, la->sz+lb->sz );
    cnt = lb->sz;
    sp = lb->arr;
    dp = &la->arr[la->sz];
    while( cnt!=0 ){
	*dp++ = *sp++;
	cnt--;
    }
    la->sz += lb->sz;
    fre_tmstring_list( lb );
    return la;
}

/**************************************************
 *    Recursive freeing routines                  *
 **************************************************/

static void rfre_switchcase_list( switchcase_list );

static void rfre_alternative( alternative );
static void rfre_field( field );
static void rfre_var( var );
static void rfre_switchcase( switchcase );

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
	    rfre_tmstring( to_CCSuper(e)->super );
	    break;

	case TAGCCFields:
	    rfre_field_list( to_CCFields(e)->fields );
	    break;

	case TAGCCAlternatives:
	    rfre_alternative_list( to_CCAlternatives(e)->alternatives );
	    break;

	case TAGCCSublist:
	    rfre_classComponent_list( to_CCSublist(e)->components );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
    fre_classComponent( e );
}

/* Recursively free an element 'e' of type 'ds'
   and all elements in it.
 */
void rfre_ds( ds e )
{
    if( e == dsNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsConstructorBase:
	    rfre_tmstring( to_DsConstructorBase(e)->name );
	    rfre_tmstring_list( to_DsConstructorBase(e)->inherits );
	    rfre_tmstring_list( to_DsConstructorBase(e)->constructors );
	    break;

	case TAGDsTuple:
	    rfre_tmstring( to_DsTuple(e)->name );
	    rfre_tmstring_list( to_DsTuple(e)->inherits );
	    rfre_field_list( to_DsTuple(e)->fields );
	    break;

	case TAGDsClass:
	    rfre_tmstring( to_DsClass(e)->name );
	    rfre_tmstring_list( to_DsClass(e)->inherits );
	    rfre_field_list( to_DsClass(e)->fields );
	    rfre_tmbool( to_DsClass(e)->virtual );
	    break;

	case TAGDsConstructor:
	    rfre_tmstring( to_DsConstructor(e)->name );
	    rfre_tmstring_list( to_DsConstructor(e)->inherits );
	    rfre_field_list( to_DsConstructor(e)->fields );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
    fre_ds( e );
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
	    rfre_int( to_Plain(e)->lno );
	    rfre_tmstring( to_Plain(e)->plainline );
	    break;

	case TAGForeach:
	    rfre_int( to_Foreach(e)->lno );
	    rfre_tmstring( to_Foreach(e)->felist );
	    rfre_tplelm_list( to_Foreach(e)->felines );
	    break;

	case TAGWhile:
	    rfre_int( to_While(e)->lno );
	    rfre_tmstring( to_While(e)->whilecond );
	    rfre_tplelm_list( to_While(e)->whilelines );
	    break;

	case TAGIf:
	    rfre_int( to_If(e)->lno );
	    rfre_tmstring( to_If(e)->ifcond );
	    rfre_tplelm_list( to_If(e)->ifthen );
	    rfre_tplelm_list( to_If(e)->ifelse );
	    break;

	case TAGSwitch:
	    rfre_int( to_Switch(e)->lno );
	    rfre_tmstring( to_Switch(e)->val );
	    rfre_switchcase_list( to_Switch(e)->cases );
	    rfre_tplelm_list( to_Switch(e)->deflt );
	    break;

	case TAGSet:
	    rfre_int( to_Set(e)->lno );
	    rfre_tmstring( to_Set(e)->setline );
	    break;

	case TAGGlobalSet:
	    rfre_int( to_GlobalSet(e)->lno );
	    rfre_tmstring( to_GlobalSet(e)->setline );
	    break;

	case TAGAppend:
	    rfre_int( to_Append(e)->lno );
	    rfre_tmstring( to_Append(e)->appline );
	    break;

	case TAGGlobalAppend:
	    rfre_int( to_GlobalAppend(e)->lno );
	    rfre_tmstring( to_GlobalAppend(e)->appline );
	    break;

	case TAGError:
	    rfre_int( to_Error(e)->lno );
	    rfre_tmstring( to_Error(e)->errstr );
	    break;

	case TAGExit:
	    rfre_int( to_Exit(e)->lno );
	    rfre_tmstring( to_Exit(e)->str );
	    break;

	case TAGRedirect:
	    rfre_int( to_Redirect(e)->lno );
	    rfre_tmstring( to_Redirect(e)->fname );
	    rfre_tplelm_list( to_Redirect(e)->body );
	    break;

	case TAGInclude:
	    rfre_int( to_Include(e)->lno );
	    rfre_tmstring( to_Include(e)->fname );
	    break;

	case TAGMacro:
	    rfre_int( to_Macro(e)->lno );
	    rfre_tmstring( to_Macro(e)->formpar );
	    rfre_tplelm_list( to_Macro(e)->macbody );
	    break;

	case TAGCall:
	    rfre_int( to_Call(e)->lno );
	    rfre_tmstring( to_Call(e)->callline );
	    break;

	case TAGReturn:
	    rfre_int( to_Return(e)->lno );
	    rfre_tmstring( to_Return(e)->retval );
	    break;

	case TAGInsert:
	    rfre_int( to_Insert(e)->lno );
	    rfre_tmstring( to_Insert(e)->fname );
	    break;

	case TAGCase:
	    rfre_int( to_Case(e)->lno );
	    rfre_tmstring( to_Case(e)->val );
	    break;

	case TAGDefault:
	    rfre_int( to_Default(e)->lno );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
    fre_tplelm( e );
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

/* Recursively free an element 'e' of type 'switchcase'
   and all elements in it.
 */
static void rfre_switchcase( switchcase e )
{
    if( e == switchcaseNIL ){
	return;
    }
    rfre_tmstring( e->cases );
    rfre_tplelm_list( e->action );
    fre_switchcase( e );
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

/* Recursively free a list of elements 'e' of type switchcase. */
static void rfre_switchcase_list( switchcase_list e )
{
    unsigned int ix;

    if( e == switchcase_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
	rfre_switchcase( e->arr[ix] );
    }
    fre_switchcase_list( e );
}

/**************************************************
 *    print_<type> and print_<type>_list routines *
 **************************************************/

static void print_field_list( TMPRINTSTATE *st, const field_list );

static void print_ds( TMPRINTSTATE *st, const ds );
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
	case TAGDsConstructorBase:
	    tm_printword( st, "DsConstructorBase" );
	    print_tmstring( st, to_DsConstructorBase(t)->name );
	    print_tmstring_list( st, to_DsConstructorBase(t)->inherits );
	    print_tmstring_list( st, to_DsConstructorBase(t)->constructors );
	    break;

	case TAGDsTuple:
	    tm_printword( st, "DsTuple" );
	    print_tmstring( st, to_DsTuple(t)->name );
	    print_tmstring_list( st, to_DsTuple(t)->inherits );
	    print_field_list( st, to_DsTuple(t)->fields );
	    break;

	case TAGDsClass:
	    tm_printword( st, "DsClass" );
	    print_tmstring( st, to_DsClass(t)->name );
	    print_tmstring_list( st, to_DsClass(t)->inherits );
	    print_field_list( st, to_DsClass(t)->fields );
	    print_tmbool( st, to_DsClass(t)->virtual );
	    break;

	case TAGDsConstructor:
	    tm_printword( st, "DsConstructor" );
	    print_tmstring( st, to_DsConstructor(t)->name );
	    print_tmstring_list( st, to_DsConstructor(t)->inherits );
	    print_field_list( st, to_DsConstructor(t)->fields );
	    break;

	default:
	    FATALTAG( (int) t->tag );
    }
    tm_closecons( st );
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

/**************************************************
 *    Duplication routines                        *
 **************************************************/

#ifdef LOGNEW
#undef rdup_ds
#define rdup_ds(e) real_rdup_ds(e,_f,_l)
#undef rdup_tplelm
#define rdup_tplelm(e) real_rdup_tplelm(e,_f,_l)
#define rdup_field(e) real_rdup_field(e,_f,_l)
#define rdup_switchcase(e) real_rdup_switchcase(e,_f,_l)
#undef rdup_field_list
#define rdup_field_list(l) real_rdup_field_list(l,_f,_l)
#undef rdup_tmstring_list
#define rdup_tmstring_list(l) real_rdup_tmstring_list(l,_f,_l)
#undef rdup_tplelm_list
#define rdup_tplelm_list(l) real_rdup_tplelm_list(l,_f,_l)
#define rdup_switchcase_list(l) real_rdup_switchcase_list(l,_f,_l)
static switchcase_list real_rdup_switchcase_list( const switchcase_list l, const char *_f, const int _l );

static field real_rdup_field( const field e, const char *_f, const int _l );
static switchcase real_rdup_switchcase( const switchcase e, const char *_f, const int _l );

#else
static switchcase_list rdup_switchcase_list( const switchcase_list l );

static field rdup_field( const field e );
static switchcase rdup_switchcase( const switchcase e );

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
	case TAGDsConstructorBase:
	{
	    tmstring i_name;
	    tmstring_list i_inherits;
	    tmstring_list i_constructors;

	    i_name = rdup_tmstring( to_DsConstructorBase(e)->name );
	    i_inherits = rdup_tmstring_list( to_DsConstructorBase(e)->inherits );
	    i_constructors = rdup_tmstring_list( to_DsConstructorBase(e)->constructors );
	    return new_DsConstructorBase( i_name, i_inherits, i_constructors );
	}

	case TAGDsTuple:
	{
	    tmstring i_name;
	    tmstring_list i_inherits;
	    field_list i_fields;

	    i_name = rdup_tmstring( to_DsTuple(e)->name );
	    i_inherits = rdup_tmstring_list( to_DsTuple(e)->inherits );
	    i_fields = rdup_field_list( to_DsTuple(e)->fields );
	    return new_DsTuple( i_name, i_inherits, i_fields );
	}

	case TAGDsClass:
	{
	    tmstring i_name;
	    tmstring_list i_inherits;
	    field_list i_fields;
	    tmbool i_virtual;

	    i_name = rdup_tmstring( to_DsClass(e)->name );
	    i_inherits = rdup_tmstring_list( to_DsClass(e)->inherits );
	    i_fields = rdup_field_list( to_DsClass(e)->fields );
	    i_virtual = rdup_tmbool( to_DsClass(e)->virtual );
	    return new_DsClass( i_name, i_inherits, i_fields, i_virtual );
	}

	case TAGDsConstructor:
	{
	    tmstring i_name;
	    tmstring_list i_inherits;
	    field_list i_fields;

	    i_name = rdup_tmstring( to_DsConstructor(e)->name );
	    i_inherits = rdup_tmstring_list( to_DsConstructor(e)->inherits );
	    i_fields = rdup_field_list( to_DsConstructor(e)->fields );
	    return new_DsConstructor( i_name, i_inherits, i_fields );
	}

	default:
	    FATALTAG( (int) e->tag );
    }
    return dsNIL;
}

/* Recursively duplicate a tplelm element 'e'. */
#ifdef LOGNEW
tplelm real_rdup_tplelm( const tplelm e, const char *_f, const int _l )
#else
tplelm rdup_tplelm( const tplelm e )
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

	    i_lno = rdup_int( to_Plain(e)->lno );
	    i_plainline = rdup_tmstring( to_Plain(e)->plainline );
	    return new_Plain( i_lno, i_plainline );
	}

	case TAGForeach:
	{
	    int i_lno;
	    tmstring i_felist;
	    tplelm_list i_felines;

	    i_lno = rdup_int( to_Foreach(e)->lno );
	    i_felist = rdup_tmstring( to_Foreach(e)->felist );
	    i_felines = rdup_tplelm_list( to_Foreach(e)->felines );
	    return new_Foreach( i_lno, i_felist, i_felines );
	}

	case TAGWhile:
	{
	    int i_lno;
	    tmstring i_whilecond;
	    tplelm_list i_whilelines;

	    i_lno = rdup_int( to_While(e)->lno );
	    i_whilecond = rdup_tmstring( to_While(e)->whilecond );
	    i_whilelines = rdup_tplelm_list( to_While(e)->whilelines );
	    return new_While( i_lno, i_whilecond, i_whilelines );
	}

	case TAGIf:
	{
	    int i_lno;
	    tmstring i_ifcond;
	    tplelm_list i_ifthen;
	    tplelm_list i_ifelse;

	    i_lno = rdup_int( to_If(e)->lno );
	    i_ifcond = rdup_tmstring( to_If(e)->ifcond );
	    i_ifthen = rdup_tplelm_list( to_If(e)->ifthen );
	    i_ifelse = rdup_tplelm_list( to_If(e)->ifelse );
	    return new_If( i_lno, i_ifcond, i_ifthen, i_ifelse );
	}

	case TAGSwitch:
	{
	    int i_lno;
	    tmstring i_val;
	    switchcase_list i_cases;
	    tplelm_list i_deflt;

	    i_lno = rdup_int( to_Switch(e)->lno );
	    i_val = rdup_tmstring( to_Switch(e)->val );
	    i_cases = rdup_switchcase_list( to_Switch(e)->cases );
	    i_deflt = rdup_tplelm_list( to_Switch(e)->deflt );
	    return new_Switch( i_lno, i_val, i_cases, i_deflt );
	}

	case TAGSet:
	{
	    int i_lno;
	    tmstring i_setline;

	    i_lno = rdup_int( to_Set(e)->lno );
	    i_setline = rdup_tmstring( to_Set(e)->setline );
	    return new_Set( i_lno, i_setline );
	}

	case TAGGlobalSet:
	{
	    int i_lno;
	    tmstring i_setline;

	    i_lno = rdup_int( to_GlobalSet(e)->lno );
	    i_setline = rdup_tmstring( to_GlobalSet(e)->setline );
	    return new_GlobalSet( i_lno, i_setline );
	}

	case TAGAppend:
	{
	    int i_lno;
	    tmstring i_appline;

	    i_lno = rdup_int( to_Append(e)->lno );
	    i_appline = rdup_tmstring( to_Append(e)->appline );
	    return new_Append( i_lno, i_appline );
	}

	case TAGGlobalAppend:
	{
	    int i_lno;
	    tmstring i_appline;

	    i_lno = rdup_int( to_GlobalAppend(e)->lno );
	    i_appline = rdup_tmstring( to_GlobalAppend(e)->appline );
	    return new_GlobalAppend( i_lno, i_appline );
	}

	case TAGError:
	{
	    int i_lno;
	    tmstring i_errstr;

	    i_lno = rdup_int( to_Error(e)->lno );
	    i_errstr = rdup_tmstring( to_Error(e)->errstr );
	    return new_Error( i_lno, i_errstr );
	}

	case TAGExit:
	{
	    int i_lno;
	    tmstring i_str;

	    i_lno = rdup_int( to_Exit(e)->lno );
	    i_str = rdup_tmstring( to_Exit(e)->str );
	    return new_Exit( i_lno, i_str );
	}

	case TAGRedirect:
	{
	    int i_lno;
	    tmstring i_fname;
	    tplelm_list i_body;

	    i_lno = rdup_int( to_Redirect(e)->lno );
	    i_fname = rdup_tmstring( to_Redirect(e)->fname );
	    i_body = rdup_tplelm_list( to_Redirect(e)->body );
	    return new_Redirect( i_lno, i_fname, i_body );
	}

	case TAGInclude:
	{
	    int i_lno;
	    tmstring i_fname;

	    i_lno = rdup_int( to_Include(e)->lno );
	    i_fname = rdup_tmstring( to_Include(e)->fname );
	    return new_Include( i_lno, i_fname );
	}

	case TAGMacro:
	{
	    int i_lno;
	    tmstring i_formpar;
	    tplelm_list i_macbody;

	    i_lno = rdup_int( to_Macro(e)->lno );
	    i_formpar = rdup_tmstring( to_Macro(e)->formpar );
	    i_macbody = rdup_tplelm_list( to_Macro(e)->macbody );
	    return new_Macro( i_lno, i_formpar, i_macbody );
	}

	case TAGCall:
	{
	    int i_lno;
	    tmstring i_callline;

	    i_lno = rdup_int( to_Call(e)->lno );
	    i_callline = rdup_tmstring( to_Call(e)->callline );
	    return new_Call( i_lno, i_callline );
	}

	case TAGReturn:
	{
	    int i_lno;
	    tmstring i_retval;

	    i_lno = rdup_int( to_Return(e)->lno );
	    i_retval = rdup_tmstring( to_Return(e)->retval );
	    return new_Return( i_lno, i_retval );
	}

	case TAGInsert:
	{
	    int i_lno;
	    tmstring i_fname;

	    i_lno = rdup_int( to_Insert(e)->lno );
	    i_fname = rdup_tmstring( to_Insert(e)->fname );
	    return new_Insert( i_lno, i_fname );
	}

	case TAGCase:
	{
	    int i_lno;
	    tmstring i_val;

	    i_lno = rdup_int( to_Case(e)->lno );
	    i_val = rdup_tmstring( to_Case(e)->val );
	    return new_Case( i_lno, i_val );
	}

	case TAGDefault:
	{
	    int i_lno;

	    i_lno = rdup_int( to_Default(e)->lno );
	    return new_Default( i_lno );
	}

	default:
	    FATALTAG( (int) e->tag );
    }
    return tplelmNIL;
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

/* Recursively duplicate a switchcase element 'e'. */
#ifdef LOGNEW
static switchcase real_rdup_switchcase( const switchcase e, const char *_f, const int _l )
#else
static switchcase rdup_switchcase( const switchcase e )
#endif
{
    tmstring i_cases;
    tplelm_list i_action;

    if( e == switchcaseNIL ){
	return switchcaseNIL;
    }
    i_cases = rdup_tmstring( e->cases );
    i_action = rdup_tplelm_list( e->action );
    return new_switchcase( i_cases, i_action );
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
    field *o_r;

    if( l == field_listNIL ){
	return field_listNIL;
    }
    nw = setroom_field_list( new_field_list(), l->sz );
    ar = nw->arr;
    o_r = l->arr;
    for( ix=0; ix<l->sz; ix++ ){
	*ar++ = rdup_field( *o_r++ );
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
    tmstring *o_r;

    if( l == tmstring_listNIL ){
	return tmstring_listNIL;
    }
    nw = setroom_tmstring_list( new_tmstring_list(), l->sz );
    ar = nw->arr;
    o_r = l->arr;
    for( ix=0; ix<l->sz; ix++ ){
	*ar++ = rdup_tmstring( *o_r++ );
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
    tplelm *o_r;

    if( l == tplelm_listNIL ){
	return tplelm_listNIL;
    }
    nw = setroom_tplelm_list( new_tplelm_list(), l->sz );
    ar = nw->arr;
    o_r = l->arr;
    for( ix=0; ix<l->sz; ix++ ){
	*ar++ = rdup_tplelm( *o_r++ );
    }
    nw->sz = l->sz;
    return nw;
}

/* Recursively duplicate switchcase list 'l'. */
#ifdef LOGNEW
static switchcase_list real_rdup_switchcase_list( const switchcase_list l, const char *_f, const int _l )
#else
static switchcase_list rdup_switchcase_list( const switchcase_list l )
#endif
{
    unsigned int ix;
    switchcase_list nw;
    switchcase *ar;
    switchcase *o_r;

    if( l == switchcase_listNIL ){
	return switchcase_listNIL;
    }
    nw = setroom_switchcase_list( new_switchcase_list(), l->sz );
    ar = nw->arr;
    o_r = l->arr;
    for( ix=0; ix<l->sz; ix++ ){
	*ar++ = rdup_switchcase( *o_r++ );
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
 *    extract_<type>_list routines                 *
 **************************************************/


/* Extract 'tmstring' element at position 'pos' in list 'l'. */
tmstring_list extract_tmstring_list(
    tmstring_list l,
    const unsigned int pos,
    tmstring *e,
    int *valid
)
{
    unsigned int ix;

    if( l == tmstring_listNIL ){
	FATAL( tm_nilptr );
    }
    if( pos >= l->sz ){
	*valid = 0;
	return l;
    }
    *valid = 1;
    *e = l->arr[pos];
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
    for( ix=0; ix<cacheix_switchcase_list; ix++ ){
	TM_FREE( cache_switchcase_list[ix] );
    }
    cacheix_switchcase_list = 0;
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
    for( ix=0; ix<cacheix_switchcase; ix++ ){
	TM_FREE( cache_switchcase[ix] );
    }
    cacheix_switchcase = 0;
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
	"DsConstructorBase",
	newcnt_DsConstructorBase,
	frecnt_DsConstructorBase,
	((newcnt_DsConstructorBase==frecnt_DsConstructorBase)? "": "<-")
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
	"DsConstructor",
	newcnt_DsConstructor,
	frecnt_DsConstructor,
	((newcnt_DsConstructor==frecnt_DsConstructor)? "": "<-")
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
	"switchcase",
	newcnt_switchcase,
	frecnt_switchcase,
	((newcnt_switchcase==frecnt_switchcase)? "": "<-")
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
	"Switch",
	newcnt_Switch,
	frecnt_Switch,
	((newcnt_Switch==frecnt_Switch)? "": "<-")
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
	"GlobalSet",
	newcnt_GlobalSet,
	frecnt_GlobalSet,
	((newcnt_GlobalSet==frecnt_GlobalSet)? "": "<-")
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
	"GlobalAppend",
	newcnt_GlobalAppend,
	frecnt_GlobalAppend,
	((newcnt_GlobalAppend==frecnt_GlobalAppend)? "": "<-")
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
	"Case",
	newcnt_Case,
	frecnt_Case,
	((newcnt_Case==frecnt_Case)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Default",
	newcnt_Default,
	frecnt_Default,
	((newcnt_Default==frecnt_Default)? "": "<-")
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
	tm_allocfreed, "switchcase_list",
	newcnt_switchcase_list,
	frecnt_switchcase_list,
	((newcnt_switchcase_list==frecnt_switchcase_list)? "": "<-")
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

/* Return -1 if there is a structure that has freed more than allocated, or
 * else return 1 if there is a structure that has been freed less than
 * allocated, or else return 0.
 */
int get_balance_tm( void )
{
    int res;

    res = 0;
#ifdef STAT
    if( newcnt_alternative_list<frecnt_alternative_list ){
        return -1;
    }
    if( newcnt_alternative_list>frecnt_alternative_list ){
        res = 1;
    }
    if( newcnt_classComponent_list<frecnt_classComponent_list ){
        return -1;
    }
    if( newcnt_classComponent_list>frecnt_classComponent_list ){
        res = 1;
    }
    if( newcnt_ds_list<frecnt_ds_list ){
        return -1;
    }
    if( newcnt_ds_list>frecnt_ds_list ){
        res = 1;
    }
    if( newcnt_field_list<frecnt_field_list ){
        return -1;
    }
    if( newcnt_field_list>frecnt_field_list ){
        res = 1;
    }
    if( newcnt_macro_list<frecnt_macro_list ){
        return -1;
    }
    if( newcnt_macro_list>frecnt_macro_list ){
        res = 1;
    }
    if( newcnt_switchcase_list<frecnt_switchcase_list ){
        return -1;
    }
    if( newcnt_switchcase_list>frecnt_switchcase_list ){
        res = 1;
    }
    if( newcnt_tmstring_list<frecnt_tmstring_list ){
        return -1;
    }
    if( newcnt_tmstring_list>frecnt_tmstring_list ){
        res = 1;
    }
    if( newcnt_tplelm_list<frecnt_tplelm_list ){
        return -1;
    }
    if( newcnt_tplelm_list>frecnt_tplelm_list ){
        res = 1;
    }
    if( newcnt_var_list<frecnt_var_list ){
        return -1;
    }
    if( newcnt_var_list>frecnt_var_list ){
        res = 1;
    }
    if( newcnt_alternative<frecnt_alternative ){
        return -1;
    }
    if( newcnt_alternative>frecnt_alternative ){
        res = 1;
    }
    if( newcnt_CCSuper<frecnt_CCSuper ){
        return -1;
    }
    if( newcnt_CCSuper>frecnt_CCSuper ){
        res = 1;
    }
    if( newcnt_CCFields<frecnt_CCFields ){
        return -1;
    }
    if( newcnt_CCFields>frecnt_CCFields ){
        res = 1;
    }
    if( newcnt_CCAlternatives<frecnt_CCAlternatives ){
        return -1;
    }
    if( newcnt_CCAlternatives>frecnt_CCAlternatives ){
        res = 1;
    }
    if( newcnt_CCSublist<frecnt_CCSublist ){
        return -1;
    }
    if( newcnt_CCSublist>frecnt_CCSublist ){
        res = 1;
    }
    if( newcnt_DsConstructorBase<frecnt_DsConstructorBase ){
        return -1;
    }
    if( newcnt_DsConstructorBase>frecnt_DsConstructorBase ){
        res = 1;
    }
    if( newcnt_DsTuple<frecnt_DsTuple ){
        return -1;
    }
    if( newcnt_DsTuple>frecnt_DsTuple ){
        res = 1;
    }
    if( newcnt_DsClass<frecnt_DsClass ){
        return -1;
    }
    if( newcnt_DsClass>frecnt_DsClass ){
        res = 1;
    }
    if( newcnt_DsConstructor<frecnt_DsConstructor ){
        return -1;
    }
    if( newcnt_DsConstructor>frecnt_DsConstructor ){
        res = 1;
    }
    if( newcnt_field<frecnt_field ){
        return -1;
    }
    if( newcnt_field>frecnt_field ){
        res = 1;
    }
    if( newcnt_macro<frecnt_macro ){
        return -1;
    }
    if( newcnt_macro>frecnt_macro ){
        res = 1;
    }
    if( newcnt_switchcase<frecnt_switchcase ){
        return -1;
    }
    if( newcnt_switchcase>frecnt_switchcase ){
        res = 1;
    }
    if( newcnt_Plain<frecnt_Plain ){
        return -1;
    }
    if( newcnt_Plain>frecnt_Plain ){
        res = 1;
    }
    if( newcnt_Foreach<frecnt_Foreach ){
        return -1;
    }
    if( newcnt_Foreach>frecnt_Foreach ){
        res = 1;
    }
    if( newcnt_While<frecnt_While ){
        return -1;
    }
    if( newcnt_While>frecnt_While ){
        res = 1;
    }
    if( newcnt_If<frecnt_If ){
        return -1;
    }
    if( newcnt_If>frecnt_If ){
        res = 1;
    }
    if( newcnt_Switch<frecnt_Switch ){
        return -1;
    }
    if( newcnt_Switch>frecnt_Switch ){
        res = 1;
    }
    if( newcnt_Set<frecnt_Set ){
        return -1;
    }
    if( newcnt_Set>frecnt_Set ){
        res = 1;
    }
    if( newcnt_GlobalSet<frecnt_GlobalSet ){
        return -1;
    }
    if( newcnt_GlobalSet>frecnt_GlobalSet ){
        res = 1;
    }
    if( newcnt_Append<frecnt_Append ){
        return -1;
    }
    if( newcnt_Append>frecnt_Append ){
        res = 1;
    }
    if( newcnt_GlobalAppend<frecnt_GlobalAppend ){
        return -1;
    }
    if( newcnt_GlobalAppend>frecnt_GlobalAppend ){
        res = 1;
    }
    if( newcnt_Error<frecnt_Error ){
        return -1;
    }
    if( newcnt_Error>frecnt_Error ){
        res = 1;
    }
    if( newcnt_Exit<frecnt_Exit ){
        return -1;
    }
    if( newcnt_Exit>frecnt_Exit ){
        res = 1;
    }
    if( newcnt_Redirect<frecnt_Redirect ){
        return -1;
    }
    if( newcnt_Redirect>frecnt_Redirect ){
        res = 1;
    }
    if( newcnt_Include<frecnt_Include ){
        return -1;
    }
    if( newcnt_Include>frecnt_Include ){
        res = 1;
    }
    if( newcnt_Macro<frecnt_Macro ){
        return -1;
    }
    if( newcnt_Macro>frecnt_Macro ){
        res = 1;
    }
    if( newcnt_Call<frecnt_Call ){
        return -1;
    }
    if( newcnt_Call>frecnt_Call ){
        res = 1;
    }
    if( newcnt_Return<frecnt_Return ){
        return -1;
    }
    if( newcnt_Return>frecnt_Return ){
        res = 1;
    }
    if( newcnt_Insert<frecnt_Insert ){
        return -1;
    }
    if( newcnt_Insert>frecnt_Insert ){
        res = 1;
    }
    if( newcnt_Case<frecnt_Case ){
        return -1;
    }
    if( newcnt_Case>frecnt_Case ){
        res = 1;
    }
    if( newcnt_Default<frecnt_Default ){
        return -1;
    }
    if( newcnt_Default>frecnt_Default ){
        res = 1;
    }
    if( newcnt_var<frecnt_var ){
        return -1;
    }
    if( newcnt_var>frecnt_var ){
        res = 1;
    }
#endif
    return res;
}

/* ---- end of /usr/local/lib/calu.ct ---- */
/* Code generation required 15190 milliseconds. */