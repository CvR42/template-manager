.. Tm - an interface code generator.
.. Author: C. van Reeuwijk.
..
.. All rights reserved.
..
.. File: need.t
.. CvR
..
.. Analysis of required code for given set of routines.
.. Given a list of wanted routines and ds definitions in the variable
.. 'wantdefs', construct a list of wanted types for each groups of definitions
.. in the variables 'want_<classlist>', and 'want_<classlist>_list' where
.. <classlist> is an element from the list below. Deduce the contents of the
.. variables 'need_<classlist>'. Using knowledge about the definition of
.. the various routines, deduce the required definitions and set them
.. in the variables 'need_<classlist>'.
..
.. The variables 'need_<classlist>' are restricted to types occurring.
.. For list classes arbitrary types are allowed.
..
.. If the variable 'alldefs' is set, all the variables are simply set to
.. ${typelist}.
..
.. Some initial checks
.set minvers 36
.if ${< $(tmvers) $(minvers)}
. error ${tplfilename}: at least tm version $(minvers) required.
. exit 1
.endif
.call apply_aliases
.set bad 0
.if ${not ${defined basename}}
. error '${tplfilename}': definition of basename required.
. set bad 1
.endif
.if ${and ${not ${defined alldefs}} ${not ${defined wantdefs}}}
. error '${tplfilename}': no definitions specified.
. error At least one of 'alldefs' and 'wantdefs' must be set.
. set bad 1
.endif
..
.if ${not ${defined notwantdefs}}
.set notwantdefs
.endif
..
.if $(bad)
. exit 1
.endif
..
.. Prefix and suffix used to construct a list type name from a name
.set listpre
.set listsuff _list
..
.. Define the list of definition classes
.set groups      ds compare destroy clone print fprint fscan
.. These are only useful for lists.
.set listgroups append concat slice reserve insert erase reverse extract
.append listgroups extractlist insertlist
.append groups $(listgroups)
.set misccode stat_$(basename) get_balance_$(basename) flush_$(basename)
.append groups is
..
.append valuetypes int long char uint ulong
.append legacytypes tmstring
..
.. Reset all want_<groups> variables
.foreach g $(groups)
.set want_$g
.endforeach
.set want_misc
..
.if ${defined alldefs}
.. All classes want all types
. foreach g ${excl $(groups) "" $(listgroups)}
.  set want_$g ${ctypelist} ${tuplelist} ${classlist}
. endforeach
. foreach g $(groups)
.  set want_$g ${suffix $(listsuff) ${ctypelist} ${tuplelist} ${classlist}}
. endforeach
. set want_misc $(misccode)
.endif
.set wantdefs ${uniq $(wantdefs)}
.. Extract the contents of the 'want_<group>' variables from the
.. 'wantdefs'.
.. Single defined type names.
.set want_ds ${comm ${typelist} "" $(wantdefs)}
.set wantdefs ${excl $(wantdefs) "" $(want_ds)}
.. Operations on single elements
.foreach g ${rmlist ds $(groups)}
.. Extract all requests starting with $g
. set want_$g ${filt $g_(*) \1 $(wantdefs)}
. set badtypes ${excl ${singletypes $(want_$g)} "" ${typelist}}
. if ${len $(badtypes)}
.  error Don't know how to generate: ${prefix $g_ $(badtypes)}
.  exit 1
. endif
. set wantdefs ${excl $(wantdefs) "" ${prefix $g_ $(want_$g)}}
.endforeach
.. Miscellaneous functions
.set want_misc ${comm $(wantdefs) "" $(misccode)}
.set wantdefs ${excl $(wantdefs) "" $(want_misc)}
.. At this point all functions on lists should have been filtered out..
.. This fact is used below..
.set want_ds_list ${filt (*)_list & $(wantdefs)}
.set wantdefs ${excl $(wantdefs) "" $(want_ds_list)}
.append want_ds $(want_ds_list)
.if ${len $(wantdefs)}
. error Can't handle definition: $(wantdefs)
. exit 1
.endif
..
.. For all wanted new_<t> of virtual types add their inheritors to the
.. want list.
.foreach t $(want_ds)
.if ${isvirtual $t}
.append want_ds "${subclasses $t}"
.endif
.endforeach
.set want_ds ${uniq $(want_ds)}
..
.. Macros to calculate all need variables.
..
.. The following macro invokes a 'req_*' macro. The extra layer allows
.. tracing, weeding out of invocations with empty parameterlists, etc
.if ${defined verbose}
.set reqlevel 0
.macro require g l
.set l ${excl ${uniq $l} "" $(need_$g)}
.if ${len $l}
. globalappend need_$g $l
// required: ${strpad "" $(reqlevel) "."}${prefix $g_ $l}
.set reqlevel $[$(reqlevel)+1]
. call req_$g "$l"
.set reqlevel $[$(reqlevel)-1]
.endif
.endmacro
.else
.macro require g l
.set l ${excl ${uniq $l} "" $(need_$g)}
.if ${len $l}
. globalappend need_$g $l
. call req_$g "$l"
.endif
.endmacro
.endif
..
.. The following macros invoke 'require' recursively to ensure that
.. the functions required by their group functions is available.
..
.. ** slice **
.macro req_slice l
.call require clone "$l"
.call require reserve "$l"
.call require append "$l"
.endmacro
..
.. ** clone **
.macro req_clone l
.call require reserve "${listtypes $l}"
.call require clone "${delisttypes $l} ${types $l}"
.call require clone "${nonvirtual ${reach $l}}"
.endmacro
..
.. ** fscan **
.macro req_fscan l
.call require append "${listtypes $l}"
.call require fscan "${delisttypes $l} ${types ${singletypes $l}}"
.call require fscan "${types ${subclasses $l}}"
.endmacro
..
.. ** print **
.macro req_print l
.call require ds "$l"
.call require print "${delisttypes $l}"
.call require print "${types ${singletypes $l} ${subclasses $l}}"
.call require print "${nonvirtual ${subclasses $l}}"
.endmacro
..
.. ** fprint **
.macro req_fprint l
.call require ds "$l"
.call require fprint "${delisttypes $l}"
.call require fprint "${types ${singletypes $l} ${subclasses $l}}"
.call require fprint "${nonvirtual ${subclasses $l}}"
.endmacro
..
.. ** compare **
.macro req_compare l
.call require ds "$l"
.call require compare "${delisttypes $l}"
.call require compare "${types ${singletypes $l} ${subclasses $l}}"
.call require compare "${nonvirtual ${subclasses $l}}"
.endmacro
..
.. ** append **
.macro req_append l
.call require reserve "$l"
.endmacro
..
.. ** concat **
.macro req_concat l
.call require reserve "$l"
.endmacro
..
.. ** reverse **
.macro req_reverse l
.call require ds "$l"
.endmacro
..
.. ** insertlist **
.macro req_insertlist l
.call require reserve "$l"
.endmacro
..
.. ** insert **
.macro req_insert l
.call require reserve "$l"
.endmacro
..
.. ** extractlist **
.macro req_extractlist l
.call require reserve "$l"
.endmacro
..
.. ** extract **
.macro req_extract l
.call require ds "$l"
.endmacro
..
.. ** erase **
.macro req_erase l
.call require destroy "${delisttypes $l}"
.call require ds "$l"
.endmacro
..
.. ** reserve **
.macro req_reserve l
.call require ds "$l"
.endmacro
..
.. ** destroy **
.macro req_destroy l
.call require destroy "${delisttypes $l}"
.call require destroy "${alltypes ${singletypes $l}}"
.call require destroy "${nonvirtual ${subclasses $l}}"
.endmacro
..
.. ** is **
.macro req_is l
.call require ds "$l"
.endmacro
..
.. ** ds **
.macro req_ds l
.call require ds "${delisttypes $l}"
.call require ds "${types ${singletypes $l} ${subclasses $l}}"
.call require ds "${subclasses $l} ${superclasses $l}"
.endmacro
..
.. From the request for new_<virtual class>, deduce the desire for
.. its subclasses.
.. Note that this modifies the *want_new* variable, *not* the need_new
.. variable that is set in the deductions below.
..
.. Reset all need_<group> variables.
.foreach g $(groups)
. set need_$g
.endforeach
.set need_misc
..
.. Set all need_<group> variables.
.foreach g $(groups)
. call require $g "$(want_$g)"
.endforeach
.set need_misc $(want_misc)
..
.. Enforce notwantdefs
.set notwantdefs ${uniq $(notwantdefs)}
.if ${len $(notwantdefs)}
. foreach g ${rmlist ds $(groups)}
.  foreach t $(need_$g)
.   if ${member $g_$t $(notwantdefs)}
.    set need_$g ${rmlist $t $(need_$g)}
.    set want_$g ${rmlist $t $(want_$g)}
.   endif
.  endforeach
. endforeach
. foreach t $(need_ds)
.  if ${member $t $(notwantdefs)}
.   set need_ds ${rmlist $t $(need_ds)}
.   set want_ds ${rmlist $t $(want_ds)}
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
.set statcode ${or ${member stat_$(basename) $(need_misc)} ${member isbalanced_$(basename) $(need_misc)}}
.if $(statcode)
. set need_stat $(need_ds)
. set want_stat $(want_ds)
.else
. set need_stat
. set want_stat
.endif
..
.. Derive the contents of the want_*_list and need_*_list variables
.. from the want_ and need_ variables
..
.foreach g $(groups) stat
. set want_$g_list ${delisttypes $(want_$g)}
. set want_$g ${singletypes $(want_$g)}
. set need_$g_list ${delisttypes $(need_$g)}
. set need_$g ${comm ${singletypes $(need_$g)} "" ${typelist}}
.endforeach
.set need_ds ${comm $(need_ds) "" ${typelist}}
.if ${defined verbose}
.foreach g $(groups) stat
// want_$g: $(want_$g)
// need_$g: $(need_$g)
// want_$g_list: $(want_$g_list)
// need_$g_list: $(need_$g_list)
.endforeach
// statcode: $(statcode)
.endif
// Requirement analysis took ${processortime} milliseconds.
