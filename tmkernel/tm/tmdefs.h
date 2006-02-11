/* File: $Id$
 *
 * Datastructures and other definitions of Tm: datastructure
 * and definition and manipulation routine generator.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined( GEMDOS ) || defined( __TOS__ )
#define PATHSEPSTR "\\"
#endif
#ifdef MSDOS
#define PATHSEPSTR "\\"
#endif

#ifndef PATHSEPSTR
#define PATHSEPSTR "/"
#endif

#ifndef __cplusplus
typedef int bool;
#endif

#define CHARNIL (char *)0

#define TRUE TMTRUE
#define FALSE TMFALSE

/* increment in dynamically growing string buffer size */
#define STRSTEP 20

/* size of local string manipulation buffers */
#define STRBUFSIZE 3000

/* size of buffer for integer string */
#define NUMBUFSIZE 40

/* size of file copy buffer. */
#define CPBUFSIZE 2000

/* The name of the variable wherein return values are stored.
 * This is not only ment to be funny: this name can not be used
 * by the user for a variable name.
 */
#define RETVALNAME "\r"

/* The names of the variables that represent the prefix and suffix
 * of list type names.
 */
#define LISTPRE "listpre"
#define LISTSUFF "listsuff"

/* Some character names */
#define OCBRAC '{'
#define CCBRAC '}'
#define ORBRAC '('
#define CRBRAC ')'
#define OSBRAC '['
#define CSBRAC ']'
#define VARCHAR '$'
#define LCOMCHAR '.'
#define DQUOTE '"'

#if __GNUC__
#define ATTRIBUTE_PRINTF(fmt,args) __attribute__((format(printf,fmt,args)))
#else
#define ATTRIBUTE_PRINTF(fmt,args)
#endif
