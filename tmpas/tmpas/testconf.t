.. Tm - an interface code generator.
.. Copyright (C) 1991, Delft University of Technology and C. van Reeuwijk.
..
.. This software is distributed under the terms of the GNU General Public
.. Licence as published by the Free Software Foundation. See the file 'LICENCE'
.. in the root directory of this distribution for details.
..
.. File: testspec.t
.set basename test
.set    wantdefs Readplotlist Writeplotlist Rfreplotlist Copyplotlist
.append wantdefs Cmpplotlist
.append wantdefs tmgetc tmreadspc tmneedc tmreadobrac tmreadcbrac
.append wantdefs tmreadc tmwritec
.append wantdefs Stat$(basename)
.foreach t integer real boolean char
.append wantdefs Read$t Write$t Cmp$t Rfre$t Copy$t
.endforeach
