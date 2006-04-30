/* File: $Id$
 *
 * Description of exported objects of tmstring.c.
 */

extern const char *scanword( const_origin org, const char *s, char **w );
extern void scan1par( const_origin org, const char *pl, char **p1 );
extern tmbool cknumpar( const_origin org, const char *n );
extern char *newboolstr( tmbool b );
extern char *newintstr( int n );
extern char *newuintstr( tmuint n );
extern tmstring_list chopstring( const_origin org, const char *p );
extern tmstring sepstrings( const_tmstring_list sl, const char *sep );
extern tmstring flatstrings( const_tmstring_list sl );
extern tmstring flatsymbols( const_tmsymbol_list sl );
extern tmbool isfalsestr( const_tmstring s );
extern tmbool istruestr( const_tmstring s );
tmstring mklistnm( const char *pre, const_tmstring tnm, const char *suff, const unsigned int level );
