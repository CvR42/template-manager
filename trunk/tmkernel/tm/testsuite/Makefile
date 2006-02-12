# File: $Id$

ERRTESTTPL = $(wildcard err*.t)

DSERRTESTTPL = $(wildcard dserr*.t)

GENTESTTPL = $(wildcard gen*.t)

TESTTPL = $(ERRTESTTPL) $(GENTESTTPL) $(DSERRTESTTPL)

# A representative output file for each class of test
DONEFILES = $(TESTTPL:%.t=%.done)

JUNK = *.done *.testout *.testerr *.exe dist.lst

PRECIOUSJUNK = *.gprof $(CHECKDONEFILES)

MAKEFILE = Makefile

SCRIPTS = runerr rungen runall

TESTFILES = $(wildcard *.flags *.err *.t *.out err*.status gen*.status dserr*.status)

DISTFILES = $(MAKEFILE) $(TESTFILES) $(SCRIPTS) .cvsignore

all:

# The files that are tested: if they change, the testsuite must
# be run again.
REFFILES = ../tm

# Rules to make the .done file of each catagory: run the 'run' script
# of the class, and after that touch the .done file

dserr%.done: dserr%.t runerr
	./rundserr $<
	touch $@

err%.done: err%.t runerr
	./runerr $<
	touch $@

gen%.done: gen%.t rungen
	./rungen $<
	touch $@

check: $(DONEFILES)

test: $(DONEFILES)

tests: $(DONEFILES)

clean:
	rm -f $(JUNK)

empty:
	rm -f $(JUNK) $(PRECIOUSJUNK)

SUBDIRS = subpack

# ------ Construct a distribution

JUNK += dist.lst

dist.lst: $(DISTFILES)
	@echo "Building $@"
	@echo $(DISTFILES) | tr ' ' '\012' > $@

$(DONEFILES): $(REFFILES)

# -- Specific dependencies
