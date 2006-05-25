/* File: $Id$
 *
 * File regular expression handling.
 */

extern /*@observer@*/ const char *ref_comp( const char *pat );
extern tmbool ref_exec( const char *lp );
extern void ref_subs( const char *src, char *dst );
