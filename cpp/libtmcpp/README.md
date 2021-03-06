
General
-------

This directory contains the sources for the Tm C++ support library.
That is, these routines provide support for the Tm C++ templates
in the directory 'tmcpp'.

Please read this file before installing the program.

You must have compiled and installed this Tm C++ support library before you
can compile and install the other components of the kernel Tm package.
Please install this before you try to compile other components.
Alternatively, you can use the Makefile in the parent directory; this will
compile everything in the correct order.

Tm requires an ANSI C++ compiler.

The library has been compiled and tested on the following systems:
 - SunOS 4.1.3 with the GNU C++ compiler
 - MS-Windows 3.1 and 95 with the Borland C++ compiler version 4.5 and 5.0

Older versions have been compiled on lots of other UNIX systems, but
this has not been tested with the new configure script.

See the section ``Compiling and installing on MS-Windows'' for
compilation and installation on this system.

Compiling and installing
------------------------

Before you can compile the library, you must configure the Makefile and the
configuration header file.  You do this by simply typing

    configure

at the command prompt. This will set reasonable defaults for the compilation.
See below if you want the change the installation directory or the
command to invoke the C++ compiler.

After than you can make all compilation targets with

    make all

run some tests on the results with

    make check

and install the software with

    make install

To delete the intermediate files generated by the complation process,
use

    make clean

or use

    make empty

to delete all files that can be generated from other files.

There are other targets in the Makefile. Do

    make help

to get an overview of them.

Changing compilation options
----------------------------

The configure script will determine on what kind of system you are,
and will adapt a number of parameters accordingly. If the configure
script can find the GNU C++ compiler (g++), it will use that, else it
will use the standard C++ compiler on your system (cc). To over-ride
this behavior, you can give configure an value for the compiler
variable `CC' by setting it in the environment.  For example (assuming
you use the csh(1)):

    setenv CC cc -Aa
    configure

The environment variable needs only be visible at the moment you run
configure.

The program will be installed <prefix>/bin. By default <prefix> is
determined by the place the GNU compiler is found, or if that cannot
be found it is '/usr/local'.  To change the prefix, you can give
configure the option '--prefix=<path>'. For example, with

    configure --prefix=/usr/blob

Tm will be installed in /usr/blob/bin.

Compiling and installing on MS-Windows
--------------------------------------

For compiling with the Borland C++ compiler under MS-Windows, a separate
makefile and config.h are provided. In the distribution they are called
'makefile.tc' and config.htc', respectively. To use them, do:
    copy makefile.tc makefile
    copy config.htc config.h
You probably want to edit the makefile to define the proper installation
paths, choose between 16 bits and 32 bits compilation, etc.
See the makefile for further explanation.

The same make targets as for UNIX are provided.

As much as possible, standard MSDOS commands are used in the makefile.
This makes it a bit clunky, but for the most part this has succeeded.
However, there is no standard MSDOS equivalent for the UNIX command 'diff'.
You may want to get a public-domain version of the program somewhere,
or you can do the file comparison by hand.

When you run 'make check', expect a few differences, because file names
under MSDOS look different from the 'normal' versions.
