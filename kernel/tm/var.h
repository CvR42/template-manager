/* File $Id$
 *
 * Extern routines for variable and macro management.
 */

extern void setmacro( const char *nm, const_origin org, const_tmstring_list pl, const_tplelm_list body );
extern /*@observer@*/ const_macro findmacro( const char *nm );
extern void setvar( const char *nm, const char *v );
extern void globalsetvar( const char *nm, const char *v );
extern void newvarctx( void );
extern void flushvar( void );
extern /*@observer@*/ const_tmstring getvar( const char *nm );
extern tmstring getretval( void );
extern /*@observer@*/ const char *match_macros( const char *pat, tmstring_list *matcnes );
extern /*@observer@*/ const char *match_vars( const char *pat, tmstring_list *matcnes );
extern void init_var( void );
extern void end_var( void );
