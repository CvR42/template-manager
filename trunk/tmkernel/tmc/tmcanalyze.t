.. File: tmcanalize.t
..
.. Generate an analyzer.
..
.set listpre
.set listsuff _list
..
..
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
.. Given a list of starting types and a list of types to reach, calculate
.. the list of types that must be visited to reach all targets
.macro calc_analyzer starts targets
.set explained 0
.set ignores
.set blocking
.foreach t $(targets)
.if ${not ${defined analyze_action_$t}}
.error No action defined for type '$t'
.if ${and ${not $(explained)} ${not ${len ${matchvar analyze_action_*}}}}
.error To do this you must set variable analyze_action_$t
.set explained 1
.endif
.else
.switch ${first $(analyze_action_$t)}
.case ignore
.if $[${len $(analyze_action_$t)}!=1]
.error Action 'ignore' for type '$t' should not have any parameters
.endif
.append ignores $t
.append blocking $t
.case constant
.if $[${len $(analyze_action_$t)}!=2]
.error Action for type '$t' must be of the form 'constant <value>'
.endif
.append blocking $t
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
.endforeach
..
.. TODO: Optimize by filtering out types that have 'ignore' as action.
.set res
.set types ${reach $(starts) "" $(blocking)}
.set bad ${excl $(targets) "" $(types)}
.if ${len $(bad)}
.if ${== ${len $(bad)} 1}
.error Target type '$(bad)' cannot be reached.
.else
.error The following target types cannot be reached: [$(bad)].
.endif
.exit 1
.endif
..
.set actiontargets ${excl $(targets) "" $(ignores)}
.foreach t $(types)
.if ${len ${comm $(actiontargets) "" ${reach $t}}}
.append res $t
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
.set skip 0
.if ${defined analyze_action_$t}
.if ${member ${first $(analyze_action_$t)} constant ignore}
.set skip 1
.endif
.endif
.if $(skip)
/* Analyzer for ${metatype $t} $t not needed. Action: $(analyze_action_$t) */
.else
static $(reduction_type) $(analysis_name)_$t${call generate_formal_parameters _e $t};
.endif
.endforeach

/* ----------- Generated forward declarations end here ----------- */
.endmacro
..
.. The big one: given a list of types to visit, and a list of action functions,
.. generate walker and action code.
.macro generate_analyzer visit_types
/* ----------- Generated code starts here ----------- */

.foreach t $(visit_types)
.set skip 0
.if ${defined analyze_action_$t}
.if ${member ${first $(analyze_action_$t)} constant}
.set skip 1
.endif
.endif
.if ${not $(skip)}
.set empty 1
/* Analyzer for ${metatype $t} $t. */
static $(reduction_type) $(analysis_name)_$t${call generate_formal_parameters _e $t}
{
    $(reduction_type) _res;
.if ${definedmacro generate_setup_code}
.call generate_setup_code $t "    " _e _res
.endif
.if ${defined analyze_action_$t}
.set action "$(analyze_action_$t)"
    /* Action: $(action) */
.else
    /* Action: (unspecified, using reduction) */
.set action reduction
.endif
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
    _res = ${call generate_reduction_operation "${shift $(action)}" "$(analysis_name)_${alias $t}${call generate_actual_parameters _e ${alias $t} $t}"};
.set empty 0
.else
    _res = ${shift $(action)};
.endif
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
	    _res = ${call generate_reduction_operation _res "$(analysis_name)_$(elmtype)${call generate_actual_parameters _e->arr[ix] $(elmtype) $(elmtype)}"};
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
.if ${not ${defined analyze_action_$(tor)}}
	    _res = $(analysis_name)_$(tor)${call generate_actual_parameters _e $(tor) $t};
.else
.set action "$(analyze_action_$(tor))"
.switch ${first $(action)}
.case ignore
	    _res = $(neutral_element);
.case constant
	    _res = ${shift $(action)};
.case function
	    _res = ${shift $(action)}${call generate_actual_parameters _e $(tor) $t};
.set empty 0
.case reduction
	    _res = $(analysis_name)_$(tor)${call generate_actual_parameters _e $(tor) $t};
.set empty 0
.endswitch
.endif
	    break;

.endif
.endforeach
.if ${not ${isvirtual $t}}
        case TAG$t:
.foreach f ${allfields $t}
.set ft ${type $t $f}
.if ${member $(ft) $(visit_types)}
.if ${neq ${first $(analyze_action_$(ft))} ignore}
.if ${defined analyze_action_$(ft)}
.set field_action $(analyze_action_$(ft))
.else
.set field_action reduction
.endif
.if ${eq ${first $(field_action)} constant}
.set impl "${shift $(field_action)}"
.else
.set impl "$(analysis_name)_$(ft)${call generate_actual_parameters _e->$f $(ft) $(ft)}"
.endif
	    _res = ${call generate_reduction_operation _res "$(impl)"};
.set empty 0
.endif
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
    /* No subclasses */
.if ${defined analyze_action_$t}
.set action "$(analyze_action_$t)"
.else
.set action reduction
.endif
.switch ${first $(action)}
.case ignore
    _res = $(neutral_element);
.case constant
    _res = ${shift $(action)};
.case function
    _res = ${shift $(action)}${call generate_actual_parameters _e $t $t};
.set empty 0
.case reduction
.set first 1
.if $[${len $(action)}==2]
    _res = ${shift $(action)};
.set first 0
.endif
.foreach f ${allfields $t}
.set ft ${type $t $f}
.if ${member $(ft) $(visit_types)}
.if ${neq ${first $(analyze_action_$(ft))} ignore}
.if ${defined analyze_action_$(ft)}
.set field_action $(analyze_action_$(ft))
.else
.set field_action reduction
.endif
.if ${eq ${first $(field_action)} constant}
.set impl "${shift $(field_action)}"
.else
.set impl "$(analysis_name)_$(ft)${call generate_actual_parameters _e->$f $(ft) $(ft)}"
.endif
.if $(first)
    _res = $(impl);
.set first 0
.else
    _res = ${call generate_reduction_operation _res "$(impl)"};
.endif
.set empty 0
.endif
.endif
.endforeach
.endswitch
.endif
.case tuple
.if ${defined analyze_action_$t}
.set action "$(analyze_action_$t)"
.else
.set action reduction
.endif
.switch ${first $(action)}
.case ignore
    _res = $(neutral_element);
.case constant
    _res = ${shift $(action)};
.case function
    _res = ${shift $(action)}${call generate_actual_parameters _e $t $t};
.set empty 0
.case reduction
.set first 1
.if $[${len $(action)}==2]
    _res = ${shift $(action)};
.set first 0
.else
    _res = $(neutral_element);
.endif
.foreach f ${allfields $t}
.set ft ${type $t $f}
.if ${member $(ft) $(visit_types)}
.if ${defined analyze_action_$(ft)}
.set field_action $(analyze_action_$(ft))
.else
.set field_action reduction
.endif
.if ${eq ${first $(field_action)} constant}
.set impl "${shift $(field_action)}"
.else
.set impl "$(analysis_name)_$(ft)${call generate_actual_parameters _e->$f $(ft) $(ft)}"
.endif
.if $(first)
    _res = $(impl);
.set first 0
.else
    _res = ${call generate_reduction_operation _res "$(impl)"};
.endif
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

.endif
.endforeach

/* ----------- Generated code ends here ----------- */
.endmacro
