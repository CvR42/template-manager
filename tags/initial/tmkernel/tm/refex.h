/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: refex.h
 *
 * file regular expression handling.
 */

extern char *ref_comp( const char *pat );
extern int ref_exec( const char *lp );
extern void ref_subs( const char *src, char *dst );
