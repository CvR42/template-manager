// File: lnt2s.c

#include "config.h"
#include "tmcpp.h"

// Given a tmtext 't' return a tmstring .
// This function assumes the tmtext contains no '\0'.
tmstring tmtext_to_tmstring_lognew( const tmtext *t, const char *file, const int line )
{
    size_t sz = (size_t) t->sz;
    // Create a string big enough to hold the text and the terminating '\0'.
    tmstring s = create_tmstring_lognew( sz+1, file, line );
    if( s == tmstringNIL ){
	return s;
    }
#if HAVE_MEMMOVE
    memcpy( s, t->arr, sz );
#else
    {
	long ix;

	for( ix=0; ix<t->sz; ix++ ){
	    s[ix] = t->arr[ix];
	}
    }
#endif
    s[sz] = '\0';
    return s;
}
