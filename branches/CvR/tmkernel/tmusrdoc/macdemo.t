..File: macdemo.t
..Demonstration of use of tm text substitution.
..Collect defined type names, constructor names, element names
..and used type names, and list each of them.
..Clear all the lists
.set dct
.set dtt
.set dc
.set de
.set ut
.foreach t ${typelist}
. if ${member $t ${ctypelist}}
.  append dct $t
.  append dc ${conslist $t}
.  foreach c ${conslist $t}
.   append de ${celmlist $t $c}
.   foreach e ${celmlist $t $c}
.    append ut ${ctypename $t $c $e}
.   endforeach
.  endforeach
. else
.  append dtt $t
.  foreach e ${telmlist $t}
.   append ut ${ttypename $t $e}
.  endforeach
. endif
.endforeach
Defined tuple types  : ${seplist ", " ${uniq $(dtt)}}
Defined const. types : ${seplist ", " ${uniq $(dct)}}
Defined constructors : ${seplist ", " ${uniq $(dc)}}
Defined element names: ${seplist ", " ${uniq $(de)}}
Used types           : ${seplist ", " ${uniq $(ut)}}
