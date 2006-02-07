/* File: $Id$
 *
 * Global variables.
 */

extern FILE *tracestream;
extern FILE *statstream;

extern tmstring tplfilename;
extern unsigned int tpllineno;
extern tmstring dsfilename;
extern FILE *dsfile;
extern unsigned int dslineno;
extern ds_list allds;

extern clock_t start_time;

/* debugging flags */
extern int fntracing;
extern int listing;
extern int maintr;
extern int prstat;
extern int sevaltr;
extern int vartr;
extern int lextr;
extern int noerrorline;
extern tmstring_list searchpath;
