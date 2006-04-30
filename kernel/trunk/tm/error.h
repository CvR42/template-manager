/* File: $Id$ */

extern void internal_error( const char *msg, ... ) ATTRIBUTE_PRINTF(1,2);
extern void origin_internal_error( const_origin org, const char *msg, ... ) ATTRIBUTE_PRINTF(2,3);
extern void origsymbol_internal_error( const_origsymbol s, const char *msg, ... ) ATTRIBUTE_PRINTF(2,3);

extern void error( const char *msg, ... ) ATTRIBUTE_PRINTF(1,2);
extern void fileline_error( const char *fnm, unsigned int lineno, const char *msg, ... ) ATTRIBUTE_PRINTF(3, 4);
extern void origin_error( const_origin s, const char *msg, ... ) ATTRIBUTE_PRINTF(2,3);
extern void origsymbol_error( const_origsymbol s, const char *msg, ... ) ATTRIBUTE_PRINTF(2,3);
extern void sys_error( int no, const char *msg, ... ) ATTRIBUTE_PRINTF(2,3);

extern void errcheck( void );
extern bool error_seen( void );
