# Tm - an interface code generator.
# Author: C. van Reeuwijk.
#
# All rights reserved.
#
# This version is specific for Borland C++ for Windows.
# It is tested on Borland C++ version 4.52; it *might* work with earlier
# versions.
#
# A few variables can be defined below to change the configuration

# You can customize this Makefile for your system by editing
# the variables immediately below. The current values are not magical;
# they just reflect what I use.
#  LOCALBIN	The place to put binaries
#  LOCALLIB	The place to get libraries and templates
#  LOCALINC	The place to get local include (.h) files
#  CC		The compiler to use: BCC32 if possible, else BCC. 
#  SYSCFLAGS	Compilation flags to use. You may want to change them
#		to choose target machine architecture, optimization level,
#		memory model, etc.
#  PROGBASE	The basename of the resulting program. If you want to generate
#		both the 16 bits and the 32 bits version, you
#		may want a name with '32' in it for one of them.
# 
LOCALBIN=d:\bin
LOCALLIB=d:\lib
LOCALINC=d:\include
CC = BCC32
LINKER = $(CC)
SYSCFLAGS = -v -P -wall -wstu -4 -O2 -DLOGNEW -DSTAT

LDFLAGS	      = $(SYSCFLAGS)

# C compilation flags
CFLAGS = $(SYSCFLAGS) -I$(LOCALINC)

# Some names of programs
TM  = tm.exe

TMCPPLIB = $(LOCALLIB)\tmcpp32.lib

LIBS = $(TMCPPLIB)

MAKEFILE = Makefile

DOC	= README

DEMOFILES =

TESTSRCS = tpltest.c cppcode.c
TESTOBJS = $(TESTSRCS:.c=.obj)

help :
	@echo " Possible make targets:"
	@echo "all		Create local running programs."
	@echo "clean		Delete all intermediate files."
	@echo "empty		Delete all files that can be re-generated."
	@echo "install		Install relevant files."
	@echo "test		Run tests."

#
all: tpltest.exe

# Add rules for the programs themselves here.

test : tpltestrun

tpltest.exe: $(TESTOBJS)
	$(LINKER) -etpltest $(LDFLAGS) $(TESTOBJS) $(LIBS)

tpltestrun: tpltest.exe testin
	tpltest.exe
	diff testout tmcokout
	diff testerr tmcokerr

tmcinstall: need.t tmcpp.ct tmcpp.ht
	copy /a macros.t+tmcid.t+need.t+tmcpp.ct $(LOCALLIB)\tmcpp.ct
	copy /a macros.t+tmcid.t+need.t+tmcpp.ht $(LOCALLIB)\tmcpp.ht

install: tmcinstall

clean:
	del *.obj
	del testerr
	del testout
	del cppcode.c
	del cppcode.h
	del tpltest.exe

empty:
	del *.obj
	del testerr
	del testout
	del cppcode.c
	del cppcode.h
	del tpltest.exe

cppcode.c: cppcode.ct tmcpp.ct tmcspec.t cltest.ds need.t macros.t
	$(TM) cltest.ds cppcode.ct > cppcode.c

cppcode.h: cppcode.ht tmcpp.ht tmcspec.t cltest.ds need.t macros.t
	$(TM) cltest.ds cppcode.ht > cppcode.h

.c.obj:
	$(CC) -c $(CFLAGS) -o$* $<

###
cppcode.obj: cppcode.h config.h
tpltest.obj: cppcode.h config.h
