# Makefile for LGrind, a LaTeX prettyprinter

# $Id: Makefile,v 1.10 2000/12/27 21:42:37 mike Exp $

#BASEDIR=/usr
#DEFSFILE=${HOME}/Work/lgrind/lgrindef
#DEFSFILE=$(BASEDIR)/share/texmf/tex/latex/lgrind/lgrindef
#TEXFILEDIR=$(BASEDIR)/share/texmf/tex/latex/lgrind
#DOCDIR=$(BASEDIR)/doc/lgrind
BASEDIR=util/lgrind
DEFSFILE=$(BASEDIR)/lgrindef
TEXFILEDIR=$(BASEDIR)
DOCDIR=$(BASEDIR)

INSTALL=install
SOURCES=lgrind.c lgutil.c regexp.c regexp.h lgrindef.c lgrindef.h retest.c v2lg.c
TEXFILES=lgrind.dtx lgrind.sty lgrind.ins

VERSION=3.66
DISTVERSION=lgrind-$(VERSION)

.PHONY:	all install clean distribution lgrind

all:	lgrind.sty lgrind.dvi lgrind

lgrind.sty: lgrind.dtx
	latex lgrind.ins

lgrind.dvi: lgrind.dtx
	latex lgrind.dtx
	latex lgrind.dtx

lgrind:
	cd source; \
	    make DEFSFILE=$(DEFSFILE) BASEDIR=$(BASEDIR) INSTALL=$(INSTALL) VERSION=$(VERSION)

clean:
	rm -f lgrind.log
	rm -f lgrind.aux
	rm -f lgrind.dvi
	rm -f lgrind.sty
	rm -f lgrind.idx
	rm -f lgrind.glo
	rm -f doc-lgrind.lg
	cd source; \
	    make clean

distribution: clean
	mkdir $(DISTVERSION)
	cp -r example $(DISTVERSION)
	rm -rf $(DISTVERSION)/example/CVS
	cp -r source $(DISTVERSION)
	rm -rf $(DISTVERSION)/source/CVS
	cp README FAQ lgrind.* lgrindef $(DISTVERSION)
	sed -e "s/^#DEFSFILE/=DEFSFILE/;s/^DEFSFILE/#DEFSFILE/;s/^=DEFSFILE/DEFSFILE/"\
	    < Makefile >$(DISTVERSION)/Makefile
	tar czf $(DISTVERSION).tar.gz $(DISTVERSION)
	rm -r $(DISTVERSION)

install: all
	$(INSTALL) -m 755 -d $(TEXFILEDIR)
	$(INSTALL) -m 644 lgrind.sty $(TEXFILEDIR)
	$(INSTALL) -m 755 -d $(DOCDIR)
	$(INSTALL) -m 644 lgrind.dvi $(DOCDIR)
	$(INSTALL) -m 644 lgrindef $(DEFSFILE)
	cd source; \
	make install BASEDIR=$(BASEDIR) INSTALL=$(INSTALL)
