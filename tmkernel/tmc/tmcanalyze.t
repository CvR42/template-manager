.. File: tmcanalize.t
..
.. Given a list of starting types and a list of types to reach, calculate
.. the list of types that must be visited to reach all targets
.set listpre
.set listsuff _list
.set err 0
.foreach m generate_formal_parameters generate_actual_parameters generate_reduction_operation
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
.foreach m generate_empty_analyzer_body
.if ${not ${definedmacro $m}}
.macro $m indent t
.endmacro
.endif
.endforeach
..
.macro calc_analyzer starts targets
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
.error No action defined for type '$t'
.if ${not ${len ${matchvar analyze_action_*}}}
.error To do this you must set variable analyze_action_$t
.endif
.else
.switch ${first $(analyze_action_$t)}
.case ignore
.if $[${len $(analyze_action_$t)}!=1]
.error Action 'ignore' for type '$t' should not have any parameters
.endif
.case constant
.if $[${len $(analyze_action_$t)}!=2]
.error Action for type '$t' must be of the form 'constant <value>'
.endif
.case function
.if $[${len $(analyze_action_$t)}!=2]
.error Action for type '$t' must be of the form 'function <functionname>'
.endif
.case reduction
.if $[${len $(analyze_action_$t)}>2]
.error Action for type '$t' must be of the form 'reduction'
.error "   or 'reduction <const>'"
.endif
.default
.error Unknown action for type '$t': '${first $(analyze_action_$t)}'
.endswitch
.endif
.endif
.endforeach
.return $(res)
.endmacro
..
.. Given a list of types to visit, generate forward declarations
.. for the analizer functions.
.macro generate_analyzer_forwards list
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
.macro generate_analyzer visit_types
/* ----------- Generated code starts here ----------- */

.foreach t $(visit_types)
.set empty 1
/* Walker for ${metatype $t} $t. */
static $(reduction_type) $(analysis_name)_$t${call generate_formal_parameters _e $t}
{
    $(reduction_type) _res;
.set action "$(analyze_action_$t)"
.switch ${metatype $t}
.case alias
.switch ${first $(action)}
.case ignore
    _res = $(neutral_element);
.case constant
    _res = ${shift $(action)};
.case function
    _res = ${shift $(action)}${call generate_actual_parameters _e $t $t};
.set empty 0
.case reduction
.if $[${len $(action)}==2]
.. There also is a local value to take into consideration
.if ${member ${alias $t} $(visit_types)}
    _res = ${call generate_reduction "${shift $(action)}" "$(analysis_name)_${alias $t}${call generate_actual_parameters _e ${alias $t} $t}"};
.else
    _res = ${shift $(action)};
.endif
.set empty 0
.else
.if ${member ${alias $t} $(visit_types)}
    _res = $(analysis_name)_${alias $t}${call generate_actual_parameters _e ${alias $t} $t};
.set empty 0
.endif
.endif
.endswitch
.case atom
.switch ${first $(action)}
.case ignore
    _res = $(neutral_element);
.case reduction
.. Only do something if there is a local value for the reduction.
.if $[${len $(action)}==2]
    _res = ${shift $(action)};
.set empty 0
.endif
.case constant
    _res = ${shift $(action)};
.case function
    _res = ${shift $(action)}${call generate_actual_parameters _e $t $t};
.set empty 0
.endswitch
.case list
.switch ${first $(action)}
.case ignore
    _res = $(neutral_element);
.case constant
    _res = ${shift $(action)};
.case function
    _res = ${shift $(action)}${call generate_actual_parameters _e $t $t};
.set empty 0
.case reduction
.set elmtype ${delisttypes $t}
.if $[${len $(action)}==2]
    _res = ${shift $(action)};
.else
    _res = $(neutral_element);
.endif
.if ${member $(elmtype) $(visit_types)}
    {
	unsigned int ix;

	for( ix=0; ix<_e->sz; ix++ ){
	    $(reduction_type) _res1 = $(analysis_name)_$(elmtype)${call generate_actual_parameters _e->arr[ix] $(elmtype) $(elmtype)};
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
.endswitch
.case class constructor constructorbase
.set sub ${comm ${inheritors $t} "" $(visit_types)}
.if ${len $(sub)}
    switch( _e->tag ){
.foreach tor ${inheritors $t}
.set l ${comm $(tor) ${subclasses $(tor)} "" $(visit_types)}
.if ${len $l}
.. There are subclasses to consider.
.foreach i $(tor) ${subclasses $(tor)}
.if ${not ${isvirtual $i}}
        case TAG$i:
.endif
.endforeach
.set action "$(analyze_action_$t)"
.switch ${first $(action)}
.case ignore
	    _res = $(neutral_element);
.case constant
	    _res = ${shift $(action)};
.case function
	    _res = ${shift $(action)}${call generate_actual_parameters _e $t $t};
.set empty 0
.case reduction
	    _res = $(analysis_name)_$(tor)${call generate_actual_parameters _e $(tor) $t};
.set empty 0
.endswitch
	    break;

.endif
.endforeach
.if ${not ${isvirtual $t}}
        case TAG$t:
.foreach f ${allfields $t}
.if ${member ${type $t $f} $(visit_types)}
	_res = ${call generate_reduction_operation _res "$(analysis_name)_${type $t $f}${call generate_actual_parameters _e->$f ${type $t $f} ${type $t $f}}"};
.set empty 0
.endif
.endforeach
            break;

.endif
.. TODO: enumerate the cases that are not handled.
	default:
	    _res = $(neutral_element);
	    break;

    }
.else
.set action "$(analyze_action_$t)"
.switch ${first $(action)}
.case ignore
    _res = $(neutral_element);
.case constant
    _res = ${shift $(action)};
.case function
    _res = ${shift $(action)}${call generate_actual_parameters _e $t $t};
.set empty 0
.case reduction
.if $[${len $(action)}==2]
    _res = ${shift $(action)};
.else
    _res = $(neutral_element);
.endif
.foreach f ${allfields $t}
.if ${member ${type $t $f} $(visit_types)}
    _res = ${call generate_reduction_operation _res "$(analysis_name)_${type $t $f}${call generate_actual_parameters _e->$f ${type $t $f} ${type $t $f}}"};
.set empty 0
.endif
.endforeach
.endswitch
.endif
.case tuple
set action "$(analyze_action_$t)"
.switch ${first action}
.case ignore
	_res = $(neutral_element);
.case constant
	_res = ${shift $(action)};
.case function
	_res = ${shift $(action)}${call generate_actual_parameters _e $t $t};
.set empty 0
.case reduction
.if $[${len $(action)}==2]
    _res = ${shift $(action)};
.else
    _res = $(neutral_element);
.endif
.foreach f ${allfields $t}
.if ${member ${type $t $f} $(visit_types)}
	_res = ${call generate_reduction_operation _res "$(analysis_name)_${type $t $f}${call generate_actual_parameters _e->$f ${type $t $f} ${type $t $f}}"};
.set empty 0
.endif
.endforeach
.endswitch
.endswitch
.if $(empty)
    (void) _e;
.call generate_empty_analyzer_body "    " $t
.endif
    return _res;
}

.endforeach

/* ----------- Generated code ends here ----------- */
.endmacro
