# Makefile for tinykactl.tex, the KTH ACM Contest Template Tinykactlrary document

BASEDIR=$(PWD)
INTERMED= \
tinykactl.aux tinykactl.dvi tinykactl.idx tinykactl.ilg tinykactl.ind \
tinykactl.log tinykactl.lol tinykactl.lop tinykactl.toc

.PHONY: \
all always clean spotless index ps pdf \
tinykactl.ps tinykactl.pdf tinykactltex util allcode allcodeclean

all:
	# Try 'make ps' or 'make pdf'!
	# These will always run latex or pdflatex, so that the index and ToC
	# may be fully generated. 'make clean' or 'make spotless' tidies up.

always: .

spotless: clean
	$(MAKE) spotless -C util BASEDIR=$(BASEDIR)
	rm -f tinykactl.pdf tinykactl.ps version tag

index:
	touch tinykactl.idx
	makeindex tinykactl.idx

getversion:
#	bk changes | head -1 | cut -d @ -f2 | cut -d ' ' -f1,2 > version
#	bk changes | head -5 | grep TAG | head -1 | cut -f 4- -d ' ' > tag
	date +%Y-%m-%d > version

ps: tinykactl.ps index always

pdf: tinykactl.pdf index always

pdfx3: tinykactl.pdfx3 index always

tinykactl.ps: tinykactltex always
	latex tinykactl.tex
	dvips -o tinykactl.ps tinykactl.dvi

tinykactl.pdf: tinykactltex always
	pdflatex tinykactl.tex

tinykactl.pdfx3: tinykactl.pdf
	pdflatex tinykactl.tex
	makeindex tinykactl.idx
	pdflatex tinykactl.tex

tinykactltex: getversion tinykactl.tex kactl.sty lgrind.sty pdflscape.sty util code

util: always
	$(MAKE) util -C util BASEDIR=$(BASEDIR)

LGSTRIP=header
SUMSTRIP=header
include $(BASEDIR)/Makefile.inc

