# Makefile for lib.tex, the KTH ACM Contest Template Library document

INTERMED=lib.aux lib.dvi lib.idx lib.log lib.lol lib.lop lib.toc

.PHONY: all clean lib.ps lib.pdf util

all:
	# Try 'make ps' or 'make pdf'!
	# These will always run latex or pdflatex, so that the index and ToC
	# may be fully generated. 'make clean' or 'make spotless' tidies up.

clean: util/code.sh
	rm -f $(INTERMED)
	cd util; make clean
	util/code.sh clean

spotless: clean
	rm -f lib.pdf lib.ps
	cd util; make spotless

index:
	makeindex lib.idx

ps: lib.ps

pdf: lib.pdf

lib.ps: lib.tex
	latex lib.tex
	dvips -o lib.ps lib.dvi

lib.pdf: lib.tex
	pdflatex lib.tex

lib.tex: style.sty lgrind.sty util code numerical graph

util:
	cd util; make all

code: util/code.sh
	util/code.sh gen

numerical:\
 numerical/numerical.tex\
 numerical/combinatorics.tex\
 numerical/combinatorics.tex

graph:\
 graph/graph.tex\
 graph/shortest_path.tex\
 graph/mst.tex

