.. Given a list of starting types and a list of types to reach, calculate
.. the list of types that must be visited to reach all targets
.set listpre
.set listsuff _list
.append valuetypes int long char uint ulong
.append legacytypes tmstring
.set err 0
.foreach m generate_walker_declaration generate_walker_signature generate_descent_call
.if ${not ${len ${matchmacro $m}}}
.error No macro $m defined
.set err 1
.endif
.endforeach
.if $(err)
.exit 1
.endif
.foreach m generate_walker_locals generate_walker_return generate_empty_walker_body
.if ${not ${len ${matchmacro $m}}}
.macro $m indent var t
.endmacro
.endif
.endforeach
..
.macro calc_treewalk starts targets
.set res
.set types ${reach $(starts)}
.set bad ${excl $(targets) "" $(types)}
.if ${len $(bad)}
.if ${== ${len $(bad)} 1}
.error Target type '$(bad)' cannot be reached.
.else
.error The following target types cannot be reached: [$(bad)].
.endif
.exit 1
.endif
.foreach t $(types)
.if ${len ${comm $(targets) "" ${reach $t}}}
.append res $t
.endif
.endforeach
.return $(res)
.endmacro
..
.. Given a list of types to visit, generate forward declarations
.. for the walk functions.
.. This is simply done by invoking the macro generate_walker_declaration
.. for each type.
.macro generate_walker_forwards list
/* ----------- Generated forward declarations start here ----------- */

/* Forward declarations. */
.foreach t $(list)
.call generate_walker_declaration e $t
.endforeach

/* ----------- Generated forward declarations end here ----------- */
.endmacro
..
.. The big one: given a list of types to visit, and a list of action functions,
.. generate walker and action code.
.macro generate_walker visit_types
/* ----------- Generated code starts here ----------- */

.foreach t $(visit_types)
.set empty 1
/* Walker for ${metatype $t} $t. */
.call generate_walker_signature e $t
{
.call generate_walker_locals "    " e $t
.switch ${metatype $t}
.case alias
.if ${member ${alias $t} $(visit_types)}
.call generate_descent_call "    " e ${alias $t} $t 
.set empty 0
.endif
.case atom
.case list
.if ${member ${delisttypes $t} $(visit_types)}
    {
	unsigned int ix;

	for( ix=0; ix<e->sz; ix++ ){
.call generate_descent_call "	    " e->arr[ix] ${delisttypes $t} ${delisttypes $t}
.set empty 0
	}
    }
.endif
.case class constructor constructorbase
.set sub ${comm ${inheritors $t} "" $(visit_types)}
.if ${len $(sub)}
    switch( e->tag ){
.foreach tor ${inheritors $t}
.if ${len ${comm $(tor) ${subclasses $(tor)} "" $(visit_types)}}
.foreach i ${comm $(tor) ${subclasses $(tor)} "" $(visit_types)}
.if ${not ${isvirtual $i}}
        case TAG$i:
.endif
.endforeach
.call generate_descent_call "	    " e $(tor) $t
.set empty 0
	    break;

.endif
.endforeach
.if ${not ${isvirtual $t}}
        case TAG$t:
.foreach f ${allfields $t}
.if ${member ${type $t $f} $(visit_types)}
.call generate_descent_call "	    " e->$f ${type $t $f} ${type $t $f}
.set empty 0
.endif
.endforeach
            break;

.endif
.. TODO: enumerate the cases that aren't handled.
	default:
	    break;

    }
.else
.foreach f ${allfields $t}
.if ${member ${type $t $f} $(visit_types)}
.call generate_descent_call "    " e->$f ${type $t $f} ${type $t $f}
.set empty 0
.endif
.endforeach
.endif
.case tuple
.foreach f ${allfields $t}
.if ${member ${type $t $f} $(visit_types)}
.call generate_descent_call "    " e->$f ${type $t $f} ${type $t $f}
.set empty 0
.endif
.endforeach
.endswitch
.if $(empty)
.call generate_empty_walker_body "    " e $t
.endif
.call generate_walker_return "    " e $t
}

.endforeach

/* ----------- Generated code ends here ----------- */
.endmacro
