IDIR = .
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

DEPS = Bitmap.c Bitmap.h Couche.c Couche.h Iris.h Iris.c main.c Neurone.c Neurone.h PMC.c PMC.h Statistiques.c Statistiques.h Util.c Util.h


OBJ = main.o Bitmap.o Couche.o Iris.o Neurone.o PMC.o Statistiques.o Util.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

rso-mnist: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core 