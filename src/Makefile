IDIR = .
CC=gcc
CFLAGS=-I$(IDIR) -ggdb

ODIR=obj
LDIR =../lib

LIBS=-lm

DEPS = main.c \
structures.c structures.h \
functionsIO.c functionsIO.h \
calcul.c calcul.h \
rso_neurones.h rso_neurones.c \
Util.c Util.h \
fonctionsRso.c fonctionsRso.h


OBJ = main.o structures.o FunctionsIO.o Calcul.o rso_neurones.o Util.o FunctionsRso.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

rso-mnist: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

rso-mini: main.o structures.o
	$(CC) -o rso $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f *.o *~ core a.out
