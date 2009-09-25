
.PHONY: pdf html


pdf: intro.pdf
intro.pdf: intro.tex
	rubber -d intro

html: intro.tex 
	mkdir -p html
	latex2html -dir html intro.tex
