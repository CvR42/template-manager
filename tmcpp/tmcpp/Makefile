# Generated automatically from Makefile.in by configure.
# Tm - an interface code generator.
# Author: C. van Reeuwijk.
#
# All rights reserved.
#
# To customize this Makefile, run configure.
#
# Compilation for MSDOS/MS-Windows with Borland C is done with a
# makefile. See the file 'README' for details.
 
CXX = c++
CC = $(CXX)
LINKER = $(CXX)
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
LOCALBIN = /usr/local/bin
LOCALLIB = /usr/local/lib
LOCALINCLUDE = /usr/local/include
LOCALMAN = /usr/local/man

# System dependent flags for compilation with debugging
DBUGFLAGS = -g -DLOGNEW -DSTAT

LDFLAGS	= $(DBUGFLAGS)

# C compilation flags
CFLAGS =  $(DBUGFLAGS) -I../libtmc -I$(LOCALINCLUDE)

# Some names of programs
TM  = tm

#TMCLIB = $(LOCALLIB)/libtmcpp.a
TMCLIB = ../libtmcpp/libtmcpp.a

LIBS =  $(TMCLIB)

MAKEFILE = Makefile

DOC = README

JUNK = tmp core makelog testerr testout config.log \
       gmon.out log dist.lst distlist \
       tpltest walktest

TESTFILES = \
    cltest.ds test.ds \
    tmcokerr tmcokout testin tmcspec.t tmccode.ct tmccode.ht \
    walktest.ct walkin walkok

FOREIGNFILES = makefile.tc config.htc config.hts

# Files for configuration
CONFIGUREFILES = configure config.hin Makefile.in configure.in

DISTFILES = $(TMMODULES) $(TESTFILES) $(DOC) $(FOREIGNFILES) \
	    $(CONFIGUREFILES)

TMMODULES     = tmcpp.ct tmcpp.ht \
                need.t cppwalk.t \
		macros.t tmcid.t

TMCTMHDRS      = tmccode.h

TMCTMSRCS      = tmccode.c

TESTSRCS   = tpltest.c tmccode.c
TESTHDRS   = tmccode.h
TESTOBJS   = tpltest.o tmccode.o

WALKTESTSRCS = walktest.c tmccode.c
WALKTESTOBJS = $(WALKTESTSRCS:.c=.o)

OBJS = $(WALKTESTOBJS) tmccode.o tpltest.o

# These sources are generated from tm templates.
TMOUT = tmccode.c tmccode.h walktest.c

help :
	@echo " Possible make targets:"
	@echo "all		Create local running programs."
	@echo "clean		Free disk space."
	@echo "empty		Free disk space."
	@echo "distfiles	List distribution files."
	@echo "install		Install relevant files."
	@echo "test		Run tests."

#
all: test walktest

test: tpltestrun walktestrun

walktest: $(WALKTESTOBJS)
	$(LINKER) $(LDFLAGS) $(WALKTESTOBJS) $(LIBS) -o walktest

walktestrun: walktest walkin walkok
	./walktest
	diff testout walkok

tpltest: $(TESTOBJS)
	$(LINKER) $(LDFLAGS) $(TESTOBJS) $(LIBS) -o tpltest

tpltestrun: tpltest testin tmcokout tmcokerr
	./tpltest
	diff testout tmcokout
	diff testerr tmcokerr

tmcinstall: need.t tmcpp.ct tmcpp.ht tmcid.t cppwalk.t
	-$(INSTALL) -d $(LOCALLIB)
	cat macros.t tmcid.t need.t tmcpp.ct > tmp4242
	$(INSTALL_DATA) tmp4242 $(LOCALLIB)/tmcpp.ct
	cat macros.t tmcid.t need.t tmcpp.ht > tmp4242
	$(INSTALL_DATA) tmp4242 $(LOCALLIB)/tmcpp.ht
	rm -f tmp4242
	$(INSTALL_DATA) cppwalk.t $(LOCALLIB)/cppwalk.t

install: tmcinstall

clean:
	rm -f $(JUNK) $(OBJS) $(TMOUT)

distclean:
	rm -f $(JUNK) $(OBJS) $(TMOUT) config.cache config.status config.h

empty:
	rm -f $(JUNK) $(OBJS) $(TMOUT) config.cache config.status config.h

distfiles:
	@echo $(DISTFILES) | tr ' ' '\012'

distlist: $(DISTFILES)
	echo $(DISTFILES) | tr ' ' '\012' > dist.lst

depend: $(TMCTMHDRS) $(TMCTMSRCS)
	mkmf -I$(LOCALINCLUDE) -f $(MAKEFILE)

walktest.c: walktest.ct cltest.ds cppwalk.t
	$(TM) cltest.ds walktest.ct > walktest.c

tmccode.c: tmccode.ct tmcpp.ct tmcspec.t cltest.ds need.t macros.t tmcid.t
	$(TM) cltest.ds tmccode.ct > tmccode.c

tmccode.h: tmccode.ht tmcpp.ht tmcspec.t cltest.ds need.t macros.t tmcid.t
	$(TM) cltest.ds tmccode.ht > tmccode.h

stats:
	wc -l $(TMMODULES)

###
tmccode.o: tmccode.h config.h
tpltest.o: tmccode.h config.h
walktest.o: tmccode.h config.h
