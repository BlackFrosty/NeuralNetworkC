IDIR = .
CC=gcc
#CFLAGS=-I$(IDIR) -ggdb
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

DEPS = main.c \
structures.c structures.h \
functionsIO.c functionsIO.h \
calculs.c calculs.h \
Util.c Util.h \
fonctionsRso.c fonctionsRso.h


OBJ = main.o structures.o functionsIO.o calculs.o Util.o fonctionsRso.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

rso-mnist: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

rso-mini: main.o structures.o
	$(CC) -o rso $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f *.o *~ core a.out rso rso-mnist
