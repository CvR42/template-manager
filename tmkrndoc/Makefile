# Makefile for tm document.  # For several reasons 'make' cannot handle this
# very efficiently.

.SUFFIXES: .spl .tex .out .xt

MAKEFILE = Makefile

# Top level LaTeX file containing the \include commands.
TOPFILE = main

# Reduction factor for draft files
REDUCT = 2

TM = tm
LEX	 = flex -b -i
YACC	 = bison -v -d -y

CALCDEMO = calc.c calc.ct calc.ds calc.h calc.ht calcconf.t calclex.l calcopt.c calcparse.y okopt.clc oktest.clc test.calc

EXAMPLEFILES = append.xt foreach.xt if.xt macro.xt var.xt cmp.xt arith.xt \
  boolean.xt textfn.xt listfn.xt regex.xt fnds.xt service.xt eval.xt math.xt \
  linemacro.xt setfn.xt switch.xt
EXAMPLEOUTFILES = $(EXAMPLEFILES:.xt=.out)

TEXFILES = main.tex tm.tex tmc.tex intro.tex \
	   ds.tex titlepage.tex dsgram.tex impl.tex calc.tex \
	   defs.tex preface.tex flow.tex upgrade.tex

AUXFILES = $(TEXFILES:.tex=.aux)

SPELLFILES = $(TEXFILES:.tex=.spl)

JUNK = $(TOPFILE).log $(TOPFILE).blg $(TOPFILE).ilg \
       demo.h demo.c macdemo.out $(TOPFILE).ind $(TOPFILE).idx \
       $(AUXFILES) $(TOPFILE).bbl $(TOPFILE).lot $(TOPFILE).lof \
       $(TOPFILE).toc dist.lst title.c

DISTFILES = $(TEXFILES) $(MAKEFILE) $(EXAMPLEFILES) $(EXAMPLEOUTFILES) \
	    demo.ct demo.ht democonf.t demospec.t \
            goodwords macdemo.t main.bib main.ps plot.ds readin.m xrefdemo.t \
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

all: $(TOPFILE).ps

fast: $(TOPFILE).dvi

test:
	@echo "Nothing to test"

install:
	@echo "Nothing to install"

# The dependency rules as implemented by latex
$(TOPFILE).dvi : $(TEXFILES) $(EXAMPLEOUTFILES) $(CALCDEMO)
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

macdemo.out: macdemo.t plot.ds
	$(TM) plot.ds macdemo.t > macdemo.out

spell: $(SPELLFILES)

$(SPELLFILES): sort

.xt.out:
	tm plot.ds $< > $*.out

clean:
	rm -f $(JUNK) $(SPELLFILES)

distclean:
	rm -f $(JUNK) $(SPELLFILES) $(TOPFILE).dvi $(TOPFILE).ps

empty:
	rm -f $(JUNK) $(EXAMPLEOUTFILES) $(SPELLFILES) $(TOPFILE).dvi $(TOPFILE).ps

distfiles:
	@echo $(DISTFILES) | tr ' ' '\012'

distlist: $(MAKEFILE) $(TOPFILE).ps
	echo $(DISTFILES) | tr ' ' '\012' > dist.lst

demo.c : plot.ds demo.ct democonf.t
	tm plot.ds demo.ct | expand > demo.c

demo.h : plot.ds demo.ht democonf.t
	tm plot.ds demo.ht | expand > demo.h

calc.c : calc.ds calc.ct calcconf.t
	tm calc.ds calc.ct | expand > calc.c

calc.h : calc.ds calc.ht calcconf.t
	tm calc.ds calc.ht | expand > calc.h

title.c: title.ct title.ds
	tm title.ds title.ct > title.c

calcpars.c tokens.h: calcpars.y
	$(YACC) $<
	mv y.tab.c calcpars.c
	mv y.tab.h tokens.h

calclex.c: calclex.l
	$(LEX) $<
	mv lex.yy.c $*.c

t:
	@echo $(CALCDEMO)

calcpars.o: calc.h
calclex.o: tokens.h
main.dvi: macdemo.out demo.c demo.h
main.dvi: readin.m
main.dvi: title.c
$(EXAMPLEOUTFILES): plot.ds
