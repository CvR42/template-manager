/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: refex.c
 *
 * File-style regular expression pattern matching and replacement
 *
 *
 * Allowed regular expressions:
 *
 *      char    matches itself, unless it is a special
 *              character (metachar): . \ [ ] * + ^ $
 *
 *      ?       matches any character.
 *
 *      \       matches the character following it, except
 *		when followed by a digit 1 to 9. (see below)
 *		It is used as an escape character for all
 *		other meta-characters, and itself. When used
 *		in a set, it is treated as an ordinary
 *		character.
 *
 *      [set]   matches one of the characters in the set.
 *              If the first character in the set is "^",
 *              it matches a character NOT in the set. A
 *              shorthand S-E is used to specify a set of
 *              characters S upto E, inclusive. The special
 *              characters "]" and "-" have no special
 *              meaning if they appear as the first chars
 *              in the set.
 *              examples:        match:
 *
 *                      [a-z]    any lowercase alpha
 *
 *                      [^]-]    any char except ] and -
 *
 *                      [^A-Z]   any char except uppercase
 *                               alpha
 *
 *                      [a-zA-Z] any alpha
 *
 *      *       matches the longest possible span of zero or more
 *              arbitrary characters.
 *
 *      (pat)   a regular expression enclosed in brackets matches what
 *              form matches. The enclosure
 *              creates a set of tags, used for pattern substution.
 *              The tagged forms are numbered starting from 1.
 */

#include "config.h"
#include <stdio.h>
#include "tmdefs.h"
#include "refex.h"
#include <tmc.h>

#define MAXDFA 1024 /* Maximal size of the DFA. */
#define MAXTAG 10   /* Maximal number of tagged patterns. */

#define DFA_OK 1
#define DFA_BAD 0

/* The dfa opcodes. */
typedef enum en_dfacode {
    PAT_END,
    PAT_CHAR,
    PAT_ANY,
    PAT_INSET,
    PAT_NOTINSET,
    PAT_BEGINSPAN,
    PAT_ENDSPAN,
    PAT_ANYSPAN
} dfacode;

#define MAXCHR	128
#define CHRBIT	8
#define BITBLK	MAXCHR/CHRBIT
#define BLKIND	0170
#define BITIND	07

/* Forward declaration. */
static const char *pmatch( const char *lp, const char *ap );

static int  tagstk[MAXTAG];             /* subpat tag stack */
static char dfa[MAXDFA];		/* the deterministic finite automaton */
static int sta = DFA_BAD;               /* status of lastpat */
static const char *bopat[MAXTAG];
static const char *eopat[MAXTAG];
static char bittab[BITBLK];		/* bit table for PAT_INSET */

static void chset( const int c )
{
    bittab[((c)&BLKIND)>>3] |= 1<<((c)&BITIND);
}

/* Given a pattern string 'pat', compile it into a DFA in the fixed
 * array dfa. Return an error message, or NULL if all went as planned.
 */
const char *ref_comp( const char *pat )
{
    const char *p;         /* pointer into the pattern.   */
    char *mp = dfa;        /* pointer into the dfa */
    int tagi = 0;          /* tag stack index   */
    int tagc = 1;          /* actual tag count  */
    int n;
    int c1;
    int c2;

    if( pat == NULL || pat[0] == '\0' ){
	if( sta == DFA_OK ){
	    return NULL;
	}
	else {
	    dfa[0] = PAT_END;
	    return "No previous regular expression";
	}
    }
    sta = DFA_BAD;
    for( p = pat; *p != '\0'; p++ ){
	switch( *p ){
	    case '?':               /* match any char..  */
		*mp++ =  PAT_ANY;
		break;

	    case '[':               /* match char class..*/
		if( *++p == '^') {
		    *mp++ =  PAT_NOTINSET;
		    p++;
		}
		else {
		    *mp++ =  PAT_INSET;
		}

		if( *p == '-' ){    /* real dash */
		    chset( *p++ );
		}
		if( *p == ']' ){    /* real brac */
		    chset( *p++ );
		}
		while (*p && *p != ']' ){
		    if( *p == '-' && *(p+1) && *(p+1) != ']' ){
			p++;
			c1 = *(p-2) + 1;
			c2 = *p++;
			while (c1 <= c2 ){
			    chset( c1++ );
			}
		    }
		    else {
			chset( *p++ );
		    }
		}
		if( !*p ){
		    dfa[0] = PAT_END;
		    return "Missing ]";
		}
		for (n = 0; n < BITBLK; bittab[n++] = (char) 0 ){
		    *mp++ =  bittab[n];
		}
		break;

	    case '*':               /* match 0 or more.. */
		*mp++ = PAT_ANYSPAN;
		break;

	    case '(':
		if( tagc>=MAXTAG ){
		    dfa[0] = PAT_END;
		    return "Too many () pairs";
		}
		tagstk[++tagi] = tagc;
		*mp++ =  PAT_BEGINSPAN;
		*mp++ =  tagc++;
		break;
	    
	    case ')':
		if( tagi<=0 ){
		    dfa[0] = PAT_END;
		    return "Unmatched ')'";
		}
		*mp++ =  PAT_ENDSPAN;
		*mp++ =  tagstk[tagi--];
		break;

	    case '\\':              /* tags, backrefs .. */
		p++;
		*mp++ =  PAT_CHAR;
		*mp++ =  *p;
		break;

	    default :               /* an ordinary char  */
		*mp++ =  PAT_CHAR;
		*mp++ =  *p;
		break;
	}
    }
    if( tagi > 0 ){
	dfa[0] = PAT_END;
	return "Unmatched '('";
    }
    *mp = PAT_END;
    sta = DFA_OK;
    return NULL;
}

/* Given a string 'lp', use the compiled dfa to determine if the
 * string matches the compiled pattern. If it does, return 1, else
 * return 0. If the pattern matches, bopat[0] and eopat[0] are set
 * to the beginning and the end of the matched fragment, respectively.
 */
int ref_exec( const char *lp )
{
    const char *ep;
    char *ap = dfa;

    bopat[0] = 0;
    bopat[1] = 0;
    bopat[2] = 0;
    bopat[3] = 0;
    bopat[4] = 0;
    bopat[5] = 0;
    bopat[6] = 0;
    bopat[7] = 0;
    bopat[8] = 0;
    bopat[9] = 0;

    if( *ap == PAT_END ){
	return 0;	/* Bad dfa. fail always */
    }
    ep = pmatch( lp, ap );
    if( !ep ){
	return 0;
    }
    bopat[0] = lp;
    eopat[0] = ep;
    return 1;
}

#define isinset(x,y) ((x)[((y)&BLKIND)>>3] & (1<<((y)&BITIND)))

/* pmatch:
 *	internal routine for the hard part
 *
 * 	This code is mostly snarfed from an early
 * 	grep written by David Conroy. The backref and
 * 	tag stuff, and various other mods are by oZ.
 *
 *	At the end of a successful match, bopat[n] and eopat[n]
 *	are set to the beginning and end of subpatterns matched
 *	by tagged expressions (n = 1 to 9).
 *
 */
static const char *pmatch( const char *lp, const char *ap )
{
    const char *e;			/* extra pointer for CLO */
    int op;
    int c;
    const char *are;			/* to save the line ptr. */

    for(;;){
	op = *ap++;
	if( op == PAT_END ){
	    break;
	}
	switch( op ) {
	    case PAT_CHAR:
		if( *lp++ != *ap++ ){
		    return NULL;
		}
		break;

	    case PAT_ANY:
		if( *lp++ == '\0' ){
		    return NULL;
		}
		break;

	    case PAT_INSET:
		c = *lp++;
		if( !isinset( ap, c ) ){
		    return NULL;
		}
		ap += BITBLK;
		break;

	    case PAT_NOTINSET:
		c = *lp++;
		if( isinset( ap, c ) ){
		    return NULL;
		}
		ap += BITBLK;
		break;

	    case PAT_BEGINSPAN:
		bopat[(int) *ap++] = lp;
		break;

	    case PAT_ENDSPAN:
		eopat[(int) *ap++] = lp;
		break;

	    case PAT_ANYSPAN:
		are = lp;
		while( *lp ){
		    lp++;
		}
		while( lp >= are ){
		    e = pmatch( lp, ap );
		    if( e != NULL ){
			return e;
		    }
		    lp--;
		}
		return NULL;

	    default:
		fprintf( stderr, "ref_exec: bad dfa opcode: %d.\n", op );
		exit( 2 );
	}
    }
    if( *lp != '\0' ){
	return NULL;
    }
    return lp;
}

/* Substitute the matched portions of the 'src' in 'dst'.
 * The following special characters are recognized in 'src':
 *
 * &:
 *	Substitute the entire matched pattern.
 *
 * \digit:
 *	Substitute a subpattern, with the given tag number. Tags are
 *	numbered from 1 to 9. If the particular tagged subpattern
 * 	does not exist, the empty string is substituted.
 */
void ref_subs( const char *src, char *dst )
{
    char c;
    int pin;
    const char *bp;
    const char *ep;

    if( src[0] == '\0' || bopat[0] == NULL ){
	return;
    }

    while( (c = *src++) != '\0' ){
	switch( c ){
	    case '&':
		pin = 0;
		break;

	    case '\\':
		c = *src++;
		if( c >= '0' && c <= '9') {
		    pin = c - '0';
		    break;
		}
		/* Fallthrough! */

	    default:
		*dst++ = c;
		continue;
	}
	bp = bopat[pin];
	ep = eopat[pin];
	if( bp && ep ){
	    while( *bp != '\0' && bp < ep ){
		*dst++ = *bp++;
	    }
	}
    }
    *dst = '\0';
}
