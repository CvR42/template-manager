/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File tmvar.h
 * extern routines for variable and macro management.
 */

extern void setmacro( const tmstring nm, const tmstring fnm, const tmstring_list pl, const tplelm_list body );
extern macro findmacro( const tmstring nm );
extern void setvar( const tmstring nm, const tmstring v );
extern void globalsetvar( const tmstring nm, const tmstring v );
extern void newvarctx( void );
extern void flushvar( void );
extern tmstring getvar( const tmstring nm );
extern tmstring getretval( void );
extern char *match_macros( const tmstring pat, tmstring_list *matcnes );
extern void init_var( void );
extern void end_var( void );
