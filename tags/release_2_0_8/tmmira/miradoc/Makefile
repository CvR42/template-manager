# Makefile for tm document.  # For several reasons 'make' cannot handle this
# very efficiently.

.SUFFIXES: .spl .tex

MAKEFILE = Makefile

TOPFILE = tmmira

TM = tm

TEXFILES = tmmira.tex

SPELLFILES = $(TEXFILES:.tex=.spl)

# Other temporary files.
TMPFILES = $(TOPFILE).dvi $(TOPFILE).ps \
    $(AUXFILES) $(TOPFILE).lot $(TOPFILE).lof $(TOPFILE).toc

JUNK = $(TOPFILE).log $(TOPFILE).ilg pasdemo.p \
       mirademo.m $(TOPFILE).ind $(TOPFILE).idx \
       $(TOPFILE).aux distlist

DISTFILES = $(TEXFILES) $(MAKEFILE) mirademo.t miraspec.t plot.ds \
    $(TOPFILE).ps goodwords .cvsignore

help:
	@echo Possible targets:
	@echo 'clean  - Remove all intermediate files.'
	@echo 'empty  - Remove all files that can be re-generated.'
	@echo 'help   - Give this list of targets.'
	@echo 'all    - Make the .dvi and the .ps file.'
	@echo 'spell  - Run spelling check.'
	@echo 'sort   - Sort spelling goodwords.'

all: $(TOPFILE).dvi $(TOPFILE).ps

test:
	@echo "Nothing to test"

install:
	@echo "Nothing to install"

$(TOPFILE).dvi: $(TEXFILES)
	latex $(TOPFILE)
	makeindex $(TOPFILE)
	latex $(TOPFILE)
	-fgrep 'get cross-references rig' $(TOPFILE).log && latex $(TOPFILE)

$(TOPFILE).ps: $(TOPFILE).dvi
	dvips $(TOPFILE)

.tex.spl:
	-detex $*.tex | spell +goodwords > $*.spl

sort: goodwords
	spell goodwords > tmp
	mv tmp goodwords
	touch sort

spell: $(SPELLFILES)

$(SPELLFILES): sort

empty:
	rm -f $(TMPFILES) $(JUNK) $(SPELLFILES)

clean:
	rm -f $(TMPFILES) $(JUNK) $(SPELLFILES)

mirademo.m: mirademo.t plot.ds miraspec.t
	$(TM) plot.ds mirademo.t | expand > mirademo.m

distlist: $(MAKEFILE) $(TOPFILE).ps
	echo $(DISTFILES) | tr ' ' '\012' > distlist

$(TOPFILE).dvi: mirademo.m
