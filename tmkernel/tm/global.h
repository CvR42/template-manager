/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: tmglobal.h
 * Global variables.
 */

extern FILE *tracestream;
extern FILE *statstream;

extern char *tplfilename;
extern int tpllineno;
extern char *dsfilename;
extern FILE *dsfile;
extern int dslineno;
extern ds_list allds;

/* debugging flags */
extern int fntr;
extern int listing;
extern int maintr;
extern int prstat;
extern int sevaltr;
extern int vartr;
extern int lextr;
extern int noerrorline;
extern tmstring_list searchpath;
