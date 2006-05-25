.. Tm - an interface code generator.
.. Author: C. van Reeuwijk.
..
.. All rights reserved.
..
.. File tmcspec.t
.set verbose
.set basename ds
.set wantdefs
.append wantdefs ${prefix new_ ${subclasses expr thing}}
.append wantdefs append_toplevel_list
.append wantdefs append_toplevel_list_list_list
.append wantdefs cmp_subtuple
.append wantdefs cmp_toplevel
.append wantdefs cmp_toplevel_list
.append wantdefs concat_toplevel_list
.append wantdefs delete_toplevel_list
.append wantdefs deletelist_toplevel_list
.append wantdefs extract_toplevel_list
.append wantdefs extractlist_toplevel_list
.append wantdefs fprint_expr
.append wantdefs fprint_label
.append wantdefs fprint_thing
.append wantdefs fprint_toplevel_list
.append wantdefs fprint_toplevel_list
.append wantdefs fprint_toplevel_list_list_list
.append wantdefs fscan_expr
.append wantdefs fscan_toplevel_list
.append wantdefs get_balance_$(basename)
.append wantdefs insert_toplevel_list
.append wantdefs insertlist_toplevel_list
.append wantdefs is_TopNone
.append wantdefs is_expr
.append wantdefs is_exprFold
.append wantdefs is_internalExpr
.append wantdefs is_toplevel_list
.append wantdefs isequal_toplevel_list
.append wantdefs new_TopNone
.append wantdefs new_label
.append wantdefs new_smt
.append wantdefs new_subtuple
.append wantdefs new_subtuple_list
.append wantdefs new_subtuple_list
.append wantdefs new_toplevel
.append wantdefs new_toplevel_list
.append wantdefs print_expr
.append wantdefs print_label
.append wantdefs print_thing
.append wantdefs print_toplevel_list
.append wantdefs rdup_toplevel
.append wantdefs rdup_toplevel_list
.append wantdefs reverse_toplevel_list
.append wantdefs rfre_expr
.append wantdefs rfre_label
.append wantdefs rfre_thing
.append wantdefs rfre_toplevel
.append wantdefs rfre_toplevel_list
.append wantdefs setroom_toplevel_list
.append wantdefs slice_toplevel_list
.append wantdefs stat_$(basename)
.append wantdefs subtuple_list
.set notwantdefs new_subtuple_list
