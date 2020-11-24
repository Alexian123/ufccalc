CC=gcc
CFLAGS=-Wall

ODIR=/usr/bin

LIBS=-lm -lncurses

default:
	@echo Run \'sudo make install\' to build and install the program
	@echo or \'sudo make uninstall\' to uninstall the program.

install: ufccalc

ufccalc: ufccalc.c
	$(CC) $(CFLAGS) -o $(ODIR)/ufccalc ufccalc.c $(LIBS)

uninstall:
	rm $(ODIR)/ufccalc

.PHONY: install uninstall
