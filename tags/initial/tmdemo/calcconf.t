.. File: calcconf.t
.set basename calc
.set wantdefs
.append wantdefs new_statement_list
.append wantdefs new_statement
.append wantdefs rfre_expr
.append wantdefs append_statement_list
.append wantdefs print_statement_list
.append wantdefs fscan_statement_list
.append wantdefs rfre_statement_list
.append wantdefs ${prefix new_ ${subclasses expr}}
.append wantdefs stat_$(basename)
.append wantdefs get_balance_$(basename)
