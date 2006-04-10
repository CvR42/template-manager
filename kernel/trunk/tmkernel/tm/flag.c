/* File: $Id$
 *
 * Handle debugging flags.
 */

#include <tmc.h>

#include "tmdefs.h"
#include "flag.h"

/* Given a character 'c' and a flag table 'flagtab',
   return a pointer to the entry of character 'c', or return
   dbflagNIL if not found.
 */
static const dbflag *finddbflag( int c, const dbflag *flagtab )
{
    const dbflag *p;

    p = flagtab;
    while( p->flagchar != '\0' ){
	if( p->flagchar == c ){
	    return p;
	}
	p++;
    }
    return dbflagNIL;
}

/* Give help information on debugging flags */
void helpdbflags( FILE *f, const dbflag *flagtab )
{
    const dbflag *p;

    fputs( "Debugging flags:\n", f );
    p = flagtab;
    while( p->flagchar != '\0' ){
	fprintf( f, " %c - %s.\n", p->flagchar, p->flagdescr );
	p++;
    }
    fputs( " . - all flags.\n", f );
}

/* Given a string 's' containing debug flags, a flag table 'flagtab' and
   a value 'val', look up all flags given in 's', and set the associated
   value to 'val'. The flag character '.' means that all flags must
   be set.
 */
void setdbflags( const char *s, const dbflag *flagtab, tmbool val )
{
    int c;
    const dbflag *e;

    while( *s != '\0' ){
	c = *s++;
	if( c == '.' ){
	    e = flagtab;
	    while( e->flagchar != '\0' ){
		*e->flagadr = val;
		e++;
	    }
	}
	else {
	    e = finddbflag( c, flagtab );
	    if( e == dbflagNIL ){
		fprintf( stderr, "Unknown debug flag: '%c'\n", c );
		exit( 1 );
	    }
	    *e->flagadr = val;
	}
    }
}
