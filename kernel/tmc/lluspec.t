.. Tm - an interface code generator.
.. Author: C. van Reeuwijk.
..
.. All rights reserved.
..
.. List of required definitions
.set basename ds
.set wantdefs 
.set verbose
.append wantdefs append_toplevel_list
.append wantdefs append_toplevel_list_list_list
.append wantdefs cmp_toplevel_list
.append wantdefs concat_toplevel_list
.append wantdefs delete_toplevel_list
.append wantdefs deletelist_toplevel_list
.append wantdefs extract_toplevel_list
.append wantdefs extractlist_toplevel_list
.append wantdefs fprint_label
.append wantdefs fprint_thing
.append wantdefs fprint_toplevel_list
.append wantdefs fscan_toplevel_list
.append wantdefs get_balance_$(basename)
.append wantdefs insert_toplevel_list
.append wantdefs insertlist_toplevel_list
.append wantdefs isequal_toplevel_list
.append wantdefs new_toplevel
.append wantdefs new_label
.append wantdefs new_thing
.append wantdefs new_toplevel_list
.append wantdefs print_label
.append wantdefs print_thing
.append wantdefs print_toplevel_list
.append wantdefs rdup_toplevel
.append wantdefs rdup_toplevel_list
.append wantdefs reverse_toplevel_list
.append wantdefs rfre_label
.append wantdefs rfre_thing
.append wantdefs rfre_toplevel
.append wantdefs rfre_toplevel_list
.append wantdefs setroom_toplevel_list
.append wantdefs setroom_toplevel_list
.append wantdefs slice_toplevel_list
.append wantdefs stat_$(basename)
