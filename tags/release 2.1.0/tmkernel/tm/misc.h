/* File: $Id$
 *
 * Description of exported objects of misc.c.
 */

extern unsigned int find_type_ix( const ds_list dl, const char *t );
extern unsigned int find_field_ix( const Field_list fl, const char *nm );
extern FILE *ckfopen( const char *nm, const char *acc );
extern void ckfreopen( const char *nm, const char *acc, FILE *f );
extern bool member_tmstring_list( const tmstring s, const tmstring_list l );
extern bool any_member_tmstring_list( const tmstring_list sl, const tmstring_list l );

extern Field find_field( const ds_list types, const char *type, const char *nm );
extern Field find_field_super( const ds_list types, tmstring_list supers, const char *nm );

extern tmstring_list extract_inherits( const ds_list types, const char *type );
extern void collect_subclasses( tmstring_list *res, const ds_list types, const tmstring type );
extern void collect_superclasses( tmstring_list *res, const ds_list types, const char *type );
extern void collect_inheritors( tmstring_list *res, const ds_list types, const tmstring type );

extern void collect_all_fields( tmstring_list *fields, const ds_list types, const char *type );
extern void collect_inherited_fields( tmstring_list *fields, const ds_list types, const char *type );
extern void collect_fields( tmstring_list *fields, const ds_list types, const char *type );

extern bool check_double_strings( const char *msg, const tmstring_list l );
extern ds_list zap_memoized_inheritors( ds_list types );