.. Tm - an interface code generator.
.. Author: C. van Reeuwijk.
..
.. All rights reserved.

.. File: testin
..
.. test command file for tm.
.. Attempts an exhausive test of all functions and commands.
..
.rename filename_string string
..
VARIABLES:
----
.set a 12
.set av z y x
.set z GOOD!
'$a'
'$(a)'
'$(${first $(av)})'
'$(iserniet)'
'$(a'
.set a
'$a'
'$(a)'
'$$' '$.' '$"'
.append av $(av)
.append unknownvariable bla bla bla
unknownvariable: '$(unknownvariable)'
'$(av)'
.set x "a"
.set y "\"a"
$x $y
----
Special variables:
dollar: '$$'
dot: '$.'
double quote: '$"'

COMMANDS:
---------

if:
----
.if 1
if 1 done
.else
if 1 not done
.endif
----
.if 0
if 0 done
.else
if 0 not done
.endif
----
.if ""
if "" done
.else
if "" not done
.endif
----

switch:
----
.switch bla
.endswitch
--
.switch bla
.default
Default of switch
.endswitch
--
.switch bla
.case bla
Case 'bla'
.default
Default of switch
.endswitch
--
.switch bla bla
.case bla
Case 'bla'
.default
Default of switch
.endswitch
--
.switch bla
Bad line
.case bla
Case 'bla'
.default
.default
Default of switch
.endswitch
--
.foreach v a b c d e f
.switch $v
.case a c
$v: 1
.case d
$v: 2
.case a d
$v: 3
.default
$v: default
.endswitch
.endforeach
----
.foreach v aap boek ccc daf eend fado
.switch $v
.case a* b*
$v: 1
.case d*
$v: 2
.case a* d*
$v: 3
.default
$v: default
.endswitch
.endforeach
----

for:
---
.for v 0 5
v = $v
.endfor
--
.for v 0 5 2
v = $v
.endfor
--
.for v 5 0
v = $v
.endfor
--
.for v 0 0
v = $v
.endfor
--
.for v 0 5 -2
v = $v
.endfor
--
.for v
v = $v
.endfor
--
.for v 0
v = $v
.endfor
--
.for v a
v = $v
.endfor
--
.for v 0 a
v = $v
.endfor
--
.for v 0 5 a
v = $v
.endfor
---

insert:
----
.set var ladidah
var = `$(var)'
.insert testsub
var = `$(var)'
----

include:
----
.set var ladidah
var = `$(var)'
.include testsub
var = `$(var)'
----

redirect:
----
.redirect testrdir
Dit moet in de redirect file te komen
.endredirect
.appendfile testrdir
En dit wordt er achter geplakt.
.endappendfile
----

error:
----
.error
.error error message line
.set msg "this is a message line"
.error $(msg)
----

foreach:
----
.foreach i a b c d
$i
.endforeach
----
.foreach i
$i
.endforeach
----

while:
----
.set l 1 2 3 4 5 6 7
.while ${len $l}
$l
.set l ${shift $l}
.endwhile
----

FUNCTIONS:
----------

Comparison functions:
----
eq : '${eq a a }' '${eq 0 00}' '${eq a aaaaaa}'
neq: '${neq a a}' '${neq 0 00}' '${neq a aaaaa}'
strcmp: '${strcmp a a}' '${strcmp 0 00}' '${strcmp 00 0}' '${strcmp a aaaaa}'
== : '${== 3 3 }' '${== 3 5}' '${== 3 -3}' '${== 3 a}'
!= : '${!= 3 3 }' '${!= 3 5}' '${!= 3 -3}' '${!= 3 a}'
<  : '${< 4 5}' '${< 4 4}' '${< 2 1}'
<= : '${<= 4 5}' '${<= 4 4}' '${<= 2 1}'
>  : '${> 4 5}' '${> 4 4}' '${> 2 1}'
>= : '${>= 4 5}' '${>= 4 4}' '${>= 2 1}'
----

Aritmetic functions:
----
+: '${+ 1 2 3 4 5}' '${+ 3}' '${+}'
-: '${- 5 1}' '${- 1 5}' '${- 1}'
*: '${* 1 2 3 4 5}' '${* 3}' '${*}'
/: '${/ 12 3}' '${/ 11 3}' '${/ 13 3}' '${/ 3 13}'
%: '${% 12 3}' '${% 11 3}' '${% 13 3}' '${% 3 13}'
max: '${max -1 1 2 3 4 5}' '${max 3}' '${max}'
min: '${min -1 1 2 3 4 5}' '${min 3}' '${min}'
bits: '${bits -1 0 1 2 3 4 5 6 7 8}' '${bits 3}' '${bits}'
----

Boolean:
----
and: '${and 1 1 1}' '${and 0 1 1}' '${and}'
not: '${not 1}' '${not 0}' '${not ""}' '${not}'
or:  '${or 0 0 0 0}' '${or 1 0 0}' '${or}'
----

If
--
.foreach b 0 1
if $b: [${if $b true false}] [${if $b true}] [${if $b}]
.endforeach
[${if}]

List manipulation:
----
.set lst a b c d e f
index:   '${index a $(lst)}' '${index z $(lst)}' '${index z}' '${index}'
member:  '${member a $(lst)}' '${member z $(lst)}' '${member z}' '${member}'
shift:   '${shift $(lst)}' '${shift}'
first:   '${first $(lst)}' '${first}'
seplist: '${seplist ", " $(lst)}' '${seplist a a}' '${seplist a}'
prefix:  '${prefix pfx_ $(lst)}' '${prefix pfx_ a}' '${prefix pfx_}'
suffix:  '${suffix _sfx $(lst)}' '${suffix _sfx a}' '${suffix _sfx}'
len:     '${len $(lst)}' '${len a}' '${len}'
sort:    '${sort $(lst) $(lst)}' '${sort 1 2 12 -1}' '${sort }'
sizesort:'${sizesort ${typelist}}' '${sizesort 1 2 12 -1}' '${sizesort }'
uniq:    '${uniq $(lst) $(lst)}' '${uniq 1 2 12 -1}' '${uniq }'
rev:     '${rev $(lst)}' '${rev}'
----

Regular expressions:
----
.set wildstring foobar fobar foo bar blabar a b barf foofoo barbar ian
.foreach fn subs filt
funtion: $(fn)
.foreach pats "* [&]" "foo* 1" "foo* &&" "(foo)* &\1" "(foo)(*) \2\1"
$(pats): [${$(fn) $(pats) $(wildstring)}]
.endforeach
.foreach pats "[a-e]* !&" "(?)(*)(?) \3\2\1"
$(pats): [${$(fn) $(pats) $(wildstring)}]
.endforeach

.endforeach
funtion: rmlist
.foreach pats "foo*" "foo*" "(foo)*"  "foo(*)" "(foo)(*)" "[a-e]*" "(?)(*)(?)"
$(pats): [${rmlist $(pats) $(wildstring)}]
.endforeach
----

Filename access functions:
----
dsfilename: '${ dsfilename }'
tplfilename: '${ tplfilename }'
tpllineno: '${ tpllineno }'
.set path ${searchpath}
${eq ${first $(path)} $(libpath)} ${shift $(path)}
${searchfile testsub}
----
Datastructure access functions:

.foreach pass 1 2 3 4
Pass $(pass)
.if ${eq $(pass) 2}
.set listpre [
.endif
.if ${eq $(pass) 3}
.set listsuff ]
.endif
.if ${eq $(pass) 4}
.set listpre
.endif
mklist: ${mklist 0 test a} ${mklist 1 test a} ${mklist 5 test a} ${mklist} ${mklist 5}
stemname: ${stemname a b] [c [d] [e]] a[f] [[g]]}
listtypes: ${listtypes a b] [c [d] [e]] a[f] [[g]]}
delisttypes: ${delisttypes a b] [c [d] [e]] a[f] [[g]]}
singletypes: ${singletypes a b] [c [d] [e]] a[f] [[g]]}
.endforeach
inherits: ${inherits} ${inherits iserniet}
inheritors: ${inheritors} ${inheritors iserniet}
superclasses: ${superclasses} ${superclasses iserniet}
subclasses: ${subclasses} ${subclasses iserniet}
.set listsuff _list
reach: [${reach}] [${reach iserniet}] [${reach toplevel "" Toptuple}]
conslist: ${conslist} ${conslist bla bla} ${conslist notatype}
fields: ${fields} ${fields bla bla} ${fields notatype}
allfields: ${allfields} ${allfields bla bla} ${allfields notatype}
types: '${types}'
.set listpre [
.set listsuff ]
.set l ${typelist} bla ${mklist 1 ${typelist}}
alias <aliases>: '${alias ${aliases}}'
alias <mklist 2 aliases>: '${alias ${mklist 2 ${aliases}}}'
alias <all>: '${alias $l}'
fields <all>: '${fields $l}'
allfields <all>: '${allfields $l}'
metatype <all>: '${metatype $l}'
virtual <all>: '${virtual $l}'
nonvirtual <all>: '${nonvirtual $l}'
.set bad ${excl ${sort $l} "" ${sort ${virtual $l} ${nonvirtual $l}}}
.if ${len $(bad)}
Returned by both virtual and nonvirtual: '$(bad)'
.else
virtual and nonvirtual behave as they should
.endif
.set bad ${excl ${sort ${virtual $l} ${nonvirtual $l}} "" ${sort $l}}
.if ${len $(bad)}
Returned by neither virtual or nonvirtual: '$(bad)'
.else
virtual and nonvirtual behave as they should
.endif
types <all>: '${types ${typelist}}'
alltypes <all>: '${alltypes ${typelist}}'
subclasses <all>: '${subclasses ${typelist}}'
reach <all>: '${reach ${typelist}}'
conslist <all>: '${conslist ${typelist}}'
metatype: ${metatype} ${metatype a b c} ${metatype a} ${metatype [a]}

=-=-=-=
.set listpre
.set listsuff _list
typelist: '${typelist}'
tuplelist: '${tuplelist}'
ctypelist: '${ctypelist}'
classlist: '${classlist}'
aliases: '${aliases}'
.foreach t ${typelist}
    conslist $t: '${conslist $t}'
    inherits $t: '${inherits $t}'
    inheritors $t: '${inheritors $t}'
    superclasses $t: '${superclasses $t}'
    subclasses $t: '${subclasses $t}'
    reach $t: '${reach $t}'
    isvirtual $t: '${isvirtual $t}'
    metatype $t: '${metatype $t}'
.foreach c ${conslist $t}
        celmlist $t $c: '${celmlist $t $c}'
        fields $c: '${fields $c}'
        allfields $c: '${allfields $c}'
.foreach e ${celmlist $t $c}
            ctypeclass $t $c $e: '${ctypeclass $t $c $e }'
	    ctypellev $t $c $e: ${ctypellev $t $c $e}
            ctypename $t $c $e: '${ctypename $t $c $e }'
	    ttypeclass $c $e: '${ttypeclass $c $e }'
	    typelevel $c $e: ${typelevel $c $e}
	    typename $c $e: '${typename $c $e}'
	    type $c $e: '${type $c $e}'
.endforeach
.endforeach
    fields $t: '${fields $t}'
    allfields $t: '${allfields $t}'
.foreach e ${allfields $t}
	ttypeclass $t $e: '${ttypeclass $t $e }'
	typelevel $t $e: ${typelevel $t $e}
	typename $t $e: '${typename $t $e}'
	type $t $e: '${type $t $e}'
.endforeach
.endforeach
----

Datastructure dependency
----
.set listpre
.set listsuff _list
.foreach t ${typelist}
..single types dependent on $t: '${deptype single $t}'
..list types dependent on $t: '${deptype list $t}'
.endforeach
Testing error handling:
..'${deptype list}'
..'${deptype reutel ${first ${typelist}}}'
..'${deptype}'
Type sorting:
depsort: [${depsort int_list int ${typelist}} ]
inheritsort: [${inheritsort int_list int ${typelist}} ]
----

String manipulation functions:
----
strpad: '${strpad bla 6 " "}' '${strpad abcdef 3 !}' '${strpad bla 11 wow}'
strpad: '${strpad "" 5 0}' '${strpad zwoing 10 ""}'
strlen: '${strlen <word> }' '${strlen ""}' '${strlen}'
leftstr: '${leftstr 3 abcdef}' '${leftstr 3 abcdef ABCDEF}' '${leftstr 3}'
leftstr: '${leftstr 12 abcdef}' '${leftstr -1 abcdef}'  '${leftstr}'
rightstr: '${rightstr 3 abcdef}' '${rightstr 3 abcdef ABCDEF}' '${rightstr 3}'
rightstr: '${rightstr 12 abcdef}' '${rightstr -1 abcdef}'  '${rightstr}'
strindex: '${strindex c abcdef}' '${strindex z abcdef}'
toupper: '${toupper bla}' '${toupper BLA bla Bla}' '${toupper}'
tolower: '${tolower bla}' '${tolower BLA bla Bla}' '${tolower}'
tochar: '${tochar 33}' '${tochar 65 66 67 126}' '${tochar}' '${tochar -1 256}'
capitalize: '${capitalize bla}' '${capitalize BLA bla Bla}' '${capitalize}'
tr: '${tr far ver bla are a Ab fever favor}' '${tr fe}' '${tr}' '${tr ab b}'
tr: '${tr - " " string-list words [a---a]}'
----

Miscellaneous functions:
----
.set yes
${defined yes} ${defined doesnotexist} ${defined} ${defined yes yes}
isinenv: [${isinenv PATH}] [${isinenv NOT_LIKELY_ENVIRONMENT_VARIABLEX}] [${isinenv}]
----

verbose flag and other command line settings:
----
verbose = '$(verbose)'
test1 = '$(test1)'
test2 = '$(test2)'
----

.foreach fn comm excl
$(fn):
----
'${$(fn) a b c d e f a b c d e f "" a e g h a}'
'${$(fn) a b c d}'
'${$(fn) a b c d ""}'
'${$(fn) "" a b c d}'
----

.endforeach

Integer expressions
-------------------

'$[-12]' '$[--12]'
'$[12+-12]' '$[1+2+3+4+5+6+7]'
'$[12*12+13*13]' '$[1*2*3*4*5*6*7]' '$[12/12]' '$[42%13]'
Left binding operators: '$[3-2-1]' '$[16/4/2]' '$[15%4%2]'
.foreach op < <= > >= != ==
$(op): '$[1$(op)2]' '$[-1$(op)-2]' '$[-1$(op)2]' '$[1$(op)-2]' '$[-42$(op)-42]'
.endforeach
.foreach op | & == != < <= >= >
 $(op)
-------
.foreach a 0 1
.foreach b 0 1
$a $b | $[$a$(op)$b]
.endforeach
.endforeach

.endforeach
$[((12))]
'$[]' '$[12+]' '$[12'
'$[a]' '$[12/0]' '$[12%0]'

Buffer size test.
Create a list with 2k worth elements.
.set l 0123456789
.while $[${len $l}<200]
.set l $l $l
${len $l}
.endwhile

Macros
------
.. Test macro faciliteiten
..
.macro test a b
.set v $a $b
[Start macro]
a:[$a]
b:[$b]
v:[$v]
[end macro]
.endmacro
..
.set v toplevelv
v:[$v]
.call test 12 34
v:[$v]
.call test a b
v:[$v]
.call test "1 2 3 4 5 6 7" "a b c d e"
v:[$v]
..
.macro test a b
.set v $a $b
..
.macro submacro nm l
$(nm):[$l] (done by macro 'submacro')
.endmacro
..
[Start new macro]
.call submacro a "$a"
.call submacro b "$b"
.call submacro v "$v"
[end new macro]
.endmacro
..
v:[$v]
.call test 12 34
v:[$v]
.call test a b
v:[$v]
.call test "1 2 3 4 5 6 7" "a b c d e"
v:[$v]
.call submacro l "a b c"
.call test a
.call test a b c
.call iserniet
.call
.call test
.macro tv a
.return 42
.return ${sort $a}
.endmacro
[${call tv "1 4 1 2 3 -1 4 5 -9 12 2343"}]
${call tv 1 2} ${call} ${call tv}
[${call test a b}]
[${call tv ""}]
.macro testglobal
.globalset gv 2
.globalsplit gs1 gs2 = a b c d
.set ngv 2
.split ngs1 ngs2 = a b c d
.globalappend gl test
.append ngl test
.endmacro
.set gv 1
.set ngv 1
.split gs1 gs2 = w x y z
.split ngs1 ngs2 = w x y z
.set gl 123
.set ngl 123
gv: $(gv), ngv: $(ngv) gl: [$(gl)], ngl: [$(ngl)]
gs1: [$(gs1)] gs2: [$(gs2)] ngs1: [$(ngs1)] ngs2: [$(ngs2)]
.call testglobal
gv: $(gv), ngv: $(ngv) gl: [$(gl)], ngl: [$(ngl)]
gs1: [$(gs1)] gs2: [$(gs2)] ngs1: [$(ngs1)] ngs2: [$(ngs2)]
matchmacro: '${matchmacro *}' '${matchmacro}' '${matchmacro (*}'
definedmacro: '${definedmacro testglobal}' '${definedmacro iserniet}' '${definedmacro}' '${definedmacro testglobal testglobal}'
matchvar: '${matchvar *}' '${matchvar}' '${matchvar *e*}'
----

Eval
----
.set x "$$[1+2]"
[$x] [${eval $x}]
----

Delete all alias types
----------------------
Before: ${typelist}
.deletetype ${aliases}
After: ${typelist}

Test time formatting
--------------------
${formattime 1 "%m/%d/%Y %H:%M:%S"}
${formattime 10 "%m/%d/%Y %H:%M:%S"}
${formattime 1000 "%m/%d/%Y %H:%M:%S"}
${formattime 10000 "%m/%d/%Y %H:%M:%S"}
${formattime 100000 "%m/%d/%Y %H:%M:%S"}
${formattime 1000000 "%m/%d/%Y %H:%M:%S"}
${formattime 10000000 "%m/%d/%Y %H:%M:%S"}
${formattime 100000000 "%m/%d/%Y %H:%M:%S"}
${formattime 1000000000 "%m/%d/%Y %H:%M:%S"}

-- .split --
.foreach pat "a b" "a b c" "a" "a b c d e f" ""
.split v1 v2 = $(pat)
'$(pat)' -> v1: '$(v1)' v2: '$(v2)'
.endforeach
.split v1 v2
.split = a b c{formattime 1000000000 "%m/%d/%Y %H:%M:%S"}
