##########################################################

CFLAGS = -g -O2 -Wall `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`


prog: skipbo
	-rm -rf *.o

skipbo: skipbo.o jeu.o cartes.o
	$(CC) skipbo.o jeu.o cartes.o $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o skipbo

skipbo.o: skipbo.c
	$(CC) -c skipbo.c $(CFLAGS) $(LDFLAGS) $(LDLIBS)

cartes.o: cartes.c cartes.h
	$(CC) -c cartes.c $(CFLAGS) $(LDFLAGS) $(LDLIBS)

jeu.o: jeu.c jeu.h
	$(CC) -c jeu.c $(CFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	-rm -rf *.o skipbo
