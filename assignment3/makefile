rm=/bin/rm -f
CC=cc
DEFS=
INCLUDES=-I.

DEFINES= $(INCLUDES) $(DEFS)
CFLAGS= -std=c99 $(DEFINES) -O2 -fomit-frame-pointer -funroll-loops -g

all: stream_driver stream.o KeccakF1600.o


stream_driver: stream_driver.c stream.c KeccakF1600.c stream.o KeccakF1600.o
	$(CC) $(CFLAGS) -o stream_driver stream_driver.c stream.o KeccakF1600.o

stream.o: stream.c stream.h
	$(CC) $(CFLAGS) -c stream.c $(LIBS)

KeccakF1600.o: KeccakF1600.c KeccakF1600.h
	$(CC) $(CFLAGS) -c KeccakF1600.c $(LIBS)

clean:
	$(rm) *.o stream_driver *~
