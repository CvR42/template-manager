# Makefile for the root of the Tm distribution

# The version numbers below reflect release versions for the various
# packages.
# The _DOS version number does not contain dots.
TMKERNEL_VERSION = 1.2-beta3
TMKERNEL_VERSION_DOS = 12b3
TMPAS_VERSION = 1.0.2
TMPAS_VERSION_DOS = 102
TMMIRA_VERSION = 1.0.2
CVSDIR = /home/gargamel/reeuwijk/Cvs

SHELL=/bin/sh
FTPDIR=/home/gargamel/ftp/pub/software/Tm

JUNK = tmkernel_distlist tmkernel_distlist_dos tmpas_distlist \
    tmpas_distlist_dos tmmira_distlist

PACKAGES = \
    tmkernel-$(TMKERNEL_VERSION).tar.gz \
    tmk$(TMKERNEL_VERSION_DOS).zip \
    tmpas-$(TMPAS_VERSION).tar.gz \
    tmp$(TMPAS_VERSION_DOS).zip \
    tmmira-$(TMMIRA_VERSION).tar.gz

FTPFILES= \
    $(FTPDIR)/tmkernel-$(TMKERNEL_VERSION).tar.gz \
    $(FTPDIR)/tmk$(TMKERNEL_VERSION_DOS).zip \
    $(FTPDIR)/tmpas-$(TMPAS_VERSION).tar.gz \
    $(FTPDIR)/tmp$(TMPAS_VERSION_DOS).zip \
    $(FTPDIR)/tmmira-$(TMMIRA_VERSION).tar.gz \
    $(FTPDIR)/README \
    $(FTPDIR)/CHANGES.tmkernel \
    $(FTPDIR)/CHANGES.tmpas \
    $(FTPDIR)/CHANGES.tmmira

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

tmpas_distlist_dos: $(MAKEFILE) tmpas tmpas/tmpas tmpas/pasdoc
	cp /dev/null tmpas_distlist_dos
	cd tmpas; $(MAKE) distlist
	sed -e "s/^/tmp$(TMPAS_VERSION_DOS)\//" tmpas/distlist >> tmpas_distlist_dos

tmkernel_distlist: $(MAKEFILE) tmkernel tmkernel/tm tmkernel/tmc tmkernel/libtmc tmkernel/tmusrdoc
	cp /dev/null tmkernel_distlist
	cd tmkernel; $(MAKE) distlist
	sed -e "s/^/tmkernel-$(TMKERNEL_VERSION)\//" tmkernel/dist.lst >> tmkernel_distlist

tmkernel_distlist_dos: $(MAKEFILE) tmkernel tmkernel/tm tmkernel/tmc tmkernel/libtmc tmkernel/tmusrdoc
	cp /dev/null tmkernel_distlist_dos
	cd tmkernel; $(MAKE) distlist
	sed -e "s/^/tmk$(TMKERNEL_VERSION_DOS)\//" tmkernel/dist.lst >> tmkernel_distlist_dos

tmkernel-$(TMKERNEL_VERSION).tar.gz: tmkernel_distlist
	-mkdir tmkernel-$(TMKERNEL_VERSION)
	cvs -d $(CVSDIR) export -r HEAD -d tmkernel-$(TMKERNEL_VERSION) tm/tmkernel
	echo '#define TMKERNEL_VERSION "$(TMKERNEL_VERSION)"' > tmkernel-$(TMKERNEL_VERSION)/version.h
	cd tmkernel-$(TMKERNEL_VERSION)/libtmc; autoconf
	cd tmkernel-$(TMKERNEL_VERSION)/tm; autoconf
	cd tmkernel-$(TMKERNEL_VERSION)/tmc; autoconf
	cd tmkernel-$(TMKERNEL_VERSION)/tmusrdoc; make main.ps
	tar cf tmkernel-$(TMKERNEL_VERSION).tar `cat tmkernel_distlist`
	gzip --best -f tmkernel-$(TMKERNEL_VERSION).tar
	rm -rf tmkernel-$(TMKERNEL_VERSION)

tmk$(TMKERNEL_VERSION_DOS).zip: tmkernel_distlist_dos
	-rm -f tmk$(TMKERNEL_VERSION_DOS).zip
	-mkdir tmk$(TMKERNEL_VERSION_DOS)
	cvs -d $(CVSDIR) export -r HEAD -d tmk$(TMKERNEL_VERSION_DOS) tm/tmkernel
	echo '#define TMKERNEL_VERSION "$(TMKERNEL_VERSION)"' > tmk$(TMKERNEL_VERSION_DOS)/version.h
	cd tmk$(TMKERNEL_VERSION_DOS)/libtmc; autoconf
	cd tmk$(TMKERNEL_VERSION_DOS)/tm; autoconf
	cd tmk$(TMKERNEL_VERSION_DOS)/tmc; autoconf
	cd tmk$(TMKERNEL_VERSION_DOS)/tmusrdoc; make main.ps
	zip -q -9 tmk$(TMKERNEL_VERSION_DOS).zip `cat tmkernel_distlist_dos`
	rm -rf tmk$(TMKERNEL_VERSION_DOS)

tmpas-$(TMPAS_VERSION).tar.gz: tmpas_distlist
	-mkdir tmpas-$(TMPAS_VERSION)
	cvs -d $(CVSDIR) export -r HEAD -d tmpas-$(TMPAS_VERSION) tm/tmpas
	cd tmpas-$(TMPAS_VERSION); autoconf
	cd tmpas-$(TMPAS_VERSION)/tmpas; autoconf
	tar cf tmpas-$(TMPAS_VERSION).tar `cat tmpas_distlist`
	gzip --best -f tmpas-$(TMPAS_VERSION).tar
	rm -rf tmpas-$(TMPAS_VERSION)

tmp$(TMPAS_VERSION_DOS).zip: tmpas_distlist_dos
	-rm -f tmp$(TMPAS_VERSION_DOS).zip
	-mkdir tmp$(TMPAS_VERSION_DOS)
	cvs -d $(CVSDIR) export -r HEAD -d tmp$(TMPAS_VERSION_DOS) tm/tmpas
	cd tmp$(TMPAS_VERSION_DOS); autoconf
	cd tmp$(TMPAS_VERSION_DOS)/tmpas; autoconf
	zip -q -9 tmp$(TMPAS_VERSION_DOS).zip `cat tmpas_distlist_dos`
	rm -rf tmp$(TMPAS_VERSION_DOS)

tmmira-$(TMMIRA_VERSION).tar.gz: tmmira_distlist
	-mkdir tmmira-$(TMMIRA_VERSION)
	cvs -d $(CVSDIR) export -r HEAD -d tmmira-$(TMMIRA_VERSION) tm/tmmira
	cd tmmira-$(TMMIRA_VERSION); autoconf
	cd tmmira-$(TMMIRA_VERSION)/tmmira; autoconf
	tar cf tmmira-$(TMMIRA_VERSION).tar `cat tmmira_distlist`
	gzip --best -f tmmira-$(TMMIRA_VERSION).tar
	rm -rf tmmira-$(TMMIRA_VERSION)

$(FTPDIR)/tmkernel-$(TMKERNEL_VERSION).tar.gz: tmkernel-$(TMKERNEL_VERSION).tar.gz
	cp tmkernel-$(TMKERNEL_VERSION).tar.gz $(FTPDIR)

$(FTPDIR)/tmk$(TMKERNEL_VERSION_DOS).zip: tmk$(TMKERNEL_VERSION_DOS).zip
	cp tmk$(TMKERNEL_VERSION_DOS).zip $(FTPDIR)

$(FTPDIR)/tmpas-$(TMPAS_VERSION).tar.gz: tmpas-$(TMPAS_VERSION).tar.gz
	cp tmpas-$(TMPAS_VERSION).tar.gz $(FTPDIR)

$(FTPDIR)/tmp$(TMPAS_VERSION_DOS).zip: tmp$(TMPAS_VERSION_DOS).zip
	cp tmp$(TMPAS_VERSION_DOS).zip $(FTPDIR)

$(FTPDIR)/tmmira-$(TMMIRA_VERSION).tar.gz: tmmira-$(TMMIRA_VERSION).tar.gz
	cp tmmira-$(TMMIRA_VERSION).tar.gz $(FTPDIR)

$(FTPDIR)/README: README.ftp
	cp README.ftp $(FTPDIR)/README

$(FTPDIR)/CHANGES.tmpas: tmpas-$(TMPAS_VERSION)/CHANGES
	cp tmpas-$(TMPAS_VERSION)/CHANGES $(FTPDIR)/CHANGES.tmpas

$(FTPDIR)/CHANGES.tmmira: tmmira-$(TMMIRA_VERSION)/CHANGES
	cp tmmira-$(TMMIRA_VERSION)/CHANGES $(FTPDIR)/CHANGES.tmmira

$(FTPDIR)/CHANGES.tmkernel: tmkernel-$(TMKERNEL_VERSION)/CHANGES
	cp tmkernel-$(TMKERNEL_VERSION)/CHANGES $(FTPDIR)/CHANGES.tmkernel

ftp: $(FTPFILES)
	touch ftp
