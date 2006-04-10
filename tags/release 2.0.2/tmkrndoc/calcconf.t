.. File: calcconf.t
.set basename calc
.set wantdefs
.append wantdefs new_command_list
.append wantdefs new_command
.append wantdefs rdup_command
.append wantdefs rfre_expr
.append wantdefs rdup_expr
.append wantdefs append_command_list
.append wantdefs delete_command_list
.append wantdefs print_command_list
.append wantdefs fscan_command_list
.append wantdefs rfre_command_list
.append wantdefs ${prefix new_ ${subclasses expr}}
.append wantdefs stat_$(basename)
.append wantdefs get_balance_$(basename)
