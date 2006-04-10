/* File: $Id$ */

/* Structure to describe debugging flags. */
typedef struct _cvr_db_flags {
    const char flagchar;	/* char to switch the flag on */
    tmbool *flagadr;		/* pointer to the flag */
    const char *flagdescr;	/* description string */
} dbflag;

#define dbflagNIL (dbflag *)0

extern void setdbflags( const char *s, const dbflag *flagtab, tmbool val );
extern void helpdbflags( FILE *f, const dbflag *flagtab );
