CC=gcc
CFLAGS=-Wall

ODIR=/usr/bin

LIBS=-lm -lncurses

default:
	@echo Run 'sudo make install' to build and install the program

install: ufccalc

ufccalc: ufccalc.c
	$(CC) $(CFLAGS) -o $(ODIR)/ufccalc ufccalc.c $(LIBS)

clean:
	rm $(ODIR)/ufccalc

.PHONY: install clean
