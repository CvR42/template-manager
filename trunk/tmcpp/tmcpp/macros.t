.. File: macros.t
.. Macros used by all templates.
..
.. Given a function class 'cl' (e.g. 'setroom_list') and 
.. a function template 'tpl', generate forward declarations
.. with prototypes for all functions that are supposed to be
.. static.
.. The template 'tpl' is supposed to contain '$t' at the appropriate
.. places.
.macro ansi_static cl tpl
.set tl ${excl $(need_$(cl)) "" $(want_$(cl))}
.if ${len $(tl)}
.foreach t $(tl)
static ${eval "$(tpl)"};
.endforeach
.endif
.endmacro
..
.. Given an element list 'el', a type inquiry function 'tf' and 
.. a list level inquiry function 'llf', return a ANSI style function
.. prototype.
.macro ansi_nproto t el
. set tl
. set sep
. foreach e $(el)
.  set et ${type $t $e}
.  if ${member $(et) $(valuetypes)}
.   set tl "$(tl)$(sep)${type $t $e} p_$e"
.  else
.   set tl "$(tl)$(sep)${type $t $e} *p_$e"
.  endif
.  set sep ", "
. endforeach
. return "$(tl)"
.endmacro
..
.. Given a type 't' and an element list 'el', 
.. a return a ANSI style function
.. prototype, suitable for lognew purposes.
.macro ansi_nproto_lognew t el
. set tl
. set sep
. foreach e $(el)
.  set et ${type $t $e}
.  if ${member $(et) $(valuetypes)}
.   set tl "$(tl)$(sep)${type $t $e} p_$e"
.  else
.   set tl "$(tl)$(sep)${type $t $e} *p_$e"
.  endif
.  set sep ", "
. endforeach
. set tl "$(tl)$(sep)const char *_f, const int _l"
. return "$(tl)"
.endmacro
..
.. Given a list name (without the last '_list') return the
.. link name for that list name
.macro linkname nm
.return ${subs ${stemname $(nm)}(*) next\1  $(nm)}
.endmacro
..
.. Given a list of types, ensure that none of these types is
.. virtual and has no subclasses
.macro no_childless_virtual l
.set bad 0
.foreach t $l
.if ${isvirtual $t}
.if $[${len ${subclasses $t}}<1]
.error '$t' is virtual but has no children.
.set bad 1
.endif
.endif
.endforeach
.if $(bad)
.exit 1
.endif
.endmacro
..
.. Given a list of types, ensure that none of these types has
.. multiple inheritance
.macro no_multiple_inheritance l
.set bad 0
.foreach t $l
.if $[${len ${inherits $t}}>1]
.if $(bad)
.else
.error Multiple inheritance not supported in this template.
.set bad 1
.endif
.error $t inherits ${seplist ", " ${inherits $t}}
.endif
.endforeach
.if $(bad)
.exit 1
.endif
.endmacro
..
.. Given a type t, return its root class
.macro rootclass t
.if ${member $t ${typelist}}
.set root ${inherits $t}
.while ${len $(root)}
.set t $(root)
.set root ${inherits $t}
.endwhile
.endif
.return $t
.endmacro
..
.. Apply all aliases, and delete the alias types.
.macro apply_aliases
.foreach t ${aliases}
.set nt ${alias $t}
.. They must be deleted, since they would cause circular definitions
.. complaints. After all, after application each alias
..    told -> tnew;
.. would read:
..    tnew -> tnew;
.deletetype $t
.rename $t $(nt)
.endforeach
.endmacro
