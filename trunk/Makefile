# Makefile for the root of the Tm distribution

# The version numbers below reflect release versions for the various
# packages.
TMKERNEL_VERSION = 2.0.10
TMPAS_VERSION = 1.0.2
TMMIRA_VERSION = 1.0.2
TMDEMO_VERSION = 1.0
CVSDIR = $(HOME)/Cvs

SHELL=/bin/sh
FTPDIR=$(HOME)/website/software/Tm
MAKEFILE=Makefile

JUNK = \
    tmkernel_distlist \
    tmpas_distlist \
    tmmira_distlist \
    tmkerneldoc_distlist

PACKAGES = \
    tmdemo-$(TMDEMO_VERSION).tar.gz \
    tmdemo-$(TMDEMO_VERSION).zip \
    tmkernel-$(TMKERNEL_VERSION).tar.gz \
    tmkernel-$(TMKERNEL_VERSION).zip \
    tmkerneldoc-$(TMKERNEL_VERSION).tar.gz \
    tmkerneldoc-$(TMKERNEL_VERSION).zip \
    tmmira-$(TMMIRA_VERSION).tar.gz \
    tmmira-$(TMMIRA_VERSION).zip \
    tmpas-$(TMPAS_VERSION).tar.gz \
    tmpas-$(TMPAS_VERSION).zip

FTPFILES= \
    $(FTPDIR)/CHANGES.tmkernel \
    $(FTPDIR)/CHANGES.tmmira \
    $(FTPDIR)/CHANGES.tmpas \
    $(FTPDIR)/README \
    $(FTPDIR)/tmdemo-$(TMDEMO_VERSION).tar.gz \
    $(FTPDIR)/tmdemo-$(TMDEMO_VERSION).zip \
    $(FTPDIR)/tmkernel-$(TMKERNEL_VERSION).tar.gz \
    $(FTPDIR)/tmkernel-$(TMKERNEL_VERSION).zip \
    $(FTPDIR)/tmkerneldoc-$(TMKERNEL_VERSION).tar.gz \
    $(FTPDIR)/tmkerneldoc-$(TMKERNEL_VERSION).zip \
    $(FTPDIR)/tmmira-$(TMMIRA_VERSION).tar.gz \
    $(FTPDIR)/tmmira-$(TMMIRA_VERSION).zip \
    $(FTPDIR)/tmpas-$(TMPAS_VERSION).tar.gz \
    $(FTPDIR)/tmpas-$(TMPAS_VERSION).zip

help:
	@echo "possible targets:"
	@echo "all	All distribution packages."
	@echo "ftp	Update the FTP presence of Tm."
	@echo "install	Install all sources."
	@echo "clean	Delete all intermediate files."
	@echo "empty	Delete all files that can be re-generated."

all: $(PACKAGES)

clean:
	rm -f $(JUNK)

empty:
	rm -f $(JUNK) $(PACKAGES)

tmmira_distlist: $(MAKEFILE) tmmira tmmira/tmmira tmmira/miradoc
	cp /dev/null tmmira_distlist
	cd tmmira; $(MAKE) distlist
	sed -e "s/^/tmmira\//" tmmira/distlist >> tmmira_distlist

tmpas_distlist: $(MAKEFILE) tmpas tmpas/tmpas tmpas/pasdoc
	cp /dev/null tmpas_distlist
	cd tmpas; $(MAKE) distlist
	sed -e "s/^/tmpas-$(TMPAS_VERSION)\//" tmpas/distlist >> tmpas_distlist

tmdemo_distlist: $(MAKEFILE) tmdemo
	cp /dev/null tmdemo_distlist
	cd tmdemo; $(MAKE) distlist
	sed -e "s/^/tmdemo-$(TMDEMO_VERSION)\//" tmdemo/dist.lst >> tmdemo_distlist

tmkernel_distlist: $(MAKEFILE) tmkernel tmkernel/tm tmkernel/tmc tmkernel/libtmc
	cp /dev/null tmkernel_distlist
	cd tmkernel; $(MAKE) distlist
	sed -e "s/^/tmkernel-$(TMKERNEL_VERSION)\//" tmkernel/dist.lst >> tmkernel_distlist

tmkerneldoc_distlist: $(MAKEFILE) tmkrndoc
	cp /dev/null tmkerneldoc_distlist
	cd tmkrndoc; $(MAKE) distlist
	sed -e "s/^/tmkerneldoc-$(TMKERNEL_VERSION)\//" tmkrndoc/dist.lst >> tmkerneldoc_distlist

tmkerneldoc-$(TMKERNEL_VERSION).tar.gz tmkerneldoc-$(TMKERNEL_VERSION).zip: tmkerneldoc_distlist
	-mkdir tmkerneldoc-$(TMKERNEL_VERSION)
	cvs -d $(CVSDIR) export -r HEAD -d tmkerneldoc-$(TMKERNEL_VERSION) tm/tmkrndoc
	tar cf tmkerneldoc-$(TMKERNEL_VERSION).tar `cat tmkerneldoc_distlist`
	gzip --best -f tmkerneldoc-$(TMKERNEL_VERSION).tar
	zip -q -9 tmkerneldoc-$(TMKERNEL_VERSION).zip `cat tmkerneldoc_distlist`
	rm -rf tmkerneldoc-$(TMKERNEL_VERSION)

tmkernel-$(TMKERNEL_VERSION).tar.gz tmkernel-$(TMKERNEL_VERSION).zip: tmkernel_distlist
	-mkdir tmkernel-$(TMKERNEL_VERSION)
	cvs -d $(CVSDIR) export -r HEAD -d tmkernel-$(TMKERNEL_VERSION) tm/tmkernel
	echo '#define TMKERNEL_VERSION "$(TMKERNEL_VERSION)"' > tmkernel-$(TMKERNEL_VERSION)/version.h
	echo '#define TMKERNEL_VERSION "$(TMKERNEL_VERSION)"' > tmkernel-$(TMKERNEL_VERSION)/tm/version.h
	cd tmkernel-$(TMKERNEL_VERSION)/libtmc; autoconf
	cd tmkernel-$(TMKERNEL_VERSION)/tm; autoconf
	cd tmkernel-$(TMKERNEL_VERSION)/tm; tm tm.ds tmcode.ct > tmcode.c
	cd tmkernel-$(TMKERNEL_VERSION)/tm; tm tm.ds tmcode.ht > tmcode.h
	cd tmkernel-$(TMKERNEL_VERSION)/tmc; autoconf
	cd tmkernel-$(TMKERNEL_VERSION); autoconf
	tar cf tmkernel-$(TMKERNEL_VERSION).tar `cat tmkernel_distlist`
	gzip --best -f tmkernel-$(TMKERNEL_VERSION).tar
	zip -q -9 tmkernel-$(TMKERNEL_VERSION).zip `cat tmkernel_distlist`
	rm -rf tmkernel-$(TMKERNEL_VERSION)

tmdemo-$(TMDEMO_VERSION).tar.gz tmdemo-$(TMDEMO_VERSION).zip: tmdemo_distlist
	-mkdir tmdemo-$(TMDEMO_VERSION)
	cvs -d $(CVSDIR) export -r HEAD -d tmdemo-$(TMDEMO_VERSION) tm/tmdemo
	tar cf tmdemo-$(TMDEMO_VERSION).tar `cat tmdemo_distlist`
	gzip --best -f tmdemo-$(TMDEMO_VERSION).tar
	zip -q -9 tmdemo-$(TMDEMO_VERSION).zip `cat tmdemo_distlist`
	rm -rf tmdemo-$(TMDEMO_VERSION)

tmpas-$(TMPAS_VERSION).tar.gz tmpas-$(TMPAS_VERSION).zip: tmpas_distlist
	-mkdir tmpas-$(TMPAS_VERSION)
	cvs -d $(CVSDIR) export -r HEAD -d tmpas-$(TMPAS_VERSION) tm/tmpas
	cd tmpas-$(TMPAS_VERSION); autoconf
	cd tmpas-$(TMPAS_VERSION)/tmpas; autoconf
	tar cf tmpas-$(TMPAS_VERSION).tar `cat tmpas_distlist`
	gzip --best -f tmpas-$(TMPAS_VERSION).tar
	zip -q -9 tmpas-$(TMPAS_VERSION).zip `cat tmpas_distlist`
	rm -rf tmpas-$(TMPAS_VERSION)

tmmira-$(TMMIRA_VERSION).tar.gz tmmira-$(TMMIRA_VERSION).zip: tmmira_distlist
	-mkdir tmmira-$(TMMIRA_VERSION)
	cvs -d $(CVSDIR) export -r HEAD -d tmmira-$(TMMIRA_VERSION) tm/tmmira
	cd tmmira-$(TMMIRA_VERSION); autoconf
	cd tmmira-$(TMMIRA_VERSION)/tmmira; autoconf
	tar cf tmmira-$(TMMIRA_VERSION).tar `cat tmmira_distlist`
	gzip --best -f tmmira-$(TMMIRA_VERSION).tar
	zip -q -9 tmmira-$(TMMIRA_VERSION).zip `cat tmmira_distlist`
	rm -rf tmmira-$(TMMIRA_VERSION)

$(FTPDIR)/tmdemo-$(TMDEMO_VERSION).tar.gz: tmdemo-$(TMDEMO_VERSION).tar.gz
	cp tmdemo-$(TMDEMO_VERSION).tar.gz $(FTPDIR)

$(FTPDIR)/tmdemo-$(TMDEMO_VERSION).zip: tmdemo-$(TMDEMO_VERSION).zip
	cp tmdemo-$(TMDEMO_VERSION).zip $(FTPDIR)

$(FTPDIR)/tmkernel-$(TMKERNEL_VERSION).tar.gz: tmkernel-$(TMKERNEL_VERSION).tar.gz
	cp tmkernel-$(TMKERNEL_VERSION).tar.gz $(FTPDIR)

$(FTPDIR)/tmkerneldoc-$(TMKERNEL_VERSION).zip: tmkerneldoc-$(TMKERNEL_VERSION).zip
	cp tmkerneldoc-$(TMKERNEL_VERSION).zip $(FTPDIR)

$(FTPDIR)/tmkerneldoc-$(TMKERNEL_VERSION).tar.gz: tmkerneldoc-$(TMKERNEL_VERSION).tar.gz
	cp tmkerneldoc-$(TMKERNEL_VERSION).tar.gz $(FTPDIR)

$(FTPDIR)/tmkernel-$(TMKERNEL_VERSION).zip: tmkernel-$(TMKERNEL_VERSION).zip
	cp tmkernel-$(TMKERNEL_VERSION).zip $(FTPDIR)

$(FTPDIR)/tmpas-$(TMPAS_VERSION).tar.gz: tmpas-$(TMPAS_VERSION).tar.gz
	cp tmpas-$(TMPAS_VERSION).tar.gz $(FTPDIR)

$(FTPDIR)/tmpas-$(TMPAS_VERSION).zip: tmpas-$(TMPAS_VERSION).zip
	cp tmpas-$(TMPAS_VERSION).zip $(FTPDIR)

$(FTPDIR)/tmmira-$(TMMIRA_VERSION).tar.gz: tmmira-$(TMMIRA_VERSION).tar.gz
	cp tmmira-$(TMMIRA_VERSION).tar.gz $(FTPDIR)

$(FTPDIR)/tmmira-$(TMMIRA_VERSION).zip: tmmira-$(TMMIRA_VERSION).zip
	cp tmmira-$(TMMIRA_VERSION).zip $(FTPDIR)

$(FTPDIR)/README: README.ftp
	cp README.ftp $(FTPDIR)/README

$(FTPDIR)/CHANGES.tmpas: tmpas/CHANGES
	cp tmpas/CHANGES $(FTPDIR)/CHANGES.tmpas

$(FTPDIR)/CHANGES.tmmira: tmmira/CHANGES
	cp tmmira/CHANGES $(FTPDIR)/CHANGES.tmmira

$(FTPDIR)/CHANGES.tmkernel: tmkernel/CHANGES
	cp tmkernel/CHANGES $(FTPDIR)/CHANGES.tmkernel

ftp: $(FTPFILES)
	touch ftp
