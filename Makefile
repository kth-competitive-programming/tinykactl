# Makefile for lib.tex, the KTH ACM Contest Template Library document

BASEDIR=$(PWD)
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

spotless: clean
	$(MAKE) spotless -C util BASEDIR=$(BASEDIR)
	rm -f lib.pdf lib.ps version tag

index:
	makeindex lib.idx

getversion:
	bk changes | head -1 | cut -d @ -f2 | cut -d ' ' -f1,2 > version
	bk changes | head -4 | grep TAG | cut -f 4- -d ' ' > tag

ps: lib.ps index always

pdf: lib.pdf index always

pdfx3: lib.pdfx3 index always

lib.ps: libtex always
	latex lib.tex
	dvips -o lib.ps lib.dvi

lib.pdf: libtex always
	pdflatex lib.tex

lib.pdfx3: lib.pdf
	pdflatex lib.tex
	makeindex lib.idx
	pdflatex lib.tex

libtex: getversion lib.tex acmlib.sty lgrind.sty pdflscape.sty util code

util: always
	$(MAKE) util -C util BASEDIR=$(BASEDIR)

LGSTRIP=header
SUMSTRIP=header
include $(BASEDIR)/Makefile.inc

