.. File: tmcanalize.t
..
.. Given a list of starting types and a list of types to reach, calculate
.. the list of types that must be visited to reach all targets
.set listpre
.set listsuff _list
.set err 0
.foreach m generate_formal_parameters generate_actual_parameters generate_reduction_operation generate_termination_test
.if ${not ${definedmacro $m}}
.error Macro $m not defined
.set err 1
.endif
.endforeach
.foreach v neutral_element reduction_type analysis_name
.if ${not ${defined $v}}
.error Variable $m not defined
.set err 1
.endif
.endforeach
.if $(err)
.exit 1
.endif
.foreach m generate_empty_walker_body
.if ${not ${definedmacro $m}}
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
.if ${not ${defined analyze_action_$t}}
.error No action defined for type `$t'
.if ${not ${len ${matchvar analyze_action_*}}}
.error To do this you must set variable analyze_action_$t
.endif
.endif
.switch ${first $(analyze_action_$t)}
.case constant
.if $[${len $(analyze_action_$t)!=2]
.error Action for type `$t' must be of the form `constant <value>'
.endif
.case function
.if $[${len $(analyze_action_$t)!=2]
.error Action for type `$t' must be of the form `function <functionname>'
.endif
.case reduction
.if $[${len $(analyze_action_$t)>2]
.error Action for type `$t' must be of the form `reduction'
.error "   or `reduction <const>'"
.endif
.default
.error Unknown action for type `$t': `${first $(analyze_action_$t)}'
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
static $(reduction_type) $(analysis_name)_$t${call generate_formal_parameters _e $t};
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
static $(reduction_type) $(analysis_name)_$t${call generate_formal_parameters _e $t};
{
    $(reduction_type) _res = $(neutral_element);
.switch ${metatype $t}
.case alias
.if ${member ${alias $t} $(visit_types)}
    _res = $(analysis_name)_${alias $t}${call generate_actual_parameters _e ${alias $t} $t};
.set empty 0
.endif
.case atom
.error Don not know what to do with atom $t
.case list
.if ${member ${delisttypes $t} $(visit_types)}
    {
	unsigned int ix;

	for( ix=0; ix<_e->sz; ix++ ){
	    $(reduction_type) _res1 = 
    _res1 = $(analysis_name)_${alias $t}${call generate_actual_parameters _e->arr[ix] $t $t};
	    _res = ${call generate_reduction _res _res1}
.if ${definedmacro generate_termination_test}
	    if( ${call generate_termination_test _res} ){
	        break;
	    }
.endif
.set empty 0
	}
    }
.endif
.case class constructor constructorbase
.set sub ${comm ${inheritors $t} "" $(visit_types)}
.if ${len $(sub)}
    switch( _e->tag ){
.foreach tor ${inheritors $t}
.set l ${comm $(tor) ${subclasses $(tor)} "" $(visit_types)}
.if ${len $l}
.foreach i $(tor) ${subclasses $(tor)}
.if ${not ${isvirtual $i}}
        case TAG$i:
.endif
.endforeach
.set action "$(analyze_action_$t)"
.switch ${first $(action)}
.case constant
	    _res = ${shift $(action)};
.set empty 0
.case function
	    _res = ${shift $(action)}${call generate_actual_parameters _e $(tor) $t};
.set empty 0
.case reduction
	    _res = 
.call generate_descent_call "	    " _e $(tor) $t
.endswitch
	    break;

.if ${not ${isvirtual $t}}
        case TAG$t:
.foreach f ${allfields $t}
.if ${member ${type $t $f} $(visit_types)}
.call generate_descent_call "	    " _e->$f ${type $t $f} ${type $t $f}
.set empty 0
.endif
.endforeach
            break;

.endif
.. TODO: enumerate the cases that are not handled.
	default:
	    break;

    }
.else
.foreach f ${allfields $t}
.if ${member ${type $t $f} $(visit_types)}
.call generate_descent_call "    " _e->$f ${type $t $f} ${type $t $f}
.set empty 0
.endif
.endforeach
.endif
.case tuple
set action "$(analyze_action_$t)"
.switch ${first action}
.case constant
.case function
.case reduction
.foreach f ${allfields $t}
.if ${member ${type $t $f} $(visit_types)}
	_res = ${generate_reduction_operation _res "${shift $(action)}${call generate_actual_parameters _e->f ${type $t $f} ${type $t $f}}"};
.set empty 0
.endif
.endforeach
.endswitch
.if $(empty)
.call generate_empty_walker_body "    " _e $t
.endif
    return _res;
}

.endforeach

/* ----------- Generated code ends here ----------- */
.endmacro
