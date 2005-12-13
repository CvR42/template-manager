/* File: $Id$
 *
 * Description of exported objects of tmstring.c.
 */

extern const char *scanword( const char *s, char **w );
extern void scan1par( const char *pl, char **p1 );
extern void cknopar( const char *s );
extern void cknumpar( const char *n );
extern char *newboolstr( bool b );
extern char *newintstr( int n );
extern char *newuintstr( tmuint n );
extern tmstring_list chopstring( const char *p );
extern tmstring sepstrings( const_tmstring_list sl, const char *sep );
extern tmstring flatstrings( const_tmstring_list sl );
extern bool isfalsestr( const_tmstring s );
extern bool istruestr( const_tmstring s );
tmstring mklistnm( const char *pre, const_tmstring tnm, const char *suff, const unsigned int level );
