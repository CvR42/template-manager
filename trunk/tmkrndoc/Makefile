# Makefile for tm document.  # For several reasons 'make' cannot handle this
# very efficiently.

.SUFFIXES: .spl .tex .out .xt

MAKEFILE = Makefile

WEBDIR = $(HOME)/website/software/Tm

# Top level LaTeX file containing the \include commands.
TOPFILE = main

# Reduction factor for draft files
REDUCT = 2

TM = tm
LEX	 = flex -b -i
YACC	 = bison -v -d -y

CALCDEMO = calc.c calc.ct calc.ds calc.h calc.ht calcconf.t calclex.l calcopt.c calcparse.y okopt.clc oktest.clc test.calc subst.ct subst.c oksubst.clc
EXAMPLEFILES = append.xt foreach.xt if.xt macro.xt var.xt cmp.xt arith.xt \
  boolean.xt textfn.xt listfn.xt regex.xt fnds.xt service.xt eval.xt math.xt \
  linemacro.xt setfn.xt switch.xt unalias.xt time.xt
EXAMPLEOUTFILES = $(EXAMPLEFILES:.xt=.out)

TEXFILES = main.tex tm.tex command.tex tmc.tex intro.tex \
	   ds.tex titlepage.tex dsgram.tex impl.tex calc.tex \
	   defs.tex preface.tex flow.tex upgrade.tex

AUXFILES = $(TEXFILES:.tex=.aux)

SPELLFILES = $(TEXFILES:.tex=.spl)

JUNK = $(TOPFILE).log $(TOPFILE).blg $(TOPFILE).ilg \
       demo.h demo.c $(TOPFILE).ind $(TOPFILE).idx \
       $(AUXFILES) $(TOPFILE).bbl $(TOPFILE).lot $(TOPFILE).lof \
       $(TOPFILE).toc dist.lst title.c

DISTFILES = $(TEXFILES) $(MAKEFILE) $(EXAMPLEFILES) $(EXAMPLEOUTFILES) \
	    $(CALCDEMO) \
            goodwords main.bib main.pdf pdstitle.sty plot.ds .cvsignore \
	    title.ct title.ds ch.sh cast.t

help:
	@echo Possible targets:
	@echo 'clean   - Remove all intermediate files.'
	@echo 'empty   - Remove all files that can be re-generated.'
	@echo 'help    - Give this list of targets.'
	@echo 'fast    - Run LaTeX once.'
	@echo 'all     - Make the .dvi and the .ps files.'
	@echo 'test    - Run tests (dummy for compatibility reasons).'
	@echo 'install - Install (dummy for compatibility reasons).'
	@echo 'spell   - Run spelling check.'
	@echo 'sort    - Sort spelling goodwords.'

all: $(TOPFILE).pdf

fast: $(TOPFILE).pdf

test:
	@echo "Nothing to test"

install:
	@echo "Nothing to install"

# The dependency rules as implemented by latex
$(TOPFILE).pdf : $(TEXFILES) $(EXAMPLEOUTFILES) $(CALCDEMO)
	pdflatex $(TOPFILE)
	makeindex $(TOPFILE)
	pdflatex $(TOPFILE)
	-fgrep 'get cross-references rig' $(TOPFILE).log && pdflatex $(TOPFILE)

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

unalias.out: unalias.xt alias.ds
	tm alias.ds unalias.xt > $*.out

.xt.out: plot.ds
	tm plot.ds $< > $*.out

clean:
	rm -f $(JUNK) $(SPELLFILES)

distclean:
	rm -f $(JUNK) $(SPELLFILES) $(TOPFILE).dvi $(TOPFILE).ps

empty:
	rm -f $(JUNK) $(EXAMPLEOUTFILES) $(SPELLFILES) $(TOPFILE).dvi $(TOPFILE).ps

distfiles:
	@echo $(DISTFILES) | tr ' ' '\012'

distlist: $(DISTFILES)
	echo $(DISTFILES) | tr ' ' '\012' > dist.lst

demo.c : plot.ds demo.ct democonf.t
	tm plot.ds demo.ct | expand > demo.c

demo.h : plot.ds demo.ht democonf.t
	tm plot.ds demo.ht | expand > demo.h

subst.c : calc.ds subst.ct
	tm calc.ds subst.ct | expand > subst.c

calc.c : calc.ds calc.ct calcconf.t
	tm calc.ds calc.ct | expand > calc.c

calc.h : calc.ds calc.ht calcconf.t
	tm calc.ds calc.ht | expand > calc.h

title.c: title.ct title.ds
	tm title.ds title.ct > title.c

t: $(CALCDEMO) $(EXAMPLEOUTFILES)
	echo $(CALCDEMO) $(EXAMPLEOUTFILES)

%.ps: %.dvi
	dvips $<

tm-manual.ps: $(TOPFILE).ps
	cp $(TOPFILE).ps tm-manual.ps

%.ps.gz: %.ps
	cp $< __tmp.ps
	gzip -9 __tmp.ps
	mv __tmp.ps.gz $*.ps.gz

docinstall: tm-manual.ps tm-manual.ps.gz
	cp tm-manual.ps $(WEBDIR)
	cp tm-manual.ps.gz $(WEBDIR)

main.dvi: $(CALCDEMO)
main.dvi: title.c
$(EXAMPLEOUTFILES): plot.ds
