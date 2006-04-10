Purpose
-------

This is a small demonstration project to show the use of Tm generated
code. Given an input file containing assignment statements like

a = 1 + 2 * 3;
b = 1 - 2;
c = - 1 + 2;
d = -(1+2);
e = c + 3 + 4;
f = c + (3 + 4);

The program 'calcparse' parses this statement list, and generates a
Tm textual representation. The program 'calcopt' reads the Tm textual
representation, removes constant expressions, and generates Tm textual
representation again. Obviously, in normal circumstances it would make
more sense to do all this in one program, but that way there would
be little left to demonstrate.

Compiling and installing
------------------------

As most Tm distribution components, this directory contains a configure
file. Just do:

./configure

or 

./configure --prefix=<path>


This will find a suitable yacc, lex and C compiler, and construct a
Makefile to reflect this. Then do

make all

to make calcparse and calcopt, and

make test

to test these programs on a small example file.

Installation is pointless for a demonstration program.

