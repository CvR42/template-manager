/* config.h.  Generated automatically by configure.  */
/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: config.h
 *
 * Some configuration constants.
 */
#define STRBUFSZ 1024    	/* Maximum size of a string */
#define FIRSTLOGNEWSZ 100	/* First table size. */
#define HASHBITS 6		/* Number of bits used in hashing. */
#define HASHSHIFT 2		/* Number of bits to skip in hashing key. */
#define TEXTGROWSTEP 40		/* The growth step of the text putc routine */

#define SYMHASHWIDTH 1024

/* #undef const */
#define STDC_HEADERS 1
#define HAVE_STRERROR 1
#define HAVE_MEMMOVE 1

#ifdef __GNUC__
#define __USE_FIXED_PROTOTYPES__
#endif

#include <string.h>
