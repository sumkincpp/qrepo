latex *.tex
mf '\mode:=localfont;' input *.mf
latex *.tex
dvipdf *.dvi
