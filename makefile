CC=gcc
CFLAGS=-Wall

ODIR=/usr/bin

LIBS=-lm -lncurses

default: ufccalc

ufccalc: ufccalc.c
	$(CC) $(CFLAGS) $(LIBS) -o $(ODIR)/ufccalc ufccalc.c

clean:
	rm $(ODIR)/ufccalc
