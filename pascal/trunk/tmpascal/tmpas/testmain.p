{ Tm - an interface code generator.
  Copyright (C) 1991, Delft University of Technology and C. van Reeuwijk.
 
  This software is distributed under the terms of the GNU General Public
  Licence as published by the Free Software Foundation. See the file 'LICENCE'
  in the root directory of this distribution for details.
 /
}
{ File: testmain.p

  Main part for test of tm pascal library
}
program tmtestprog( input, output );

type
#include "testtype.h"

var
    root: plotlist;
    vcopy: plotlist;
    readback: plotlist;
    err: boolean;

{ external pascal code }
#include "testcode.h"

{ Some external C functions that are necessary }
procedure exit(i: integer);
external;

begin
    writeln ('|| TMTEST');
    writeln( '|| Initalizing.' );
    Inittest;
    writeln( '|| Opening input file.');
    writeln( '|| Reading Miranda data structure. ');
    tmgetc( input );
    err := Readplotlist( input, output, root );
    if not err then begin
	writeln( '|| Copying data structure.' );
	vcopy := Copyplotlist( root );
	writeln( '|| Comparing.' );
	if Cmpplotlist( vcopy, root ) <> 0 then begin
	    writeln( '|| Strange, copied datastructure is not equal.' );
	    err := true
	end;
    end;
    if not err then begin
	writeln( '|| Disposing data structure.' );
	Rfreplotlist( root );
	writeln( '|| Generating Miranda.' );
	Writeplotlist( output, vcopy );
	writeln( '|| Statistics.' );
	Rfreplotlist( vcopy );
	Rfreplotlist( readback );
	Stattest( output );
	writeln( '|| Done.' );
    end;
    if err then
	exit( 1 )
    else
	exit( 0 );
end.
