..file: typedef.t
.. Generate Clean datastructure definitions
.set listpre [
.set listsuff ]
.foreach t $(need_ds)
.if ${len ${telmlist $t}}
.set el
.foreach e ${telmlist $t}
.append el ${mklist ${ttypellev $t $e} ${capitalize ${ttypename $t $e}}}
.endforeach
TYPE :: ${capitalize $t} -> (${seplist ", " $(el)});

.else
TYPE
:: ${capitalize $t}
.foreach c ${conslist $t}
.set el
.foreach e ${celmlist $t $c}
.append el ${mklist ${ctypellev $t $c $e} ${capitalize ${ctypename $t $c $e}}}
.endforeach
   -> $c $(el)
.endforeach
   ;

.endif
.endforeach
