.. File: clneed.t
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
.set minvers 33
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
.. Prefix and suffix used to construct a list type name from a name
.set listpre [
.set listsuff ]
.. Define the list of definition classes
.set class ds Scan Show
..
.. Reset all want_<classlist> variables
.foreach v $(class)
.set want_$v
.endforeach
..
.if ${defined alldefs}
.. All classes want all types
. foreach v $(class)
.  set want_$v ${typelist}
. endforeach
.else
.. Extract the contents of the 'want_<classlist>' variables from the
.. 'wantdefs'.
.. Extract requests for functions and datastructure requests from
.. the list.
. set wantdefs ${uniq $(wantdefs)}
. foreach v ${rmlist ds $(class)}
.. Extract all requests starting with $v
.  set want_$v ${filt $v_(*) \1 $(wantdefs)}
.  set bad ${excl $(want_$v) "" ${typelist}}
.  if ${len $(bad)}
.   error Cannot generate: ${seplist ", " ${prefix $v_ $(bad)}}
.   exit 1
.  endif
.  set wantdefs ${excl $(wantdefs) "" ${prefix $v_ $(want_$v)}}
. endforeach
. set want_ds ${comm ${typelist} "" $(wantdefs)}
. set wantdefs ${excl $(wantdefs) "" $(want_ds)}
. if ${len $(wantdefs)}
.  error Unknown type or function: ${seplist ", " ${prefix $v_ $(bad)}}
.  exit 1
. endif
.endif
..
.. Initialize all need_<classlist> variables.
.foreach v $(class)
. set need_$v $(want_$v)
.endforeach
..
.. ** Scan **
.set need_Scan ${deptype single $(need_Scan)}
.set need_ds ${uniq $(need_ds) $(need_Scan)}
..
.. ** Show **
.set need_Show ${deptype single $(need_Show)}
.set need_ds ${uniq $(need_ds) $(need_Show)}
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
