# Makefile for lib.tex, the KTH ACM Contest Template Library document

INTERMED=lib.aux lib.dvi lib.idx lib.log lib.lol lib.lop lib.toc

.PHONY: all always clean spotless index lib.ps lib.pdf util code codeclean

all:
	# Try 'make ps' or 'make pdf'!
	# These will always run latex or pdflatex, so that the index and ToC
	# may be fully generated. 'make clean' or 'make spotless' tidies up.

always: .

clean: codeclean
	rm -f $(INTERMED)
	cd util && $(MAKE) clean

spotless: clean
	rm -f lib.pdf lib.ps
	cd util && $(MAKE) spotless

index:
	makeindex lib.idx

ps: lib.ps index always

pdf: lib.pdf index always

lib.ps: lib.tex always
	latex lib.tex
	dvips -o lib.ps lib.dvi

lib.pdf: lib.tex always
	pdflatex lib.tex

lib.tex: style.sty lgrind.sty util code

util: always
	cd util && $(MAKE) util

code: always
	cd util && $(MAKE) code
	cd general && $(MAKE) code
	cd numerical && $(MAKE) code
	cd graph && $(MAKE) code
	cd graph/mst && $(MAKE) code
	cd geometry && $(MAKE) code
	cd geometry/hull && $(MAKE) code
	cd pattern && $(MAKE) code

codeclean: always
	cd util && $(MAKE) codeclean
	cd general && $(MAKE) codeclean
	cd numerical && $(MAKE) codeclean
	cd graph && $(MAKE) codeclean
	cd graph/mst && $(MAKE) codeclean
	cd geometry && $(MAKE) codeclean
	cd geometry/hull && $(MAKE) codeclean
	cd pattern && $(MAKE) codeclean

