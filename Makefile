CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g -DNDEBUG
RM = rm -rf
MKDIR = mkdir -p
COPY = cp
CD = cd

SRCDIR = src
DISTDIR = dist
EXECFILE = main

build: clean mkdir lib compile

compile:
	$(CC) $(CFLAGS) $(SRCDIR)/main.c $(DISTDIR)/lib.a -o $(DISTDIR)/$(EXECFILE)

lib:
	$(CC) -c $(CFLAGS) $(SRCDIR)/lib.c -o $(DISTDIR)/lib.o
	ar rsc $(DISTDIR)/lib.a $(DISTDIR)/lib.o

clean:
	$(RM) $(DISTDIR)

mkdir:
	$(MKDIR) $(DISTDIR)

check-mem-leaks:
	$(CD) $(DISTDIR) && valgrind --leak-check=full --track-origins=yes  ./$(EXECFILE)
