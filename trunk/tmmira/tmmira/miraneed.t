.. File: miraneed.t
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
.. in ${typelist} and $(otherlists).
..
.. If the variable 'alldefs' is set, all the variables are simply set to
.. ${typelist}.
..
.. Some initial checks
.set minvers 21
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
.if ${not ${defined otherlists}}
.set otherlists
.endif
.if ${not ${defined notwantdefs}}
.set notwantdefs
.endif
..
.. Define the list of definition classes
.set class_list ds scan show
.set class ds scan show
.set    misccode scan_num show_num
.append misccode scan_bool show_bool
.append misccode scan_string show_string
.append misccode scan_char show_char
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
.  set want_$v_list ${typelist} $(otherlists)
. endforeach
. set want_misc $(misccode)
.else
.. Extract the contents of the 'want_<classlist>' variables from the
.. 'wantdefs'.
. set wantdefs ${uniq $(wantdefs)}
. set gotdefs
. foreach v ${rmlist ds $(class)}
.  foreach t ${typelist}
.   if ${index $v_$t $(wantdefs)}
.    append want_$v $t
.    append gotdefs $v_$t
.   endif
.  endforeach
. endforeach
. foreach t ${typelist}
.  if ${index $t $(wantdefs)}
.   append want_ds $t
.   append gotdefs $t
.  endif
. endforeach
. foreach v ${rmlist ds $(class_list)}
.  foreach t ${typelist} $(otherlists)
.   if ${index $v_$t_list $(wantdefs)}
.    append want_$v_list $t
.    append gotdefs $v_$t_list
.   endif
.  endforeach
. endforeach
. foreach t ${typelist} $(otherlists)
.  if ${index $t_list $(wantdefs)}
.    append want_ds_list $t
.    append gotdefs $t_list
.  endif
. endforeach
. foreach f $(misccode)
.  if ${index $f $(wantdefs)}
.   append want_misc $f
.   append gotdefs $f
.  endif
. endforeach
. set gotdefs ${uniq $(gotdefs)}
. if ${!= ${len $(wantdefs)} ${len $(gotdefs)}}
.  foreach e $(gotdefs)
.   set wantdefs ${rmlist $e $(wantdefs)}
.  endforeach
.  error Can't handle definition: $(wantdefs)
.  exit 1
. endif
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
.. ** scan **
.set need_scan ${deptype single $(need_scan_list) $(need_scan)}
.set need_scan_list ${uniq $(need_scan_list) ${deptype list $(need_scan)}}
.set need_ds ${uniq $(need_ds) $(need_scan)}
.set need_ds_list ${uniq $(need_ds_list) $(need_scan_list)}
..
.. ** show **
.set need_show ${deptype single $(need_show_list) $(need_show)}
.set need_show_list ${uniq $(need_show_list) ${deptype list $(need_show)}}
.set need_ds ${uniq $(need_ds) $(need_show)}
.set need_ds_list ${uniq $(need_ds_list) $(need_show_list)}
..
.. ** ds **
.set need_ds ${deptype single $(need_ds) $(need_ds_list)}
.set need_ds_list ${uniq $(need_ds_list) ${deptype list $(need_ds)}}
..
.. Enforce notwantdefs
.set notwantdefs ${uniq $(notwantdefs)}
.foreach v ${rmlist ds $(class)}
. foreach t $(need_$v)
.  if ${index $v_$t $(notwantdefs)}
.   set need_$v ${rmlist $t $(need_$v)}
.   set want_$v ${rmlist $t $(want_$v)}
.  endif
. endforeach
.endforeach
.foreach t $(need_ds)
. if ${index $t $(notwantdefs)}
.  set need_ds ${rmlist $t $(need_ds)}
.  set want_ds ${rmlist $t $(want_ds)}
. endif
.endforeach
.foreach v ${rmlist ds $(class_list)}
. foreach t $(need_$v_list)
.  if ${index $v_$t_list $(notwantdefs)}
.   set need_$v_list ${rmlist $t $(need_$v_list)}
.   set want_$v_list ${rmlist $t $(want_$v_list)}
.  endif
. endforeach
.endforeach
.foreach t $(need_$v_list)
. if ${index $t_list $(notwantdefs)}
.   set need_ds_list ${rmlist $t $(need_ds_list)}
.   set want_ds_list ${rmlist $t $(want_ds_list)}
. endif
.endforeach
.foreach f $(misccode)
. if ${index $f $(notwantdefs)}
.  set need_misc ${rmlist $f $(need_misc)}
.  set want_misc ${rmlist $f $(want_misc)}
. endif
.endforeach
