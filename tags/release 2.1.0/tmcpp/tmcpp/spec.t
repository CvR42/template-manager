.. Tm - an interface code generator.
.. Author: C. van Reeuwijk.
..
.. All rights reserved.
..
.. File spec.t
..set verbose
.set basename ds
.set wantdefs
.append wantdefs fprint_label
.append wantdefs fprint_thing
.append wantdefs fprint_expr
.append wantdefs print_label
.append wantdefs print_thing
.append wantdefs print_expr
.append wantdefs fscan_expr
.append wantdefs destroy_label
.append wantdefs destroy_thing
.append wantdefs destroy_expr
.append wantdefs clone_toplevel
.append wantdefs compare_toplevel
.append wantdefs reserve_toplevel_list
.append wantdefs slice_toplevel_list
.append wantdefs extractlist_toplevel_list
.append wantdefs insertlist_toplevel_list
.append wantdefs append_toplevel_list
.append wantdefs append_toplevel_list_list_list
.append wantdefs reverse_toplevel_list
.append wantdefs insert_toplevel_list
.append wantdefs erase_toplevel_list
.append wantdefs extract_toplevel_list
.append wantdefs fscan_toplevel_list
.append wantdefs destroy_toplevel
.append wantdefs clone_toplevel_list
.append wantdefs concat_toplevel_list
.append wantdefs fprint_toplevel_list
.append wantdefs fprint_toplevel_list_list_list
.append wantdefs fprint_toplevel_list
.append wantdefs destroy_toplevel_list
.append wantdefs print_toplevel_list
.append wantdefs compare_toplevel_list
.append wantdefs stat_$(basename)
.append wantdefs get_balance_$(basename)
.append wantdefs flush_$(basename)
.append wantdefs compare_subtuple
.append wantdefs subtuple_list
.append wantdefs is_expr
.append wantdefs is_toplevel_list
.append wantdefs is_exprFold
.append wantdefs is_internalExpr
.append wantdefs is_TopNone
..
.append wantdefs destroy_int_list
.append wantdefs append_int_list
.append wantdefs erase_int_list
.append wantdefs clone_int_list
.append wantdefs concat_int_list
.append wantdefs extract_int_list
.append wantdefs extractlist_int_list
.append wantdefs compare_int_list
.append wantdefs reverse_int_list
.append wantdefs insertlist_int_list
.append wantdefs insert_int_list
.append wantdefs fprint_int_list
.append wantdefs fscan_int_list
.append wantdefs slice_int_list
.append wantdefs print_int_list
..
