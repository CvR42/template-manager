# File: $Id$

ERRTESTSSL = $(wildcard err*.rl)

GENTESTSSL = $(wildcard gen*.rl)

VFYTESTSSL = $(wildcard vfy*.rl)

OKTESTSSL = $(wildcard ok*.rl)

RTETESTSSL = $(wildcard rte*.rl)

TPLFILES = $(wildcard *.t)

TESTSSL = $(ERRTESTSSL) $(OKTESTSSL) $(VFYTESTSSL) $(GENTESTSSL) $(RTETESTSSL) 

# A representative output file for each class of test
DONEFILES = $(TESTSSL:%.rl=%.done)

# For make check we omit the 'gen' tests.
CHECKDONEFILES = \
    $(ERRTESTSSL:%.rl=%.done) \
    $(OKTESTSSL:%.rl=%.done) \
    $(VFYTESTSSL:%.rl=%.done) \
    $(RTETESTSSL:%.rl=%.done)

JUNK = $(DONEFILES) *.testout *.testerr *.tv *.exe dist.lst

PRECIOUSJUNK = *.gprof $(CHECKDONEFILES)

MAKEFILE = Makefile

SCRIPTS = runok runerr rungen runrte runall

TESTFILES = $(wildcard *.flags *.rl *.argv *.err *.v *.out err*.status gen*.status vfy*.status ok*.status rte*.status)

DISTFILES = $(MAKEFILE) $(TESTFILES) $(SCRIPTS) $(TPLFILES) .cvsignore

all:

# The files that are tested: if they change, the testsuite must
# be run again.
REFFILES = ../ruler $(wildcard ../templates/*.ct)

# Rules to make the .done file of each catagory: run the 'run' script
# of the class, and after that touch the .done file
ok%.done: ok%.rl ok%.in runok
	./runok $<
	touch $@

err%.done: err%.rl runerr
	./runerr $<
	touch $@

gen%.done: gen%.rl rungen
	./rungen $<
	touch $@

vfy%.done: vfy%.rl runvfy
	./runvfy $<
	touch $@

rte%.done: rte%.rl rte%.in runrte
	./runrte $<
	touch $@

check: $(CHECKDONEFILES)

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
gentpl.done: gentpl.t gentpl.err gentpl.out gentplsub.t
