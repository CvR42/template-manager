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

/* Requirement analysis took 460 milliseconds. */
/*** WARNING: THIS IS GENERATED CODE. ***/

/* ---- start of /usr/local/lib/tmc.ct ---- */

/* Routines for 'tm'.

   template file:      /usr/local/lib/tmc.ct
   datastructure file: tm.ds
   tm version:         36
   tm kernel version:  2.0-beta7
 */

#ifndef FIRSTROOM
#define FIRSTROOM 0
#endif

/* Counters for allocation and freeing. */
static long newcnt_alternative_list = 0, frecnt_alternative_list = 0;
static long newcnt_classComponent_list = 0, frecnt_classComponent_list = 0;
static long newcnt_ds_list = 0, frecnt_ds_list = 0;
static long newcnt_field_list = 0, frecnt_field_list = 0;
static long newcnt_macro_list = 0, frecnt_macro_list = 0;
static long newcnt_switchcase_list = 0, frecnt_switchcase_list = 0;
static long newcnt_tmstring_list = 0, frecnt_tmstring_list = 0;
static long newcnt_tplelm_list = 0, frecnt_tplelm_list = 0;
static long newcnt_var_list = 0, frecnt_var_list = 0;
static long newcnt_Append = 0, frecnt_Append = 0;
static long newcnt_Appendfile = 0, frecnt_Appendfile = 0;
static long newcnt_CCAlternatives = 0, frecnt_CCAlternatives = 0;
static long newcnt_CCFields = 0, frecnt_CCFields = 0;
static long newcnt_CCSublist = 0, frecnt_CCSublist = 0;
static long newcnt_CCSuper = 0, frecnt_CCSuper = 0;
static long newcnt_Call = 0, frecnt_Call = 0;
static long newcnt_Case = 0, frecnt_Case = 0;
static long newcnt_Default = 0, frecnt_Default = 0;
static long newcnt_DsClass = 0, frecnt_DsClass = 0;
static long newcnt_DsConstructor = 0, frecnt_DsConstructor = 0;
static long newcnt_DsConstructorBase = 0, frecnt_DsConstructorBase = 0;
static long newcnt_DsTuple = 0, frecnt_DsTuple = 0;
static long newcnt_Error = 0, frecnt_Error = 0;
static long newcnt_Exit = 0, frecnt_Exit = 0;
static long newcnt_Foreach = 0, frecnt_Foreach = 0;
static long newcnt_GlobalAppend = 0, frecnt_GlobalAppend = 0;
static long newcnt_GlobalSet = 0, frecnt_GlobalSet = 0;
static long newcnt_If = 0, frecnt_If = 0;
static long newcnt_Include = 0, frecnt_Include = 0;
static long newcnt_Insert = 0, frecnt_Insert = 0;
static long newcnt_Macro = 0, frecnt_Macro = 0;
static long newcnt_Plain = 0, frecnt_Plain = 0;
static long newcnt_Redirect = 0, frecnt_Redirect = 0;
static long newcnt_Rename = 0, frecnt_Rename = 0;
static long newcnt_Return = 0, frecnt_Return = 0;
static long newcnt_Set = 0, frecnt_Set = 0;
static long newcnt_Switch = 0, frecnt_Switch = 0;
static long newcnt_While = 0, frecnt_While = 0;
static long newcnt_alternative = 0, frecnt_alternative = 0;
static long newcnt_field = 0, frecnt_field = 0;
static long newcnt_macro = 0, frecnt_macro = 0;
static long newcnt_switchcase = 0, frecnt_switchcase = 0;
static long newcnt_var = 0, frecnt_var = 0;


static char tm_srcfile[] = __FILE__;

#ifndef FATAL
#define FATAL(msg) tm_fatal(tm_srcfile,__LINE__,msg)
#endif

/* Error strings. */
static char tm_nilptr[] = "NIL pointer";

#ifndef FATALTAG
#define FATALTAG(tag) tm_badtag(tm_srcfile,__LINE__,(int) tag)
#endif

/**************************************************
 *    set array room routines                     *
 **************************************************/

/* Announce that you will need room for 'rm' elements in
 *  field_list 'l'.
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
 *  tmstring_list 'l'.
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
 *  tplelm_list 'l'.
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
 *  switchcase_list 'l'.
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
 *  alternative_list 'l'.
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
 *  classComponent_list 'l'.
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
 *  ds_list 'l'.
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
 *  var_list 'l'.
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
 *  macro_list 'l'.
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
#undef new_Append
#define new_Append(lno,line) real_new_Append(lno,line,_f,_l)
#undef new_Appendfile
#define new_Appendfile(lno,fname,body) real_new_Appendfile(lno,fname,body,_f,_l)
#undef new_CCAlternatives
#define new_CCAlternatives(alternatives) real_new_CCAlternatives(alternatives,_f,_l)
#undef new_CCFields
#define new_CCFields(fields) real_new_CCFields(fields,_f,_l)
#undef new_CCSublist
#define new_CCSublist(components) real_new_CCSublist(components,_f,_l)
#undef new_CCSuper
#define new_CCSuper(super) real_new_CCSuper(super,_f,_l)
#undef new_Call
#define new_Call(lno,line) real_new_Call(lno,line,_f,_l)
#undef new_Case
#define new_Case(lno,val) real_new_Case(lno,val,_f,_l)
#undef new_Default
#define new_Default(lno) real_new_Default(lno,_f,_l)
#undef new_DsClass
#define new_DsClass(name,inherits,fields,virtual) real_new_DsClass(name,inherits,fields,virtual,_f,_l)
#undef new_DsConstructor
#define new_DsConstructor(name,inherits,fields) real_new_DsConstructor(name,inherits,fields,_f,_l)
#undef new_DsConstructorBase
#define new_DsConstructorBase(name,inherits,constructors) real_new_DsConstructorBase(name,inherits,constructors,_f,_l)
#undef new_DsTuple
#define new_DsTuple(name,inherits,fields) real_new_DsTuple(name,inherits,fields,_f,_l)
#undef new_Error
#define new_Error(lno,str) real_new_Error(lno,str,_f,_l)
#undef new_Exit
#define new_Exit(lno,str) real_new_Exit(lno,str,_f,_l)
#undef new_Foreach
#define new_Foreach(lno,felist,body) real_new_Foreach(lno,felist,body,_f,_l)
#undef new_GlobalAppend
#define new_GlobalAppend(lno,line) real_new_GlobalAppend(lno,line,_f,_l)
#undef new_GlobalSet
#define new_GlobalSet(lno,line) real_new_GlobalSet(lno,line,_f,_l)
#undef new_If
#define new_If(lno,cond,ifthen,ifelse) real_new_If(lno,cond,ifthen,ifelse,_f,_l)
#undef new_Include
#define new_Include(lno,fname) real_new_Include(lno,fname,_f,_l)
#undef new_Insert
#define new_Insert(lno,fname) real_new_Insert(lno,fname,_f,_l)
#undef new_Macro
#define new_Macro(lno,formals,body) real_new_Macro(lno,formals,body,_f,_l)
#undef new_Plain
#define new_Plain(lno,line) real_new_Plain(lno,line,_f,_l)
#undef new_Redirect
#define new_Redirect(lno,fname,body) real_new_Redirect(lno,fname,body,_f,_l)
#undef new_Rename
#define new_Rename(lno,line) real_new_Rename(lno,line,_f,_l)
#undef new_Return
#define new_Return(lno,retval) real_new_Return(lno,retval,_f,_l)
#undef new_Set
#define new_Set(lno,line) real_new_Set(lno,line,_f,_l)
#undef new_Switch
#define new_Switch(lno,val,cases,deflt) real_new_Switch(lno,val,cases,deflt,_f,_l)
#undef new_While
#define new_While(lno,cond,body) real_new_While(lno,cond,body,_f,_l)
#undef new_alternative
#define new_alternative(label,component) real_new_alternative(label,component,_f,_l)
#undef new_field
#define new_field(level,name,type) real_new_field(level,name,type,_f,_l)
#undef new_macro
#define new_macro(lvl,name,orgfile,fpl,body) real_new_macro(lvl,name,orgfile,fpl,body,_f,_l)
#undef new_switchcase
#define new_switchcase(cases,action) real_new_switchcase(cases,action,_f,_l)
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

    nw = TM_MALLOC( alternative_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (alternative *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( alternative *, FIRSTROOM*sizeof(alternative) );
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
#if FIRSTROOM==0
    nw->arr = (classComponent *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( classComponent *, FIRSTROOM*sizeof(classComponent) );
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
#if FIRSTROOM==0
    nw->arr = (ds *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( ds *, FIRSTROOM*sizeof(ds) );
    nw->room = FIRSTROOM;
#endif
    newcnt_ds_list++;
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

    nw = TM_MALLOC( field_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (field *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( field *, FIRSTROOM*sizeof(field) );
    nw->room = FIRSTROOM;
#endif
    newcnt_field_list++;
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
#if FIRSTROOM==0
    nw->arr = (macro *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( macro *, FIRSTROOM*sizeof(macro) );
    nw->room = FIRSTROOM;
#endif
    newcnt_macro_list++;
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

    nw = TM_MALLOC( switchcase_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (switchcase *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( switchcase *, FIRSTROOM*sizeof(switchcase) );
    nw->room = FIRSTROOM;
#endif
    newcnt_switchcase_list++;
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
#if FIRSTROOM==0
    nw->arr = (tmstring *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( tmstring *, FIRSTROOM*sizeof(tmstring) );
    nw->room = FIRSTROOM;
#endif
    newcnt_tmstring_list++;
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
#if FIRSTROOM==0
    nw->arr = (tplelm *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( tplelm *, FIRSTROOM*sizeof(tplelm) );
    nw->room = FIRSTROOM;
#endif
    newcnt_tplelm_list++;
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

    nw = TM_MALLOC( var_list, sizeof(*nw) );
    nw->sz = 0;
#if FIRSTROOM==0
    nw->arr = (var *) 0;
    nw->room = 0;
#else
    nw->arr = TM_MALLOC( var *, FIRSTROOM*sizeof(var) );
    nw->room = FIRSTROOM;
#endif
    newcnt_var_list++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Append'. */
#ifdef LOGNEW
Append real_new_Append( int p_lno, tmstring p_line, const char *_f, const int _l )
#else
Append new_Append( int p_lno, tmstring p_line )
#endif
{
    Append nw;

    nw = TM_MALLOC( Append, sizeof(*nw) );
    nw->tag = TAGAppend;
    nw->lno = p_lno;
    nw->line = p_line;
    newcnt_Append++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Appendfile'. */
#ifdef LOGNEW
Appendfile real_new_Appendfile( int p_lno, tmstring p_fname, tplelm_list p_body, const char *_f, const int _l )
#else
Appendfile new_Appendfile( int p_lno, tmstring p_fname, tplelm_list p_body )
#endif
{
    Appendfile nw;

    nw = TM_MALLOC( Appendfile, sizeof(*nw) );
    nw->tag = TAGAppendfile;
    nw->lno = p_lno;
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
CCFields real_new_CCFields( field_list p_fields, const char *_f, const int _l )
#else
CCFields new_CCFields( field_list p_fields )
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
CCSuper real_new_CCSuper( tmstring p_super, const char *_f, const int _l )
#else
CCSuper new_CCSuper( tmstring p_super )
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
Call real_new_Call( int p_lno, tmstring p_line, const char *_f, const int _l )
#else
Call new_Call( int p_lno, tmstring p_line )
#endif
{
    Call nw;

    nw = TM_MALLOC( Call, sizeof(*nw) );
    nw->tag = TAGCall;
    nw->lno = p_lno;
    nw->line = p_line;
    newcnt_Call++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Case'. */
#ifdef LOGNEW
Case real_new_Case( int p_lno, tmstring p_val, const char *_f, const int _l )
#else
Case new_Case( int p_lno, tmstring p_val )
#endif
{
    Case nw;

    nw = TM_MALLOC( Case, sizeof(*nw) );
    nw->tag = TAGCase;
    nw->lno = p_lno;
    nw->val = p_val;
    newcnt_Case++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Default'. */
#ifdef LOGNEW
Default real_new_Default( int p_lno, const char *_f, const int _l )
#else
Default new_Default( int p_lno )
#endif
{
    Default nw;

    nw = TM_MALLOC( Default, sizeof(*nw) );
    nw->tag = TAGDefault;
    nw->lno = p_lno;
    newcnt_Default++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'DsClass'. */
#ifdef LOGNEW
DsClass real_new_DsClass( tmstring p_name, tmstring_list p_inherits, field_list p_fields, tmbool p_virtual, const char *_f, const int _l )
#else
DsClass new_DsClass( tmstring p_name, tmstring_list p_inherits, field_list p_fields, tmbool p_virtual )
#endif
{
    DsClass nw;

    nw = TM_MALLOC( DsClass, sizeof(*nw) );
    nw->tag = TAGDsClass;
    nw->name = p_name;
    nw->inherits = p_inherits;
    nw->fields = p_fields;
    nw->virtual = p_virtual;
    newcnt_DsClass++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'DsConstructor'. */
#ifdef LOGNEW
DsConstructor real_new_DsConstructor( tmstring p_name, tmstring_list p_inherits, field_list p_fields, const char *_f, const int _l )
#else
DsConstructor new_DsConstructor( tmstring p_name, tmstring_list p_inherits, field_list p_fields )
#endif
{
    DsConstructor nw;

    nw = TM_MALLOC( DsConstructor, sizeof(*nw) );
    nw->tag = TAGDsConstructor;
    nw->name = p_name;
    nw->inherits = p_inherits;
    nw->fields = p_fields;
    newcnt_DsConstructor++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'DsConstructorBase'. */
#ifdef LOGNEW
DsConstructorBase real_new_DsConstructorBase( tmstring p_name, tmstring_list p_inherits, tmstring_list p_constructors, const char *_f, const int _l )
#else
DsConstructorBase new_DsConstructorBase( tmstring p_name, tmstring_list p_inherits, tmstring_list p_constructors )
#endif
{
    DsConstructorBase nw;

    nw = TM_MALLOC( DsConstructorBase, sizeof(*nw) );
    nw->tag = TAGDsConstructorBase;
    nw->name = p_name;
    nw->inherits = p_inherits;
    nw->constructors = p_constructors;
    newcnt_DsConstructorBase++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'DsTuple'. */
#ifdef LOGNEW
DsTuple real_new_DsTuple( tmstring p_name, tmstring_list p_inherits, field_list p_fields, const char *_f, const int _l )
#else
DsTuple new_DsTuple( tmstring p_name, tmstring_list p_inherits, field_list p_fields )
#endif
{
    DsTuple nw;

    nw = TM_MALLOC( DsTuple, sizeof(*nw) );
    nw->tag = TAGDsTuple;
    nw->name = p_name;
    nw->inherits = p_inherits;
    nw->fields = p_fields;
    newcnt_DsTuple++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Error'. */
#ifdef LOGNEW
Error real_new_Error( int p_lno, tmstring p_str, const char *_f, const int _l )
#else
Error new_Error( int p_lno, tmstring p_str )
#endif
{
    Error nw;

    nw = TM_MALLOC( Error, sizeof(*nw) );
    nw->tag = TAGError;
    nw->lno = p_lno;
    nw->str = p_str;
    newcnt_Error++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Exit'. */
#ifdef LOGNEW
Exit real_new_Exit( int p_lno, tmstring p_str, const char *_f, const int _l )
#else
Exit new_Exit( int p_lno, tmstring p_str )
#endif
{
    Exit nw;

    nw = TM_MALLOC( Exit, sizeof(*nw) );
    nw->tag = TAGExit;
    nw->lno = p_lno;
    nw->str = p_str;
    newcnt_Exit++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Foreach'. */
#ifdef LOGNEW
Foreach real_new_Foreach( int p_lno, tmstring p_felist, tplelm_list p_body, const char *_f, const int _l )
#else
Foreach new_Foreach( int p_lno, tmstring p_felist, tplelm_list p_body )
#endif
{
    Foreach nw;

    nw = TM_MALLOC( Foreach, sizeof(*nw) );
    nw->tag = TAGForeach;
    nw->lno = p_lno;
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
GlobalAppend real_new_GlobalAppend( int p_lno, tmstring p_line, const char *_f, const int _l )
#else
GlobalAppend new_GlobalAppend( int p_lno, tmstring p_line )
#endif
{
    GlobalAppend nw;

    nw = TM_MALLOC( GlobalAppend, sizeof(*nw) );
    nw->tag = TAGGlobalAppend;
    nw->lno = p_lno;
    nw->line = p_line;
    newcnt_GlobalAppend++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'GlobalSet'. */
#ifdef LOGNEW
GlobalSet real_new_GlobalSet( int p_lno, tmstring p_line, const char *_f, const int _l )
#else
GlobalSet new_GlobalSet( int p_lno, tmstring p_line )
#endif
{
    GlobalSet nw;

    nw = TM_MALLOC( GlobalSet, sizeof(*nw) );
    nw->tag = TAGGlobalSet;
    nw->lno = p_lno;
    nw->line = p_line;
    newcnt_GlobalSet++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'If'. */
#ifdef LOGNEW
If real_new_If( int p_lno, tmstring p_cond, tplelm_list p_ifthen, tplelm_list p_ifelse, const char *_f, const int _l )
#else
If new_If( int p_lno, tmstring p_cond, tplelm_list p_ifthen, tplelm_list p_ifelse )
#endif
{
    If nw;

    nw = TM_MALLOC( If, sizeof(*nw) );
    nw->tag = TAGIf;
    nw->lno = p_lno;
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
Include real_new_Include( int p_lno, tmstring p_fname, const char *_f, const int _l )
#else
Include new_Include( int p_lno, tmstring p_fname )
#endif
{
    Include nw;

    nw = TM_MALLOC( Include, sizeof(*nw) );
    nw->tag = TAGInclude;
    nw->lno = p_lno;
    nw->fname = p_fname;
    newcnt_Include++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Insert'. */
#ifdef LOGNEW
Insert real_new_Insert( int p_lno, tmstring p_fname, const char *_f, const int _l )
#else
Insert new_Insert( int p_lno, tmstring p_fname )
#endif
{
    Insert nw;

    nw = TM_MALLOC( Insert, sizeof(*nw) );
    nw->tag = TAGInsert;
    nw->lno = p_lno;
    nw->fname = p_fname;
    newcnt_Insert++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Macro'. */
#ifdef LOGNEW
Macro real_new_Macro( int p_lno, tmstring p_formals, tplelm_list p_body, const char *_f, const int _l )
#else
Macro new_Macro( int p_lno, tmstring p_formals, tplelm_list p_body )
#endif
{
    Macro nw;

    nw = TM_MALLOC( Macro, sizeof(*nw) );
    nw->tag = TAGMacro;
    nw->lno = p_lno;
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
Plain real_new_Plain( int p_lno, tmstring p_line, const char *_f, const int _l )
#else
Plain new_Plain( int p_lno, tmstring p_line )
#endif
{
    Plain nw;

    nw = TM_MALLOC( Plain, sizeof(*nw) );
    nw->tag = TAGPlain;
    nw->lno = p_lno;
    nw->line = p_line;
    newcnt_Plain++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Redirect'. */
#ifdef LOGNEW
Redirect real_new_Redirect( int p_lno, tmstring p_fname, tplelm_list p_body, const char *_f, const int _l )
#else
Redirect new_Redirect( int p_lno, tmstring p_fname, tplelm_list p_body )
#endif
{
    Redirect nw;

    nw = TM_MALLOC( Redirect, sizeof(*nw) );
    nw->tag = TAGRedirect;
    nw->lno = p_lno;
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
Rename real_new_Rename( int p_lno, tmstring p_line, const char *_f, const int _l )
#else
Rename new_Rename( int p_lno, tmstring p_line )
#endif
{
    Rename nw;

    nw = TM_MALLOC( Rename, sizeof(*nw) );
    nw->tag = TAGRename;
    nw->lno = p_lno;
    nw->line = p_line;
    newcnt_Rename++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Return'. */
#ifdef LOGNEW
Return real_new_Return( int p_lno, tmstring p_retval, const char *_f, const int _l )
#else
Return new_Return( int p_lno, tmstring p_retval )
#endif
{
    Return nw;

    nw = TM_MALLOC( Return, sizeof(*nw) );
    nw->tag = TAGReturn;
    nw->lno = p_lno;
    nw->retval = p_retval;
    newcnt_Return++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Set'. */
#ifdef LOGNEW
Set real_new_Set( int p_lno, tmstring p_line, const char *_f, const int _l )
#else
Set new_Set( int p_lno, tmstring p_line )
#endif
{
    Set nw;

    nw = TM_MALLOC( Set, sizeof(*nw) );
    nw->tag = TAGSet;
    nw->lno = p_lno;
    nw->line = p_line;
    newcnt_Set++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'Switch'. */
#ifdef LOGNEW
Switch real_new_Switch( int p_lno, tmstring p_val, switchcase_list p_cases, tplelm_list p_deflt, const char *_f, const int _l )
#else
Switch new_Switch( int p_lno, tmstring p_val, switchcase_list p_cases, tplelm_list p_deflt )
#endif
{
    Switch nw;

    nw = TM_MALLOC( Switch, sizeof(*nw) );
    nw->tag = TAGSwitch;
    nw->lno = p_lno;
    nw->val = p_val;
    nw->cases = p_cases;
    nw->deflt = p_deflt;
    newcnt_Switch++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of class 'While'. */
#ifdef LOGNEW
While real_new_While( int p_lno, tmstring p_cond, tplelm_list p_body, const char *_f, const int _l )
#else
While new_While( int p_lno, tmstring p_cond, tplelm_list p_body )
#endif
{
    While nw;

    nw = TM_MALLOC( While, sizeof(*nw) );
    nw->tag = TAGWhile;
    nw->lno = p_lno;
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
alternative real_new_alternative( tmstring p_label, classComponent p_component, const char *_f, const int _l )
#else
alternative new_alternative( tmstring p_label, classComponent p_component )
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

/* Allocate a new instance of tuple 'field'. */
#ifdef LOGNEW
field real_new_field( int p_level, tmstring p_name, tmstring p_type, const char *_f, const int _l )
#else
field new_field( int p_level, tmstring p_name, tmstring p_type )
#endif
{
    field nw;

    nw = TM_MALLOC( field, sizeof(*nw) );
    nw->level = p_level;
    nw->name = p_name;
    nw->type = p_type;
    newcnt_field++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of tuple 'macro'. */
#ifdef LOGNEW
macro real_new_macro( uint p_lvl, tmstring p_name, tmstring p_orgfile, tmstring_list p_fpl, tplelm_list p_body, const char *_f, const int _l )
#else
macro new_macro( uint p_lvl, tmstring p_name, tmstring p_orgfile, tmstring_list p_fpl, tplelm_list p_body )
#endif
{
    macro nw;

    nw = TM_MALLOC( macro, sizeof(*nw) );
    nw->lvl = p_lvl;
    nw->name = p_name;
    nw->orgfile = p_orgfile;
    nw->fpl = p_fpl;
    nw->body = p_body;
    newcnt_macro++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of tuple 'switchcase'. */
#ifdef LOGNEW
switchcase real_new_switchcase( tmstring p_cases, tplelm_list p_action, const char *_f, const int _l )
#else
switchcase new_switchcase( tmstring p_cases, tplelm_list p_action )
#endif
{
    switchcase nw;

    nw = TM_MALLOC( switchcase, sizeof(*nw) );
    nw->cases = p_cases;
    nw->action = p_action;
    newcnt_switchcase++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/* Allocate a new instance of tuple 'var'. */
#ifdef LOGNEW
var real_new_var( uint p_lvl, tmstring p_name, tmstring p_val, const char *_f, const int _l )
#else
var new_var( uint p_lvl, tmstring p_name, tmstring p_val )
#endif
{
    var nw;

    nw = TM_MALLOC( var, sizeof(*nw) );
    nw->lvl = p_lvl;
    nw->name = p_name;
    nw->val = p_val;
    newcnt_var++;
#ifdef LOGNEW
    nw->lognew_id = tm_new_logid( _f, _l );
#endif
    return nw;
}

/**************************************************
 *    Freeing routines                            *
 **************************************************/

/* Free an element 'e' of tuple type 'switchcase'. */
static void fre_switchcase( switchcase e )
{
    if( e == switchcaseNIL ){
	return;
    }
    frecnt_switchcase++;
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

/* Free an element 'e' of tuple type 'var'. */
static void fre_var( var e )
{
    if( e == varNIL ){
	return;
    }
    frecnt_var++;
#ifdef LOGNEW
    tm_fre_logid( e->lognew_id );
#endif
    TM_FREE( e );
}

/* Free an element 'e' of tuple type 'field'. */
static void fre_field( field e )
{
    if( e == fieldNIL ){
	return;
    }
    frecnt_field++;
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
    if( l->room!=0 ){
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
    if( l->room!=0 ){
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
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
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
    frecnt_field_list++;
    if( l->room!=0 ){
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
    if( l->room!=0 ){
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
    if( l->room!=0 ){
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
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
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
    frecnt_var_list++;
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
    TM_FREE( l );
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
    frecnt_switchcase_list++;
    if( l->room!=0 ){
	TM_FREE( l->arr );
    }
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
static void rfre_Append( Append );
static void rfre_Appendfile( Appendfile );
static void rfre_CCAlternatives( CCAlternatives );
static void rfre_CCFields( CCFields );
static void rfre_CCSublist( CCSublist );
static void rfre_CCSuper( CCSuper );
static void rfre_Call( Call );
static void rfre_Case( Case );
static void rfre_Default( Default );
static void rfre_DsClass( DsClass );
static void rfre_DsConstructor( DsConstructor );
static void rfre_DsConstructorBase( DsConstructorBase );
static void rfre_DsTuple( DsTuple );
static void rfre_Error( Error );
static void rfre_Exit( Exit );
static void rfre_Foreach( Foreach );
static void rfre_GlobalAppend( GlobalAppend );
static void rfre_GlobalSet( GlobalSet );
static void rfre_If( If );
static void rfre_Include( Include );
static void rfre_Insert( Insert );
static void rfre_Macro( Macro );
static void rfre_Plain( Plain );
static void rfre_Redirect( Redirect );
static void rfre_Rename( Rename );
static void rfre_Return( Return );
static void rfre_Set( Set );
static void rfre_Switch( Switch );
static void rfre_While( While );
static void rfre_switchcase( switchcase );
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

/* Recursively free an element 'e' of class type 'ds'
 * and all elements in it.
 */
void rfre_ds( ds e )
{
    if( e == dsNIL ){
	return;
    }
    switch( e->tag ){
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

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of tuple type 'macro'
 * and all elements in it.
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

/* Recursively free an element 'e' of class type 'tplelm'
 * and all elements in it.
 */
void rfre_tplelm( tplelm e )
{
    if( e == tplelmNIL ){
	return;
    }
    switch( e->tag ){
	case TAGPlain:
	    rfre_Plain( (Plain) e );
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

	case TAGRename:
	    rfre_Rename( (Rename) e );
	    break;

	case TAGGlobalSet:
	    rfre_GlobalSet( (GlobalSet) e );
	    break;

	case TAGAppend:
	    rfre_Append( (Append) e );
	    break;

	case TAGGlobalAppend:
	    rfre_GlobalAppend( (GlobalAppend) e );
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

/* Recursively free an element 'e' of tuple type 'alternative'
 * and all elements in it.
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

/* Recursively free an element 'e' of tuple type 'field'
 * and all elements in it.
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

/* Recursively free an element 'e' of tuple type 'var'
 * and all elements in it.
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
	    rfre_tmstring( e->fname );
	    rfre_tplelm_list( e->body );
	    fre_Appendfile( e );
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
	    rfre_field_list( e->fields );
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
	    rfre_tmstring( e->super );
	    fre_CCSuper( e );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
	    fre_Default( e );
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
	    rfre_tmstring( e->name );
	    rfre_tmstring_list( e->inherits );
	    rfre_field_list( e->fields );
	    rfre_tmbool( e->virtual );
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
	    rfre_tmstring( e->name );
	    rfre_tmstring_list( e->inherits );
	    rfre_field_list( e->fields );
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
	    rfre_tmstring( e->name );
	    rfre_tmstring_list( e->inherits );
	    rfre_tmstring_list( e->constructors );
	    fre_DsConstructorBase( e );
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
	    rfre_tmstring( e->name );
	    rfre_tmstring_list( e->inherits );
	    rfre_field_list( e->fields );
	    fre_DsTuple( e );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
	    rfre_tmstring( e->str );
	    fre_Exit( e );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
	    rfre_tmstring( e->line );
	    fre_GlobalSet( e );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
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
	    rfre_int( e->lno );
	    rfre_tmstring( e->line );
	    fre_Set( e );
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
	    rfre_int( e->lno );
	    rfre_tmstring( e->val );
	    rfre_switchcase_list( e->cases );
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
	    rfre_int( e->lno );
	    rfre_tmstring( e->cond );
	    rfre_tplelm_list( e->body );
	    fre_While( e );
	    break;

	default:
	    FATALTAG( (int) e->tag );
    }
}

/* Recursively free an element 'e' of tuple type 'switchcase'
 * and all elements in it.
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
static void print_DsClass( TMPRINTSTATE *st, const DsClass );
static void print_DsConstructor( TMPRINTSTATE *st, const DsConstructor );
static void print_DsConstructorBase( TMPRINTSTATE *st, const DsConstructorBase );
static void print_DsTuple( TMPRINTSTATE *st, const DsTuple );
/* Print an element 't' of class type 'ds'
 * using print optimizer.
 */
static void print_ds( TMPRINTSTATE *st, const ds t )
{
    if( t == dsNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsConstructorBase:
	    print_DsConstructorBase( st, (DsConstructorBase) t );
	    break;

	case TAGDsTuple:
	    print_DsTuple( st, (DsTuple) t );
	    break;

	case TAGDsClass:
	    print_DsClass( st, (DsClass) t );
	    break;

	case TAGDsConstructor:
	    print_DsConstructor( st, (DsConstructor) t );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of tuple type 'field'
 * using print optimizer.
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

/* Print an element 't' of class type 'DsClass'
 * using print optimizer.
 */
static void print_DsClass( TMPRINTSTATE *st, const DsClass t )
{
    if( t == DsClassNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsClass:
	    tm_opencons( st );
	    tm_printword( st, "DsClass" );
	    print_tmstring( st, t->name );
	    print_tmstring_list( st, t->inherits );
	    print_field_list( st, t->fields );
	    print_tmbool( st, t->virtual );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'DsConstructor'
 * using print optimizer.
 */
static void print_DsConstructor( TMPRINTSTATE *st, const DsConstructor t )
{
    if( t == DsConstructorNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsConstructor:
	    tm_opencons( st );
	    tm_printword( st, "DsConstructor" );
	    print_tmstring( st, t->name );
	    print_tmstring_list( st, t->inherits );
	    print_field_list( st, t->fields );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'DsConstructorBase'
 * using print optimizer.
 */
static void print_DsConstructorBase( TMPRINTSTATE *st, const DsConstructorBase t )
{
    if( t == DsConstructorBaseNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsConstructorBase:
	    tm_opencons( st );
	    tm_printword( st, "DsConstructorBase" );
	    print_tmstring( st, t->name );
	    print_tmstring_list( st, t->inherits );
	    print_tmstring_list( st, t->constructors );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
}

/* Print an element 't' of class type 'DsTuple'
 * using print optimizer.
 */
static void print_DsTuple( TMPRINTSTATE *st, const DsTuple t )
{
    if( t == DsTupleNIL ){
	tm_printword( st, "@" );
	return;
    }
    switch( t->tag ){
	case TAGDsTuple:
	    tm_opencons( st );
	    tm_printword( st, "DsTuple" );
	    print_tmstring( st, t->name );
	    print_tmstring_list( st, t->inherits );
	    print_field_list( st, t->fields );
	    tm_closecons( st );
	    break;

	default:
	    FATALTAG( t->tag );
    }
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
#define rdup_Append(e) real_rdup_Append(e,_f,_l)
#define rdup_Appendfile(e) real_rdup_Appendfile(e,_f,_l)
#define rdup_Call(e) real_rdup_Call(e,_f,_l)
#define rdup_Case(e) real_rdup_Case(e,_f,_l)
#define rdup_Default(e) real_rdup_Default(e,_f,_l)
#define rdup_DsClass(e) real_rdup_DsClass(e,_f,_l)
#define rdup_DsConstructor(e) real_rdup_DsConstructor(e,_f,_l)
#define rdup_DsConstructorBase(e) real_rdup_DsConstructorBase(e,_f,_l)
#define rdup_DsTuple(e) real_rdup_DsTuple(e,_f,_l)
#define rdup_Error(e) real_rdup_Error(e,_f,_l)
#define rdup_Exit(e) real_rdup_Exit(e,_f,_l)
#define rdup_Foreach(e) real_rdup_Foreach(e,_f,_l)
#define rdup_GlobalAppend(e) real_rdup_GlobalAppend(e,_f,_l)
#define rdup_GlobalSet(e) real_rdup_GlobalSet(e,_f,_l)
#define rdup_If(e) real_rdup_If(e,_f,_l)
#define rdup_Include(e) real_rdup_Include(e,_f,_l)
#define rdup_Insert(e) real_rdup_Insert(e,_f,_l)
#define rdup_Macro(e) real_rdup_Macro(e,_f,_l)
#define rdup_Plain(e) real_rdup_Plain(e,_f,_l)
#define rdup_Redirect(e) real_rdup_Redirect(e,_f,_l)
#define rdup_Rename(e) real_rdup_Rename(e,_f,_l)
#define rdup_Return(e) real_rdup_Return(e,_f,_l)
#define rdup_Set(e) real_rdup_Set(e,_f,_l)
#define rdup_Switch(e) real_rdup_Switch(e,_f,_l)
#define rdup_While(e) real_rdup_While(e,_f,_l)
#define rdup_switchcase(e) real_rdup_switchcase(e,_f,_l)
#undef rdup_field_list
#define rdup_field_list(l) real_rdup_field_list(l,_f,_l)
#undef rdup_tmstring_list
#define rdup_tmstring_list(l) real_rdup_tmstring_list(l,_f,_l)
#undef rdup_tplelm_list
#define rdup_tplelm_list(l) real_rdup_tplelm_list(l,_f,_l)
#define rdup_switchcase_list(l) real_rdup_switchcase_list(l,_f,_l)
static switchcase_list real_rdup_switchcase_list( const switchcase_list, const char *, const int );
static field real_rdup_field( const field, const char *, const int );
static Append real_rdup_Append( const Append, const char *, const int );
static Appendfile real_rdup_Appendfile( const Appendfile, const char *, const int );
static Call real_rdup_Call( const Call, const char *, const int );
static Case real_rdup_Case( const Case, const char *, const int );
static Default real_rdup_Default( const Default, const char *, const int );
static DsClass real_rdup_DsClass( const DsClass, const char *, const int );
static DsConstructor real_rdup_DsConstructor( const DsConstructor, const char *, const int );
static DsConstructorBase real_rdup_DsConstructorBase( const DsConstructorBase, const char *, const int );
static DsTuple real_rdup_DsTuple( const DsTuple, const char *, const int );
static Error real_rdup_Error( const Error, const char *, const int );
static Exit real_rdup_Exit( const Exit, const char *, const int );
static Foreach real_rdup_Foreach( const Foreach, const char *, const int );
static GlobalAppend real_rdup_GlobalAppend( const GlobalAppend, const char *, const int );
static GlobalSet real_rdup_GlobalSet( const GlobalSet, const char *, const int );
static If real_rdup_If( const If, const char *, const int );
static Include real_rdup_Include( const Include, const char *, const int );
static Insert real_rdup_Insert( const Insert, const char *, const int );
static Macro real_rdup_Macro( const Macro, const char *, const int );
static Plain real_rdup_Plain( const Plain, const char *, const int );
static Redirect real_rdup_Redirect( const Redirect, const char *, const int );
static Rename real_rdup_Rename( const Rename, const char *, const int );
static Return real_rdup_Return( const Return, const char *, const int );
static Set real_rdup_Set( const Set, const char *, const int );
static Switch real_rdup_Switch( const Switch, const char *, const int );
static While real_rdup_While( const While, const char *, const int );
static switchcase real_rdup_switchcase( const switchcase, const char *, const int );
#else
static switchcase_list rdup_switchcase_list( const switchcase_list );
static field rdup_field( const field );
static Append rdup_Append( const Append );
static Appendfile rdup_Appendfile( const Appendfile );
static Call rdup_Call( const Call );
static Case rdup_Case( const Case );
static Default rdup_Default( const Default );
static DsClass rdup_DsClass( const DsClass );
static DsConstructor rdup_DsConstructor( const DsConstructor );
static DsConstructorBase rdup_DsConstructorBase( const DsConstructorBase );
static DsTuple rdup_DsTuple( const DsTuple );
static Error rdup_Error( const Error );
static Exit rdup_Exit( const Exit );
static Foreach rdup_Foreach( const Foreach );
static GlobalAppend rdup_GlobalAppend( const GlobalAppend );
static GlobalSet rdup_GlobalSet( const GlobalSet );
static If rdup_If( const If );
static Include rdup_Include( const Include );
static Insert rdup_Insert( const Insert );
static Macro rdup_Macro( const Macro );
static Plain rdup_Plain( const Plain );
static Redirect rdup_Redirect( const Redirect );
static Rename rdup_Rename( const Rename );
static Return rdup_Return( const Return );
static Set rdup_Set( const Set );
static Switch rdup_Switch( const Switch );
static While rdup_While( const While );
static switchcase rdup_switchcase( const switchcase );
#endif
/* Recursively duplicate a class ds element 'e'. */
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
	    return (ds) rdup_DsConstructorBase( (DsConstructorBase) e );

	case TAGDsTuple:
	    return (ds) rdup_DsTuple( (DsTuple) e );

	case TAGDsClass:
	    return (ds) rdup_DsClass( (DsClass) e );

	case TAGDsConstructor:
	    return (ds) rdup_DsConstructor( (DsConstructor) e );

	default:
	    FATALTAG( e->tag );
    }
    return dsNIL;
}

/* Recursively duplicate a class tplelm element 'e'. */
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
	    return (tplelm) rdup_Plain( (Plain) e );

	case TAGForeach:
	    return (tplelm) rdup_Foreach( (Foreach) e );

	case TAGWhile:
	    return (tplelm) rdup_While( (While) e );

	case TAGIf:
	    return (tplelm) rdup_If( (If) e );

	case TAGSwitch:
	    return (tplelm) rdup_Switch( (Switch) e );

	case TAGSet:
	    return (tplelm) rdup_Set( (Set) e );

	case TAGRename:
	    return (tplelm) rdup_Rename( (Rename) e );

	case TAGGlobalSet:
	    return (tplelm) rdup_GlobalSet( (GlobalSet) e );

	case TAGAppend:
	    return (tplelm) rdup_Append( (Append) e );

	case TAGGlobalAppend:
	    return (tplelm) rdup_GlobalAppend( (GlobalAppend) e );

	case TAGError:
	    return (tplelm) rdup_Error( (Error) e );

	case TAGExit:
	    return (tplelm) rdup_Exit( (Exit) e );

	case TAGRedirect:
	    return (tplelm) rdup_Redirect( (Redirect) e );

	case TAGAppendfile:
	    return (tplelm) rdup_Appendfile( (Appendfile) e );

	case TAGMacro:
	    return (tplelm) rdup_Macro( (Macro) e );

	case TAGCall:
	    return (tplelm) rdup_Call( (Call) e );

	case TAGReturn:
	    return (tplelm) rdup_Return( (Return) e );

	case TAGInclude:
	    return (tplelm) rdup_Include( (Include) e );

	case TAGInsert:
	    return (tplelm) rdup_Insert( (Insert) e );

	case TAGCase:
	    return (tplelm) rdup_Case( (Case) e );

	case TAGDefault:
	    return (tplelm) rdup_Default( (Default) e );

	default:
	    FATALTAG( e->tag );
    }
    return tplelmNIL;
}

/* Recursively duplicate a tuple field element 'e'. */
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

/* Recursively duplicate a class Append element 'e'. */
#ifdef LOGNEW
static Append real_rdup_Append( const Append e, const char *_f, const int _l )
#else
static Append rdup_Append( const Append e )
#endif
{
    int i_lno;
    tmstring i_line;

    if( e == AppendNIL ){
	return AppendNIL;
    }
    i_lno = rdup_int( e->lno );
    i_line = rdup_tmstring( e->line );
    return new_Append( i_lno, i_line );
}

/* Recursively duplicate a class Appendfile element 'e'. */
#ifdef LOGNEW
static Appendfile real_rdup_Appendfile( const Appendfile e, const char *_f, const int _l )
#else
static Appendfile rdup_Appendfile( const Appendfile e )
#endif
{
    int i_lno;
    tmstring i_fname;
    tplelm_list i_body;

    if( e == AppendfileNIL ){
	return AppendfileNIL;
    }
    i_lno = rdup_int( e->lno );
    i_fname = rdup_tmstring( e->fname );
    i_body = rdup_tplelm_list( e->body );
    return new_Appendfile( i_lno, i_fname, i_body );
}

/* Recursively duplicate a class Call element 'e'. */
#ifdef LOGNEW
static Call real_rdup_Call( const Call e, const char *_f, const int _l )
#else
static Call rdup_Call( const Call e )
#endif
{
    int i_lno;
    tmstring i_line;

    if( e == CallNIL ){
	return CallNIL;
    }
    i_lno = rdup_int( e->lno );
    i_line = rdup_tmstring( e->line );
    return new_Call( i_lno, i_line );
}

/* Recursively duplicate a class Case element 'e'. */
#ifdef LOGNEW
static Case real_rdup_Case( const Case e, const char *_f, const int _l )
#else
static Case rdup_Case( const Case e )
#endif
{
    int i_lno;
    tmstring i_val;

    if( e == CaseNIL ){
	return CaseNIL;
    }
    i_lno = rdup_int( e->lno );
    i_val = rdup_tmstring( e->val );
    return new_Case( i_lno, i_val );
}

/* Recursively duplicate a class Default element 'e'. */
#ifdef LOGNEW
static Default real_rdup_Default( const Default e, const char *_f, const int _l )
#else
static Default rdup_Default( const Default e )
#endif
{
    int i_lno;

    if( e == DefaultNIL ){
	return DefaultNIL;
    }
    i_lno = rdup_int( e->lno );
    return new_Default( i_lno );
}

/* Recursively duplicate a class DsClass element 'e'. */
#ifdef LOGNEW
static DsClass real_rdup_DsClass( const DsClass e, const char *_f, const int _l )
#else
static DsClass rdup_DsClass( const DsClass e )
#endif
{
    tmstring i_name;
    tmstring_list i_inherits;
    field_list i_fields;
    tmbool i_virtual;

    if( e == DsClassNIL ){
	return DsClassNIL;
    }
    i_name = rdup_tmstring( e->name );
    i_inherits = rdup_tmstring_list( e->inherits );
    i_fields = rdup_field_list( e->fields );
    i_virtual = rdup_tmbool( e->virtual );
    return new_DsClass( i_name, i_inherits, i_fields, i_virtual );
}

/* Recursively duplicate a class DsConstructor element 'e'. */
#ifdef LOGNEW
static DsConstructor real_rdup_DsConstructor( const DsConstructor e, const char *_f, const int _l )
#else
static DsConstructor rdup_DsConstructor( const DsConstructor e )
#endif
{
    tmstring i_name;
    tmstring_list i_inherits;
    field_list i_fields;

    if( e == DsConstructorNIL ){
	return DsConstructorNIL;
    }
    i_name = rdup_tmstring( e->name );
    i_inherits = rdup_tmstring_list( e->inherits );
    i_fields = rdup_field_list( e->fields );
    return new_DsConstructor( i_name, i_inherits, i_fields );
}

/* Recursively duplicate a class DsConstructorBase element 'e'. */
#ifdef LOGNEW
static DsConstructorBase real_rdup_DsConstructorBase( const DsConstructorBase e, const char *_f, const int _l )
#else
static DsConstructorBase rdup_DsConstructorBase( const DsConstructorBase e )
#endif
{
    tmstring i_name;
    tmstring_list i_inherits;
    tmstring_list i_constructors;

    if( e == DsConstructorBaseNIL ){
	return DsConstructorBaseNIL;
    }
    i_name = rdup_tmstring( e->name );
    i_inherits = rdup_tmstring_list( e->inherits );
    i_constructors = rdup_tmstring_list( e->constructors );
    return new_DsConstructorBase( i_name, i_inherits, i_constructors );
}

/* Recursively duplicate a class DsTuple element 'e'. */
#ifdef LOGNEW
static DsTuple real_rdup_DsTuple( const DsTuple e, const char *_f, const int _l )
#else
static DsTuple rdup_DsTuple( const DsTuple e )
#endif
{
    tmstring i_name;
    tmstring_list i_inherits;
    field_list i_fields;

    if( e == DsTupleNIL ){
	return DsTupleNIL;
    }
    i_name = rdup_tmstring( e->name );
    i_inherits = rdup_tmstring_list( e->inherits );
    i_fields = rdup_field_list( e->fields );
    return new_DsTuple( i_name, i_inherits, i_fields );
}

/* Recursively duplicate a class Error element 'e'. */
#ifdef LOGNEW
static Error real_rdup_Error( const Error e, const char *_f, const int _l )
#else
static Error rdup_Error( const Error e )
#endif
{
    int i_lno;
    tmstring i_str;

    if( e == ErrorNIL ){
	return ErrorNIL;
    }
    i_lno = rdup_int( e->lno );
    i_str = rdup_tmstring( e->str );
    return new_Error( i_lno, i_str );
}

/* Recursively duplicate a class Exit element 'e'. */
#ifdef LOGNEW
static Exit real_rdup_Exit( const Exit e, const char *_f, const int _l )
#else
static Exit rdup_Exit( const Exit e )
#endif
{
    int i_lno;
    tmstring i_str;

    if( e == ExitNIL ){
	return ExitNIL;
    }
    i_lno = rdup_int( e->lno );
    i_str = rdup_tmstring( e->str );
    return new_Exit( i_lno, i_str );
}

/* Recursively duplicate a class Foreach element 'e'. */
#ifdef LOGNEW
static Foreach real_rdup_Foreach( const Foreach e, const char *_f, const int _l )
#else
static Foreach rdup_Foreach( const Foreach e )
#endif
{
    int i_lno;
    tmstring i_felist;
    tplelm_list i_body;

    if( e == ForeachNIL ){
	return ForeachNIL;
    }
    i_lno = rdup_int( e->lno );
    i_felist = rdup_tmstring( e->felist );
    i_body = rdup_tplelm_list( e->body );
    return new_Foreach( i_lno, i_felist, i_body );
}

/* Recursively duplicate a class GlobalAppend element 'e'. */
#ifdef LOGNEW
static GlobalAppend real_rdup_GlobalAppend( const GlobalAppend e, const char *_f, const int _l )
#else
static GlobalAppend rdup_GlobalAppend( const GlobalAppend e )
#endif
{
    int i_lno;
    tmstring i_line;

    if( e == GlobalAppendNIL ){
	return GlobalAppendNIL;
    }
    i_lno = rdup_int( e->lno );
    i_line = rdup_tmstring( e->line );
    return new_GlobalAppend( i_lno, i_line );
}

/* Recursively duplicate a class GlobalSet element 'e'. */
#ifdef LOGNEW
static GlobalSet real_rdup_GlobalSet( const GlobalSet e, const char *_f, const int _l )
#else
static GlobalSet rdup_GlobalSet( const GlobalSet e )
#endif
{
    int i_lno;
    tmstring i_line;

    if( e == GlobalSetNIL ){
	return GlobalSetNIL;
    }
    i_lno = rdup_int( e->lno );
    i_line = rdup_tmstring( e->line );
    return new_GlobalSet( i_lno, i_line );
}

/* Recursively duplicate a class If element 'e'. */
#ifdef LOGNEW
static If real_rdup_If( const If e, const char *_f, const int _l )
#else
static If rdup_If( const If e )
#endif
{
    int i_lno;
    tmstring i_cond;
    tplelm_list i_ifthen;
    tplelm_list i_ifelse;

    if( e == IfNIL ){
	return IfNIL;
    }
    i_lno = rdup_int( e->lno );
    i_cond = rdup_tmstring( e->cond );
    i_ifthen = rdup_tplelm_list( e->ifthen );
    i_ifelse = rdup_tplelm_list( e->ifelse );
    return new_If( i_lno, i_cond, i_ifthen, i_ifelse );
}

/* Recursively duplicate a class Include element 'e'. */
#ifdef LOGNEW
static Include real_rdup_Include( const Include e, const char *_f, const int _l )
#else
static Include rdup_Include( const Include e )
#endif
{
    int i_lno;
    tmstring i_fname;

    if( e == IncludeNIL ){
	return IncludeNIL;
    }
    i_lno = rdup_int( e->lno );
    i_fname = rdup_tmstring( e->fname );
    return new_Include( i_lno, i_fname );
}

/* Recursively duplicate a class Insert element 'e'. */
#ifdef LOGNEW
static Insert real_rdup_Insert( const Insert e, const char *_f, const int _l )
#else
static Insert rdup_Insert( const Insert e )
#endif
{
    int i_lno;
    tmstring i_fname;

    if( e == InsertNIL ){
	return InsertNIL;
    }
    i_lno = rdup_int( e->lno );
    i_fname = rdup_tmstring( e->fname );
    return new_Insert( i_lno, i_fname );
}

/* Recursively duplicate a class Macro element 'e'. */
#ifdef LOGNEW
static Macro real_rdup_Macro( const Macro e, const char *_f, const int _l )
#else
static Macro rdup_Macro( const Macro e )
#endif
{
    int i_lno;
    tmstring i_formals;
    tplelm_list i_body;

    if( e == MacroNIL ){
	return MacroNIL;
    }
    i_lno = rdup_int( e->lno );
    i_formals = rdup_tmstring( e->formals );
    i_body = rdup_tplelm_list( e->body );
    return new_Macro( i_lno, i_formals, i_body );
}

/* Recursively duplicate a class Plain element 'e'. */
#ifdef LOGNEW
static Plain real_rdup_Plain( const Plain e, const char *_f, const int _l )
#else
static Plain rdup_Plain( const Plain e )
#endif
{
    int i_lno;
    tmstring i_line;

    if( e == PlainNIL ){
	return PlainNIL;
    }
    i_lno = rdup_int( e->lno );
    i_line = rdup_tmstring( e->line );
    return new_Plain( i_lno, i_line );
}

/* Recursively duplicate a class Redirect element 'e'. */
#ifdef LOGNEW
static Redirect real_rdup_Redirect( const Redirect e, const char *_f, const int _l )
#else
static Redirect rdup_Redirect( const Redirect e )
#endif
{
    int i_lno;
    tmstring i_fname;
    tplelm_list i_body;

    if( e == RedirectNIL ){
	return RedirectNIL;
    }
    i_lno = rdup_int( e->lno );
    i_fname = rdup_tmstring( e->fname );
    i_body = rdup_tplelm_list( e->body );
    return new_Redirect( i_lno, i_fname, i_body );
}

/* Recursively duplicate a class Rename element 'e'. */
#ifdef LOGNEW
static Rename real_rdup_Rename( const Rename e, const char *_f, const int _l )
#else
static Rename rdup_Rename( const Rename e )
#endif
{
    int i_lno;
    tmstring i_line;

    if( e == RenameNIL ){
	return RenameNIL;
    }
    i_lno = rdup_int( e->lno );
    i_line = rdup_tmstring( e->line );
    return new_Rename( i_lno, i_line );
}

/* Recursively duplicate a class Return element 'e'. */
#ifdef LOGNEW
static Return real_rdup_Return( const Return e, const char *_f, const int _l )
#else
static Return rdup_Return( const Return e )
#endif
{
    int i_lno;
    tmstring i_retval;

    if( e == ReturnNIL ){
	return ReturnNIL;
    }
    i_lno = rdup_int( e->lno );
    i_retval = rdup_tmstring( e->retval );
    return new_Return( i_lno, i_retval );
}

/* Recursively duplicate a class Set element 'e'. */
#ifdef LOGNEW
static Set real_rdup_Set( const Set e, const char *_f, const int _l )
#else
static Set rdup_Set( const Set e )
#endif
{
    int i_lno;
    tmstring i_line;

    if( e == SetNIL ){
	return SetNIL;
    }
    i_lno = rdup_int( e->lno );
    i_line = rdup_tmstring( e->line );
    return new_Set( i_lno, i_line );
}

/* Recursively duplicate a class Switch element 'e'. */
#ifdef LOGNEW
static Switch real_rdup_Switch( const Switch e, const char *_f, const int _l )
#else
static Switch rdup_Switch( const Switch e )
#endif
{
    int i_lno;
    tmstring i_val;
    switchcase_list i_cases;
    tplelm_list i_deflt;

    if( e == SwitchNIL ){
	return SwitchNIL;
    }
    i_lno = rdup_int( e->lno );
    i_val = rdup_tmstring( e->val );
    i_cases = rdup_switchcase_list( e->cases );
    i_deflt = rdup_tplelm_list( e->deflt );
    return new_Switch( i_lno, i_val, i_cases, i_deflt );
}

/* Recursively duplicate a class While element 'e'. */
#ifdef LOGNEW
static While real_rdup_While( const While e, const char *_f, const int _l )
#else
static While rdup_While( const While e )
#endif
{
    int i_lno;
    tmstring i_cond;
    tplelm_list i_body;

    if( e == WhileNIL ){
	return WhileNIL;
    }
    i_lno = rdup_int( e->lno );
    i_cond = rdup_tmstring( e->cond );
    i_body = rdup_tplelm_list( e->body );
    return new_While( i_lno, i_cond, i_body );
}

/* Recursively duplicate a tuple switchcase element 'e'. */
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
/* Print allocation and freeing statistics to file 'f'. */
void stat_tm( FILE *f )
{
    const char tm_allocfreed[] = "%-20s: %6ld allocated, %6ld freed.%s\n";

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
	"Appendfile",
	newcnt_Appendfile,
	frecnt_Appendfile,
	((newcnt_Appendfile==frecnt_Appendfile)? "": "<-")
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
	"CCFields",
	newcnt_CCFields,
	frecnt_CCFields,
	((newcnt_CCFields==frecnt_CCFields)? "": "<-")
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
	"CCSuper",
	newcnt_CCSuper,
	frecnt_CCSuper,
	((newcnt_CCSuper==frecnt_CCSuper)? "": "<-")
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
	"Foreach",
	newcnt_Foreach,
	frecnt_Foreach,
	((newcnt_Foreach==frecnt_Foreach)? "": "<-")
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
	"GlobalSet",
	newcnt_GlobalSet,
	frecnt_GlobalSet,
	((newcnt_GlobalSet==frecnt_GlobalSet)? "": "<-")
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
	"Include",
	newcnt_Include,
	frecnt_Include,
	((newcnt_Include==frecnt_Include)? "": "<-")
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
	"Macro",
	newcnt_Macro,
	frecnt_Macro,
	((newcnt_Macro==frecnt_Macro)? "": "<-")
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
	"Redirect",
	newcnt_Redirect,
	frecnt_Redirect,
	((newcnt_Redirect==frecnt_Redirect)? "": "<-")
    );
    fprintf(
	f,
	tm_allocfreed,
	"Rename",
	newcnt_Rename,
	frecnt_Rename,
	((newcnt_Rename==frecnt_Rename)? "": "<-")
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
	"Set",
	newcnt_Set,
	frecnt_Set,
	((newcnt_Set==frecnt_Set)? "": "<-")
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
	"While",
	newcnt_While,
	frecnt_While,
	((newcnt_While==frecnt_While)? "": "<-")
    );
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
}

/* Return -1 if there is a structure that has freed more than allocated, or
 * else return 1 if there is a structure that has been freed less than
 * allocated, or else return 0.
 */
int get_balance_tm( void )
{
    /* Check for too many fre()s. */
    if( newcnt_alternative_list<frecnt_alternative_list ){
	return -1;
    }
    if( newcnt_classComponent_list<frecnt_classComponent_list ){
	return -1;
    }
    if( newcnt_ds_list<frecnt_ds_list ){
	return -1;
    }
    if( newcnt_field_list<frecnt_field_list ){
	return -1;
    }
    if( newcnt_macro_list<frecnt_macro_list ){
	return -1;
    }
    if( newcnt_switchcase_list<frecnt_switchcase_list ){
	return -1;
    }
    if( newcnt_tmstring_list<frecnt_tmstring_list ){
	return -1;
    }
    if( newcnt_tplelm_list<frecnt_tplelm_list ){
	return -1;
    }
    if( newcnt_var_list<frecnt_var_list ){
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
    if( newcnt_DsClass<frecnt_DsClass ){
	return -1;
    }
    if( newcnt_DsConstructor<frecnt_DsConstructor ){
	return -1;
    }
    if( newcnt_DsConstructorBase<frecnt_DsConstructorBase ){
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
    if( newcnt_Foreach<frecnt_Foreach ){
	return -1;
    }
    if( newcnt_GlobalAppend<frecnt_GlobalAppend ){
	return -1;
    }
    if( newcnt_GlobalSet<frecnt_GlobalSet ){
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
    if( newcnt_Switch<frecnt_Switch ){
	return -1;
    }
    if( newcnt_While<frecnt_While ){
	return -1;
    }
    if( newcnt_alternative<frecnt_alternative ){
	return -1;
    }
    if( newcnt_field<frecnt_field ){
	return -1;
    }
    if( newcnt_macro<frecnt_macro ){
	return -1;
    }
    if( newcnt_switchcase<frecnt_switchcase ){
	return -1;
    }
    if( newcnt_var<frecnt_var ){
	return -1;
    }
    /* Check for too few free()s. */
    if( newcnt_alternative_list>frecnt_alternative_list ){
	return 1;
    }
    if( newcnt_classComponent_list>frecnt_classComponent_list ){
	return 1;
    }
    if( newcnt_ds_list>frecnt_ds_list ){
	return 1;
    }
    if( newcnt_field_list>frecnt_field_list ){
	return 1;
    }
    if( newcnt_macro_list>frecnt_macro_list ){
	return 1;
    }
    if( newcnt_switchcase_list>frecnt_switchcase_list ){
	return 1;
    }
    if( newcnt_tmstring_list>frecnt_tmstring_list ){
	return 1;
    }
    if( newcnt_tplelm_list>frecnt_tplelm_list ){
	return 1;
    }
    if( newcnt_var_list>frecnt_var_list ){
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
    if( newcnt_DsClass>frecnt_DsClass ){
	return 1;
    }
    if( newcnt_DsConstructor>frecnt_DsConstructor ){
	return 1;
    }
    if( newcnt_DsConstructorBase>frecnt_DsConstructorBase ){
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
    if( newcnt_Foreach>frecnt_Foreach ){
	return 1;
    }
    if( newcnt_GlobalAppend>frecnt_GlobalAppend ){
	return 1;
    }
    if( newcnt_GlobalSet>frecnt_GlobalSet ){
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
    if( newcnt_Switch>frecnt_Switch ){
	return 1;
    }
    if( newcnt_While>frecnt_While ){
	return 1;
    }
    if( newcnt_alternative>frecnt_alternative ){
	return 1;
    }
    if( newcnt_field>frecnt_field ){
	return 1;
    }
    if( newcnt_macro>frecnt_macro ){
	return 1;
    }
    if( newcnt_switchcase>frecnt_switchcase ){
	return 1;
    }
    if( newcnt_var>frecnt_var ){
	return 1;
    }
    return 0;
}

/* ---- end of /usr/local/lib/tmc.ct ---- */
/* Code generation required 800 milliseconds. */
