# Makefile for tm document.  # For several reasons 'make' cannot handle this
# very efficiently.

.SUFFIXES: .spl .tex

MAKEFILE = Makefile

TOPFILE = tmpas

TM = tm

TEXFILES = tmpas.tex 

AUXFILES = $(TEXFILES:.tex=.aux)

SPELLFILES = $(TEXFILES:.tex=.spl)

JUNK = $(TOPFILE).log $(TOPFILE).blg $(TOPFILE).ilg \
       $(TOPFILE).ind $(TOPFILE).idx \
       $(AUXFILES) $(TOPFILE).bbl $(TOPFILE).lot $(TOPFILE).lof \
       $(TOPFILE).toc distlist

DISTFILES = $(TEXFILES) $(MAKEFILE) goodwords $(TOPFILE).ps plot.ds pasdemo.pt

help:
	@echo Possible targets:
	@echo 'clean   - Remove all intermediate files.'
	@echo 'empty   - Remove all files that can be re-generated.'
	@echo 'help    - Give this list of targets.'
	@echo 'all     - Make the .dvi and the .ps file.'
	@echo 'spell   - Run spelling check.'
	@echo 'sort    - Sort spelling goodwords.'

all: $(TOPFILE).ps

test:
	@echo "Nothing to test"

install:
	@echo "Nothing to install"

$(TOPFILE).dvi : $(TEXFILES)
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

clean:
	rm -f $(JUNK) $(SPELLFILES)

empty:
	rm -f $(JUNK) $(SPELLFILES) $(TOPFILE).dvi $(TOPFILE).ps

distfiles: $(MAKEFILE)
	@echo $(DISTFILES) | tr ' ' '\012'

distlist: $(MAKEFILE) $(TOPFILE).ps
	echo $(DISTFILES) | tr ' ' '\012' > distlist
