/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: error.h
   Description of exported objects of error.c
 */

extern int errno;

#define ERRARGLEN 80       /* max length of argument arrays below */
extern char errpos[];      /* describes position of the error */
extern char errarg[];      /* contains an argument to the error message */

extern void init_error( void );
extern void error( const char *msg );
extern void fatal( const char *msg );
extern void sys_error( int no );
extern void line_error( const char *msg );
extern void docrash( const char *file, int line, const char *msg );
extern void errcheck( void );

#define crash(n) docrash(__FILE__, __LINE__,n)
