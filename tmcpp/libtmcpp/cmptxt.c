/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

// File: cmptxt.c

#include "config.h"
#include "tmcpp.h"

// Compare two texts.
int compare( const tmtext &a, const tmtext &b )
{
    tmtext::size_type sz = a.size();
    if( b.size()<sz ){
	sz = b.size();
    }
    for( long i=0; i<sz; i++ ){
	if( a.arr[i]!=b.arr[i] ){
	    return (int) (a.arr[i]-b.arr[i]);
	}
    }
    if( a.size() == b.size() ){
	return 0;
    }
    if( a.size()<b.size() ){
	return -1;
    }
    return 1;
}

