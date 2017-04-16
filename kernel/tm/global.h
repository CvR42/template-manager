/* File: $Id$
 *
 * Global variables.
 */

extern FILE *tracestream;
extern FILE *statstream;

/*@only@*/ extern tmstring tplfilename;
/*@only@*/ extern tmstring dsfilename;
/*@only@*/ extern ds_list allds;

extern clock_t start_time;

/* debugging flags */
extern tmbool fntracing;
extern tmbool listing;
extern tmbool maintr;
extern tmbool prstat;
extern tmbool sevaltr;
extern tmbool vartr;
extern tmbool noerrorline;
extern tmstring_list searchpath;
