.. Tm - an interface code generator.
.. Author: C. van Reeuwijk.
..
.. All rights reserved.
..
.. File: lluneed.t
.. CvR
..
.. Analysis of required code for given set of routines.
.. Given a list of want_ed routines and ds definitions in the variables
.. 'want_<classlist>', and 'want_<classlist>_list' where <classlist> is an
.. element from the list below, deduce the contents of the variables
.. 'need_<classlist>'.
..
.. The variables 'need_<classlist>' are restricted to types occurring
.. in ${typelist}.
..
.. If the variable 'alldefs' is set, all the variables are simply set to
.. ${typelist}.
..
.call expand_inherits
..
.set minvers 34
.if ${< $(tmvers) $(minvers)}
. error '${tplfilename}': at least tm version $(minvers) required.
. exit 1
.endif
.if ${not ${defined basename}}
. error '${tplfilename}': definition of basename required.
. exit 1
.endif
.if $[!(${defined alldefs} | ${defined wantdefs})]
. error '${tplfilename}': no definitions specified.
. error At least one of 'alldefs' and 'wantdefs' must be set.
. exit 1
.endif
..
.. Detect the use of 'tag' in constructor types.
.set bad 0
.. Check for use of reserved element names
.foreach t ${ctypelist}
.. Do nothing for tuple types.
. foreach c ${conslist $t}
.  if ${member tag ${celmlist $t $c}}
.   error type $t: field name `tag' is not allowed in constructors.
.   set bad 1
.  endif
. endforeach
.endforeach
..
.. Detect the use of `next' as field name.
.set reselmname next
.set bad 0
.foreach t ${ttypelist}
. if ${member next ${stemname ${telmlist $t}}}
.  error Error: type '$t': field names of the form `next[_list]' are reserved.
.  set bad 1
. endif
.endforeach
.foreach t ${ctypelist}
. foreach c ${conslist $t}
.  if ${member next ${stemname ${celmlist $t $c}}}
.   error Error: type '$t': field names of the form `next[_list]' are reserved.
.   set bad 1
.  endif
. endforeach
.endforeach
..
.if $(bad)
. exit 1
.endif
.if $[!${defined notwantdefs}]
. set notwantdefs
.endif
..
.. Set the prefix and suffix used for list names
.set listpre
.set listsuff _list
..
.. Define the list of definition classes
.set    class      ds new fre rfre rdup fprint print fscan cmp 
.set    class_list ds new fre rfre rdup fprint print fscan cmp append concat
.append class_list insert delete slice setroom reverse extract
.set misccode   stat_$(basename) get_balance_$(basename) flush_$(basename)
..
.. Reset all want_<classlist> variables
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
.set want_ds ${comm ${typelist} "" $(wantdefs)}
.set wantdefs ${excl $(wantdefs) "" $(want_ds)}
.set l
.foreach t ${typelist}
.append l ${filt $t_*list & $(wantdefs)}
.endforeach
.set wantdefs ${excl $(wantdefs) "" $l}
.set want_ds_list ${filt (*)_list \1 $l}
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
.foreach v ${rmlist ds $(class_list)}
.. Extract all requests starting with $v
.. Use only types that can be handled
. set want_$v_list ${filt $v_(*)_list \1 $(wantdefs)}
. set badtypes ${excl ${stemname $l} "" ${typelist}}
. if ${len $(badtypes)}
.  error Don't know type: $(badtypes)
.  exit 1
. endif
. set wantdefs ${excl $(wantdefs) "" ${subs * $v_&_list $(want_$v_list)}}
.endforeach
.set want_misc ${comm $(misccode) "" $(wantdefs)}
.set wantdefs ${excl $(wantdefs) "" $(want_misc)}
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
.. ** setroom **
.set need_ds_list ${uniq $(need_ds_list) $(need_setroom_list)}
..
.. ** append **
.set need_ds_list ${uniq $(need_ds_list) $(need_append_list)}
..
.. ** concat **
.set need_ds_list ${uniq $(need_ds_list) $(need_concat_list)}
..
.. ** insert **
.set need_ds_list ${uniq $(need_ds_list) $(need_insert_list)}
..
.. ** delete **
.set need_rfre ${uniq $(need_rfre) $(need_delete_list)}
.set need_ds_list ${uniq $(need_ds_list) $(need_delete_list)}
..
.. ** extract **
.set need_ds_list ${uniq $(need_ds_list) $(need_extract_list)}
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
.. ** slice **
.set need_rdup ${uniq $(need_rdup) $(need_slice_list)}
.set need_new_list ${uniq $(need_new_list) $(need_slice_list)}
.set need_ds_list ${uniq $(need_ds_list) $(need_slice_list)}
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
.set need_ds ${uniq $(need_ds) $(need_rdup)}
.set need_ds_list ${uniq $(need_ds_list) $(need_rdup_list)}
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
.set need_new_list ${uniq $(need_new_list) $(need_fscan_list)}
.set need_append_list ${uniq $(need_append_list) $(need_fscan_list)}
.set need_ds ${uniq $(need_ds) $(need_fscan)}
.set need_ds_list ${uniq $(need_ds_list) $(need_fscan_list)}
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
.. ** new **
.set need_ds ${uniq $(need_ds) $(need_new)}
.set need_ds_list ${uniq $(need_ds_list) $(need_new_list)}
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
.. ** ds **
.set need_ds ${deptype single $(need_ds) $(need_ds_list)}
.set need_ds_list ${uniq $(need_ds_list) ${deptype list $(need_ds)}}
.set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(need_ds_list)}
.while ${len $(higherlists)}
. set need_ds_list ${uniq $(need_ds_list) $(higherlists)}
. set higherlists ${filt $(listpre)(*)$(listsuff) \1 $(higherlists)}
.endwhile
..
.. Enforce notwantdefs
.set notwantdefs ${uniq $(notwantdefs)}
.set l ${comm $(notwantdefs) "" ${typelist}}
.set need_ds ${excl $(need_ds) "" $l}
.set want_ds ${excl $(want_ds) "" $l}
.set l ${comm $(notwantdefs) "" ${suffix _list ${typelist}}}
.set l ${filt (*)_list \1 $l}
.set need_ds_list ${excl $(need_ds_list) "" $l}
.set want_ds_list ${excl $(want_ds_list) "" $l}
.foreach v ${rmlist ds $(class)}
. set l ${filt $v_(*) \1 $(notwantdefs)}
. set l ${rmlist *_list $l}
. set need_$v ${excl $(need_$v) "" $l}
. set want_$v ${excl $(want_$v) "" $l}
.endforeach
.foreach v ${rmlist ds $(class_list)}
. set l ${filt $v_(*)_list \1 $(notwantdefs)}
. set need_$v_list ${excl $(need_$v_list) "" $l}
. set want_$v_list ${excl $(want_$v_list) "" $l}
.endforeach
.set need_misc ${excl $(need_misc) "" $(notwantdefs)}
.set want_misc ${excl $(want_misc) "" $(notwantdefs)}
..
.. ** derived variables **
.if ${or ${member stat_$(basename) $(need_misc)} ${member is_balanced_$(basename) $(need_misc)}}
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
