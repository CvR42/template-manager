/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: misc.h
   Description of exported objects of misc.c
 */

extern unsigned int find_type_ix( const ds_list dl, const char *t );
extern unsigned int find_constructor_ix( const constructor_list cl, const char *nm );
extern const tmstring get_type_name( const ds t );
extern FILE *ckfopen( const char *nm, const char *acc );
extern void ckfreopen( const char *nm, const char *acc, FILE *f );
extern bool member_tmstring_list( const tmstring s, const tmstring_list l );

extern void ckconstructor( tmstring nm, constructor_list cons );
