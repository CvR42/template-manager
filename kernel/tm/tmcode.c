/* file: tmcode.c */

/* Standard UNIX libraries */
#include <stdio.h>

/* Standard tm library */
#include <tmc.h>

#include <time.h>


#include "tmcode.h"
#include "tmstring.h"
#include "global.h"
#include "misc.h"

/* Requirement analysis took 16 milliseconds. */
/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /Users/reeuwijk/lab/lib/tmc.ct ---- */

/* Routines for 'tm'.

   template file:      /Users/reeuwijk/lab/lib/tmc.ct
   datastructure file: tm.ds
   tm version:         36
   tm kernel version:  *** development -- not for distribution ***
 */

#ifndef FIRSTROOM
#define FIRSTROOM 1U
#endif

/* Counters for allocation and freeing. */
static long newcnt_Field_list = 0L, frecnt_Field_list = 0L;
static long newcnt_Switchcase_list = 0L, frecnt_Switchcase_list = 0L;
static long newcnt_Type_list = 0L, frecnt_Type_list = 0L;
static long newcnt_alternative_list = 0L, frecnt_alternative_list = 0L;
static long newcnt_classComponent_list = 0L, frecnt_classComponent_list = 0L;
static long newcnt_ds_list = 0L, frecnt_ds_list = 0L;
static long newcnt_macro_list = 0L, frecnt_macro_list = 0L;
static long newcnt_tmstring_list = 0L, frecnt_tmstring_list = 0L;
static long newcnt_tmsymbol_list = 0L, frecnt_tmsymbol_list = 0L;
static long newcnt_tplelm_list = 0L, frecnt_tplelm_list = 0L;
static long newcnt_variable_list = 0L, frecnt_variable_list = 0L;
static long newcnt_Append = 0L, frecnt_Append = 0L;
static long newcnt_Appendfile = 0L, frecnt_Appendfile = 0L;
static long newcnt_CCAlternatives = 0L, frecnt_CCAlternatives = 0L;
static long newcnt_CCFields = 0L, frecnt_CCFields = 0L;
static long newcnt_CCSublist = 0L, frecnt_CCSublist = 0L;
static long newcnt_CCSuper = 0L, frecnt_CCSuper = 0L;
static long newcnt_Call = 0L, frecnt_Call = 0L;
static long newcnt_Case = 0L, frecnt_Case = 0L;
static long newcnt_Default = 0L, frecnt_Default = 0L;
static long newcnt_DeleteType = 0L, frecnt_DeleteType = 0L;
static long newcnt_DsAlias = 0L, frecnt_DsAlias = 0L;
static long newcnt_DsClass = 0L, frecnt_DsClass = 0L;
static long newcnt_DsConstructor = 0L, frecnt_DsConstructor = 0L;
static long newcnt_DsConstructorBase = 0L, frecnt_DsConstructorBase = 0L;
static long newcnt_DsInclude = 0L, frecnt_DsInclude = 0L;
static long newcnt_DsTuple = 0L, frecnt_DsTuple = 0L;
static long newcnt_Error = 0L, frecnt_Error = 0L;
static long newcnt_Exit = 0L, frecnt_Exit = 0L;
static long newcnt_Field = 0L, frecnt_Field = 0L;
static long newcnt_For = 0L, frecnt_For = 0L;
static long newcnt_Foreach = 0L, frecnt_Foreach = 0L;
static long newcnt_GlobalAppend = 0L, frecnt_GlobalAppend = 0L;
static long newcnt_GlobalSet = 0L, frecnt_GlobalSet = 0L;
static long newcnt_GlobalSplit = 0L, frecnt_GlobalSplit = 0L;
static long newcnt_If = 0L, frecnt_If = 0L;
static long newcnt_Include = 0L, frecnt_Include = 0L;
static long newcnt_Insert = 0L, frecnt_Insert = 0L;
static long newcnt_Macro = 0L, frecnt_Macro = 0L;
static long newcnt_Plain = 0L, frecnt_Plain = 0L;
static long newcnt_Redirect = 0L, frecnt_Redirect = 0L;
static long newcnt_Rename = 0L, frecnt_Rename = 0L;
static long newcnt_Return = 0L, frecnt_Return = 0L;
static long newcnt_Set = 0L, frecnt_Set = 0L;
static long newcnt_Split = 0L, frecnt_Split = 0L;
static long newcnt_Switch = 0L, frecnt_Switch = 0L;
static long newcnt_Switchcase = 0L, frecnt_Switchcase = 0L;
static long newcnt_Type = 0L, frecnt_Type = 0L;
static long newcnt_While = 0L, frecnt_While = 0L;
static long newcnt_alternative = 0L, frecnt_alternative = 0L;
static long newcnt_macro = 0L, frecnt_macro = 0L;
static long newcnt_origin = 0L, frecnt_origin = 0L;
static long newcnt_origsymbol = 0L, frecnt_origsymbol = 0L;
static long newcnt_variable = 0L, frecnt_variable = 0L;


#ifndef FATAL
#define FATAL(msg) tm_fatal(__FILE__,__LINE__,msg)
#endif

/* Error strings. */
static const char tm_nilptr[] = "NIL pointer";

#ifndef FATALTAG
#define FATALTAG(tag) tm_badtag(__FILE__,__LINE__,(int) tag)
#endif

/**************************************************
 *    set array room routines                     *
 **************************************************/

/* Announce that you will need room for 'rm' elements in
 *  Field_list 'l'.
 */
static  Field_list setroom_Field_list(  Field_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->arr==NULL ){
	l->arr = TM_MALLOC( Field *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( Field *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need room for 'rm' elements in
 *  tmstring_list 'l'.
 */
 tmstring_list setroom_tmstring_list(  tmstring_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->arr==NULL ){
	l->arr = TM_MALLOC( tmstring *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( tmstring *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need room for 'rm' elements in
 *  tmsymbol_list 'l'.
 */
 tmsymbol_list setroom_tmsymbol_list(  tmsymbol_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->arr==NULL ){
	l->arr = TM_MALLOC( tmsymbol *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( tmsymbol *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need room for 'rm' elements in
 *  tplelm_list 'l'.
 */
static  tplelm_list setroom_tplelm_list(  tplelm_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->arr==NULL ){
	l->arr = TM_MALLOC( tplelm *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( tplelm *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need room for 'rm' elements in
 *  Switchcase_list 'l'.
 */
static  Switchcase_list setroom_Switchcase_list(  Switchcase_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->arr==NULL ){
	l->arr = TM_MALLOC( Switchcase *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( Switchcase *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need room for 'rm' elements in
 *  Type_list 'l'.
 */
static  Type_list setroom_Type_list(  Type_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->arr==NULL ){
	l->arr = TM_MALLOC( Type *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( Type *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need room for 'rm' elements in
 *  alternative_list 'l'.
 */
static  alternative_list setroom_alternative_list(  alternative_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->arr==NULL ){
	l->arr = TM_MALLOC( alternative *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( alternative *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need room for 'rm' elements in
 *  classComponent_list 'l'.
 */
static  classComponent_list setroom_classComponent_list(  classComponent_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->arr==NULL ){
	l->arr = TM_MALLOC( classComponent *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( classComponent *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need room for 'rm' elements in
 *  ds_list 'l'.
 */
static  ds_list setroom_ds_list(  ds_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->arr==NULL ){
	l->arr = TM_MALLOC( ds *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( ds *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need room for 'rm' elements in
 *  variable_list 'l'.
 */
static  variable_list setroom_variable_list(  variable_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->arr==NULL ){
	l->arr = TM_MALLOC( variable *, rm * sizeof(*(l->arr)) );
    }
    else {
	l->arr = TM_REALLOC( variable *, l->arr, rm * sizeof(*(l->arr)) );
    }
    l->room = rm;
    return l;
}

/* Announce that you will need room for 'rm' elements in
 *  macro_list 'l'.
 */
static  macro_list setroom_macro_list(  macro_list l, const unsigned int rm )
{
    if( l->room>=rm ){
	return l;
    }
    if( l->arr==NULL ){
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
#undef new_Append
#define new_Append(org,line) real_new_Append(org,line,_f,_l)
#undef new_Appendfile
#define new_Appendfile(org,fname,body) real_new_Appendfile(org,fname,body,_f,_l)
#undef new_CCAlternatives
#define new_CCAlternatives(alternatives) real_new_CCAlternatives(alternatives,_f,_l)
#undef new_CCFields
#define new_CCFields(fields) real_new_CCFields(fields,_f,_l)
#undef new_CCSublist
#define new_CCSublist(components) real_new_CCSublist(components,_f,_l)
#undef new_CCSuper
#define new_CCSuper(super) real_new_CCSuper(super,_f,_l)
#undef new_Call
#define new_Call(org,line) real_new_Call(org,line,_f,_l)
#undef new_Case
#define new_Case(org,val) real_new_Case(org,val,_f,_l)
#undef new_Default
#define new_Default(org) real_new_Default(org,_f,_l)
#undef new_DeleteType
#define new_DeleteType(org,line) real_new_DeleteType(org,line,_f,_l)
#undef new_DsAlias
#define new_DsAlias(name,inherits,inheritors,type) real_new_DsAlias(name,inherits,inheritors,type,_f,_l)
#undef new_DsClass
#define new_DsClass(name,inherits,inheritors,fields,isvirtual) real_new_DsClass(name,inherits,inheritors,fields,isvirtual,_f,_l)
#undef new_DsConstructor
#define new_DsConstructor(name,inherits,inheritors,fields) real_new_DsConstructor(name,inherits,inheritors,fields,_f,_l)
#undef new_DsConstructorBase
#define new_DsConstructorBase(name,inherits,inheritors,constructors) real_new_DsConstructorBase(name,inherits,inheritors,constructors,_f,_l)
#undef new_DsInclude
#define new_DsInclude(name,inherits,inheritors,fnm) real_new_DsInclude(name,inherits,inheritors,fnm,_f,_l)
#undef new_DsTuple
#define new_DsTuple(name,inherits,inheritors,fields) real_new_DsTuple(name,inherits,inheritors,fields,_f,_l)
#undef new_Error
#define new_Error(org,str) real_new_Error(org,str,_f,_l)
#undef new_Exit
#define new_Exit(org,str) real_new_Exit(org,str,_f,_l)
#undef new_Field
#define new_Field(name,type) real_new_Field(name,type,_f,_l)
#undef new_For
#define new_For(org,parms,body) real_new_For(org,parms,body,_f,_l)
#undef new_Foreach
#define new_Foreach(org,felist,body) real_new_Foreach(org,felist,body,_f,_l)
#undef new_GlobalAppend
#define new_GlobalAppend(org,line) real_new_GlobalAppend(org,line,_f,_l)
#undef new_GlobalSet
#define new_GlobalSet(org,line) real_new_GlobalSet(org,line,_f,_l)
#undef new_GlobalSplit
#define new_GlobalSplit(org,line) real_new_GlobalSplit(org,line,_f,_l)
#undef new_If
#define new_If(org,cond,ifthen,ifelse) real_new_If(org,cond,ifthen,ifelse,_f,_l)
#undef new_Include
#define new_Include(org,fname) real_new_Include(org,fname,_f,_l)
#undef new_Insert
#define new_Insert(org,fname) real_new_Insert(org,fname,_f,_l)
#undef new_Macro
#define new_Macro(org,formals,body) real_new_Macro(org,formals,body,_f,_l)
#undef new_Plain
#define new_Plain(org,line) real_new_Plain(org,line,_f,_l)
#undef new_Redirect
#define new_Redirect(org,fname,body) real_new_Redirect(org,fname,body,_f,_l)
#undef new_Rename
#define new_Rename(org,line) real_new_Rename(org,line,_f,_l)
#undef new_Return
#define new_Return(org,retval) real_new_Return(org,retval,_f,_l)
#undef new_Set
#define new_Set(org,line) real_new_Set(org,line,_f,_l)
#undef new_Split
#define new_Split(org,line) real_new_Split(org,line,_f,_l)
#undef new_Switch
#define new_Switch(org,val,cases,deflt) real_new_Switch(org,val,cases,deflt,_f,_l)
#undef new_Switchcase
#define new_Switchcase(cases,action) real_new_Switchcase(cases,action,_f,_l)
#undef new_Type
#define new_Type(level,basetype) real_new_Type(level,basetype,_f,_l)
#undef new_While
#define new_While(org,cond,body) real_new_While(org,cond,body,_f,_l)
#undef new_alternative
#define new_alternative(label,component) real_new_alternative(label,component,_f,_l)
#undef new_macro
#define new_macro(org,lvl,name,fpl,body) real_new_macro(org,lvl,name,fpl,body,_f,_l)
#undef new_origin
#define new_origin(file,line) real_new_origin(file,line,_f,_l)
#undef new_origsymbol
#define new_origsymbol(sym,org) real_new_origsymbol(sym,org,_f,_l)
#undef new_variable
#define new_variable(lvl,name,val) real_new_variable(lvl,name,val,_f,_l)
#undef new_Field_list
#define new_Field_list() real_new_Field_list(_f,_l)
#undef new_Switchcase_list
#define new_Switchcase_list() real_new_Switchcase_list(_f,_l)
#undef new_Type_list
#define new_Type_list() real_new_Type_list(_f,_l)
#undef new_alternative_list
#define new_alternative_list() real_new_alternative_list(_f,_l)
#undef new_classComponent_list
#define new_classComponent_list() real_new_classComponent_list(_f,_l)
#undef new_ds_list
#define new_ds_list() real_new_ds_list(_f,_l)
#undef new_macro_list
#define new_macro_list() real_new_macro_list(_f,_l)
#undef new_tmstring_list
#define new_tmstring_list() real_new_tmstring_list(_f,_l)
#undef new_tmsymbol_list
#define new_tmsymbol_list() real_new_tmsymbol_list(_f,_l)
#undef new_tplelm_list
#define new_tplelm_list() real_new_tplelm_list(_f,_l)
#undef new_variable_list
#define new_variable_list() real_new_variable_list(_f,_l)
#endif

#ifdef LOGNEW
 Field_list real_new_Field_list( const char *_f, const int _l )
#else
 Field_list new_Field_list( void )
#endif
{
    Field_list nw;

    nw = TM_MALLOC( Field_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0U
    nw->arr = (Field *) 0;
    nw->room = 0;
#else
    nw->arr = TM_CALLOC( Field *, sizeof(Field), FIRSTROOM );
    nw->room = FIRSTROOM;
#endif
    newcnt_Field_list++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
 Switchcase_list real_new_Switchcase_list( const char *_f, const int _l )
#else
 Switchcase_list new_Switchcase_list( void )
#endif
{
    Switchcase_list nw;

    nw = TM_MALLOC( Switchcase_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0U
    nw->arr = (Switchcase *) 0;
    nw->room = 0;
#else
    nw->arr = TM_CALLOC( Switchcase *, sizeof(Switchcase), FIRSTROOM );
    nw->room = FIRSTROOM;
#endif
    newcnt_Switchcase_list++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
 Type_list real_new_Type_list( const char *_f, const int _l )
#else
 Type_list new_Type_list( void )
#endif
{
    Type_list nw;

    nw = TM_MALLOC( Type_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0U
    nw->arr = (Type *) 0;
    nw->room = 0;
#else
    nw->arr = TM_CALLOC( Type *, sizeof(Type), FIRSTROOM );
    nw->room = FIRSTROOM;
#endif
    newcnt_Type_list++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
 alternative_list real_new_alternative_list( const char *_f, const int _l )
#else
 alternative_list new_alternative_list( void )
#endif
{
    alternative_list nw;

    nw = TM_MALLOC( alternative_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0U
    nw->arr = (alternative *) 0;
    nw->room = 0;
#else
    nw->arr = TM_CALLOC( alternative *, sizeof(alternative), FIRSTROOM );
    nw->room = FIRSTROOM;
#endif
    newcnt_alternative_list++;
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

    nw = TM_MALLOC( classComponent_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0U
    nw->arr = (classComponent *) 0;
    nw->room = 0;
#else
    nw->arr = TM_CALLOC( classComponent *, sizeof(classComponent), FIRSTROOM );
    nw->room = FIRSTROOM;
#endif
    newcnt_classComponent_list++;
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

    nw = TM_MALLOC( ds_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0U
    nw->arr = (ds *) 0;
    nw->room = 0;
#else
    nw->arr = TM_CALLOC( ds *, sizeof(ds), FIRSTROOM );
    nw->room = FIRSTROOM;
#endif
    newcnt_ds_list++;
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

    nw = TM_MALLOC( macro_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0U
    nw->arr = (macro *) 0;
    nw->room = 0;
#else
    nw->arr = TM_CALLOC( macro *, sizeof(macro), FIRSTROOM );
    nw->room = FIRSTROOM;
#endif
    newcnt_macro_list++;
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

    nw = TM_MALLOC( tmstring_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0U
    nw->arr = (tmstring *) 0;
    nw->room = 0;
#else
    nw->arr = TM_CALLOC( tmstring *, sizeof(tmstring), FIRSTROOM );
    nw->room = FIRSTROOM;
#endif
    newcnt_tmstring_list++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
 tmsymbol_list real_new_tmsymbol_list( const char *_f, const int _l )
#else
 tmsymbol_list new_tmsymbol_list( void )
#endif
{
    tmsymbol_list nw;

    nw = TM_MALLOC( tmsymbol_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0U
    nw->arr = (tmsymbol *) 0;
    nw->room = 0;
#else
    nw->arr = TM_CALLOC( tmsymbol *, sizeof(tmsymbol), FIRSTROOM );
    nw->room = FIRSTROOM;
#endif
    newcnt_tmsymbol_list++;
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

    nw = TM_MALLOC( tplelm_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0U
    nw->arr = (tplelm *) 0;
    nw->room = 0;
#else
    nw->arr = TM_CALLOC( tplelm *, sizeof(tplelm), FIRSTROOM );
    nw->room = FIRSTROOM;
#endif
    newcnt_tplelm_list++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

#ifdef LOGNEW
 variable_list real_new_variable_list( const char *_f, const int _l )
#else
 variable_list new_variable_list( void )
#endif
{
    variable_list nw;

    nw = TM_MALLOC( variable_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0U
    nw->arr = (variable *) 0;
    nw->room = 0;
#else
    nw->arr = TM_CALLOC( variable *, sizeof(variable), FIRSTROOM );
    nw->room = FIRSTROOM;
#endif
    newcnt_variable_list++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Append'. */
#ifdef LOGNEW
Append real_new_Append( origin p_org, tmstring p_line, const char *_f, const int _l )
#else
Append new_Append( origin p_org, tmstring p_line )
#endif
{
    Append nw;

    nw = TM_MALLOC( Append, sizeof(*nw) );
    nw->tag = TAGAppend;
    nw->org = p_org;
    nw->line = p_line;
    newcnt_Append++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Appendfile'. */
#ifdef LOGNEW
Appendfile real_new_Appendfile( origin p_org, tmstring p_fname, tplelm_list p_body, const char *_f, const int _l )
#else
Appendfile new_Appendfile( origin p_org, tmstring p_fname, tplelm_list p_body )
#endif
{
    Appendfile nw;

    nw = TM_MALLOC( Appendfile, sizeof(*nw) );
    nw->tag = TAGAppendfile;
    nw->org = p_org;
    nw->fname = p_fname;
    nw->body = p_body;
    newcnt_Appendfile++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'CCAlternatives'. */
#ifdef LOGNEW
CCAlternatives real_new_CCAlternatives( alternative_list p_alternatives, const char *_f, const int _l )
#else
CCAlternatives new_CCAlternatives( alternative_list p_alternatives )
#endif
{
    CCAlternatives nw;

    nw = TM_MALLOC( CCAlternatives, sizeof(*nw) );
    nw->tag = TAGCCAlternatives;
    nw->alternatives = p_alternatives;
    newcnt_CCAlternatives++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'CCFields'. */
#ifdef LOGNEW
CCFields real_new_CCFields( Field_list p_fields, const char *_f, const int _l )
#else
CCFields new_CCFields( Field_list p_fields )
#endif
{
    CCFields nw;

    nw = TM_MALLOC( CCFields, sizeof(*nw) );
    nw->tag = TAGCCFields;
    nw->fields = p_fields;
    newcnt_CCFields++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'CCSublist'. */
#ifdef LOGNEW
CCSublist real_new_CCSublist( classComponent_list p_components, const char *_f, const int _l )
#else
CCSublist new_CCSublist( classComponent_list p_components )
#endif
{
    CCSublist nw;

    nw = TM_MALLOC( CCSublist, sizeof(*nw) );
    nw->tag = TAGCCSublist;
    nw->components = p_components;
    newcnt_CCSublist++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'CCSuper'. */
#ifdef LOGNEW
CCSuper real_new_CCSuper( tmsymbol p_super, const char *_f, const int _l )
#else
CCSuper new_CCSuper( tmsymbol p_super )
#endif
{
    CCSuper nw;

    nw = TM_MALLOC( CCSuper, sizeof(*nw) );
    nw->tag = TAGCCSuper;
    nw->super = p_super;
    newcnt_CCSuper++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Call'. */
#ifdef LOGNEW
Call real_new_Call( origin p_org, tmstring p_line, const char *_f, const int _l )
#else
Call new_Call( origin p_org, tmstring p_line )
#endif
{
    Call nw;

    nw = TM_MALLOC( Call, sizeof(*nw) );
    nw->tag = TAGCall;
    nw->org = p_org;
    nw->line = p_line;
    newcnt_Call++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Case'. */
#ifdef LOGNEW
Case real_new_Case( origin p_org, tmstring p_val, const char *_f, const int _l )
#else
Case new_Case( origin p_org, tmstring p_val )
#endif
{
    Case nw;

    nw = TM_MALLOC( Case, sizeof(*nw) );
    nw->tag = TAGCase;
    nw->org = p_org;
    nw->val = p_val;
    newcnt_Case++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Default'. */
#ifdef LOGNEW
Default real_new_Default( origin p_org, const char *_f, const int _l )
#else
Default new_Default( origin p_org )
#endif
{
    Default nw;

    nw = TM_MALLOC( Default, sizeof(*nw) );
    nw->tag = TAGDefault;
    nw->org = p_org;
    newcnt_Default++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'DeleteType'. */
#ifdef LOGNEW
DeleteType real_new_DeleteType( origin p_org, tmstring p_line, const char *_f, const int _l )
#else
DeleteType new_DeleteType( origin p_org, tmstring p_line )
#endif
{
    DeleteType nw;

    nw = TM_MALLOC( DeleteType, sizeof(*nw) );
    nw->tag = TAGDeleteType;
    nw->org = p_org;
    nw->line = p_line;
    newcnt_DeleteType++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'DsAlias'. */
#ifdef LOGNEW
DsAlias real_new_DsAlias( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, Type p_type, const char *_f, const int _l )
#else
DsAlias new_DsAlias( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, Type p_type )
#endif
{
    DsAlias nw;

    nw = TM_MALLOC( DsAlias, sizeof(*nw) );
    nw->tag = TAGDsAlias;
    nw->name = p_name;
    nw->inherits = p_inherits;
    nw->inheritors = p_inheritors;
    nw->type = p_type;
    newcnt_DsAlias++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'DsClass'. */
#ifdef LOGNEW
DsClass real_new_DsClass( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, Field_list p_fields, tmbool p_isvirtual, const char *_f, const int _l )
#else
DsClass new_DsClass( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, Field_list p_fields, tmbool p_isvirtual )
#endif
{
    DsClass nw;

    nw = TM_MALLOC( DsClass, sizeof(*nw) );
    nw->tag = TAGDsClass;
    nw->name = p_name;
    nw->inherits = p_inherits;
    nw->inheritors = p_inheritors;
    nw->fields = p_fields;
    nw->isvirtual = p_isvirtual;
    newcnt_DsClass++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'DsConstructor'. */
#ifdef LOGNEW
DsConstructor real_new_DsConstructor( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, Field_list p_fields, const char *_f, const int _l )
#else
DsConstructor new_DsConstructor( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, Field_list p_fields )
#endif
{
    DsConstructor nw;

    nw = TM_MALLOC( DsConstructor, sizeof(*nw) );
    nw->tag = TAGDsConstructor;
    nw->name = p_name;
    nw->inherits = p_inherits;
    nw->inheritors = p_inheritors;
    nw->fields = p_fields;
    newcnt_DsConstructor++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'DsConstructorBase'. */
#ifdef LOGNEW
DsConstructorBase real_new_DsConstructorBase( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, tmsymbol_list p_constructors, const char *_f, const int _l )
#else
DsConstructorBase new_DsConstructorBase( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, tmsymbol_list p_constructors )
#endif
{
    DsConstructorBase nw;

    nw = TM_MALLOC( DsConstructorBase, sizeof(*nw) );
    nw->tag = TAGDsConstructorBase;
    nw->name = p_name;
    nw->inherits = p_inherits;
    nw->inheritors = p_inheritors;
    nw->constructors = p_constructors;
    newcnt_DsConstructorBase++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'DsInclude'. */
#ifdef LOGNEW
DsInclude real_new_DsInclude( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, tmstring p_fnm, const char *_f, const int _l )
#else
DsInclude new_DsInclude( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, tmstring p_fnm )
#endif
{
    DsInclude nw;

    nw = TM_MALLOC( DsInclude, sizeof(*nw) );
    nw->tag = TAGDsInclude;
    nw->name = p_name;
    nw->inherits = p_inherits;
    nw->inheritors = p_inheritors;
    nw->fnm = p_fnm;
    newcnt_DsInclude++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'DsTuple'. */
#ifdef LOGNEW
DsTuple real_new_DsTuple( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, Field_list p_fields, const char *_f, const int _l )
#else
DsTuple new_DsTuple( origsymbol p_name, tmsymbol_list p_inherits, tmsymbol_list p_inheritors, Field_list p_fields )
#endif
{
    DsTuple nw;

    nw = TM_MALLOC( DsTuple, sizeof(*nw) );
    nw->tag = TAGDsTuple;
    nw->name = p_name;
    nw->inherits = p_inherits;
    nw->inheritors = p_inheritors;
    nw->fields = p_fields;
    newcnt_DsTuple++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Error'. */
#ifdef LOGNEW
Error real_new_Error( origin p_org, tmstring p_str, const char *_f, const int _l )
#else
Error new_Error( origin p_org, tmstring p_str )
#endif
{
    Error nw;

    nw = TM_MALLOC( Error, sizeof(*nw) );
    nw->tag = TAGError;
    nw->org = p_org;
    nw->str = p_str;
    newcnt_Error++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Exit'. */
#ifdef LOGNEW
Exit real_new_Exit( origin p_org, tmstring p_str, const char *_f, const int _l )
#else
Exit new_Exit( origin p_org, tmstring p_str )
#endif
{
    Exit nw;

    nw = TM_MALLOC( Exit, sizeof(*nw) );
    nw->tag = TAGExit;
    nw->org = p_org;
    nw->str = p_str;
    newcnt_Exit++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of tuple 'Field'. */
#ifdef LOGNEW
Field real_new_Field( origsymbol p_name, Type p_type, const char *_f, const int _l )
#else
Field new_Field( origsymbol p_name, Type p_type )
#endif
{
    Field nw;

    nw = TM_MALLOC( Field, sizeof(*nw) );
    nw->name = p_name;
    nw->type = p_type;
    newcnt_Field++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'For'. */
#ifdef LOGNEW
For real_new_For( origin p_org, tmstring p_parms, tplelm_list p_body, const char *_f, const int _l )
#else
For new_For( origin p_org, tmstring p_parms, tplelm_list p_body )
#endif
{
    For nw;

    nw = TM_MALLOC( For, sizeof(*nw) );
    nw->tag = TAGFor;
    nw->org = p_org;
    nw->parms = p_parms;
    nw->body = p_body;
    newcnt_For++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Foreach'. */
#ifdef LOGNEW
Foreach real_new_Foreach( origin p_org, tmstring p_felist, tplelm_list p_body, const char *_f, const int _l )
#else
Foreach new_Foreach( origin p_org, tmstring p_felist, tplelm_list p_body )
#endif
{
    Foreach nw;

    nw = TM_MALLOC( Foreach, sizeof(*nw) );
    nw->tag = TAGForeach;
    nw->org = p_org;
    nw->felist = p_felist;
    nw->body = p_body;
    newcnt_Foreach++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'GlobalAppend'. */
#ifdef LOGNEW
GlobalAppend real_new_GlobalAppend( origin p_org, tmstring p_line, const char *_f, const int _l )
#else
GlobalAppend new_GlobalAppend( origin p_org, tmstring p_line )
#endif
{
    GlobalAppend nw;

    nw = TM_MALLOC( GlobalAppend, sizeof(*nw) );
    nw->tag = TAGGlobalAppend;
    nw->org = p_org;
    nw->line = p_line;
    newcnt_GlobalAppend++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'GlobalSet'. */
#ifdef LOGNEW
GlobalSet real_new_GlobalSet( origin p_org, tmstring p_line, const char *_f, const int _l )
#else
GlobalSet new_GlobalSet( origin p_org, tmstring p_line )
#endif
{
    GlobalSet nw;

    nw = TM_MALLOC( GlobalSet, sizeof(*nw) );
    nw->tag = TAGGlobalSet;
    nw->org = p_org;
    nw->line = p_line;
    newcnt_GlobalSet++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'GlobalSplit'. */
#ifdef LOGNEW
GlobalSplit real_new_GlobalSplit( origin p_org, tmstring p_line, const char *_f, const int _l )
#else
GlobalSplit new_GlobalSplit( origin p_org, tmstring p_line )
#endif
{
    GlobalSplit nw;

    nw = TM_MALLOC( GlobalSplit, sizeof(*nw) );
    nw->tag = TAGGlobalSplit;
    nw->org = p_org;
    nw->line = p_line;
    newcnt_GlobalSplit++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'If'. */
#ifdef LOGNEW
If real_new_If( origin p_org, tmstring p_cond, tplelm_list p_ifthen, tplelm_list p_ifelse, const char *_f, const int _l )
#else
If new_If( origin p_org, tmstring p_cond, tplelm_list p_ifthen, tplelm_list p_ifelse )
#endif
{
    If nw;

    nw = TM_MALLOC( If, sizeof(*nw) );
    nw->tag = TAGIf;
    nw->org = p_org;
    nw->cond = p_cond;
    nw->ifthen = p_ifthen;
    nw->ifelse = p_ifelse;
    newcnt_If++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Include'. */
#ifdef LOGNEW
Include real_new_Include( origin p_org, tmstring p_fname, const char *_f, const int _l )
#else
Include new_Include( origin p_org, tmstring p_fname )
#endif
{
    Include nw;

    nw = TM_MALLOC( Include, sizeof(*nw) );
    nw->tag = TAGInclude;
    nw->org = p_org;
    nw->fname = p_fname;
    newcnt_Include++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Insert'. */
#ifdef LOGNEW
Insert real_new_Insert( origin p_org, tmstring p_fname, const char *_f, const int _l )
#else
Insert new_Insert( origin p_org, tmstring p_fname )
#endif
{
    Insert nw;

    nw = TM_MALLOC( Insert, sizeof(*nw) );
    nw->tag = TAGInsert;
    nw->org = p_org;
    nw->fname = p_fname;
    newcnt_Insert++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Macro'. */
#ifdef LOGNEW
Macro real_new_Macro( origin p_org, tmstring p_formals, tplelm_list p_body, const char *_f, const int _l )
#else
Macro new_Macro( origin p_org, tmstring p_formals, tplelm_list p_body )
#endif
{
    Macro nw;

    nw = TM_MALLOC( Macro, sizeof(*nw) );
    nw->tag = TAGMacro;
    nw->org = p_org;
    nw->formals = p_formals;
    nw->body = p_body;
    newcnt_Macro++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Plain'. */
#ifdef LOGNEW
Plain real_new_Plain( origin p_org, tmstring p_line, const char *_f, const int _l )
#else
Plain new_Plain( origin p_org, tmstring p_line )
#endif
{
    Plain nw;

    nw = TM_MALLOC( Plain, sizeof(*nw) );
    nw->tag = TAGPlain;
    nw->org = p_org;
    nw->line = p_line;
    newcnt_Plain++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Redirect'. */
#ifdef LOGNEW
Redirect real_new_Redirect( origin p_org, tmstring p_fname, tplelm_list p_body, const char *_f, const int _l )
#else
Redirect new_Redirect( origin p_org, tmstring p_fname, tplelm_list p_body )
#endif
{
    Redirect nw;

    nw = TM_MALLOC( Redirect, sizeof(*nw) );
    nw->tag = TAGRedirect;
    nw->org = p_org;
    nw->fname = p_fname;
    nw->body = p_body;
    newcnt_Redirect++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Rename'. */
#ifdef LOGNEW
Rename real_new_Rename( origin p_org, tmstring p_line, const char *_f, const int _l )
#else
Rename new_Rename( origin p_org, tmstring p_line )
#endif
{
    Rename nw;

    nw = TM_MALLOC( Rename, sizeof(*nw) );
    nw->tag = TAGRename;
    nw->org = p_org;
    nw->line = p_line;
    newcnt_Rename++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Return'. */
#ifdef LOGNEW
Return real_new_Return( origin p_org, tmstring p_retval, const char *_f, const int _l )
#else
Return new_Return( origin p_org, tmstring p_retval )
#endif
{
    Return nw;

    nw = TM_MALLOC( Return, sizeof(*nw) );
    nw->tag = TAGReturn;
    nw->org = p_org;
    nw->retval = p_retval;
    newcnt_Return++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Set'. */
#ifdef LOGNEW
Set real_new_Set( origin p_org, tmstring p_line, const char *_f, const int _l )
#else
Set new_Set( origin p_org, tmstring p_line )
#endif
{
    Set nw;

    nw = TM_MALLOC( Set, sizeof(*nw) );
    nw->tag = TAGSet;
    nw->org = p_org;
    nw->line = p_line;
    newcnt_Set++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Split'. */
#ifdef LOGNEW
Split real_new_Split( origin p_org, tmstring p_line, const char *_f, const int _l )
#else
Split new_Split( origin p_org, tmstring p_line )
#endif
{
    Split nw;

    nw = TM_MALLOC( Split, sizeof(*nw) );
    nw->tag = TAGSplit;
    nw->org = p_org;
    nw->line = p_line;
    newcnt_Split++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Switch'. */
#ifdef LOGNEW
Switch real_new_Switch( origin p_org, tmstring p_val, Switchcase_list p_cases, tplelm_list p_deflt, const char *_f, const int _l )
#else
Switch new_Switch( origin p_org, tmstring p_val, Switchcase_list p_cases, tplelm_list p_deflt )
#endif
{
    Switch nw;

    nw = TM_MALLOC( Switch, sizeof(*nw) );
    nw->tag = TAGSwitch;
    nw->org = p_org;
    nw->val = p_val;
    nw->cases = p_cases;
    nw->deflt = p_deflt;
    newcnt_Switch++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of tuple 'Switchcase'. */
#ifdef LOGNEW
Switchcase real_new_Switchcase( tmstring p_cases, tplelm_list p_action, const char *_f, const int _l )
#else
Switchcase new_Switchcase( tmstring p_cases, tplelm_list p_action )
#endif
{
    Switchcase nw;

    nw = TM_MALLOC( Switchcase, sizeof(*nw) );
    nw->cases = p_cases;
    nw->action = p_action;
    newcnt_Switchcase++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of tuple 'Type'. */
#ifdef LOGNEW
Type real_new_Type( tmuint p_level, tmsymbol p_basetype, const char *_f, const int _l )
#else
Type new_Type( tmuint p_level, tmsymbol p_basetype )
#endif
{
    Type nw;

    nw = TM_MALLOC( Type, sizeof(*nw) );
    nw->level = p_level;
    nw->basetype = p_basetype;
    newcnt_Type++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'While'. */
#ifdef LOGNEW
While real_new_While( origin p_org, tmstring p_cond, tplelm_list p_body, const char *_f, const int _l )
#else
While new_While( origin p_org, tmstring p_cond, tplelm_list p_body )
#endif
{
    While nw;

    nw = TM_MALLOC( While, sizeof(*nw) );
    nw->tag = TAGWhile;
    nw->org = p_org;
    nw->cond = p_cond;
    nw->body = p_body;
    newcnt_While++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of tuple 'alternative'. */
#ifdef LOGNEW
alternative real_new_alternative( tmsymbol p_label, classComponent p_component, const char *_f, const int _l )
#else
alternative new_alternative( tmsymbol p_label, classComponent p_component )
#endif
{
    alternative nw;

    nw = TM_MALLOC( alternative, sizeof(*nw) );
    nw->label = p_label;
    nw->component = p_component;
    newcnt_alternative++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of tuple 'macro'. */
#ifdef LOGNEW
macro real_new_macro( origin p_org, tmuint p_lvl, tmstring p_name, tmstring_list p_fpl, tplelm_list p_body, const char *_f, const int _l )
#else
macro new_macro( origin p_org, tmuint p_lvl, tmstring p_name, tmstring_list p_fpl, tplelm_list p_body )
#endif
{
    macro nw;

    nw = TM_MALLOC( macro, sizeof(*nw) );
    nw->org = p_org;
    nw->lvl = p_lvl;
    nw->name = p_name;
    nw->fpl = p_fpl;
    nw->body = p_body;
    newcnt_macro++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of tuple 'origin'. */
#ifdef LOGNEW
origin real_new_origin( tmsymbol p_file, tmuint p_line, const char *_f, const int _l )
#else
origin new_origin( tmsymbol p_file, tmuint p_line )
#endif
{
    origin nw;

    nw = TM_MALLOC( origin, sizeof(*nw) );
    nw->file = p_file;
    nw->line = p_line;
    newcnt_origin++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of tuple 'origsymbol'. */
#ifdef LOGNEW
origsymbol real_new_origsymbol( tmsymbol p_sym, origin p_org, const char *_f, const int _l )
#else
origsymbol new_origsymbol( tmsymbol p_sym, origin p_org )
#endif
{
    origsymbol nw;

    nw = TM_MALLOC( origsymbol, sizeof(*nw) );
    nw->sym = p_sym;
    nw->org = p_org;
    newcnt_origsymbol++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of tuple 'variable'. */
#ifdef LOGNEW
variable real_new_variable( tmuint p_lvl, tmstring p_name, tmstring p_val, const char *_f, const int _l )
#else
variable new_variable( tmuint p_lvl, tmstring p_name, tmstring p_val )
#endif
{
    variable nw;

    nw = TM_MALLOC( variable, sizeof(*nw) );
    nw->lvl = p_lvl;
    nw->name = p_name;
    nw->val = p_val;
    newcnt_variable++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/**************************************************
 *    Freeing routines                            *
 **************************************************/

static void fre_Type_list( Type_list );
static void fre_alternative_list( alternative_list );
static void fre_classComponent_list( classComponent_list );
static void fre_ds_list( ds_list );
static void fre_macro_list( macro_list );
static void fre_tmstring_list( tmstring_list );
static void fre_tmsymbol_list( tmsymbol_list );
static void fre_tplelm_list( tplelm_list );
static void fre_variable_list( variable_list );
static void fre_Switchcase_list( Switchcase_list );
static void fre_Field_list( Field_list );
static void fre_Type( Type );
static void fre_origin( origin );
static void fre_alternative( alternative );
static void fre_macro( macro );
static void fre_variable( variable );
static void fre_Append( Append );
static void fre_Appendfile( Appendfile );
static void fre_Call( Call );
static void fre_Case( Case );
static void fre_Default( Default );
static void fre_DeleteType( DeleteType );
static void fre_Error( Error );
static void fre_Exit( Exit );
static void fre_For( For );
static void fre_Foreach( Foreach );
static void fre_GlobalAppend( GlobalAppend );
static void fre_GlobalSet( GlobalSet );
static void fre_GlobalSplit( GlobalSplit );
static void fre_If( If );
static void fre_Include( Include );
static void fre_Insert( Insert );
static void fre_Macro( Macro );
static void fre_Plain( Plain );
static void fre_Redirect( Redirect );
static void fre_Rename( Rename );
static void fre_Return( Return );
static void fre_Set( Set );
static void fre_Split( Split );
static void fre_Switch( Switch );
static void fre_While( While );
static void fre_Switchcase( Switchcase );
static void fre_origsymbol( origsymbol );
static void fre_CCAlternatives( CCAlternatives );
static void fre_CCFields( CCFields );
static void fre_CCSublist( CCSublist );
static void fre_CCSuper( CCSuper );
static void fre_DsAlias( DsAlias );
static void fre_DsClass( DsClass );
static void fre_DsConstructor( DsConstructor );
static void fre_DsConstructorBase( DsConstructorBase );
static void fre_DsInclude( DsInclude );
static void fre_DsTuple( DsTuple );
static void fre_Field( Field );
/* Free an element 'e' of tuple type 'Field'. */
static void fre_Field( Field e )
{
    if( e == FieldNIL ){
	return;
    }
    frecnt_Field++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of class type 'DsTuple'. */
static void fre_DsTuple( DsTuple e )
{
    if( e == DsTupleNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsTuple:
	    frecnt_DsTuple++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'DsInclude'. */
static void fre_DsInclude( DsInclude e )
{
    if( e == DsIncludeNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsInclude:
	    frecnt_DsInclude++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'DsConstructorBase'. */
static void fre_DsConstructorBase( DsConstructorBase e )
{
    if( e == DsConstructorBaseNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsConstructorBase:
	    frecnt_DsConstructorBase++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'DsConstructor'. */
static void fre_DsConstructor( DsConstructor e )
{
    if( e == DsConstructorNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsConstructor:
	    frecnt_DsConstructor++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'DsClass'. */
static void fre_DsClass( DsClass e )
{
    if( e == DsClassNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsClass:
	    frecnt_DsClass++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'DsAlias'. */
static void fre_DsAlias( DsAlias e )
{
    if( e == DsAliasNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsAlias:
	    frecnt_DsAlias++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'CCSuper'. */
static void fre_CCSuper( CCSuper e )
{
    if( e == CCSuperNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCCSuper:
	    frecnt_CCSuper++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'CCSublist'. */
static void fre_CCSublist( CCSublist e )
{
    if( e == CCSublistNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCCSublist:
	    frecnt_CCSublist++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'CCFields'. */
static void fre_CCFields( CCFields e )
{
    if( e == CCFieldsNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCCFields:
	    frecnt_CCFields++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'CCAlternatives'. */
static void fre_CCAlternatives( CCAlternatives e )
{
    if( e == CCAlternativesNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCCAlternatives:
	    frecnt_CCAlternatives++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of tuple type 'origsymbol'. */
static void fre_origsymbol( origsymbol e )
{
    if( e == origsymbolNIL ){
	return;
    }
    frecnt_origsymbol++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of tuple type 'Switchcase'. */
static void fre_Switchcase( Switchcase e )
{
    if( e == SwitchcaseNIL ){
	return;
    }
    frecnt_Switchcase++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of class type 'While'. */
static void fre_While( While e )
{
    if( e == WhileNIL ){
	return;
    }
    switch( e->tag ){
	case TAGWhile:
	    frecnt_While++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Switch'. */
static void fre_Switch( Switch e )
{
    if( e == SwitchNIL ){
	return;
    }
    switch( e->tag ){
	case TAGSwitch:
	    frecnt_Switch++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Split'. */
static void fre_Split( Split e )
{
    if( e == SplitNIL ){
	return;
    }
    switch( e->tag ){
	case TAGSplit:
	    frecnt_Split++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Set'. */
static void fre_Set( Set e )
{
    if( e == SetNIL ){
	return;
    }
    switch( e->tag ){
	case TAGSet:
	    frecnt_Set++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Return'. */
static void fre_Return( Return e )
{
    if( e == ReturnNIL ){
	return;
    }
    switch( e->tag ){
	case TAGReturn:
	    frecnt_Return++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Rename'. */
static void fre_Rename( Rename e )
{
    if( e == RenameNIL ){
	return;
    }
    switch( e->tag ){
	case TAGRename:
	    frecnt_Rename++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Redirect'. */
static void fre_Redirect( Redirect e )
{
    if( e == RedirectNIL ){
	return;
    }
    switch( e->tag ){
	case TAGRedirect:
	    frecnt_Redirect++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Plain'. */
static void fre_Plain( Plain e )
{
    if( e == PlainNIL ){
	return;
    }
    switch( e->tag ){
	case TAGPlain:
	    frecnt_Plain++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Macro'. */
static void fre_Macro( Macro e )
{
    if( e == MacroNIL ){
	return;
    }
    switch( e->tag ){
	case TAGMacro:
	    frecnt_Macro++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Insert'. */
static void fre_Insert( Insert e )
{
    if( e == InsertNIL ){
	return;
    }
    switch( e->tag ){
	case TAGInsert:
	    frecnt_Insert++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Include'. */
static void fre_Include( Include e )
{
    if( e == IncludeNIL ){
	return;
    }
    switch( e->tag ){
	case TAGInclude:
	    frecnt_Include++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'If'. */
static void fre_If( If e )
{
    if( e == IfNIL ){
	return;
    }
    switch( e->tag ){
	case TAGIf:
	    frecnt_If++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'GlobalSplit'. */
static void fre_GlobalSplit( GlobalSplit e )
{
    if( e == GlobalSplitNIL ){
	return;
    }
    switch( e->tag ){
	case TAGGlobalSplit:
	    frecnt_GlobalSplit++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'GlobalSet'. */
static void fre_GlobalSet( GlobalSet e )
{
    if( e == GlobalSetNIL ){
	return;
    }
    switch( e->tag ){
	case TAGGlobalSet:
	    frecnt_GlobalSet++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'GlobalAppend'. */
static void fre_GlobalAppend( GlobalAppend e )
{
    if( e == GlobalAppendNIL ){
	return;
    }
    switch( e->tag ){
	case TAGGlobalAppend:
	    frecnt_GlobalAppend++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Foreach'. */
static void fre_Foreach( Foreach e )
{
    if( e == ForeachNIL ){
	return;
    }
    switch( e->tag ){
	case TAGForeach:
	    frecnt_Foreach++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'For'. */
static void fre_For( For e )
{
    if( e == ForNIL ){
	return;
    }
    switch( e->tag ){
	case TAGFor:
	    frecnt_For++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Exit'. */
static void fre_Exit( Exit e )
{
    if( e == ExitNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExit:
	    frecnt_Exit++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Error'. */
static void fre_Error( Error e )
{
    if( e == ErrorNIL ){
	return;
    }
    switch( e->tag ){
	case TAGError:
	    frecnt_Error++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'DeleteType'. */
static void fre_DeleteType( DeleteType e )
{
    if( e == DeleteTypeNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDeleteType:
	    frecnt_DeleteType++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Default'. */
static void fre_Default( Default e )
{
    if( e == DefaultNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDefault:
	    frecnt_Default++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Case'. */
static void fre_Case( Case e )
{
    if( e == CaseNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCase:
	    frecnt_Case++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Call'. */
static void fre_Call( Call e )
{
    if( e == CallNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCall:
	    frecnt_Call++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Appendfile'. */
static void fre_Appendfile( Appendfile e )
{
    if( e == AppendfileNIL ){
	return;
    }
    switch( e->tag ){
	case TAGAppendfile:
	    frecnt_Appendfile++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of class type 'Append'. */
static void fre_Append( Append e )
{
    if( e == AppendNIL ){
	return;
    }
    switch( e->tag ){
	case TAGAppend:
	    frecnt_Append++;
#ifdef LOGNEW
	    tm_fre_logid( e->lognew_id );
#endif
	    TM_FREE( e );
	    break;

	default:
	    FATALTAG( e->tag );
    }
}

/* Free an element 'e' of tuple type 'variable'. */
static void fre_variable( variable e )
{
    if( e == variableNIL ){
	return;
    }
    frecnt_variable++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of tuple type 'macro'. */
static void fre_macro( macro e )
{
    if( e == macroNIL ){
	return;
    }
    frecnt_macro++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of tuple type 'alternative'. */
static void fre_alternative( alternative e )
{
    if( e == alternativeNIL ){
	return;
    }
    frecnt_alternative++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of tuple type 'origin'. */
static void fre_origin( origin e )
{
    if( e == originNIL ){
	return;
    }
    frecnt_origin++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of tuple type 'Type'. */
static void fre_Type( Type e )
{
    if( e == TypeNIL ){
	return;
    }
    frecnt_Type++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free a list of Type elements 'l'. */
static void fre_Type_list( Type_list l )
{
    if( l == Type_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
    frecnt_Type_list++;
    if( l->arr != NULL ){
	TM_FREE( l->arr );
    }
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
    frecnt_alternative_list++;
    if( l->arr != NULL ){
	TM_FREE( l->arr );
    }
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
    frecnt_classComponent_list++;
    if( l->arr != NULL ){
	TM_FREE( l->arr );
    }
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
    frecnt_ds_list++;
    if( l->arr != NULL ){
	TM_FREE( l->arr );
    }
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
    frecnt_macro_list++;
    if( l->arr != NULL ){
	TM_FREE( l->arr );
    }
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
    frecnt_tmstring_list++;
    if( l->arr != NULL ){
	TM_FREE( l->arr );
    }
    TM_FREE( l );
}

/* Free a list of tmsymbol elements 'l'. */
static void fre_tmsymbol_list( tmsymbol_list l )
{
    if( l == tmsymbol_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
    frecnt_tmsymbol_list++;
    if( l->arr != NULL ){
	TM_FREE( l->arr );
    }
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
    frecnt_tplelm_list++;
    if( l->arr != NULL ){
	TM_FREE( l->arr );
    }
    TM_FREE( l );
}

/* Free a list of variable elements 'l'. */
static void fre_variable_list( variable_list l )
{
    if( l == variable_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
    frecnt_variable_list++;
    if( l->arr != NULL ){
	TM_FREE( l->arr );
    }
    TM_FREE( l );
}

/* Free a list of Switchcase elements 'l'. */
static void fre_Switchcase_list( Switchcase_list l )
{
    if( l == Switchcase_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
    frecnt_Switchcase_list++;
    if( l->arr != NULL ){
	TM_FREE( l->arr );
    }
    TM_FREE( l );
}

/* Free a list of Field elements 'l'. */
static void fre_Field_list( Field_list l )
{
    if( l == Field_listNIL ){
	return;
    }
#ifdef LOGNEW
    tm_fre_logid( l->lognew_id );
#endif
    frecnt_Field_list++;
    if( l->arr != NULL ){
	TM_FREE( l->arr );
    }
    TM_FREE( l );
}

/**************************************************
 *    Append routines                             *
 **************************************************/

/* Append a Field element 'e' to list 'l', and return the new list. */
Field_list append_Field_list( Field_list l, Field e )
{
    if( l->sz >= l->room ){
	l = setroom_Field_list( l, 1U+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a Switchcase element 'e' to list 'l', and return the new list. */
Switchcase_list append_Switchcase_list( Switchcase_list l, Switchcase e )
{
    if( l->sz >= l->room ){
	l = setroom_Switchcase_list( l, 1U+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a Type element 'e' to list 'l', and return the new list. */
Type_list append_Type_list( Type_list l, Type e )
{
    if( l->sz >= l->room ){
	l = setroom_Type_list( l, 1U+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a alternative element 'e' to list 'l', and return the new list. */
alternative_list append_alternative_list( alternative_list l, alternative e )
{
    if( l->sz >= l->room ){
	l = setroom_alternative_list( l, 1U+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a classComponent element 'e' to list 'l', and return the new list. */
classComponent_list append_classComponent_list( classComponent_list l, classComponent e )
{
    if( l->sz >= l->room ){
	l = setroom_classComponent_list( l, 1U+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a ds element 'e' to list 'l', and return the new list. */
ds_list append_ds_list( ds_list l, ds e )
{
    if( l->sz >= l->room ){
	l = setroom_ds_list( l, 1U+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a tmstring element 'e' to list 'l', and return the new list. */
tmstring_list append_tmstring_list( tmstring_list l, tmstring e )
{
    if( l->sz >= l->room ){
	l = setroom_tmstring_list( l, 1U+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a tmsymbol element 'e' to list 'l', and return the new list. */
tmsymbol_list append_tmsymbol_list( tmsymbol_list l, tmsymbol e )
{
    if( l->sz >= l->room ){
	l = setroom_tmsymbol_list( l, 1U+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a tplelm element 'e' to list 'l', and return the new list. */
tplelm_list append_tplelm_list( tplelm_list l, tplelm e )
{
    if( l->sz >= l->room ){
	l = setroom_tplelm_list( l, 1U+(l->sz)+(l->sz) );
    }
    l->arr[l->sz] = e;
    l->sz++;
    return l;
}

/* Append a variable element 'e' to list 'l', and return the new list. */
variable_list append_variable_list( variable_list l, variable e )
{
    if( l->sz >= l->room ){
	l = setroom_variable_list( l, 1U+(l->sz)+(l->sz) );
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
        /*@notreached@*/
	return l;
    }
    if( l->sz >= l->room ){
	l = setroom_macro_list( l, 1U+(l->sz)+(l->sz) );
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
        /*@notreached@*/
	return l;
    }
    if( l->sz >= l->room ){
	l = setroom_tmstring_list( l, 1U+(l->sz)+(l->sz) );
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

/* Insert a variable element 'e' to into list 'l' at position 'pos'. */
variable_list insert_variable_list( variable_list l, const unsigned int pos, variable e )
{
    unsigned int ix;
    variable *arr;
    unsigned int the_pos = pos;

    if( l == variable_listNIL ){
	FATAL( tm_nilptr );
        /*@notreached@*/
	return l;
    }
    if( l->sz >= l->room ){
	l = setroom_variable_list( l, 1U+(l->sz)+(l->sz) );
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

/**************************************************
 *    insertlist_<type>_list routines                 *
 **************************************************/

/* Insert a ds list 'lb' to into list 'la' at position 'pos'.
 * The elements of 'lb' are copied into 'la', and the container is destroyed.
 */
ds_list insertlist_ds_list( ds_list la, unsigned int pos, ds_list lb )
{

    if( la == ds_listNIL ){
	FATAL( tm_nilptr );
        /*@notreached@*/
	return la;
    }
    if( lb != ds_listNIL && lb->sz != 0 ){
	const unsigned int szb = lb->sz;
	unsigned int ix;
	ds *arr;

	la = setroom_ds_list( la, la->sz+szb );
	if( pos>la->sz ){
	    pos = la->sz;
	}

	/* Move up elements */
	arr = la->arr;
	for( ix=la->sz+szb-1; ix>=(pos+szb); ix-- ){
	    arr[ix] = arr[ix-szb];
	}
	la->sz += szb;
	/* Copy in elements from 'lb' */
	{
	    unsigned int cnt = szb;
	    ds *sp = lb->arr;
	    ds *dp = &la->arr[pos];

	    while( cnt!=0 ){
		*dp++ = *sp++;
		cnt--;
	    }
	}
    }
    fre_ds_list( lb );
    return la;
}

/**************************************************
 *    Concatenate routines                        *
 **************************************************/

/* Concatenate Field list 'lb' after Field list 'la'.
 * The elements of 'lb' are copied into 'la', and the container is destroyed.
 */
Field_list concat_Field_list( Field_list la, Field_list lb )
{
    unsigned int cnt;
    Field *sp;
    Field *dp;

    if( la == Field_listNIL ){
	FATAL( tm_nilptr );
        /*@notreached@*/
	return la;
    }
    la = setroom_Field_list( la, la->sz+lb->sz );
    cnt = lb->sz;
    sp = lb->arr;
    dp = &la->arr[la->sz];
    while( cnt!=0 ){
	*dp++ = *sp++;
	cnt--;
    }
    la->sz += lb->sz;
    fre_Field_list( lb );
    return la;
}

/* Concatenate ds list 'lb' after ds list 'la'.
 * The elements of 'lb' are copied into 'la', and the container is destroyed.
 */
ds_list concat_ds_list( ds_list la, ds_list lb )
{
    unsigned int cnt;
    ds *sp;
    ds *dp;

    if( la == ds_listNIL ){
	FATAL( tm_nilptr );
        /*@notreached@*/
	return la;
    }
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

/* Concatenate tmsymbol list 'lb' after tmsymbol list 'la'.
 * The elements of 'lb' are copied into 'la', and the container is destroyed.
 */
tmsymbol_list concat_tmsymbol_list( tmsymbol_list la, tmsymbol_list lb )
{
    unsigned int cnt;
    tmsymbol *sp;
    tmsymbol *dp;

    if( la == tmsymbol_listNIL ){
	FATAL( tm_nilptr );
        /*@notreached@*/
	return la;
    }
    la = setroom_tmsymbol_list( la, la->sz+lb->sz );
    cnt = lb->sz;
    sp = lb->arr;
    dp = &la->arr[la->sz];
    while( cnt!=0 ){
	*dp++ = *sp++;
	cnt--;
    }
    la->sz += lb->sz;
    fre_tmsymbol_list( lb );
    return la;
}

/**************************************************
 *    Recursive freeing routines                  *
 **************************************************/

static void rfre_Switchcase_list( Switchcase_list );
static void rfre_Field_list( Field_list );
static void rfre_alternative( alternative );
static void rfre_macro( macro );
static void rfre_tplelm( tplelm );
static void rfre_variable( variable );
static void rfre_Append( Append );
static void rfre_Appendfile( Appendfile );
static void rfre_Call( Call );
static void rfre_Case( Case );
static void rfre_Default( Default );
static void rfre_DeleteType( DeleteType );
static void rfre_Error( Error );
static void rfre_Exit( Exit );
static void rfre_For( For );
static void rfre_Foreach( Foreach );
static void rfre_GlobalAppend( GlobalAppend );
static void rfre_GlobalSet( GlobalSet );
static void rfre_GlobalSplit( GlobalSplit );
static void rfre_If( If );
static void rfre_Include( Include );
static void rfre_Insert( Insert );
static void rfre_Macro( Macro );
static void rfre_Plain( Plain );
static void rfre_Redirect( Redirect );
static void rfre_Rename( Rename );
static void rfre_Return( Return );
static void rfre_Set( Set );
static void rfre_Split( Split );
static void rfre_Switch( Switch );
static void rfre_While( While );
static void rfre_Switchcase( Switchcase );
static void rfre_origsymbol( origsymbol );
static void rfre_CCAlternatives( CCAlternatives );
static void rfre_CCFields( CCFields );
static void rfre_CCSublist( CCSublist );
static void rfre_CCSuper( CCSuper );
static void rfre_DsAlias( DsAlias );
static void rfre_DsClass( DsClass );
static void rfre_DsConstructor( DsConstructor );
static void rfre_DsConstructorBase( DsConstructorBase );
static void rfre_DsInclude( DsInclude );
static void rfre_DsTuple( DsTuple );
static void rfre_Field( Field );
/* Recursively free an element 'e' of tuple type 'Type'
 * and all elements in it.
 */
void rfre_Type( Type e )
{
    if( e == TypeNIL ){
	return;
    }
    rfre_tmuint( e->level );
    rfre_tmsymbol( e->basetype );
    fre_Type( e );
}

/* Recursively free an element 'e' of class type 'classComponent'
 * and all elements in it.
 */
void rfre_classComponent( classComponent e )
{
    if( e == classComponentNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCCSuper:
	    rfre_CCSuper( (CCSuper) e );
	    break;

	case TAGCCFields:
	    rfre_CCFields( (CCFields) e );
	    break;

	case TAGCCAlternatives:
	    rfre_CCAlternatives( (CCAlternatives) e );
	    break;

	case TAGCCSublist:
	    rfre_CCSublist( (CCSublist) e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of tuple type 'origin'
 * and all elements in it.
 */
void rfre_origin( origin e )
{
    if( e == originNIL ){
	return;
    }
    rfre_tmsymbol( e->file );
    rfre_tmuint( e->line );
    fre_origin( e );
}

/* Recursively free an element 'e' of tuple type 'alternative'
 * and all elements in it.
 */
static void rfre_alternative( alternative e )
{
    if( e == alternativeNIL ){
	return;
    }
    rfre_tmsymbol( e->label );
    rfre_classComponent( e->component );
    fre_alternative( e );
}

/* Recursively free an element 'e' of tuple type 'macro'
 * and all elements in it.
 */
static void rfre_macro( macro e )
{
    if( e == macroNIL ){
	return;
    }
    rfre_origin( e->org );
    rfre_tmuint( e->lvl );
    rfre_tmstring( e->name );
    rfre_tmstring_list( e->fpl );
    rfre_tplelm_list( e->body );
    fre_macro( e );
}

/* Recursively free an element 'e' of class type 'tplelm'
 * and all elements in it.
 */
static void rfre_tplelm( tplelm e )
{
    if( e == tplelmNIL ){
	return;
    }
    switch( e->tag ){
	case TAGPlain:
	    rfre_Plain( (Plain) e );
	    break;

	case TAGFor:
	    rfre_For( (For) e );
	    break;

	case TAGForeach:
	    rfre_Foreach( (Foreach) e );
	    break;

	case TAGWhile:
	    rfre_While( (While) e );
	    break;

	case TAGIf:
	    rfre_If( (If) e );
	    break;

	case TAGSwitch:
	    rfre_Switch( (Switch) e );
	    break;

	case TAGSet:
	    rfre_Set( (Set) e );
	    break;

	case TAGSplit:
	    rfre_Split( (Split) e );
	    break;

	case TAGRename:
	    rfre_Rename( (Rename) e );
	    break;

	case TAGGlobalSet:
	    rfre_GlobalSet( (GlobalSet) e );
	    break;

	case TAGGlobalSplit:
	    rfre_GlobalSplit( (GlobalSplit) e );
	    break;

	case TAGAppend:
	    rfre_Append( (Append) e );
	    break;

	case TAGGlobalAppend:
	    rfre_GlobalAppend( (GlobalAppend) e );
	    break;

	case TAGDeleteType:
	    rfre_DeleteType( (DeleteType) e );
	    break;

	case TAGError:
	    rfre_Error( (Error) e );
	    break;

	case TAGExit:
	    rfre_Exit( (Exit) e );
	    break;

	case TAGRedirect:
	    rfre_Redirect( (Redirect) e );
	    break;

	case TAGAppendfile:
	    rfre_Appendfile( (Appendfile) e );
	    break;

	case TAGMacro:
	    rfre_Macro( (Macro) e );
	    break;

	case TAGCall:
	    rfre_Call( (Call) e );
	    break;

	case TAGReturn:
	    rfre_Return( (Return) e );
	    break;

	case TAGInclude:
	    rfre_Include( (Include) e );
	    break;

	case TAGInsert:
	    rfre_Insert( (Insert) e );
	    break;

	case TAGCase:
	    rfre_Case( (Case) e );
	    break;

	case TAGDefault:
	    rfre_Default( (Default) e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of tuple type 'variable'
 * and all elements in it.
 */
static void rfre_variable( variable e )
{
    if( e == variableNIL ){
	return;
    }
    rfre_tmuint( e->lvl );
    rfre_tmstring( e->name );
    rfre_tmstring( e->val );
    fre_variable( e );
}

/* Recursively free an element 'e' of class type 'Append'
 * and all elements in it.
 */
static void rfre_Append( Append e )
{
    if( e == AppendNIL ){
	return;
    }
    switch( e->tag ){
	case TAGAppend:
	    rfre_origin( e->org );
	    rfre_tmstring( e->line );
	    fre_Append( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Appendfile'
 * and all elements in it.
 */
static void rfre_Appendfile( Appendfile e )
{
    if( e == AppendfileNIL ){
	return;
    }
    switch( e->tag ){
	case TAGAppendfile:
	    rfre_origin( e->org );
	    rfre_tmstring( e->fname );
	    rfre_tplelm_list( e->body );
	    fre_Appendfile( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Call'
 * and all elements in it.
 */
static void rfre_Call( Call e )
{
    if( e == CallNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCall:
	    rfre_origin( e->org );
	    rfre_tmstring( e->line );
	    fre_Call( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Case'
 * and all elements in it.
 */
static void rfre_Case( Case e )
{
    if( e == CaseNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCase:
	    rfre_origin( e->org );
	    rfre_tmstring( e->val );
	    fre_Case( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Default'
 * and all elements in it.
 */
static void rfre_Default( Default e )
{
    if( e == DefaultNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDefault:
	    rfre_origin( e->org );
	    fre_Default( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'DeleteType'
 * and all elements in it.
 */
static void rfre_DeleteType( DeleteType e )
{
    if( e == DeleteTypeNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDeleteType:
	    rfre_origin( e->org );
	    rfre_tmstring( e->line );
	    fre_DeleteType( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Error'
 * and all elements in it.
 */
static void rfre_Error( Error e )
{
    if( e == ErrorNIL ){
	return;
    }
    switch( e->tag ){
	case TAGError:
	    rfre_origin( e->org );
	    rfre_tmstring( e->str );
	    fre_Error( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Exit'
 * and all elements in it.
 */
static void rfre_Exit( Exit e )
{
    if( e == ExitNIL ){
	return;
    }
    switch( e->tag ){
	case TAGExit:
	    rfre_origin( e->org );
	    rfre_tmstring( e->str );
	    fre_Exit( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'For'
 * and all elements in it.
 */
static void rfre_For( For e )
{
    if( e == ForNIL ){
	return;
    }
    switch( e->tag ){
	case TAGFor:
	    rfre_origin( e->org );
	    rfre_tmstring( e->parms );
	    rfre_tplelm_list( e->body );
	    fre_For( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Foreach'
 * and all elements in it.
 */
static void rfre_Foreach( Foreach e )
{
    if( e == ForeachNIL ){
	return;
    }
    switch( e->tag ){
	case TAGForeach:
	    rfre_origin( e->org );
	    rfre_tmstring( e->felist );
	    rfre_tplelm_list( e->body );
	    fre_Foreach( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'GlobalAppend'
 * and all elements in it.
 */
static void rfre_GlobalAppend( GlobalAppend e )
{
    if( e == GlobalAppendNIL ){
	return;
    }
    switch( e->tag ){
	case TAGGlobalAppend:
	    rfre_origin( e->org );
	    rfre_tmstring( e->line );
	    fre_GlobalAppend( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'GlobalSet'
 * and all elements in it.
 */
static void rfre_GlobalSet( GlobalSet e )
{
    if( e == GlobalSetNIL ){
	return;
    }
    switch( e->tag ){
	case TAGGlobalSet:
	    rfre_origin( e->org );
	    rfre_tmstring( e->line );
	    fre_GlobalSet( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'GlobalSplit'
 * and all elements in it.
 */
static void rfre_GlobalSplit( GlobalSplit e )
{
    if( e == GlobalSplitNIL ){
	return;
    }
    switch( e->tag ){
	case TAGGlobalSplit:
	    rfre_origin( e->org );
	    rfre_tmstring( e->line );
	    fre_GlobalSplit( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'If'
 * and all elements in it.
 */
static void rfre_If( If e )
{
    if( e == IfNIL ){
	return;
    }
    switch( e->tag ){
	case TAGIf:
	    rfre_origin( e->org );
	    rfre_tmstring( e->cond );
	    rfre_tplelm_list( e->ifthen );
	    rfre_tplelm_list( e->ifelse );
	    fre_If( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Include'
 * and all elements in it.
 */
static void rfre_Include( Include e )
{
    if( e == IncludeNIL ){
	return;
    }
    switch( e->tag ){
	case TAGInclude:
	    rfre_origin( e->org );
	    rfre_tmstring( e->fname );
	    fre_Include( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Insert'
 * and all elements in it.
 */
static void rfre_Insert( Insert e )
{
    if( e == InsertNIL ){
	return;
    }
    switch( e->tag ){
	case TAGInsert:
	    rfre_origin( e->org );
	    rfre_tmstring( e->fname );
	    fre_Insert( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Macro'
 * and all elements in it.
 */
static void rfre_Macro( Macro e )
{
    if( e == MacroNIL ){
	return;
    }
    switch( e->tag ){
	case TAGMacro:
	    rfre_origin( e->org );
	    rfre_tmstring( e->formals );
	    rfre_tplelm_list( e->body );
	    fre_Macro( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Plain'
 * and all elements in it.
 */
static void rfre_Plain( Plain e )
{
    if( e == PlainNIL ){
	return;
    }
    switch( e->tag ){
	case TAGPlain:
	    rfre_origin( e->org );
	    rfre_tmstring( e->line );
	    fre_Plain( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Redirect'
 * and all elements in it.
 */
static void rfre_Redirect( Redirect e )
{
    if( e == RedirectNIL ){
	return;
    }
    switch( e->tag ){
	case TAGRedirect:
	    rfre_origin( e->org );
	    rfre_tmstring( e->fname );
	    rfre_tplelm_list( e->body );
	    fre_Redirect( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Rename'
 * and all elements in it.
 */
static void rfre_Rename( Rename e )
{
    if( e == RenameNIL ){
	return;
    }
    switch( e->tag ){
	case TAGRename:
	    rfre_origin( e->org );
	    rfre_tmstring( e->line );
	    fre_Rename( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Return'
 * and all elements in it.
 */
static void rfre_Return( Return e )
{
    if( e == ReturnNIL ){
	return;
    }
    switch( e->tag ){
	case TAGReturn:
	    rfre_origin( e->org );
	    rfre_tmstring( e->retval );
	    fre_Return( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Set'
 * and all elements in it.
 */
static void rfre_Set( Set e )
{
    if( e == SetNIL ){
	return;
    }
    switch( e->tag ){
	case TAGSet:
	    rfre_origin( e->org );
	    rfre_tmstring( e->line );
	    fre_Set( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Split'
 * and all elements in it.
 */
static void rfre_Split( Split e )
{
    if( e == SplitNIL ){
	return;
    }
    switch( e->tag ){
	case TAGSplit:
	    rfre_origin( e->org );
	    rfre_tmstring( e->line );
	    fre_Split( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'Switch'
 * and all elements in it.
 */
static void rfre_Switch( Switch e )
{
    if( e == SwitchNIL ){
	return;
    }
    switch( e->tag ){
	case TAGSwitch:
	    rfre_origin( e->org );
	    rfre_tmstring( e->val );
	    rfre_Switchcase_list( e->cases );
	    rfre_tplelm_list( e->deflt );
	    fre_Switch( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'While'
 * and all elements in it.
 */
static void rfre_While( While e )
{
    if( e == WhileNIL ){
	return;
    }
    switch( e->tag ){
	case TAGWhile:
	    rfre_origin( e->org );
	    rfre_tmstring( e->cond );
	    rfre_tplelm_list( e->body );
	    fre_While( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of tuple type 'Switchcase'
 * and all elements in it.
 */
static void rfre_Switchcase( Switchcase e )
{
    if( e == SwitchcaseNIL ){
	return;
    }
    rfre_tmstring( e->cases );
    rfre_tplelm_list( e->action );
    fre_Switchcase( e );
}

/* Recursively free an element 'e' of tuple type 'origsymbol'
 * and all elements in it.
 */
static void rfre_origsymbol( origsymbol e )
{
    if( e == origsymbolNIL ){
	return;
    }
    rfre_tmsymbol( e->sym );
    rfre_origin( e->org );
    fre_origsymbol( e );
}

/* Recursively free an element 'e' of class type 'ds'
 * and all elements in it.
 */
void rfre_ds( ds e )
{
    if( e == dsNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsInclude:
	    rfre_DsInclude( (DsInclude) e );
	    break;

	case TAGDsConstructorBase:
	    rfre_DsConstructorBase( (DsConstructorBase) e );
	    break;

	case TAGDsTuple:
	    rfre_DsTuple( (DsTuple) e );
	    break;

	case TAGDsClass:
	    rfre_DsClass( (DsClass) e );
	    break;

	case TAGDsConstructor:
	    rfre_DsConstructor( (DsConstructor) e );
	    break;

	case TAGDsAlias:
	    rfre_DsAlias( (DsAlias) e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'CCAlternatives'
 * and all elements in it.
 */
static void rfre_CCAlternatives( CCAlternatives e )
{
    if( e == CCAlternativesNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCCAlternatives:
	    rfre_alternative_list( e->alternatives );
	    fre_CCAlternatives( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'CCFields'
 * and all elements in it.
 */
static void rfre_CCFields( CCFields e )
{
    if( e == CCFieldsNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCCFields:
	    rfre_Field_list( e->fields );
	    fre_CCFields( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'CCSublist'
 * and all elements in it.
 */
static void rfre_CCSublist( CCSublist e )
{
    if( e == CCSublistNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCCSublist:
	    rfre_classComponent_list( e->components );
	    fre_CCSublist( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'CCSuper'
 * and all elements in it.
 */
static void rfre_CCSuper( CCSuper e )
{
    if( e == CCSuperNIL ){
	return;
    }
    switch( e->tag ){
	case TAGCCSuper:
	    rfre_tmsymbol( e->super );
	    fre_CCSuper( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'DsAlias'
 * and all elements in it.
 */
static void rfre_DsAlias( DsAlias e )
{
    if( e == DsAliasNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsAlias:
	    rfre_origsymbol( e->name );
	    rfre_tmsymbol_list( e->inherits );
	    rfre_tmsymbol_list( e->inheritors );
	    rfre_Type( e->type );
	    fre_DsAlias( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'DsClass'
 * and all elements in it.
 */
static void rfre_DsClass( DsClass e )
{
    if( e == DsClassNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsClass:
	    rfre_origsymbol( e->name );
	    rfre_tmsymbol_list( e->inherits );
	    rfre_tmsymbol_list( e->inheritors );
	    rfre_Field_list( e->fields );
	    rfre_tmbool( e->isvirtual );
	    fre_DsClass( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'DsConstructor'
 * and all elements in it.
 */
static void rfre_DsConstructor( DsConstructor e )
{
    if( e == DsConstructorNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsConstructor:
	    rfre_origsymbol( e->name );
	    rfre_tmsymbol_list( e->inherits );
	    rfre_tmsymbol_list( e->inheritors );
	    rfre_Field_list( e->fields );
	    fre_DsConstructor( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'DsConstructorBase'
 * and all elements in it.
 */
static void rfre_DsConstructorBase( DsConstructorBase e )
{
    if( e == DsConstructorBaseNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsConstructorBase:
	    rfre_origsymbol( e->name );
	    rfre_tmsymbol_list( e->inherits );
	    rfre_tmsymbol_list( e->inheritors );
	    rfre_tmsymbol_list( e->constructors );
	    fre_DsConstructorBase( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'DsInclude'
 * and all elements in it.
 */
static void rfre_DsInclude( DsInclude e )
{
    if( e == DsIncludeNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsInclude:
	    rfre_origsymbol( e->name );
	    rfre_tmsymbol_list( e->inherits );
	    rfre_tmsymbol_list( e->inheritors );
	    rfre_tmstring( e->fnm );
	    fre_DsInclude( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of class type 'DsTuple'
 * and all elements in it.
 */
static void rfre_DsTuple( DsTuple e )
{
    if( e == DsTupleNIL ){
	return;
    }
    switch( e->tag ){
	case TAGDsTuple:
	    rfre_origsymbol( e->name );
	    rfre_tmsymbol_list( e->inherits );
	    rfre_tmsymbol_list( e->inheritors );
	    rfre_Field_list( e->fields );
	    fre_DsTuple( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of tuple type 'Field'
 * and all elements in it.
 */
static void rfre_Field( Field e )
{
    if( e == FieldNIL ){
	return;
    }
    rfre_origsymbol( e->name );
    rfre_Type( e->type );
    fre_Field( e );
}

/* Recursively free a list of elements 'e' of type Type. */
void rfre_Type_list( Type_list e )
{
    unsigned int ix;

    if( e == Type_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
        rfre_Type( e->arr[ix] );
    }
    fre_Type_list( e );
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

/* Recursively free a list of elements 'e' of type tmsymbol. */
void rfre_tmsymbol_list( tmsymbol_list e )
{
    unsigned int ix;

    if( e == tmsymbol_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
        rfre_tmsymbol( e->arr[ix] );
    }
    fre_tmsymbol_list( e );
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

/* Recursively free a list of elements 'e' of type variable. */
void rfre_variable_list( variable_list e )
{
    unsigned int ix;

    if( e == variable_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
        rfre_variable( e->arr[ix] );
    }
    fre_variable_list( e );
}

/* Recursively free a list of elements 'e' of type Switchcase. */
static void rfre_Switchcase_list( Switchcase_list e )
{
    unsigned int ix;

    if( e == Switchcase_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
        rfre_Switchcase( e->arr[ix] );
    }
    fre_Switchcase_list( e );
}

/* Recursively free a list of elements 'e' of type Field. */
static void rfre_Field_list( Field_list e )
{
    unsigned int ix;

    if( e == Field_listNIL ){
	return;
    }
    for( ix=0; ix<e->sz; ix++ ){
        rfre_Field( e->arr[ix] );
    }
    fre_Field_list( e );
}

/**************************************************
 *    print_<type> and print_<type>_list routines *
 **************************************************/

static void print_Field_list( TMPRINTSTATE *st, const const_Field_list );
static void print_tmsymbol_list( TMPRINTSTATE *st, const const_tmsymbol_list );
static void print_ds( TMPRINTSTATE *st, const const_ds );
static void print_Type( TMPRINTSTATE *st, const const_Type );
static void print_origsymbol( TMPRINTSTATE *st, const const_origsymbol );
static void print_Field( TMPRINTSTATE *st, const const_Field );
static void print_origin( TMPRINTSTATE *st, const const_origin );
static void print_DsAlias( TMPRINTSTATE *st, const const_DsAlias );
static void print_DsClass( TMPRINTSTATE *st, const const_DsClass );
static void print_DsConstructor( TMPRINTSTATE *st, const const_DsConstructor );
static void print_DsConstructorBase( TMPRINTSTATE *st, const const_DsConstructorBase );
static void print_DsInclude( TMPRINTSTATE *st, const const_DsInclude );
static void print_DsTuple( TMPRINTSTATE *st, const const_DsTuple );
/* Print an element 't' of class type 'ds'
 * using print optimizer.
 */
static void print_ds( TMPRINTSTATE *st, const const_ds t )
{
    if( t == dsNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsInclude:
	    print_DsInclude( st, to_const_DsInclude( t ) );
	    break;

	case TAGDsConstructorBase:
	    print_DsConstructorBase( st, to_const_DsConstructorBase( t ) );
	    break;

	case TAGDsTuple:
	    print_DsTuple( st, to_const_DsTuple( t ) );
	    break;

	case TAGDsClass:
	    print_DsClass( st, to_const_DsClass( t ) );
	    break;

	case TAGDsConstructor:
	    print_DsConstructor( st, to_const_DsConstructor( t ) );
	    break;

	case TAGDsAlias:
	    print_DsAlias( st, to_const_DsAlias( t ) );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of tuple type 'Type'
 * using print optimizer.
 */
static void print_Type( TMPRINTSTATE *st, const const_Type t )
{
    if( t == TypeNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_opentuple( st );
    print_tmuint( st, t->level );
    print_tmsymbol( st, t->basetype );
    tm_closetuple( st );
}

/* Print an element 't' of tuple type 'origsymbol'
 * using print optimizer.
 */
static void print_origsymbol( TMPRINTSTATE *st, const const_origsymbol t )
{
    if( t == origsymbolNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_opentuple( st );
    print_tmsymbol( st, t->sym );
    print_origin( st, t->org );
    tm_closetuple( st );
}

/* Print an element 't' of tuple type 'Field'
 * using print optimizer.
 */
static void print_Field( TMPRINTSTATE *st, const const_Field t )
{
    if( t == FieldNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_opentuple( st );
    print_origsymbol( st, t->name );
    print_Type( st, t->type );
    tm_closetuple( st );
}

/* Print an element 't' of tuple type 'origin'
 * using print optimizer.
 */
static void print_origin( TMPRINTSTATE *st, const const_origin t )
{
    if( t == originNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_opentuple( st );
    print_tmsymbol( st, t->file );
    print_tmuint( st, t->line );
    tm_closetuple( st );
}

/* Print an element 't' of class type 'DsAlias'
 * using print optimizer.
 */
static void print_DsAlias( TMPRINTSTATE *st, const const_DsAlias t )
{
    if( t == DsAliasNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsAlias:
	    tm_opencons( st );
	    tm_printword( st, "DsAlias" );
	    print_origsymbol( st, t->name );
	    print_tmsymbol_list( st, t->inherits );
	    print_tmsymbol_list( st, t->inheritors );
	    print_Type( st, t->type );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'DsClass'
 * using print optimizer.
 */
static void print_DsClass( TMPRINTSTATE *st, const const_DsClass t )
{
    if( t == DsClassNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsClass:
	    tm_opencons( st );
	    tm_printword( st, "DsClass" );
	    print_origsymbol( st, t->name );
	    print_tmsymbol_list( st, t->inherits );
	    print_tmsymbol_list( st, t->inheritors );
	    print_Field_list( st, t->fields );
	    print_tmbool( st, t->isvirtual );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'DsConstructor'
 * using print optimizer.
 */
static void print_DsConstructor( TMPRINTSTATE *st, const const_DsConstructor t )
{
    if( t == DsConstructorNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsConstructor:
	    tm_opencons( st );
	    tm_printword( st, "DsConstructor" );
	    print_origsymbol( st, t->name );
	    print_tmsymbol_list( st, t->inherits );
	    print_tmsymbol_list( st, t->inheritors );
	    print_Field_list( st, t->fields );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'DsConstructorBase'
 * using print optimizer.
 */
static void print_DsConstructorBase( TMPRINTSTATE *st, const const_DsConstructorBase t )
{
    if( t == DsConstructorBaseNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsConstructorBase:
	    tm_opencons( st );
	    tm_printword( st, "DsConstructorBase" );
	    print_origsymbol( st, t->name );
	    print_tmsymbol_list( st, t->inherits );
	    print_tmsymbol_list( st, t->inheritors );
	    print_tmsymbol_list( st, t->constructors );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'DsInclude'
 * using print optimizer.
 */
static void print_DsInclude( TMPRINTSTATE *st, const const_DsInclude t )
{
    if( t == DsIncludeNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsInclude:
	    tm_opencons( st );
	    tm_printword( st, "DsInclude" );
	    print_origsymbol( st, t->name );
	    print_tmsymbol_list( st, t->inherits );
	    print_tmsymbol_list( st, t->inheritors );
	    print_tmstring( st, t->fnm );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'DsTuple'
 * using print optimizer.
 */
static void print_DsTuple( TMPRINTSTATE *st, const const_DsTuple t )
{
    if( t == DsTupleNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsTuple:
	    tm_opencons( st );
	    tm_printword( st, "DsTuple" );
	    print_origsymbol( st, t->name );
	    print_tmsymbol_list( st, t->inherits );
	    print_tmsymbol_list( st, t->inheritors );
	    print_Field_list( st, t->fields );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print a list of elements 'l' of type 'ds'
   using print optimizer.
 */
void print_ds_list( TMPRINTSTATE *st, const const_ds_list l )
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

/* Print a list of elements 'l' of type 'Field'
   using print optimizer.
 */
static void print_Field_list( TMPRINTSTATE *st, const const_Field_list l )
{
    unsigned int ix;

    if( l == Field_listNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_openlist( st );
    for( ix=0; ix<l->sz; ix++ ){
	print_Field( st, l->arr[ix] );
    }
    tm_closelist( st );
}

/* Print a list of elements 'l' of type 'tmsymbol'
   using print optimizer.
 */
static void print_tmsymbol_list( TMPRINTSTATE *st, const const_tmsymbol_list l )
{
    unsigned int ix;

    if( l == tmsymbol_listNIL ){
	tm_printword( st, "@" );
	return;
    }
    tm_openlist( st );
    for( ix=0; ix<l->sz; ix++ ){
	print_tmsymbol( st, l->arr[ix] );
    }
    tm_closelist( st );
}

/**************************************************
 *    Duplication routines                        *
 **************************************************/

#ifdef LOGNEW
#undef rdup_Type
#define rdup_Type(e) real_rdup_Type(e,_f,_l)
#undef rdup_ds
#define rdup_ds(e) real_rdup_ds(e,_f,_l)
#undef rdup_origin
#define rdup_origin(e) real_rdup_origin(e,_f,_l)
#undef rdup_origsymbol
#define rdup_origsymbol(e) real_rdup_origsymbol(e,_f,_l)
#undef rdup_tplelm
#define rdup_tplelm(e) real_rdup_tplelm(e,_f,_l)
#define rdup_Field(e) real_rdup_Field(e,_f,_l)
#define rdup_Append(e) real_rdup_Append(e,_f,_l)
#define rdup_Appendfile(e) real_rdup_Appendfile(e,_f,_l)
#define rdup_Call(e) real_rdup_Call(e,_f,_l)
#define rdup_Case(e) real_rdup_Case(e,_f,_l)
#define rdup_Default(e) real_rdup_Default(e,_f,_l)
#define rdup_DeleteType(e) real_rdup_DeleteType(e,_f,_l)
#define rdup_DsAlias(e) real_rdup_DsAlias(e,_f,_l)
#define rdup_DsClass(e) real_rdup_DsClass(e,_f,_l)
#define rdup_DsConstructor(e) real_rdup_DsConstructor(e,_f,_l)
#define rdup_DsConstructorBase(e) real_rdup_DsConstructorBase(e,_f,_l)
#define rdup_DsInclude(e) real_rdup_DsInclude(e,_f,_l)
#define rdup_DsTuple(e) real_rdup_DsTuple(e,_f,_l)
#define rdup_Error(e) real_rdup_Error(e,_f,_l)
#define rdup_Exit(e) real_rdup_Exit(e,_f,_l)
#define rdup_For(e) real_rdup_For(e,_f,_l)
#define rdup_Foreach(e) real_rdup_Foreach(e,_f,_l)
#define rdup_GlobalAppend(e) real_rdup_GlobalAppend(e,_f,_l)
#define rdup_GlobalSet(e) real_rdup_GlobalSet(e,_f,_l)
#define rdup_GlobalSplit(e) real_rdup_GlobalSplit(e,_f,_l)
#define rdup_If(e) real_rdup_If(e,_f,_l)
#define rdup_Include(e) real_rdup_Include(e,_f,_l)
#define rdup_Insert(e) real_rdup_Insert(e,_f,_l)
#define rdup_Macro(e) real_rdup_Macro(e,_f,_l)
#define rdup_Plain(e) real_rdup_Plain(e,_f,_l)
#define rdup_Redirect(e) real_rdup_Redirect(e,_f,_l)
#define rdup_Rename(e) real_rdup_Rename(e,_f,_l)
#define rdup_Return(e) real_rdup_Return(e,_f,_l)
#define rdup_Set(e) real_rdup_Set(e,_f,_l)
#define rdup_Split(e) real_rdup_Split(e,_f,_l)
#define rdup_Switch(e) real_rdup_Switch(e,_f,_l)
#define rdup_Switchcase(e) real_rdup_Switchcase(e,_f,_l)
#define rdup_While(e) real_rdup_While(e,_f,_l)
#undef rdup_Field_list
#define rdup_Field_list(l) real_rdup_Field_list(l,_f,_l)
#undef rdup_tmstring_list
#define rdup_tmstring_list(l) real_rdup_tmstring_list(l,_f,_l)
#undef rdup_tmsymbol_list
#define rdup_tmsymbol_list(l) real_rdup_tmsymbol_list(l,_f,_l)
#undef rdup_tplelm_list
#define rdup_tplelm_list(l) real_rdup_tplelm_list(l,_f,_l)
#define rdup_Switchcase_list(l) real_rdup_Switchcase_list(l,_f,_l)
static   Switchcase_list real_rdup_Switchcase_list( const_Switchcase_list, const char *, const int );
static  Field  real_rdup_Field( const_Field, const char *, const int );
static  Append  real_rdup_Append( const_Append, const char *, const int );
static  Appendfile  real_rdup_Appendfile( const_Appendfile, const char *, const int );
static  Call  real_rdup_Call( const_Call, const char *, const int );
static  Case  real_rdup_Case( const_Case, const char *, const int );
static  Default  real_rdup_Default( const_Default, const char *, const int );
static  DeleteType  real_rdup_DeleteType( const_DeleteType, const char *, const int );
static  DsAlias  real_rdup_DsAlias( const_DsAlias, const char *, const int );
static  DsClass  real_rdup_DsClass( const_DsClass, const char *, const int );
static  DsConstructor  real_rdup_DsConstructor( const_DsConstructor, const char *, const int );
static  DsConstructorBase  real_rdup_DsConstructorBase( const_DsConstructorBase, const char *, const int );
static  DsInclude  real_rdup_DsInclude( const_DsInclude, const char *, const int );
static  DsTuple  real_rdup_DsTuple( const_DsTuple, const char *, const int );
static  Error  real_rdup_Error( const_Error, const char *, const int );
static  Exit  real_rdup_Exit( const_Exit, const char *, const int );
static  For  real_rdup_For( const_For, const char *, const int );
static  Foreach  real_rdup_Foreach( const_Foreach, const char *, const int );
static  GlobalAppend  real_rdup_GlobalAppend( const_GlobalAppend, const char *, const int );
static  GlobalSet  real_rdup_GlobalSet( const_GlobalSet, const char *, const int );
static  GlobalSplit  real_rdup_GlobalSplit( const_GlobalSplit, const char *, const int );
static  If  real_rdup_If( const_If, const char *, const int );
static  Include  real_rdup_Include( const_Include, const char *, const int );
static  Insert  real_rdup_Insert( const_Insert, const char *, const int );
static  Macro  real_rdup_Macro( const_Macro, const char *, const int );
static  Plain  real_rdup_Plain( const_Plain, const char *, const int );
static  Redirect  real_rdup_Redirect( const_Redirect, const char *, const int );
static  Rename  real_rdup_Rename( const_Rename, const char *, const int );
static  Return  real_rdup_Return( const_Return, const char *, const int );
static  Set  real_rdup_Set( const_Set, const char *, const int );
static  Split  real_rdup_Split( const_Split, const char *, const int );
static  Switch  real_rdup_Switch( const_Switch, const char *, const int );
static  Switchcase  real_rdup_Switchcase( const_Switchcase, const char *, const int );
static  While  real_rdup_While( const_While, const char *, const int );
#else
static   Switchcase_list rdup_Switchcase_list( const const_Switchcase_list );
static   Field rdup_Field( const const_Field );
static   Append rdup_Append( const const_Append );
static   Appendfile rdup_Appendfile( const const_Appendfile );
static   Call rdup_Call( const const_Call );
static   Case rdup_Case( const const_Case );
static   Default rdup_Default( const const_Default );
static   DeleteType rdup_DeleteType( const const_DeleteType );
static   DsAlias rdup_DsAlias( const const_DsAlias );
static   DsClass rdup_DsClass( const const_DsClass );
static   DsConstructor rdup_DsConstructor( const const_DsConstructor );
static   DsConstructorBase rdup_DsConstructorBase( const const_DsConstructorBase );
static   DsInclude rdup_DsInclude( const const_DsInclude );
static   DsTuple rdup_DsTuple( const const_DsTuple );
static   Error rdup_Error( const const_Error );
static   Exit rdup_Exit( const const_Exit );
static   For rdup_For( const const_For );
static   Foreach rdup_Foreach( const const_Foreach );
static   GlobalAppend rdup_GlobalAppend( const const_GlobalAppend );
static   GlobalSet rdup_GlobalSet( const const_GlobalSet );
static   GlobalSplit rdup_GlobalSplit( const const_GlobalSplit );
static   If rdup_If( const const_If );
static   Include rdup_Include( const const_Include );
static   Insert rdup_Insert( const const_Insert );
static   Macro rdup_Macro( const const_Macro );
static   Plain rdup_Plain( const const_Plain );
static   Redirect rdup_Redirect( const const_Redirect );
static   Rename rdup_Rename( const const_Rename );
static   Return rdup_Return( const const_Return );
static   Set rdup_Set( const const_Set );
static   Split rdup_Split( const const_Split );
static   Switch rdup_Switch( const const_Switch );
static   Switchcase rdup_Switchcase( const const_Switchcase );
static   While rdup_While( const const_While );
#endif
/* Recursively duplicate a tuple Type element 'e'. */
#ifdef LOGNEW
Type real_rdup_Type( const const_Type e, const char *_f, const int _l )
#else
Type rdup_Type( const const_Type e )
#endif
{
    tmuint i_level;
    tmsymbol i_basetype;

    if( e == TypeNIL ){
	return TypeNIL;
    }
    i_level = rdup_tmuint( e->level );
    i_basetype = rdup_tmsymbol( e->basetype );
    return new_Type( i_level, i_basetype );
}

/* Recursively duplicate a class ds element 'e'. */
#ifdef LOGNEW
ds real_rdup_ds( const const_ds e, const char *_f, const int _l )
#else
ds rdup_ds( const const_ds e )
#endif
{
    if( e == dsNIL ){
	return dsNIL;
    }
    switch( e->tag ){
	case TAGDsInclude:
	    return (ds) rdup_DsInclude( to_const_DsInclude(e) );

	case TAGDsConstructorBase:
	    return (ds) rdup_DsConstructorBase( to_const_DsConstructorBase(e) );

	case TAGDsTuple:
	    return (ds) rdup_DsTuple( to_const_DsTuple(e) );

	case TAGDsClass:
	    return (ds) rdup_DsClass( to_const_DsClass(e) );

	case TAGDsConstructor:
	    return (ds) rdup_DsConstructor( to_const_DsConstructor(e) );

	case TAGDsAlias:
	    return (ds) rdup_DsAlias( to_const_DsAlias(e) );

	default:
	    FATALTAG( e->tag );
    }
    return dsNIL;
}

/* Recursively duplicate a tuple origin element 'e'. */
#ifdef LOGNEW
origin real_rdup_origin( const const_origin e, const char *_f, const int _l )
#else
origin rdup_origin( const const_origin e )
#endif
{
    tmsymbol i_file;
    tmuint i_line;

    if( e == originNIL ){
	return originNIL;
    }
    i_file = rdup_tmsymbol( e->file );
    i_line = rdup_tmuint( e->line );
    return new_origin( i_file, i_line );
}

/* Recursively duplicate a tuple origsymbol element 'e'. */
#ifdef LOGNEW
origsymbol real_rdup_origsymbol( const const_origsymbol e, const char *_f, const int _l )
#else
origsymbol rdup_origsymbol( const const_origsymbol e )
#endif
{
    tmsymbol i_sym;
    origin i_org;

    if( e == origsymbolNIL ){
	return origsymbolNIL;
    }
    i_sym = rdup_tmsymbol( e->sym );
    i_org = rdup_origin( e->org );
    return new_origsymbol( i_sym, i_org );
}

/* Recursively duplicate a class tplelm element 'e'. */
#ifdef LOGNEW
tplelm real_rdup_tplelm( const const_tplelm e, const char *_f, const int _l )
#else
tplelm rdup_tplelm( const const_tplelm e )
#endif
{
    if( e == tplelmNIL ){
	return tplelmNIL;
    }
    switch( e->tag ){
	case TAGPlain:
	    return (tplelm) rdup_Plain( to_const_Plain(e) );

	case TAGFor:
	    return (tplelm) rdup_For( to_const_For(e) );

	case TAGForeach:
	    return (tplelm) rdup_Foreach( to_const_Foreach(e) );

	case TAGWhile:
	    return (tplelm) rdup_While( to_const_While(e) );

	case TAGIf:
	    return (tplelm) rdup_If( to_const_If(e) );

	case TAGSwitch:
	    return (tplelm) rdup_Switch( to_const_Switch(e) );

	case TAGSet:
	    return (tplelm) rdup_Set( to_const_Set(e) );

	case TAGSplit:
	    return (tplelm) rdup_Split( to_const_Split(e) );

	case TAGRename:
	    return (tplelm) rdup_Rename( to_const_Rename(e) );

	case TAGGlobalSet:
	    return (tplelm) rdup_GlobalSet( to_const_GlobalSet(e) );

	case TAGGlobalSplit:
	    return (tplelm) rdup_GlobalSplit( to_const_GlobalSplit(e) );

	case TAGAppend:
	    return (tplelm) rdup_Append( to_const_Append(e) );

	case TAGGlobalAppend:
	    return (tplelm) rdup_GlobalAppend( to_const_GlobalAppend(e) );

	case TAGDeleteType:
	    return (tplelm) rdup_DeleteType( to_const_DeleteType(e) );

	case TAGError:
	    return (tplelm) rdup_Error( to_const_Error(e) );

	case TAGExit:
	    return (tplelm) rdup_Exit( to_const_Exit(e) );

	case TAGRedirect:
	    return (tplelm) rdup_Redirect( to_const_Redirect(e) );

	case TAGAppendfile:
	    return (tplelm) rdup_Appendfile( to_const_Appendfile(e) );

	case TAGMacro:
	    return (tplelm) rdup_Macro( to_const_Macro(e) );

	case TAGCall:
	    return (tplelm) rdup_Call( to_const_Call(e) );

	case TAGReturn:
	    return (tplelm) rdup_Return( to_const_Return(e) );

	case TAGInclude:
	    return (tplelm) rdup_Include( to_const_Include(e) );

	case TAGInsert:
	    return (tplelm) rdup_Insert( to_const_Insert(e) );

	case TAGCase:
	    return (tplelm) rdup_Case( to_const_Case(e) );

	case TAGDefault:
	    return (tplelm) rdup_Default( to_const_Default(e) );

	default:
	    FATALTAG( e->tag );
    }
    return tplelmNIL;
}

/* Recursively duplicate a tuple Field element 'e'. */
#ifdef LOGNEW
static Field real_rdup_Field( const const_Field e, const char *_f, const int _l )
#else
static Field rdup_Field( const const_Field e )
#endif
{
    origsymbol i_name;
    Type i_type;

    if( e == FieldNIL ){
	return FieldNIL;
    }
    i_name = rdup_origsymbol( e->name );
    i_type = rdup_Type( e->type );
    return new_Field( i_name, i_type );
}

/* Recursively duplicate a class Append element 'e'. */
#ifdef LOGNEW
static Append real_rdup_Append( const const_Append e, const char *_f, const int _l )
#else
static Append rdup_Append( const const_Append e )
#endif
{
    origin i_org;
    tmstring i_line;

    if( e == AppendNIL ){
	return AppendNIL;
    }
    i_org = rdup_origin( e->org );
    i_line = rdup_tmstring( e->line );
    return new_Append( i_org, i_line );
}

/* Recursively duplicate a class Appendfile element 'e'. */
#ifdef LOGNEW
static Appendfile real_rdup_Appendfile( const const_Appendfile e, const char *_f, const int _l )
#else
static Appendfile rdup_Appendfile( const const_Appendfile e )
#endif
{
    origin i_org;
    tmstring i_fname;
    tplelm_list i_body;

    if( e == AppendfileNIL ){
	return AppendfileNIL;
    }
    i_org = rdup_origin( e->org );
    i_fname = rdup_tmstring( e->fname );
    i_body = rdup_tplelm_list( e->body );
    return new_Appendfile( i_org, i_fname, i_body );
}

/* Recursively duplicate a class Call element 'e'. */
#ifdef LOGNEW
static Call real_rdup_Call( const const_Call e, const char *_f, const int _l )
#else
static Call rdup_Call( const const_Call e )
#endif
{
    origin i_org;
    tmstring i_line;

    if( e == CallNIL ){
	return CallNIL;
    }
    i_org = rdup_origin( e->org );
    i_line = rdup_tmstring( e->line );
    return new_Call( i_org, i_line );
}

/* Recursively duplicate a class Case element 'e'. */
#ifdef LOGNEW
static Case real_rdup_Case( const const_Case e, const char *_f, const int _l )
#else
static Case rdup_Case( const const_Case e )
#endif
{
    origin i_org;
    tmstring i_val;

    if( e == CaseNIL ){
	return CaseNIL;
    }
    i_org = rdup_origin( e->org );
    i_val = rdup_tmstring( e->val );
    return new_Case( i_org, i_val );
}

/* Recursively duplicate a class Default element 'e'. */
#ifdef LOGNEW
static Default real_rdup_Default( const const_Default e, const char *_f, const int _l )
#else
static Default rdup_Default( const const_Default e )
#endif
{
    origin i_org;

    if( e == DefaultNIL ){
	return DefaultNIL;
    }
    i_org = rdup_origin( e->org );
    return new_Default( i_org );
}

/* Recursively duplicate a class DeleteType element 'e'. */
#ifdef LOGNEW
static DeleteType real_rdup_DeleteType( const const_DeleteType e, const char *_f, const int _l )
#else
static DeleteType rdup_DeleteType( const const_DeleteType e )
#endif
{
    origin i_org;
    tmstring i_line;

    if( e == DeleteTypeNIL ){
	return DeleteTypeNIL;
    }
    i_org = rdup_origin( e->org );
    i_line = rdup_tmstring( e->line );
    return new_DeleteType( i_org, i_line );
}

/* Recursively duplicate a class DsAlias element 'e'. */
#ifdef LOGNEW
static DsAlias real_rdup_DsAlias( const const_DsAlias e, const char *_f, const int _l )
#else
static DsAlias rdup_DsAlias( const const_DsAlias e )
#endif
{
    origsymbol i_name;
    tmsymbol_list i_inherits;
    tmsymbol_list i_inheritors;
    Type i_type;

    if( e == DsAliasNIL ){
	return DsAliasNIL;
    }
    i_name = rdup_origsymbol( e->name );
    i_inherits = rdup_tmsymbol_list( e->inherits );
    i_inheritors = rdup_tmsymbol_list( e->inheritors );
    i_type = rdup_Type( e->type );
    return new_DsAlias( i_name, i_inherits, i_inheritors, i_type );
}

/* Recursively duplicate a class DsClass element 'e'. */
#ifdef LOGNEW
static DsClass real_rdup_DsClass( const const_DsClass e, const char *_f, const int _l )
#else
static DsClass rdup_DsClass( const const_DsClass e )
#endif
{
    origsymbol i_name;
    tmsymbol_list i_inherits;
    tmsymbol_list i_inheritors;
    Field_list i_fields;
    tmbool i_isvirtual;

    if( e == DsClassNIL ){
	return DsClassNIL;
    }
    i_name = rdup_origsymbol( e->name );
    i_inherits = rdup_tmsymbol_list( e->inherits );
    i_inheritors = rdup_tmsymbol_list( e->inheritors );
    i_fields = rdup_Field_list( e->fields );
    i_isvirtual = rdup_tmbool( e->isvirtual );
    return new_DsClass( i_name, i_inherits, i_inheritors, i_fields, i_isvirtual );
}

/* Recursively duplicate a class DsConstructor element 'e'. */
#ifdef LOGNEW
static DsConstructor real_rdup_DsConstructor( const const_DsConstructor e, const char *_f, const int _l )
#else
static DsConstructor rdup_DsConstructor( const const_DsConstructor e )
#endif
{
    origsymbol i_name;
    tmsymbol_list i_inherits;
    tmsymbol_list i_inheritors;
    Field_list i_fields;

    if( e == DsConstructorNIL ){
	return DsConstructorNIL;
    }
    i_name = rdup_origsymbol( e->name );
    i_inherits = rdup_tmsymbol_list( e->inherits );
    i_inheritors = rdup_tmsymbol_list( e->inheritors );
    i_fields = rdup_Field_list( e->fields );
    return new_DsConstructor( i_name, i_inherits, i_inheritors, i_fields );
}

/* Recursively duplicate a class DsConstructorBase element 'e'. */
#ifdef LOGNEW
static DsConstructorBase real_rdup_DsConstructorBase( const const_DsConstructorBase e, const char *_f, const int _l )
#else
static DsConstructorBase rdup_DsConstructorBase( const const_DsConstructorBase e )
#endif
{
    origsymbol i_name;
    tmsymbol_list i_inherits;
    tmsymbol_list i_inheritors;
    tmsymbol_list i_constructors;

    if( e == DsConstructorBaseNIL ){
	return DsConstructorBaseNIL;
    }
    i_name = rdup_origsymbol( e->name );
    i_inherits = rdup_tmsymbol_list( e->inherits );
    i_inheritors = rdup_tmsymbol_list( e->inheritors );
    i_constructors = rdup_tmsymbol_list( e->constructors );
    return new_DsConstructorBase( i_name, i_inherits, i_inheritors, i_constructors );
}

/* Recursively duplicate a class DsInclude element 'e'. */
#ifdef LOGNEW
static DsInclude real_rdup_DsInclude( const const_DsInclude e, const char *_f, const int _l )
#else
static DsInclude rdup_DsInclude( const const_DsInclude e )
#endif
{
    origsymbol i_name;
    tmsymbol_list i_inherits;
    tmsymbol_list i_inheritors;
    tmstring i_fnm;

    if( e == DsIncludeNIL ){
	return DsIncludeNIL;
    }
    i_name = rdup_origsymbol( e->name );
    i_inherits = rdup_tmsymbol_list( e->inherits );
    i_inheritors = rdup_tmsymbol_list( e->inheritors );
    i_fnm = rdup_tmstring( e->fnm );
    return new_DsInclude( i_name, i_inherits, i_inheritors, i_fnm );
}

/* Recursively duplicate a class DsTuple element 'e'. */
#ifdef LOGNEW
static DsTuple real_rdup_DsTuple( const const_DsTuple e, const char *_f, const int _l )
#else
static DsTuple rdup_DsTuple( const const_DsTuple e )
#endif
{
    origsymbol i_name;
    tmsymbol_list i_inherits;
    tmsymbol_list i_inheritors;
    Field_list i_fields;

    if( e == DsTupleNIL ){
	return DsTupleNIL;
    }
    i_name = rdup_origsymbol( e->name );
    i_inherits = rdup_tmsymbol_list( e->inherits );
    i_inheritors = rdup_tmsymbol_list( e->inheritors );
    i_fields = rdup_Field_list( e->fields );
    return new_DsTuple( i_name, i_inherits, i_inheritors, i_fields );
}

/* Recursively duplicate a class Error element 'e'. */
#ifdef LOGNEW
static Error real_rdup_Error( const const_Error e, const char *_f, const int _l )
#else
static Error rdup_Error( const const_Error e )
#endif
{
    origin i_org;
    tmstring i_str;

    if( e == ErrorNIL ){
	return ErrorNIL;
    }
    i_org = rdup_origin( e->org );
    i_str = rdup_tmstring( e->str );
    return new_Error( i_org, i_str );
}

/* Recursively duplicate a class Exit element 'e'. */
#ifdef LOGNEW
static Exit real_rdup_Exit( const const_Exit e, const char *_f, const int _l )
#else
static Exit rdup_Exit( const const_Exit e )
#endif
{
    origin i_org;
    tmstring i_str;

    if( e == ExitNIL ){
	return ExitNIL;
    }
    i_org = rdup_origin( e->org );
    i_str = rdup_tmstring( e->str );
    return new_Exit( i_org, i_str );
}

/* Recursively duplicate a class For element 'e'. */
#ifdef LOGNEW
static For real_rdup_For( const const_For e, const char *_f, const int _l )
#else
static For rdup_For( const const_For e )
#endif
{
    origin i_org;
    tmstring i_parms;
    tplelm_list i_body;

    if( e == ForNIL ){
	return ForNIL;
    }
    i_org = rdup_origin( e->org );
    i_parms = rdup_tmstring( e->parms );
    i_body = rdup_tplelm_list( e->body );
    return new_For( i_org, i_parms, i_body );
}

/* Recursively duplicate a class Foreach element 'e'. */
#ifdef LOGNEW
static Foreach real_rdup_Foreach( const const_Foreach e, const char *_f, const int _l )
#else
static Foreach rdup_Foreach( const const_Foreach e )
#endif
{
    origin i_org;
    tmstring i_felist;
    tplelm_list i_body;

    if( e == ForeachNIL ){
	return ForeachNIL;
    }
    i_org = rdup_origin( e->org );
    i_felist = rdup_tmstring( e->felist );
    i_body = rdup_tplelm_list( e->body );
    return new_Foreach( i_org, i_felist, i_body );
}

/* Recursively duplicate a class GlobalAppend element 'e'. */
#ifdef LOGNEW
static GlobalAppend real_rdup_GlobalAppend( const const_GlobalAppend e, const char *_f, const int _l )
#else
static GlobalAppend rdup_GlobalAppend( const const_GlobalAppend e )
#endif
{
    origin i_org;
    tmstring i_line;

    if( e == GlobalAppendNIL ){
	return GlobalAppendNIL;
    }
    i_org = rdup_origin( e->org );
    i_line = rdup_tmstring( e->line );
    return new_GlobalAppend( i_org, i_line );
}

/* Recursively duplicate a class GlobalSet element 'e'. */
#ifdef LOGNEW
static GlobalSet real_rdup_GlobalSet( const const_GlobalSet e, const char *_f, const int _l )
#else
static GlobalSet rdup_GlobalSet( const const_GlobalSet e )
#endif
{
    origin i_org;
    tmstring i_line;

    if( e == GlobalSetNIL ){
	return GlobalSetNIL;
    }
    i_org = rdup_origin( e->org );
    i_line = rdup_tmstring( e->line );
    return new_GlobalSet( i_org, i_line );
}

/* Recursively duplicate a class GlobalSplit element 'e'. */
#ifdef LOGNEW
static GlobalSplit real_rdup_GlobalSplit( const const_GlobalSplit e, const char *_f, const int _l )
#else
static GlobalSplit rdup_GlobalSplit( const const_GlobalSplit e )
#endif
{
    origin i_org;
    tmstring i_line;

    if( e == GlobalSplitNIL ){
	return GlobalSplitNIL;
    }
    i_org = rdup_origin( e->org );
    i_line = rdup_tmstring( e->line );
    return new_GlobalSplit( i_org, i_line );
}

/* Recursively duplicate a class If element 'e'. */
#ifdef LOGNEW
static If real_rdup_If( const const_If e, const char *_f, const int _l )
#else
static If rdup_If( const const_If e )
#endif
{
    origin i_org;
    tmstring i_cond;
    tplelm_list i_ifthen;
    tplelm_list i_ifelse;

    if( e == IfNIL ){
	return IfNIL;
    }
    i_org = rdup_origin( e->org );
    i_cond = rdup_tmstring( e->cond );
    i_ifthen = rdup_tplelm_list( e->ifthen );
    i_ifelse = rdup_tplelm_list( e->ifelse );
    return new_If( i_org, i_cond, i_ifthen, i_ifelse );
}

/* Recursively duplicate a class Include element 'e'. */
#ifdef LOGNEW
static Include real_rdup_Include( const const_Include e, const char *_f, const int _l )
#else
static Include rdup_Include( const const_Include e )
#endif
{
    origin i_org;
    tmstring i_fname;

    if( e == IncludeNIL ){
	return IncludeNIL;
    }
    i_org = rdup_origin( e->org );
    i_fname = rdup_tmstring( e->fname );
    return new_Include( i_org, i_fname );
}

/* Recursively duplicate a class Insert element 'e'. */
#ifdef LOGNEW
static Insert real_rdup_Insert( const const_Insert e, const char *_f, const int _l )
#else
static Insert rdup_Insert( const const_Insert e )
#endif
{
    origin i_org;
    tmstring i_fname;

    if( e == InsertNIL ){
	return InsertNIL;
    }
    i_org = rdup_origin( e->org );
    i_fname = rdup_tmstring( e->fname );
    return new_Insert( i_org, i_fname );
}

/* Recursively duplicate a class Macro element 'e'. */
#ifdef LOGNEW
static Macro real_rdup_Macro( const const_Macro e, const char *_f, const int _l )
#else
static Macro rdup_Macro( const const_Macro e )
#endif
{
    origin i_org;
    tmstring i_formals;
    tplelm_list i_body;

    if( e == MacroNIL ){
	return MacroNIL;
    }
    i_org = rdup_origin( e->org );
    i_formals = rdup_tmstring( e->formals );
    i_body = rdup_tplelm_list( e->body );
    return new_Macro( i_org, i_formals, i_body );
}

/* Recursively duplicate a class Plain element 'e'. */
#ifdef LOGNEW
static Plain real_rdup_Plain( const const_Plain e, const char *_f, const int _l )
#else
static Plain rdup_Plain( const const_Plain e )
#endif
{
    origin i_org;
    tmstring i_line;

    if( e == PlainNIL ){
	return PlainNIL;
    }
    i_org = rdup_origin( e->org );
    i_line = rdup_tmstring( e->line );
    return new_Plain( i_org, i_line );
}

/* Recursively duplicate a class Redirect element 'e'. */
#ifdef LOGNEW
static Redirect real_rdup_Redirect( const const_Redirect e, const char *_f, const int _l )
#else
static Redirect rdup_Redirect( const const_Redirect e )
#endif
{
    origin i_org;
    tmstring i_fname;
    tplelm_list i_body;

    if( e == RedirectNIL ){
	return RedirectNIL;
    }
    i_org = rdup_origin( e->org );
    i_fname = rdup_tmstring( e->fname );
    i_body = rdup_tplelm_list( e->body );
    return new_Redirect( i_org, i_fname, i_body );
}

/* Recursively duplicate a class Rename element 'e'. */
#ifdef LOGNEW
static Rename real_rdup_Rename( const const_Rename e, const char *_f, const int _l )
#else
static Rename rdup_Rename( const const_Rename e )
#endif
{
    origin i_org;
    tmstring i_line;

    if( e == RenameNIL ){
	return RenameNIL;
    }
    i_org = rdup_origin( e->org );
    i_line = rdup_tmstring( e->line );
    return new_Rename( i_org, i_line );
}

/* Recursively duplicate a class Return element 'e'. */
#ifdef LOGNEW
static Return real_rdup_Return( const const_Return e, const char *_f, const int _l )
#else
static Return rdup_Return( const const_Return e )
#endif
{
    origin i_org;
    tmstring i_retval;

    if( e == ReturnNIL ){
	return ReturnNIL;
    }
    i_org = rdup_origin( e->org );
    i_retval = rdup_tmstring( e->retval );
    return new_Return( i_org, i_retval );
}

/* Recursively duplicate a class Set element 'e'. */
#ifdef LOGNEW
static Set real_rdup_Set( const const_Set e, const char *_f, const int _l )
#else
static Set rdup_Set( const const_Set e )
#endif
{
    origin i_org;
    tmstring i_line;

    if( e == SetNIL ){
	return SetNIL;
    }
    i_org = rdup_origin( e->org );
    i_line = rdup_tmstring( e->line );
    return new_Set( i_org, i_line );
}

/* Recursively duplicate a class Split element 'e'. */
#ifdef LOGNEW
static Split real_rdup_Split( const const_Split e, const char *_f, const int _l )
#else
static Split rdup_Split( const const_Split e )
#endif
{
    origin i_org;
    tmstring i_line;

    if( e == SplitNIL ){
	return SplitNIL;
    }
    i_org = rdup_origin( e->org );
    i_line = rdup_tmstring( e->line );
    return new_Split( i_org, i_line );
}

/* Recursively duplicate a class Switch element 'e'. */
#ifdef LOGNEW
static Switch real_rdup_Switch( const const_Switch e, const char *_f, const int _l )
#else
static Switch rdup_Switch( const const_Switch e )
#endif
{
    origin i_org;
    tmstring i_val;
    Switchcase_list i_cases;
    tplelm_list i_deflt;

    if( e == SwitchNIL ){
	return SwitchNIL;
    }
    i_org = rdup_origin( e->org );
    i_val = rdup_tmstring( e->val );
    i_cases = rdup_Switchcase_list( e->cases );
    i_deflt = rdup_tplelm_list( e->deflt );
    return new_Switch( i_org, i_val, i_cases, i_deflt );
}

/* Recursively duplicate a tuple Switchcase element 'e'. */
#ifdef LOGNEW
static Switchcase real_rdup_Switchcase( const const_Switchcase e, const char *_f, const int _l )
#else
static Switchcase rdup_Switchcase( const const_Switchcase e )
#endif
{
    tmstring i_cases;
    tplelm_list i_action;

    if( e == SwitchcaseNIL ){
	return SwitchcaseNIL;
    }
    i_cases = rdup_tmstring( e->cases );
    i_action = rdup_tplelm_list( e->action );
    return new_Switchcase( i_cases, i_action );
}

/* Recursively duplicate a class While element 'e'. */
#ifdef LOGNEW
static While real_rdup_While( const const_While e, const char *_f, const int _l )
#else
static While rdup_While( const const_While e )
#endif
{
    origin i_org;
    tmstring i_cond;
    tplelm_list i_body;

    if( e == WhileNIL ){
	return WhileNIL;
    }
    i_org = rdup_origin( e->org );
    i_cond = rdup_tmstring( e->cond );
    i_body = rdup_tplelm_list( e->body );
    return new_While( i_org, i_cond, i_body );
}

/* Recursively duplicate Field list 'l'. */
#ifdef LOGNEW
Field_list real_rdup_Field_list( const const_Field_list l, const char *_f, const int _l )
#else
Field_list rdup_Field_list( const const_Field_list l )
#endif
{
    unsigned int ix;
    Field_list nw;
    Field *ar;
    Field *o_r;

    if( l == Field_listNIL ){
	return Field_listNIL;
    }
    nw = setroom_Field_list( new_Field_list(), l->sz );
    ar = nw->arr;
    o_r = l->arr;
    for( ix=0; ix<l->sz; ix++ ){
	*ar++ = rdup_Field( *o_r++ );
    }
    nw->sz = l->sz;
    return nw;
}

/* Recursively duplicate tmstring list 'l'. */
#ifdef LOGNEW
tmstring_list real_rdup_tmstring_list( const const_tmstring_list l, const char *_f, const int _l )
#else
tmstring_list rdup_tmstring_list( const const_tmstring_list l )
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

/* Recursively duplicate tmsymbol list 'l'. */
#ifdef LOGNEW
tmsymbol_list real_rdup_tmsymbol_list( const const_tmsymbol_list l, const char *_f, const int _l )
#else
tmsymbol_list rdup_tmsymbol_list( const const_tmsymbol_list l )
#endif
{
    unsigned int ix;
    tmsymbol_list nw;
    tmsymbol *ar;
    tmsymbol *o_r;

    if( l == tmsymbol_listNIL ){
	return tmsymbol_listNIL;
    }
    nw = setroom_tmsymbol_list( new_tmsymbol_list(), l->sz );
    ar = nw->arr;
    o_r = l->arr;
    for( ix=0; ix<l->sz; ix++ ){
	*ar++ = rdup_tmsymbol( *o_r++ );
    }
    nw->sz = l->sz;
    return nw;
}

/* Recursively duplicate tplelm list 'l'. */
#ifdef LOGNEW
tplelm_list real_rdup_tplelm_list( const const_tplelm_list l, const char *_f, const int _l )
#else
tplelm_list rdup_tplelm_list( const const_tplelm_list l )
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

/* Recursively duplicate Switchcase list 'l'. */
#ifdef LOGNEW
static Switchcase_list real_rdup_Switchcase_list( const const_Switchcase_list l, const char *_f, const int _l )
#else
static Switchcase_list rdup_Switchcase_list( const const_Switchcase_list l )
#endif
{
    unsigned int ix;
    Switchcase_list nw;
    Switchcase *ar;
    Switchcase *o_r;

    if( l == Switchcase_listNIL ){
	return Switchcase_listNIL;
    }
    nw = setroom_Switchcase_list( new_Switchcase_list(), l->sz );
    ar = nw->arr;
    o_r = l->arr;
    for( ix=0; ix<l->sz; ix++ ){
	*ar++ = rdup_Switchcase( *o_r++ );
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

/* Delete 'tmsymbol' element at position 'pos' in list 'l'. */
tmsymbol_list delete_tmsymbol_list( tmsymbol_list l, const unsigned int pos )
{
    unsigned int ix;

    if( l == tmsymbol_listNIL ){
	FATAL( tm_nilptr );
    }
    if( pos >= l->sz ){
	return l;
    }
    rfre_tmsymbol( l->arr[pos] );
    l->sz--;
    for( ix=pos; ix<l->sz; ix++ ){
	l->arr[ix] = l->arr[ix+1];
    }
    return l;
}

/* Delete 'variable' element at position 'pos' in list 'l'. */
variable_list delete_variable_list( variable_list l, const unsigned int pos )
{
    unsigned int ix;

    if( l == variable_listNIL ){
	FATAL( tm_nilptr );
    }
    if( pos >= l->sz ){
	return l;
    }
    rfre_variable( l->arr[pos] );
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
        *e = tmstringNIL;
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

/* Extract 'tmsymbol' element at position 'pos' in list 'l'. */
tmsymbol_list extract_tmsymbol_list(
    tmsymbol_list l,
    const unsigned int pos,
    tmsymbol *e,
    int *valid
)
{
    unsigned int ix;

    if( l == tmsymbol_listNIL ){
	FATAL( tm_nilptr );
    }
    if( pos >= l->sz ){
	*valid = 0;
        *e = tmsymbolNIL;
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
 *    extractlist_<type>_list routines            *
 **************************************************/

#ifdef LOGNEW
#undef extractlist_tmstring_list
#define extractlist_tmstring_list(l,b,e,res) real_extractlist_tmstring(l,b,e,res,_f,_l)
#endif

/* Given a tmstring list 'l', a range 'from' to 'to' and a pointer to a
 * tmstring list 'res', create a new list '*res', and move the elements
 * from 'from' up to, but not including 'to' to this new list. All
 * elements beyond the range are moved down to close the gap. If necessary,
 * the range is silently adjusted to cover only exisiting elements.
 */
#ifdef LOGNEW
tmstring_list real_extractlist_tmstring_list(
    tmstring_list l,
    unsigned int from,
    unsigned int to,
    tmstring_list *res,
    const char *_f,
    const int _l
)
#else
tmstring_list extractlist_tmstring_list(
    tmstring_list l,
    unsigned int from,
    unsigned int to,
    tmstring_list *res
)
#endif
{
    unsigned int ix;
    unsigned int ressz;

    if( l == tmstring_listNIL ){
	FATAL( tm_nilptr );
    }
    if( to>=l->sz ){
	to = l->sz;
    }
    if( from>to ){
	from = to;
    }
    ressz = to - from;
    *res = setroom_tmstring_list( new_tmstring_list(), ressz );
    /* Copy in elements into 'res' */
    {
	unsigned int cnt = ressz;
	tmstring *sp = &l->arr[from];
	tmstring *dp = (*res)->arr;

	while( cnt!=0 ){
	    *dp++ = *sp++;
	    cnt--;
	}
    }
    (*res)->sz = ressz;
    l->sz -= ressz;
    for( ix=from; ix<l->sz; ix++ ){
	l->arr[ix] = l->arr[ix+ressz];
    }
    return l;
}

/**************************************************
 *    Miscellaneous routines                      *
 **************************************************/
/* Print allocation and freeing statistics to file 'f'. */
void stat_tm( FILE *f )
{

    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Append",
	newcnt_Append,
	frecnt_Append,
	((newcnt_Append==frecnt_Append)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Appendfile",
	newcnt_Appendfile,
	frecnt_Appendfile,
	((newcnt_Appendfile==frecnt_Appendfile)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"CCAlternatives",
	newcnt_CCAlternatives,
	frecnt_CCAlternatives,
	((newcnt_CCAlternatives==frecnt_CCAlternatives)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"CCFields",
	newcnt_CCFields,
	frecnt_CCFields,
	((newcnt_CCFields==frecnt_CCFields)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"CCSublist",
	newcnt_CCSublist,
	frecnt_CCSublist,
	((newcnt_CCSublist==frecnt_CCSublist)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"CCSuper",
	newcnt_CCSuper,
	frecnt_CCSuper,
	((newcnt_CCSuper==frecnt_CCSuper)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Call",
	newcnt_Call,
	frecnt_Call,
	((newcnt_Call==frecnt_Call)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Case",
	newcnt_Case,
	frecnt_Case,
	((newcnt_Case==frecnt_Case)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Default",
	newcnt_Default,
	frecnt_Default,
	((newcnt_Default==frecnt_Default)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"DeleteType",
	newcnt_DeleteType,
	frecnt_DeleteType,
	((newcnt_DeleteType==frecnt_DeleteType)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"DsAlias",
	newcnt_DsAlias,
	frecnt_DsAlias,
	((newcnt_DsAlias==frecnt_DsAlias)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"DsClass",
	newcnt_DsClass,
	frecnt_DsClass,
	((newcnt_DsClass==frecnt_DsClass)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"DsConstructor",
	newcnt_DsConstructor,
	frecnt_DsConstructor,
	((newcnt_DsConstructor==frecnt_DsConstructor)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"DsConstructorBase",
	newcnt_DsConstructorBase,
	frecnt_DsConstructorBase,
	((newcnt_DsConstructorBase==frecnt_DsConstructorBase)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"DsInclude",
	newcnt_DsInclude,
	frecnt_DsInclude,
	((newcnt_DsInclude==frecnt_DsInclude)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"DsTuple",
	newcnt_DsTuple,
	frecnt_DsTuple,
	((newcnt_DsTuple==frecnt_DsTuple)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Error",
	newcnt_Error,
	frecnt_Error,
	((newcnt_Error==frecnt_Error)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Exit",
	newcnt_Exit,
	frecnt_Exit,
	((newcnt_Exit==frecnt_Exit)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Field",
	newcnt_Field,
	frecnt_Field,
	((newcnt_Field==frecnt_Field)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"For",
	newcnt_For,
	frecnt_For,
	((newcnt_For==frecnt_For)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Foreach",
	newcnt_Foreach,
	frecnt_Foreach,
	((newcnt_Foreach==frecnt_Foreach)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"GlobalAppend",
	newcnt_GlobalAppend,
	frecnt_GlobalAppend,
	((newcnt_GlobalAppend==frecnt_GlobalAppend)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"GlobalSet",
	newcnt_GlobalSet,
	frecnt_GlobalSet,
	((newcnt_GlobalSet==frecnt_GlobalSet)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"GlobalSplit",
	newcnt_GlobalSplit,
	frecnt_GlobalSplit,
	((newcnt_GlobalSplit==frecnt_GlobalSplit)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"If",
	newcnt_If,
	frecnt_If,
	((newcnt_If==frecnt_If)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Include",
	newcnt_Include,
	frecnt_Include,
	((newcnt_Include==frecnt_Include)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Insert",
	newcnt_Insert,
	frecnt_Insert,
	((newcnt_Insert==frecnt_Insert)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Macro",
	newcnt_Macro,
	frecnt_Macro,
	((newcnt_Macro==frecnt_Macro)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Plain",
	newcnt_Plain,
	frecnt_Plain,
	((newcnt_Plain==frecnt_Plain)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Redirect",
	newcnt_Redirect,
	frecnt_Redirect,
	((newcnt_Redirect==frecnt_Redirect)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Rename",
	newcnt_Rename,
	frecnt_Rename,
	((newcnt_Rename==frecnt_Rename)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Return",
	newcnt_Return,
	frecnt_Return,
	((newcnt_Return==frecnt_Return)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Set",
	newcnt_Set,
	frecnt_Set,
	((newcnt_Set==frecnt_Set)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Split",
	newcnt_Split,
	frecnt_Split,
	((newcnt_Split==frecnt_Split)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Switch",
	newcnt_Switch,
	frecnt_Switch,
	((newcnt_Switch==frecnt_Switch)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Switchcase",
	newcnt_Switchcase,
	frecnt_Switchcase,
	((newcnt_Switchcase==frecnt_Switchcase)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"Type",
	newcnt_Type,
	frecnt_Type,
	((newcnt_Type==frecnt_Type)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"While",
	newcnt_While,
	frecnt_While,
	((newcnt_While==frecnt_While)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"alternative",
	newcnt_alternative,
	frecnt_alternative,
	((newcnt_alternative==frecnt_alternative)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"macro",
	newcnt_macro,
	frecnt_macro,
	((newcnt_macro==frecnt_macro)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"origin",
	newcnt_origin,
	frecnt_origin,
	((newcnt_origin==frecnt_origin)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"origsymbol",
	newcnt_origsymbol,
	frecnt_origsymbol,
	((newcnt_origsymbol==frecnt_origsymbol)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
	"variable",
	newcnt_variable,
	frecnt_variable,
	((newcnt_variable==frecnt_variable)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
        "Field_list",
	newcnt_Field_list,
	frecnt_Field_list,
	((newcnt_Field_list==frecnt_Field_list)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
        "Switchcase_list",
	newcnt_Switchcase_list,
	frecnt_Switchcase_list,
	((newcnt_Switchcase_list==frecnt_Switchcase_list)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
        "Type_list",
	newcnt_Type_list,
	frecnt_Type_list,
	((newcnt_Type_list==frecnt_Type_list)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
        "alternative_list",
	newcnt_alternative_list,
	frecnt_alternative_list,
	((newcnt_alternative_list==frecnt_alternative_list)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
        "classComponent_list",
	newcnt_classComponent_list,
	frecnt_classComponent_list,
	((newcnt_classComponent_list==frecnt_classComponent_list)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
        "ds_list",
	newcnt_ds_list,
	frecnt_ds_list,
	((newcnt_ds_list==frecnt_ds_list)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
        "macro_list",
	newcnt_macro_list,
	frecnt_macro_list,
	((newcnt_macro_list==frecnt_macro_list)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
        "tmstring_list",
	newcnt_tmstring_list,
	frecnt_tmstring_list,
	((newcnt_tmstring_list==frecnt_tmstring_list)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
        "tmsymbol_list",
	newcnt_tmsymbol_list,
	frecnt_tmsymbol_list,
	((newcnt_tmsymbol_list==frecnt_tmsymbol_list)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
        "tplelm_list",
	newcnt_tplelm_list,
	frecnt_tplelm_list,
	((newcnt_tplelm_list==frecnt_tplelm_list)? "": "<-")
    );
    fprintf(
	f,
	"%-20s: %6ld allocated, %6ld freed.%s\n",
        "variable_list",
	newcnt_variable_list,
	frecnt_variable_list,
	((newcnt_variable_list==frecnt_variable_list)? "": "<-")
    );
}

/* Return -1 if there is a structure that has freed more than allocated, or
 * else return 1 if there is a structure that has been freed less than
 * allocated, or else return 0.
 */
int get_balance_tm( void )
{
    /* Check for too many fre()s. */
    if( newcnt_Field_list<frecnt_Field_list ){
	return -1;
    }
    if( newcnt_Switchcase_list<frecnt_Switchcase_list ){
	return -1;
    }
    if( newcnt_Type_list<frecnt_Type_list ){
	return -1;
    }
    if( newcnt_alternative_list<frecnt_alternative_list ){
	return -1;
    }
    if( newcnt_classComponent_list<frecnt_classComponent_list ){
	return -1;
    }
    if( newcnt_ds_list<frecnt_ds_list ){
	return -1;
    }
    if( newcnt_macro_list<frecnt_macro_list ){
	return -1;
    }
    if( newcnt_tmstring_list<frecnt_tmstring_list ){
	return -1;
    }
    if( newcnt_tmsymbol_list<frecnt_tmsymbol_list ){
	return -1;
    }
    if( newcnt_tplelm_list<frecnt_tplelm_list ){
	return -1;
    }
    if( newcnt_variable_list<frecnt_variable_list ){
	return -1;
    }
    if( newcnt_Append<frecnt_Append ){
	return -1;
    }
    if( newcnt_Appendfile<frecnt_Appendfile ){
	return -1;
    }
    if( newcnt_CCAlternatives<frecnt_CCAlternatives ){
	return -1;
    }
    if( newcnt_CCFields<frecnt_CCFields ){
	return -1;
    }
    if( newcnt_CCSublist<frecnt_CCSublist ){
	return -1;
    }
    if( newcnt_CCSuper<frecnt_CCSuper ){
	return -1;
    }
    if( newcnt_Call<frecnt_Call ){
	return -1;
    }
    if( newcnt_Case<frecnt_Case ){
	return -1;
    }
    if( newcnt_Default<frecnt_Default ){
	return -1;
    }
    if( newcnt_DeleteType<frecnt_DeleteType ){
	return -1;
    }
    if( newcnt_DsAlias<frecnt_DsAlias ){
	return -1;
    }
    if( newcnt_DsClass<frecnt_DsClass ){
	return -1;
    }
    if( newcnt_DsConstructor<frecnt_DsConstructor ){
	return -1;
    }
    if( newcnt_DsConstructorBase<frecnt_DsConstructorBase ){
	return -1;
    }
    if( newcnt_DsInclude<frecnt_DsInclude ){
	return -1;
    }
    if( newcnt_DsTuple<frecnt_DsTuple ){
	return -1;
    }
    if( newcnt_Error<frecnt_Error ){
	return -1;
    }
    if( newcnt_Exit<frecnt_Exit ){
	return -1;
    }
    if( newcnt_Field<frecnt_Field ){
	return -1;
    }
    if( newcnt_For<frecnt_For ){
	return -1;
    }
    if( newcnt_Foreach<frecnt_Foreach ){
	return -1;
    }
    if( newcnt_GlobalAppend<frecnt_GlobalAppend ){
	return -1;
    }
    if( newcnt_GlobalSet<frecnt_GlobalSet ){
	return -1;
    }
    if( newcnt_GlobalSplit<frecnt_GlobalSplit ){
	return -1;
    }
    if( newcnt_If<frecnt_If ){
	return -1;
    }
    if( newcnt_Include<frecnt_Include ){
	return -1;
    }
    if( newcnt_Insert<frecnt_Insert ){
	return -1;
    }
    if( newcnt_Macro<frecnt_Macro ){
	return -1;
    }
    if( newcnt_Plain<frecnt_Plain ){
	return -1;
    }
    if( newcnt_Redirect<frecnt_Redirect ){
	return -1;
    }
    if( newcnt_Rename<frecnt_Rename ){
	return -1;
    }
    if( newcnt_Return<frecnt_Return ){
	return -1;
    }
    if( newcnt_Set<frecnt_Set ){
	return -1;
    }
    if( newcnt_Split<frecnt_Split ){
	return -1;
    }
    if( newcnt_Switch<frecnt_Switch ){
	return -1;
    }
    if( newcnt_Switchcase<frecnt_Switchcase ){
	return -1;
    }
    if( newcnt_Type<frecnt_Type ){
	return -1;
    }
    if( newcnt_While<frecnt_While ){
	return -1;
    }
    if( newcnt_alternative<frecnt_alternative ){
	return -1;
    }
    if( newcnt_macro<frecnt_macro ){
	return -1;
    }
    if( newcnt_origin<frecnt_origin ){
	return -1;
    }
    if( newcnt_origsymbol<frecnt_origsymbol ){
	return -1;
    }
    if( newcnt_variable<frecnt_variable ){
	return -1;
    }
    /* Check for too few free()s. */
    if( newcnt_Field_list>frecnt_Field_list ){
	return 1;
    }
    if( newcnt_Switchcase_list>frecnt_Switchcase_list ){
	return 1;
    }
    if( newcnt_Type_list>frecnt_Type_list ){
	return 1;
    }
    if( newcnt_alternative_list>frecnt_alternative_list ){
	return 1;
    }
    if( newcnt_classComponent_list>frecnt_classComponent_list ){
	return 1;
    }
    if( newcnt_ds_list>frecnt_ds_list ){
	return 1;
    }
    if( newcnt_macro_list>frecnt_macro_list ){
	return 1;
    }
    if( newcnt_tmstring_list>frecnt_tmstring_list ){
	return 1;
    }
    if( newcnt_tmsymbol_list>frecnt_tmsymbol_list ){
	return 1;
    }
    if( newcnt_tplelm_list>frecnt_tplelm_list ){
	return 1;
    }
    if( newcnt_variable_list>frecnt_variable_list ){
	return 1;
    }
    if( newcnt_Append>frecnt_Append ){
	return 1;
    }
    if( newcnt_Appendfile>frecnt_Appendfile ){
	return 1;
    }
    if( newcnt_CCAlternatives>frecnt_CCAlternatives ){
	return 1;
    }
    if( newcnt_CCFields>frecnt_CCFields ){
	return 1;
    }
    if( newcnt_CCSublist>frecnt_CCSublist ){
	return 1;
    }
    if( newcnt_CCSuper>frecnt_CCSuper ){
	return 1;
    }
    if( newcnt_Call>frecnt_Call ){
	return 1;
    }
    if( newcnt_Case>frecnt_Case ){
	return 1;
    }
    if( newcnt_Default>frecnt_Default ){
	return 1;
    }
    if( newcnt_DeleteType>frecnt_DeleteType ){
	return 1;
    }
    if( newcnt_DsAlias>frecnt_DsAlias ){
	return 1;
    }
    if( newcnt_DsClass>frecnt_DsClass ){
	return 1;
    }
    if( newcnt_DsConstructor>frecnt_DsConstructor ){
	return 1;
    }
    if( newcnt_DsConstructorBase>frecnt_DsConstructorBase ){
	return 1;
    }
    if( newcnt_DsInclude>frecnt_DsInclude ){
	return 1;
    }
    if( newcnt_DsTuple>frecnt_DsTuple ){
	return 1;
    }
    if( newcnt_Error>frecnt_Error ){
	return 1;
    }
    if( newcnt_Exit>frecnt_Exit ){
	return 1;
    }
    if( newcnt_Field>frecnt_Field ){
	return 1;
    }
    if( newcnt_For>frecnt_For ){
	return 1;
    }
    if( newcnt_Foreach>frecnt_Foreach ){
	return 1;
    }
    if( newcnt_GlobalAppend>frecnt_GlobalAppend ){
	return 1;
    }
    if( newcnt_GlobalSet>frecnt_GlobalSet ){
	return 1;
    }
    if( newcnt_GlobalSplit>frecnt_GlobalSplit ){
	return 1;
    }
    if( newcnt_If>frecnt_If ){
	return 1;
    }
    if( newcnt_Include>frecnt_Include ){
	return 1;
    }
    if( newcnt_Insert>frecnt_Insert ){
	return 1;
    }
    if( newcnt_Macro>frecnt_Macro ){
	return 1;
    }
    if( newcnt_Plain>frecnt_Plain ){
	return 1;
    }
    if( newcnt_Redirect>frecnt_Redirect ){
	return 1;
    }
    if( newcnt_Rename>frecnt_Rename ){
	return 1;
    }
    if( newcnt_Return>frecnt_Return ){
	return 1;
    }
    if( newcnt_Set>frecnt_Set ){
	return 1;
    }
    if( newcnt_Split>frecnt_Split ){
	return 1;
    }
    if( newcnt_Switch>frecnt_Switch ){
	return 1;
    }
    if( newcnt_Switchcase>frecnt_Switchcase ){
	return 1;
    }
    if( newcnt_Type>frecnt_Type ){
	return 1;
    }
    if( newcnt_While>frecnt_While ){
	return 1;
    }
    if( newcnt_alternative>frecnt_alternative ){
	return 1;
    }
    if( newcnt_macro>frecnt_macro ){
	return 1;
    }
    if( newcnt_origin>frecnt_origin ){
	return 1;
    }
    if( newcnt_origsymbol>frecnt_origsymbol ){
	return 1;
    }
    if( newcnt_variable>frecnt_variable ){
	return 1;
    }
    return 0;
}

/* ---- end of /Users/reeuwijk/lab/lib/tmc.ct ---- */
/* Code generation required 31 milliseconds. */
