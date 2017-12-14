##########################################################

CFLAGS = -g -Wall `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`



prog: cleanprog skipbo extras
	-rm -rf *.o

all: prog progpropre pdf

skipbo: skipbo.o jeu.o cartes.o interface.o
	$(CC) skipbo.o jeu.o cartes.o interface.o $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o skipbo

skipbo.o: skipbo.c
	$(CC) -c skipbo.c $(CFLAGS) $(LDFLAGS) $(LDLIBS)

cartes.o: cartes.c cartes.h
	$(CC) -c cartes.c $(CFLAGS) $(LDFLAGS) $(LDLIBS)

jeu.o: jeu.c jeu.h
	$(CC) -c jeu.c $(CFLAGS) $(LDFLAGS) $(LDLIBS)

interface.o: interface.c interface.h
	$(CC) -c interface.c $(CFLAGS) $(LDFLAGS) $(LDLIBS)

extras:
	$(CC) extras.c $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o extras

pdf: latex cleanlatex

latex: rapport.tex
	pdflatex rapport.tex

clean:
	rm -rf *.o skipbo *.aux *.fdb_latexmk *.fls *.log *.synctex.gz *~

cleanprog:
	rm -rf *.o skipbo *~

progpropre:
	-rm -rf *.o *~

cleanlatex:
	rm -rf *.aux *.fdb_latexmk *.fls *.log *.synctex.gz *~
