/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* file: tmtrans.h
 * translation routines.
 */

extern tmstring alevalto( char **spi, const char sc );
extern void dotrans( const tplelm_list tpl, FILE *outfile );
extern void translate( FILE *infile, FILE *outfile );
