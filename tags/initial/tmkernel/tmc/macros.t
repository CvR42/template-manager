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
.macro ansi_nproto el tf llf
. set tl
. set sep
. foreach e $(el)
.  set tl "$(tl)$(sep)${mklist ${$(llf) $e} ${$(tf) $e}} p_$e"
.  set sep ", "
. endforeach
. if ${== ${len $(tl)} 0}
.  set tl void
. endif
. return "$(tl)"
.endmacro
..
.. Given an element list 'el', a type inquiry function 'tf' and 
.. a list level inquiry function 'llf', return a ANSI style function
.. prototype, suitable for lognew purposes.
.macro ansi_nproto_lognew el tf llf
. set tl
. set sep
. foreach e $(el)
.  set tl "$(tl)$(sep)${mklist ${$(llf) $e} ${$(tf) $e}} p_$e"
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
.. Try to expand inherits. This is only possible in more recent
.. versions of Tm. If there are no inherits, also accept older
.. versions, but warn that one should upgrade.
.macro expand_inherits
. expandinherits ${typelist}
.endmacro
