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
.append wantdefs new_ds
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
.append wantdefs new_field_list
.append wantdefs new_field
.append wantdefs append_field_list
.append wantdefs concat_field_list
.append wantdefs rdup_field_list
.append wantdefs rfre_field_list
..
.append wantdefs new_tmstring_list
.append wantdefs rfre_tmstring_list
.append wantdefs rdup_tmstring_list
.append wantdefs print_tmstring_list
.append wantdefs append_tmstring_list
.append wantdefs concat_tmstring_list
.append wantdefs delete_tmstring_list
.append wantdefs extract_tmstring_list
.append wantdefs insert_tmstring_list
..
.append wantdefs new_tplelm
.append wantdefs new_tplelm_list
.append wantdefs rfre_tplelm
.append wantdefs rfre_tplelm_list
.append wantdefs rdup_tplelm_list
.append wantdefs rdup_tplelm
.append wantdefs append_tplelm_list
..
.append wantdefs stat_$(basename)
.append wantdefs get_balance_$(basename)
.append wantdefs flush_$(basename)
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
.append wantdefs new_classComponent
.append wantdefs append_classComponent_list
..
.append wantdefs new_alternative
.append wantdefs new_alternative_list
.append wantdefs rfre_alternative_list
.append wantdefs append_alternative_list
..
.append wantdefs new_switchcase
.append wantdefs new_switchcase_list
.append wantdefs append_switchcase_list
