.. File: test.mt
.. Test of Miranda support
|| File: test.m
int == num
string == [char]

show_int = show_num
scan_int = scan_num

.insert testspec.t
.insert miraneed.t
.include mira.mt
