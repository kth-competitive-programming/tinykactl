# Makefile for lib.tex, the KTH ACM Contest Template Library document

INTERMED= \
lib.aux lib.dvi lib.idx lib.ilg lib.ind \
lib.log lib.lol lib.lop lib.toc

.PHONY: \
all always clean spotless index ps pdf \
lib.ps lib.pdf libtex util allcode allcodeclean

all:
	# Try 'make ps' or 'make pdf'!
	# These will always run latex or pdflatex, so that the index and ToC
	# may be fully generated. 'make clean' or 'make spotless' tidies up.

always: .

clean: allcodeclean
	rm -f $(INTERMED)
	cd util && $(MAKE) clean

spotless: clean
	rm -f lib.pdf lib.ps
	cd util && $(MAKE) spotless

index:
	makeindex lib.idx

ps: lib.ps index always

pdf: lib.pdf index always

lib.ps: libtex always
	latex lib.tex
	dvips -o lib.ps lib.dvi

lib.pdf: libtex always
	pdflatex lib.tex

libtex: style.sty lgrind.sty pdflscape.sty util allcode

util: always
	cd util && $(MAKE) util

allcode: always
	cd . && $(MAKE) code
	cd util && $(MAKE) code
	cd general && $(MAKE) code
	cd io && $(MAKE) code
	cd numerical && $(MAKE) code
	cd numerical/bigint && $(MAKE) code
	cd graph && $(MAKE) code
	cd graph/mst && $(MAKE) code
	cd geometry && $(MAKE) code
	cd geometry/hull && $(MAKE) code
	cd pattern && $(MAKE) code

allcodeclean: always
	cd . && $(MAKE) codeclean
	cd util && $(MAKE) codeclean
	cd general && $(MAKE) codeclean
	cd io && $(MAKE) codeclean
	cd numerical && $(MAKE) codeclean
	cd numerical/bigint && $(MAKE) codeclean
	cd graph && $(MAKE) codeclean
	cd graph/mst && $(MAKE) codeclean
	cd geometry && $(MAKE) codeclean
	cd geometry/hull && $(MAKE) codeclean
	cd pattern && $(MAKE) codeclean

LGSTRIP=header
SUMSTRIP=header
UTIL=util
include $(UTIL)/makecode
