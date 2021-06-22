IDIR = .
CC=gcc
CFLAGS=-I$(IDIR) -ggdb

ODIR=obj
LDIR =../lib

LIBS=-lm

DEPS = main.c structures.c structures.h functionsIO.c functionsIO.h Calcul.c Calcul.h rso_neurones.h rso_neruones.c Util.c Util.h


OBJ = main.o structures.o functionsIO.o Calcul.o rso_neurones.o Util.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

rso-mnist: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

rso-mini: main.o structures.o
	$(CC) -o rso $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f *.o *~ core a.out
