.. File: dsspec.t
..
.. Tm - an interface code generator.
.. Author: C. van Reeuwijk.
.. All rights reserved.
.. Specification of required code
..
.set basename tm
.set wantdefs
..
.append wantdefs rfre_ds
.append wantdefs ${prefix new_ ${subclasses ds}}
.append wantdefs rdup_ds
.append wantdefs new_ds_list
.append wantdefs delete_ds_list
.append wantdefs append_ds_list
.append wantdefs concat_ds_list
.append wantdefs rfre_ds_list
.append wantdefs print_ds_list
..
..append wantdefs new_constructor
..append wantdefs rfre_constructor
..append wantdefs new_constructor_list
..append wantdefs rdup_constructor_list
..append wantdefs rdup_constructor
..append wantdefs append_constructor_list
..
.append wantdefs new_Type
.append wantdefs rdup_Type
.append wantdefs new_Type_list
.append wantdefs append_Type_list
.append wantdefs rfre_Type_list
.append wantdefs rfre_Type
..
.append wantdefs new_Field_list
.append wantdefs new_Field
.append wantdefs append_Field_list
.append wantdefs concat_Field_list
.append wantdefs rdup_Field_list
.append wantdefs rfre_Field_list
..
.append wantdefs new_tmstring_list
.append wantdefs rfre_tmstring_list
.append wantdefs rdup_tmstring_list
.append wantdefs print_tmstring_list
.append wantdefs append_tmstring_list
.append wantdefs concat_tmstring_list
.append wantdefs setroom_tmstring_list
.append wantdefs delete_tmstring_list
.append wantdefs extract_tmstring_list
.append wantdefs extractlist_tmstring_list
.append wantdefs insert_tmstring_list
..
.append wantdefs ${prefix new_ ${subclasses tplelm}}
.append wantdefs new_tplelm_list
.append wantdefs rfre_tplelm
.append wantdefs rfre_tplelm_list
.append wantdefs rdup_tplelm_list
.append wantdefs rdup_tplelm
.append wantdefs append_tplelm_list
..
.append wantdefs stat_$(basename)
.append wantdefs get_balance_$(basename)
..
.append wantdefs new_var
.append wantdefs new_var_list
.append wantdefs append_var_list
.append wantdefs delete_var_list
.append wantdefs insert_var_list
.append wantdefs rfre_var_list
.append wantdefs insert_var_list
..
.append wantdefs new_macro
.append wantdefs rfre_macro
.append wantdefs new_macro_list
.append wantdefs rfre_macro_list
.append wantdefs delete_macro_list
.append wantdefs insert_macro_list
..
.append wantdefs classComponent_list
.append wantdefs rfre_classComponent_list
.append wantdefs rfre_classComponent
.append wantdefs new_classComponent_list
.append wantdefs ${prefix new_ ${subclasses classComponent}}
.append wantdefs append_classComponent_list
..
.append wantdefs new_alternative
.append wantdefs new_alternative_list
.append wantdefs rfre_alternative_list
.append wantdefs append_alternative_list
..
.append wantdefs new_Switchcase
.append wantdefs new_Switchcase_list
.append wantdefs append_Switchcase_list
..
.append wantdefs new_origin
.append wantdefs rfre_origin
.append wantdefs rdup_origin
..
.append wantdefs new_origsymbol
.append wantdefs rdup_origsymbol
.append wantdefs new_origsymbol_list
..
.append wantdefs new_tmsymbol_list
.append wantdefs append_tmsymbol_list
.append wantdefs rfre_tmsymbol_list
.append wantdefs rdup_tmsymbol_list
.append wantdefs extract_tmsymbol_list
.append wantdefs concat_tmsymbol_list
.append wantdefs setroom_tmsymbol_list
.append wantdefs delete_tmsymbol_list
