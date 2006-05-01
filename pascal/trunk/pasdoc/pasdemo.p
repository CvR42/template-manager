program tmdemoprog( input, output );

type
    int = integer;

var
    root: plot;
    err: boolean;


{ Functions for primitive types }
procedure Rfreint( var n: int );
begin
    n:=0;
end;

procedure Writeint( var f: text; n: int );
begin
    writeln( f, '(', n:1, ')' );
end;

function Copyint( i: int ): int;
begin
    Copyint := i;
end;

function Readint( var f, rf: text; var n: int ): boolean;
begin
    Readint := Readinteger( f, rf, n );
end; { Readint }


begin
    Initdemo;
    tmgetc( input );
    err := Readplot( input, output, root );
    if err then begin
        writeln( 'Read error encountered, STOP.' );
    end
    else begin
        Writeplot( output, root );
        Statdemo( output );
    end;
end.
