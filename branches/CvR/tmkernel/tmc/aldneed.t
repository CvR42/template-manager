.. Tm - an interface code generator.
.. Author: C. van Reeuwijk.
..
.. All rights reserved.
..
.. File: aldneed.t
.. CvR
..
.. Analysis of required code for given set of routines.
.. Given a list of wanted routines and ds definitions in the variable
.. 'wantdefs', construct a list of wanted types for each class of definitions
.. in the variables 'want_<classlist>', and 'want_<classlist>_list' where
.. <classlist> is an element from the list below. Deduce the contents of the
.. variables 'need_<classlist>'. Using knowledge about the definition of
.. the various routines, deduce the required definitions and set them
.. in the variables 'need_<classlist>'.
..
.. The variables 'need_<classlist>' are restricted to types occurring
.. in ${typelist}. For list types arbitrary list names are allowed.
..
.. If the variable 'alldefs' is set, all the variables are simply set to
.. ${typelist}.
..
.call expand_inherits
..
.. Some initial checks
.set minvers 34
.if ${< $(tmvers) $(minvers)}
. error ${tplfilename}: at least tm version $(minvers) required.
. exit 1
.endif
.if ${not ${defined basename}}
. error '${tplfilename}': definition of basename required.
. exit 1
.endif
.if ${and ${not ${defined alldefs}} ${not ${defined wantdefs}}}
. error '${tplfilename}': no definitions specified.
. error At least one of 'alldefs' and 'wantdefs' must be set.
. exit 1
.endif
..
.. Detect the use of 'tag' in constructor types.
.set bad 0
.. Check for use of reserved element names
.foreach t ${ctypelist}
. foreach c ${conslist $t}
.  if ${member tag ${celmlist $t $c}}
.   error type $t: field name `tag' is not allowed in constructors.
.   set bad 1
.  endif
. endforeach
.endforeach
..
.if ${not ${defined notwantdefs}}
.set notwantdefs
.endif
..
.if $(bad)
. exit 1
.endif
..
.. Set the prefix and suffix used for list names
.set listpre
.set listsuff _list
..
.. Define the list of definition classes
.set    class      ds cmp new fre rfre rdup print fprint fscan null
.set    class_list ds cmp new fre rfre rdup print fprint fscan append setroom
.append class_list concat insert delete slice null reverse extract
.set misccode stat_$(basename) get_balance_$(basename) flush_$(basename)
..
.. Reset all want_<classlist> variables
.foreach v $(class)
.set want_$v
.endforeach
.foreach v $(class_list)
.set want_$v_list
.endforeach
.set want_misc
..
.if ${defined alldefs}
.. All classes want all types
. foreach v $(class)
.  set want_$v ${typelist}
. endforeach
. foreach v $(class_list)
.  set want_$v_list ${typelist}
. endforeach
. set want_misc $(misccode)
.endif
.. Extract the contents of the 'want_<classlist>' variables from the
.. 'wantdefs'.
.. Single defined type names.
.set wantdefs ${uniq $(wantdefs)}
.set want_ds ${comm ${typelist} "" $(wantdefs)}
.set wantdefs ${excl $(wantdefs) "" $(want_ds)}
.. Operations on single elements
.foreach v ${rmlist ds $(class)}
.. Extract all requests starting with $v
. set want_$v ${rmlist *_list ${filt $v_(*) \1 $(wantdefs)}}
. set badtypes ${excl $(want_$v) "" ${typelist}}
. if ${len $(badtypes)}
.  error Don't know type: $(badtypes)
.  exit 1
. endif
. set wantdefs ${excl $(wantdefs) "" ${prefix $v_ $(want_$v)}}
.endforeach
.. Operations on lists. Any list name is allowed, provided it does
.. not have a '_' in it.
.foreach v ${rmlist ds $(class_list)}
. set want_$v_list ${filt $v_(*)_list \1 $(wantdefs)}
. set badtypes ${filt *_* & ${stemname $(want_$v_list)}}
. if ${len $(badtypes)}
.  error Bad list type: $(badtypes)
.  exit 1
. endif
. set wantdefs ${excl $(wantdefs) "" ${subs * $v_&_list $(want_$v_list)}}
.endforeach
.. Miscellaneous functions
.set want_misc ${comm $(wantdefs) "" $(misccode)}
.set wantdefs ${excl $(wantdefs) "" $(want_misc)}
.. At this point all functions on lists should have been filtered out..
.. This fact is used below..
.set want_ds_list ${filt (*)_list \1 $(wantdefs)}
.set wantdefs ${excl $(wantdefs) "" ${suffix _list $(want_ds_list)}}
.. Put definitions with bad list names back in wantdefs
.foreach t ${filt *_* & ${stemname $(want_$v_list)}}
. append wantdefs ${filt *$t* & $(want_$v_list)}
. error wantdefs appended to: [$(wantdefs)]
.endforeach
.if ${len $(wantdefs)}
. error Can't handle definition: $(wantdefs)
. exit 1
.endif
..
.. Initialize all need_<classlist> variables.
.foreach v $(class)
. set need_$v $(want_$v)
.endforeach
.foreach v $(class_list)
. set need_$v_list $(want_$v_list)
.endforeach
.set need_misc $(want_misc)
..
.. ** slice **
.set need_rdup ${uniq $(need_slice_list) $(need_rdup)}
.set need_new_list ${uniq $(need_new_list) $(need_slice_list)}
.set need_setroom_list ${uniq $(need_setroom_list) $(need_slice_list)}
.set need_append_list ${uniq $(need_append_list) $(need_slice_list)}
..
.. ** rdup **
.set need_rdup ${deptype single $(need_rdup_list) $(need_rdup)}
.set need_rdup_list ${uniq $(need_rdup_list) ${deptype list $(need_rdup)}}
.set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(need_rdup_list)}
.while ${len $(higherlists)}
. set need_rdup_list ${uniq $(need_rdup_list) $(higherlists)}
. set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(higherlists)}
.endwhile
.set need_new ${uniq $(need_new) $(need_rdup)}
.set need_new_list ${uniq $(need_new_list) $(need_rdup_list)}
.set need_setroom_list ${uniq $(need_setroom_list) $(need_rdup_list)}
..
.. ** fscan **
.set need_fscan ${deptype single $(need_fscan_list) $(need_fscan)}
.set need_fscan_list ${uniq $(need_fscan_list) ${deptype list $(need_fscan)}}
.set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(need_fscan_list)}
.while ${len $(higherlists)}
. set need_fscan_list ${uniq $(need_fscan_list) $(higherlists)}
. set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(higherlists)}
.endwhile
.set need_new ${uniq $(need_new) $(need_fscan)}
.set need_null ${uniq $(need_null) $(need_fscan)}
.set need_new_list ${uniq $(need_new_list) $(need_fscan_list)}
.set need_append_list ${uniq $(need_append_list) $(need_fscan_list)}
.set need_null_list ${uniq $(need_null_list) $(need_fscan_list)}
..
.. ** print **
.set need_print ${deptype single $(need_print_list) $(need_print)}
.set need_print_list ${uniq $(need_print_list) ${deptype list $(need_print)}}
.set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(need_print_list)}
.while ${len $(higherlists)}
. set need_print_list ${uniq $(need_print_list) $(higherlists)}
. set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(higherlists)}
.endwhile
.set need_ds ${uniq $(need_ds) $(need_print)}
.set need_ds_list ${uniq $(need_ds_list) $(need_print_list)}
..
.. ** fprint **
.set need_fprint ${deptype single $(need_fprint_list) $(need_fprint)}
.set need_fprint_list ${uniq $(need_fprint_list) ${deptype list $(need_fprint)}}
.set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(need_fprint_list)}
.while ${len $(higherlists)}
. set need_fprint_list ${uniq $(need_fprint_list) $(higherlists)}
. set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(higherlists)}
.endwhile
.set need_ds ${uniq $(need_ds) $(need_fprint)}
.set need_ds_list ${uniq $(need_ds_list) $(need_fprint_list)}
..
.. ** cmp **
.set need_cmp ${deptype single $(need_cmp_list) $(need_cmp)}
.set need_cmp_list ${uniq $(need_cmp_list) ${deptype list $(need_cmp)}}
.set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(need_cmp_list)}
.while ${len $(higherlists)}
. set need_cmp_list ${uniq $(need_cmp_list) $(higherlists)}
. set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(higherlists)}
.endwhile
.set need_ds ${uniq $(need_ds) $(need_cmp)}
.set need_ds_list ${uniq $(need_ds_list) $(need_cmp_list)}
..
.. ** append **
.set need_setroom_list ${uniq $(need_setroom_list) $(need_append_list)}
.set need_ds_list ${uniq $(need_ds_list) $(need_append_list)}
..
.. ** concat **
.set need_fre_list ${uniq $(need_fre_list) $(need_concat_list)}
.set need_setroom_list ${uniq $(need_setroom_list) $(need_concat_list)}
..
.. ** insert **
.set need_setroom_list ${uniq $(need_setroom_list) $(need_insert_list)}
..
.. ** extract **
.set need_ds_list ${uniq $(need_ds_list) $(need_extract_list)}
..
.. ** delete **
.set need_rfre ${uniq $(need_rfre) ${stemname $(need_delete_list)}}
.set need_rfre_list ${uniq $(need_rfre_list) ${filt $(listpre)(*)$(listsuff) \1 $(need_delete_list)}}
.set need_ds_list ${uniq $(need_ds_list) $(need_delete_list)}
..
.. ** setroom **
.set need_ds_list ${uniq $(need_ds_list) $(need_setroom_list)}
..
.. ** rfre **
.set need_rfre ${deptype single ${uniq $(need_rfre) $(need_rfre_list)}}
.set need_rfre_list ${uniq $(need_rfre_list) ${deptype list $(need_rfre)}}
.set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(need_rfre_list)}
.while ${len $(higherlists)}
. set need_rfre_list ${uniq $(need_rfre_list) $(higherlists)}
. set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(higherlists)}
.endwhile
.set need_fre ${uniq $(need_fre) $(need_rfre)}
.set need_fre_list ${uniq $(need_fre_list) $(need_rfre_list)}
.set need_ds ${uniq $(need_ds) $(need_rfre)}
.set need_ds_list ${uniq $(need_ds_list) $(need_rfre_list)}
..
.. ** fre **
.set need_ds ${uniq $(need_ds) $(need_fre)}
.set need_ds_list ${uniq $(need_ds_list) $(need_fre_list)}
..
.. ** new **
.set need_ds ${uniq $(need_ds) $(need_new)}
.set need_ds_list ${uniq $(need_ds_list) $(need_new_list)}
..
.. ** ds **
.set need_ds ${deptype single $(need_ds) $(need_ds_list)}
.set need_ds_list ${uniq $(need_ds_list) ${deptype list $(need_ds)}}
.set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(need_ds_list)}
.while ${len $(higherlists)}
. set need_ds_list ${uniq $(need_ds_list) $(higherlists)}
. set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(higherlists)}
.endwhile
..
.. ** null **
.set old 
.while $[${len $(old)}!=${len $(need_null)}]
.set old $(need_null)
.foreach t ${comm $(need_null) "" ${ttypelist}}
.foreach e ${telmlist $t}
.if ${eq single ${ttypeclass $t $e}}
.append need_null ${ttypename $t $e}
.endif
.endforeach
.endforeach
.set need_null ${comm ${typelist} "" ${uniq $(need_null)}}
.endwhile
..
.. Enforce notwantdefs
.set notwantdefs ${uniq $(notwantdefs)}
.if ${len $(notwantdefs)}
. foreach v ${rmlist ds $(class)}
.  foreach t $(need_$v)
.   if ${member $v_$t $(notwantdefs)}
.    set need_$v ${rmlist $t $(need_$v)}
.    set want_$v ${rmlist $t $(want_$v)}
.   endif
.  endforeach
. endforeach
. foreach t $(need_ds)
.  if ${member $t $(notwantdefs)}
.   set need_ds ${rmlist $t $(need_ds)}
.   set want_ds ${rmlist $t $(want_ds)}
.  endif
. endforeach
. foreach v ${rmlist ds $(class_list)}
.  foreach t $(need_$v_list)
.   if ${member $v_$t_list $(notwantdefs)}
.    set need_$v_list ${rmlist $t $(need_$v_list)}
.    set want_$v_list ${rmlist $t $(want_$v_list)}
.   endif
.  endforeach
. endforeach
. foreach t $(need_$v_list)
.  if ${member $t_list $(notwantdefs)}
.   set need_ds_list ${rmlist $t $(need_ds_list)}
.   set want_ds_list ${rmlist $t $(want_ds_list)}
.  endif
. endforeach
. foreach f $(misccode)
.  if ${member $f $(notwantdefs)}
.   set need_misc ${rmlist $f $(need_misc)}
.   set want_misc ${rmlist $f $(want_misc)}
.  endif
. endforeach
.endif
..
.. ** derived definitions **
.if ${or ${member stat_$(basename) $(need_misc)} ${member get_balance_$(basename) $(need_misc)}}
.set need_stat ${uniq $(need_new) $(need_fre)}
.set need_stat_list ${uniq $(need_new_list) $(need_fre_list)}
.set want_stat ${uniq $(want_new) $(want_fre)}
.set want_stat_list ${uniq $(want_new_list) $(want_fre_list)}
.else
.set need_stat
.set need_stat_list
.set want_stat
.set want_stat_list
.endif
