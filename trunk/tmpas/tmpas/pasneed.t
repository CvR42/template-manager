.. Tm - an interface code generator.
.. Copyright (C) 1991, Delft University of Technology and C. van Reeuwijk.
..
.. This software is distributed under the terms of the GNU General Public
.. Licence as published by the Free Software Foundation. See the file 'LICENCE'
.. in the root directory of this distribution for details.
..
.. File: pasneed.t
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
.set minvers 23
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
.. Detect the use of reserved element names
.. (as set by the variable `reselmname').
.set reselmname tag next
.set bad 0
.. Check for use of reserved element names
.foreach t ${ttypelist}
. foreach e ${telmlist $t}
.  if ${index $e $(reselmname)}
.   error Warning: in type '$t': element name `$e' is reserved.
.   set bad 1
.  endif
. endforeach
.endforeach
.foreach t ${ctypelist}
. foreach c ${conslist $t}
.  foreach e ${celmlist $t $c}
.   if ${index $e $(reselmname)}
.    error Error: in type '$t': element name `$e' is reserved.
.    set bad 1
.   endif
.  endforeach
. endforeach
.endforeach
..
.if $(bad)
. exit 1
.endif
..
.if ${not ${defined otherlists}}
.set otherlists
.endif
.if ${not ${defined notwantdefs}}
.set notwantdefs
.endif
..
.. Define the list of definition classes
.set class_list ds New Free Rfre Copy Write Read Cmp
.set class      ds New Free Rfre Copy Write Read App Cmp
.set    miscdefs Stat$(basename)
.append miscdefs Readinteger Writeinteger Cmpinteger Rfreinteger Copyinteger
.append miscdefs Readreal Writereal Cmpreal Rfrereal Copyreal
.append miscdefs Readboolean Writeboolean Cmpboolean Rfreboolean Copyboolean
.append miscdefs Readchar Writechar Cmpchar Rfrechar Copychar
.append miscdefs tmgetc tmreadspc tmneedc tmreadobrac tmreadcbrac
.append miscdefs tmwritec tmreadc
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
. set want_misc $(miscdefs)
.else
.. Extract the contents of the 'want_<classlist>' variables from the
.. 'wantdefs'.
. set wantdefs ${uniq $(wantdefs)}
. set gotdefs
. foreach v ${rmlist ds $(class)}
.  foreach t ${typelist}
.   if ${index $v$t $(wantdefs)}
.    append want_$v $t
.    append gotdefs $v$t
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
.   if ${index $v$tlist $(wantdefs)}
.    append want_$v_list $t
.    append gotdefs $v$tlist
.   endif
.  endforeach
. endforeach
. foreach t ${typelist} $(otherlists)
.  if ${index $tlist $(wantdefs)}
.    append want_ds_list $t
.    append gotdefs $tlist
.  endif
. endforeach
. foreach f $(miscdefs)
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
.. ** Rfre **
.set need_Rfre ${deptype single ${uniq $(need_Rfre) $(need_Rfre_list)}}
.set need_Rfre_list ${uniq $(need_Rfre_list) ${deptype list $(need_Rfre)}}
.set need_Free ${uniq $(need_Free) $(need_Rfre)}
.set need_Free_list ${uniq $(need_Free_list) $(need_Rfre_list)}
.set need_ds ${uniq $(need_ds) $(need_Rfre)}
.set need_ds_list ${uniq $(need_ds_list) $(need_Rfre_list)}
..
.. ** Free **
.set need_ds ${uniq $(need_ds) $(need_Free)}
.set need_ds_list ${uniq $(need_ds_list) $(need_Free_list)}
..
.. ** Copy **
.set need_Copy ${deptype single $(need_Copy_list) $(need_Copy)}
.set need_Copy_list ${uniq $(need_Copy_list) ${deptype list $(need_Copy)}}
.set need_New ${uniq $(need_New) $(need_Copy)}
.set need_New_list ${uniq $(need_New_list) $(need_Copy_list)}
.set need_ds ${uniq $(need_ds) $(need_Copy)}
.set need_ds_list ${uniq $(need_ds_list) $(need_Copy_list)}
..
.. ** Read **
.set need_Read ${deptype single $(need_Read_list) $(need_Read)}
.set need_Read_list ${uniq $(need_Read_list) ${deptype list $(need_Read)}}
.set need_New ${uniq $(need_New) $(need_Read)}
.set need_New_list ${uniq $(need_New_list) $(need_Read_list)}
.set need_App ${uniq $(need_App) $(need_Read_list)}
.set need_ds ${uniq $(need_ds) $(need_Read)}
.set need_ds_list ${uniq $(need_ds_list) $(need_Read_list)}
..
.. ** Write **
.set need_Write ${deptype single $(need_Write_list) $(need_Write)}
.set need_Write_list ${uniq $(need_Write_list) ${deptype list $(need_Write)}}
.set need_ds ${uniq $(need_ds) $(need_Write)}
.set need_ds_list ${uniq $(need_ds_list) $(need_Write_list)}
..
.. ** Cmp **
.set need_Cmp ${deptype single $(need_Cmp_list) $(need_Cmp)}
.set need_Cmp_list ${uniq $(need_Cmp_list) ${deptype list $(need_Cmp)}}
.set need_ds ${uniq $(need_ds) $(need_Cmp)}
.set need_ds_list ${uniq $(need_ds_list) $(need_Cmp_list)}
..
.. ** New **
.set need_ds ${uniq $(need_ds) $(need_New)}
.set need_ds_list ${uniq $(need_ds_list) $(need_New_list)}
..
.. ** ds **
.set need_ds ${deptype single $(need_ds) $(need_ds_list)}
.set need_ds_list ${uniq $(need_ds_list) $(need_ds) ${deptype list $(need_ds)}}
..
.. Enforce notwantdefs
.set notwantdefs ${uniq $(notwantdefs)}
.foreach v ${rmlist ds $(class)}
. foreach t $(need_$v)
.  if ${index $v$t $(notwantdefs)}
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
.  if ${index $v$tlist $(notwantdefs)}
.   set need_$v_list ${rmlist $t $(need_$v_list)}
.   set want_$v_list ${rmlist $t $(want_$v_list)}
.  endif
. endforeach
.endforeach
.foreach t $(need_$v_list)
. if ${index $tlist $(notwantdefs)}
.   set need_ds_list ${rmlist $t $(need_ds_list)}
.   set want_ds_list ${rmlist $t $(want_ds_list)}
. endif
.endforeach
.foreach f $(miscdefs)
. if ${index $f $(notwantdefs)}
.  set need_misc ${rmlist $f $(need_misc)}
.  set want_misc ${rmlist $f $(want_misc)}
. endif
.endforeach
..
.. ** derived definitions **
.if ${index Stat$(basename) $(need_misc)}
.set need_stat ${uniq $(need_New) $(need_Free)}
.set need_stat_list ${uniq $(need_New_list) $(need_Free_list)}
.set want_stat ${uniq $(want_New) $(want_Free)}
.set want_stat_list ${uniq $(want_New_list) $(want_Free_list)}
.else
.set need_stat
.set need_stat_list
.set want_stat
.set want_stat_list
.endif
