TARGETS = skipbo


##########################################################

CC=gcc

CFLAGS = -g -O2 -Wall `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`

skipbo : skipbo.o jeu.o
	$(CC) skipbo.o jeu.o $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(TARGETS)

skipbo.o : skipbo.c
	$(CC) -c $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o skipbo.o

jeu.o : jeu.c jeu.h
	$(CC) -c $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o jeu.o

clean:
	-rm -rf $(TARGETS) $(OBJECTS)
