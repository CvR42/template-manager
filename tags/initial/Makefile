# Makefile for the root of the Tm distribution

# The version numbers below reflect release versions for the various
# packages.
# The _DOS version number does not contain dots.
TMKERNEL_VERSION = 1.2
TMKERNEL_VERSION_DOS = 12
TMPAS_VERSION = 1.0.1
TMPAS_VERSION_DOS = 101
TMMIRA_VERSION = 1.0.1

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

tmmira_distlist: $(MAKEFILE) tmmira-$(TMMIRA_VERSION) tmmira-$(TMMIRA_VERSION)/tmmira tmmira-$(TMMIRA_VERSION)/miradoc
	cp /dev/null tmmira_distlist
	cd tmmira-$(TMPAS_VERSION); $(MAKE) distlist
	sed -e "s/^/tmmira-$(TMMIRA_VERSION)\//" tmmira-$(TMMIRA_VERSION)/distlist >> tmmira_distlist

tmpas_distlist: $(MAKEFILE) tmpas-$(TMPAS_VERSION) tmpas-$(TMPAS_VERSION)/tmpas tmpas-$(TMPAS_VERSION)/pasdoc
	cp /dev/null tmpas_distlist
	cd tmpas-$(TMPAS_VERSION); $(MAKE) distlist
	sed -e "s/^/tmpas-$(TMPAS_VERSION)\//" tmpas-$(TMPAS_VERSION)/distlist >> tmpas_distlist

tmpas_distlist_dos: $(MAKEFILE) tmpas-$(TMPAS_VERSION) tmpas-$(TMPAS_VERSION)/tmpas tmpas-$(TMPAS_VERSION)/pasdoc
	cp /dev/null tmpas_distlist_dos
	cd tmpas-$(TMPAS_VERSION); $(MAKE) distlist
	sed -e "s/^/tmp$(TMPAS_VERSION_DOS)\//" tmpas-$(TMPAS_VERSION)/distlist >> tmpas_distlist_dos

tmkernel_distlist: $(MAKEFILE) tmkernel-$(TMKERNEL_VERSION) tmkernel-$(TMKERNEL_VERSION)/tm tmkernel-$(TMKERNEL_VERSION)/tmc tmkernel-$(TMKERNEL_VERSION)/libtmc tmkernel-$(TMKERNEL_VERSION)/tmusrdoc
	cp /dev/null tmkernel_distlist
	cd tmkernel-$(TMKERNEL_VERSION); $(MAKE) distlist
	sed -e "s/^/tmkernel-$(TMKERNEL_VERSION)\//" tmkernel-$(TMKERNEL_VERSION)/dist.lst >> tmkernel_distlist

tmkernel_distlist_dos: $(MAKEFILE) tmkernel-$(TMKERNEL_VERSION) tmkernel-$(TMKERNEL_VERSION)/tm tmkernel-$(TMKERNEL_VERSION)/tmc tmkernel-$(TMKERNEL_VERSION)/libtmc tmkernel-$(TMKERNEL_VERSION)/tmusrdoc
	cp /dev/null tmkernel_distlist_dos
	cd tmkernel-$(TMKERNEL_VERSION); $(MAKE) distlist
	sed -e "s/^/tmk$(TMKERNEL_VERSION_DOS)\//" tmkernel-$(TMKERNEL_VERSION)/dist.lst >> tmkernel_distlist_dos

tmkernel-$(TMKERNEL_VERSION).tar.gz: tmkernel_distlist
	tar cf tmkernel-$(TMKERNEL_VERSION).tar `cat tmkernel_distlist`
	gzip --best -f tmkernel-$(TMKERNEL_VERSION).tar

tmk$(TMKERNEL_VERSION_DOS).zip: tmkernel_distlist_dos
	rm -f tmk$(TMKERNEL_VERSION_DOS) tmk$(TMKERNEL_VERSION_DOS).zip
	ln -s tmkernel-$(TMKERNEL_VERSION) tmk$(TMKERNEL_VERSION_DOS)
	zip -q -9 tmk$(TMKERNEL_VERSION_DOS).zip `cat tmkernel_distlist_dos`

tmpas-$(TMPAS_VERSION).tar.gz: tmpas_distlist
	tar cf tmpas-$(TMPAS_VERSION).tar `cat tmpas_distlist`
	gzip --best -f tmpas-$(TMPAS_VERSION).tar

tmp$(TMPAS_VERSION_DOS).zip: tmpas_distlist_dos
	rm -f tmp$(TMPAS_VERSION_DOS) tmp$(TMPAS_VERSION_DOS).zip
	ln -s tmpas-$(TMPAS_VERSION) tmp$(TMPAS_VERSION_DOS)
	zip -q -9 tmp$(TMPAS_VERSION_DOS).zip `cat tmpas_distlist_dos`

tmmira-$(TMMIRA_VERSION).tar.gz: tmmira_distlist
	tar cf tmmira-$(TMMIRA_VERSION).tar `cat tmmira_distlist`
	gzip --best -f tmmira-$(TMMIRA_VERSION).tar

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
