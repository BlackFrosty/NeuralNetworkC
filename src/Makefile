IDIR = .
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

DEPS = main.c structures.c structures.h fonctions_io.c fonctions_io.h fonctions_calcul.c fonctions_calcul.h rso_neurones.h rso_neruones.c


OBJ = main.o structures.o fonctions_io.o fonctions_calcul.o rso_neurones.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

rso-mnist: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core 
