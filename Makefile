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

getversion:
	bk changes | head -1 | cut -d @ -f2 | cut -d ' ' -f1,2 > version

ps: getversion lib.ps index always

pdf: getversion lib.pdf index always

pdfx3: getversion lib.pdfx3 index always

lib.ps: libtex always
	latex lib.tex
	dvips -o lib.ps lib.dvi

lib.pdf: libtex always
	pdflatex lib.tex

lib.pdfx3: lib.pdf
	pdflatex lib.tex
	pdflatex lib.tex

libtex: style.sty lgrind.sty pdflscape.sty util allcode

util: always
	cd util && $(MAKE) util

allcode: always
	cd . && $(MAKE) code
	cd util && $(MAKE) code
	cd contest && $(MAKE) code
	cd datastructures && $(MAKE) code
	cd io && $(MAKE) code
	cd numerical && $(MAKE) code
	cd combinatorial && $(MAKE) code
	cd numerical/bigint && $(MAKE) code
	cd graph && $(MAKE) code
	cd graph/mst && $(MAKE) code
	cd graph/maxflow && $(MAKE) code
	cd geometry && $(MAKE) code
	cd geometry/hull && $(MAKE) code
	cd geometry/voronoi && $(MAKE) code
	cd pattern && $(MAKE) code
	cd gametheory && $(MAKE) code
	cd solved && $(MAKE) code
	cd solved/other && $(MAKE) code
	cd solved/valladolid && $(MAKE) code

allcodeclean: always
	cd . && $(MAKE) codeclean
	cd util && $(MAKE) codeclean
	cd contest && $(MAKE) codeclean
	cd datastructures && $(MAKE) codeclean
	cd io && $(MAKE) codeclean
	cd numerical && $(MAKE) codeclean
	cd combinatorial && $(MAKE) codeclean
	cd numerical/bigint && $(MAKE) codeclean
	cd graph && $(MAKE) codeclean
	cd graph/mst && $(MAKE) codeclean
	cd graph/maxflow && $(MAKE) codeclean
	cd geometry && $(MAKE) codeclean
	cd geometry/hull && $(MAKE) codeclean
	cd geometry/voronoi && $(MAKE) codeclean
	cd pattern && $(MAKE) codeclean
	cd gametheory && $(MAKE) codeclean
	cd solved && $(MAKE) codeclean
	cd solved/other && $(MAKE) codeclean
	cd solved/valladolid && $(MAKE) codeclean

LGSTRIP=header
SUMSTRIP=header
UTIL=util
include $(UTIL)/makecode

