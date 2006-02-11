/* File: $Id$
 *
 * Description of exported objects of misc.c.
 */

extern unsigned int find_type_ix( const_ds_list types, const_tmsymbol t );
extern FILE *ckfopen( const char *nm, const char *acc );
extern void ckfreopen( const char *nm, const char *acc, FILE *f );
extern bool member_tmsymbol_list( const_tmsymbol s, const_tmsymbol_list l );
extern bool member_tmstring_list( const_tmstring s, const_tmstring_list l );
extern bool any_member_tmsymbol_list( const_tmsymbol_list sl, const_tmsymbol_list l );

extern Field find_field( const_ds_list types, const_tmsymbol type, const_tmsymbol nm );

extern tmsymbol_list extract_inherits( const_ds_list types, const_tmsymbol type );
extern void collect_subclasses( tmsymbol_list *res, const_ds_list types, tmsymbol type );
extern void collect_superclasses( tmsymbol_list *res, const_ds_list types, tmsymbol type );
extern void collect_inheritors( tmsymbol_list *res, const_ds_list types, tmsymbol type );

extern void collect_fields( tmsymbol_list *fields, const_ds_list types, const_tmsymbol type );
extern void collect_all_fields( tmsymbol_list *fields, const_ds_list types, const_tmsymbol type );

extern bool check_double_symbols( const char *msg, const_tmsymbol_list l );
extern ds_list zap_memoized_inheritors( ds_list types );
