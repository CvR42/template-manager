#!/bin/csh -f
# apply sed(1) with commands in file $1 to the files $2 $3 ..
set sedfile = $1
set tmpfile = ch$$
set me = $0
shift
foreach i ($*)
    sed -f $sedfile < $i > $tmpfile
    if $status then
	echo "${me}: file '$i' left unchanged."
	rm $tmpfile
    else
	cmp -s $tmpfile $i
	if $status then
	    mv $tmpfile $i
	endif
    endif
end
rm -f $tmpfile
