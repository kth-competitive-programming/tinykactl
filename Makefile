all: always
	# Try 'make ps' or 'make pdf'!
	# These will always run latex or pdflatex, so that the index and ToC
	# may be fully generated

ps: lib.ps

pdf: lib.pdf

lib.ps: lib.tex always
	latex lib.tex
	dvips -o lib.ps lib.dvi

lib.pdf: lib.tex always
	pdflatex lib.tex

lib.tex: style.sty numerical graph

numerical: numerical/numerical.tex numerical/combinatorics.tex numerical/combinatorics.tex

# Dummy dependency to always make a target
always: .
