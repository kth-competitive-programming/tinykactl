# Makefile for lgrind, a LaTeX prettyprinter
# make binaries
# $Id: Makefile,v 1.4 1999/12/18 21:54:29 mike Exp $

BINDIR=$(BASEDIR)/bin
MANDIR=$(BASEDIR)/man

CC=gcc
MANPAGES1=lgrind.1
MANPAGES5=lgrindef.5
OBJS=lgrind.o regexp.o retest.o lgrindef.o v2lg.o

CFLAGS=-O2
# CFLAGS=-Dpopen=fopen -Dpclose=fclose
# There are operating systems and compilers without these...

.PHONY:	all install clean distribution

all:	lgrind

lgrind: lgrind.o lgrindef.o regexp.o
	$(CC) $(CFLAGS) -o lgrind lgrind.o lgrindef.o regexp.o

lgrind.o: lgrind.c lgutil.c
	$(CC) $(CFLAGS) -DDEFSFILE=\"$(DEFSFILE)\" -DVERSION=\"$(VERSION)\" -c lgrind.c

v2lg:	v2lg.o
	$(CC) $(CFLAGS) -o v2lg v2lg.o

retest: retest.o regexp.o
	$(CC) $(CFLAGS) -o retest retest.o regexp.o

install: all
	$(INSTALL) -s lgrind $(BINDIR)/lgrind
	$(INSTALL) -m 644 $(MANPAGES1) $(MANDIR)/man1
	$(INSTALL) -m 644 $(MANPAGES5) $(MANDIR)/man5

clean:
	rm -f $(OBJS) lgrind retest v2lg
