VERSION = 4

DOC	= CHANGES README

TEST    = test.ict test.dct testspec.t testtop.icl testdata goodout test.ds

CODE    = clneed.t clean.clt

JUNK = tmp core makelog tmclean.aux tmclean.dvi tmclean.log cleandemo.icl \
       cleandemo.x readin.x test.icl test.dcl version.tex testout \
       install tmclean.alw

MAKEFILE = Makefile

TM =tm

DISTFILES = $(DOC) $(CODE) $(MAKEFILE) $(TEST)

#++ make module local start, do NOT touch this line. ++
# Installation dependent make variables.
# This configuration is for 'dutedih'.

# full path of the ESPRIT environment
ESPRITDIR = /users/reeuwijk/esprit

#  BDIR     : bin directory
#  IDIR     : include directory
#  LDIR     : library directory
BDIR = $(ESPRITDIR)/bin
IDIR = $(ESPRITDIR)/include
LDIR = $(ESPRITDIR)/lib

FULLDS = $(ESPRITDIR)/ds/fullglass.ds
KERNDS = $(ESPRITDIR)/ds/kernglass.ds
NFULLDS = $(ESPRITDIR)/ds/nfullgl.ds
NKERNDS = $(ESPRITDIR)/ds/nkerngl.ds
DRAWDS = $(ESPRITDIR)/ds/draw.ds

#  HOSTNAME : name of installation machine.
HOSTNAME=dutedih

# SYS     : name of operating system or machine type
#     BSD	For generic BSD systems
#     HPUX	For all HP-UX systems
#     SUN	For all SUN systems
#     APOLLO	For all Apollo systems
SYS = SUN

SYSCFLAGS =
SYSCPROFFLAGS = -p
SYSCDBUGFLAGS = -g
SYSLINTFLAGS = -ach
SYSPFLAGS =

# CLIBLOC : required C, lint and Pascal libraries
CLIBLOC =
LINTLIBLOC =
PLIBLOC =

# CBADADR : address that will cause a core-dump if read or written.
CBADADR = 0

# Collection of host dependent make rules.

### libinstall ###
# MODULE	- module to install
libinstall:
	cp $(MODULE) $(LDIR)/$(MODULE)

### includeinstall ###
# MODULE	- module to install
includeinstall:
	cp $(MODULE) $(IDIR)/$(MODULE)

### maninstall ###
# MAN		- manual page to install
maninstall:
	cp $(MAN) /usr/man/manl

### bininstall ###
# MODULE	- module to install
bininstall:
	cp $(MODULE) $(BDIR)/$(MODULE)
	strip $(BDIR)/$(MODULE)

### arlibinstall ###
# MODULE	- module to install
arlibinstall:
	cp $(MODULE) $(LDIR)/$(MODULE)
	ranlib $(LDIR)/$(MODULE)
#++ make module local end, do NOT touch this line. ++

help:
	@echo " Possible make targets:"
	@echo "all		Create local running programs."
	@echo "clean		Free disk space."
	@echo "distfiles	List distribution files."
	@echo "doc		Creat documentation."
	@echo "install		Install relevant files."
	@echo "setup		Adapt sources to local situation."
	@echo "test		Run tests."

all:

test: test.icl test.dcl testtop.icl
	clm testtop -o test
#	test
#	diff testout goodout

install: clneed.t clean.clt
	cat clneed.t clean.clt > $(LDIR)/clean.clt
	touch install

clean:
	rm -f $(JUNK)

distfiles:
	@echo $(DISTFILES) | tr ' ' '\012'

distlist:
	echo $(DISTFILES) | tr ' ' '\012' > distlist

setup:
	modmake local ../make.local $(MAKEFILE)

# Non-standard make rules
test.icl: test.ict clspec.t test.ds testspec.t clneed.t clean.ict typedef.t
	$(TM) test.ds test.ict > test.icl

test.dcl: test.dct clspec.t test.ds testspec.t clneed.t clean.dct typedef.t
	$(TM) test.ds test.dct > test.dcl

###
