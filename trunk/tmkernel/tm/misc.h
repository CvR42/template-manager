/* Tm - an interface code generator.
 * Author: C. van Reeuwijk.
 *
 * All rights reserved.
 */

/* File: misc.h
   Description of exported objects of misc.c
 */

extern unsigned int find_type_ix( const ds_list dl, const char *t );
extern unsigned int find_field_ix( const field_list fl, const char *nm );
extern unsigned int find_constructor_ix( const constructor_list cl, const char *nm );
extern const tmstring get_type_name( const ds t );
extern FILE *ckfopen( const char *nm, const char *acc );
extern void ckfreopen( const char *nm, const char *acc, FILE *f );
extern bool member_tmstring_list( const tmstring s, const tmstring_list l );

extern field find_class_field( const ds_list types, const char *type, const char *nm );
extern field find_class_field_super( const ds_list types, tmstring_list supers, const char *nm );

extern const tmstring_list extract_inherits( const ds_list types, const char *type );
extern void collect_subclasses( tmstring_list *res, const ds_list types, const tmstring type );
extern void collect_superclasses( tmstring_list *res, const ds_list types, const char *type );
extern void collect_inheritors( tmstring_list *res, const ds_list types, const tmstring type );

void collect_all_fields( tmstring_list *fields, const ds_list types, const char *type );
void collect_inherited_fields( tmstring_list *fields, const ds_list types, const char *type );
void collect_fields( tmstring_list *fields, const ds_list types, const char *type );
