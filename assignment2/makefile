rm=/bin/rm -f
CC=cc
DEFS=
INCLUDES=-I.

DEFINES= $(INCLUDES) $(DEFS)
CFLAGS= -std=c99 $(DEFINES) -O2 -fomit-frame-pointer -funroll-loops

all: Keccak_r1024_driver

Keccak_r1024_driver:  Keccak_r1024_driver.c KeccakF1600.o Keccak_r1024.o
	$(CC) $(CFLAGS) -o Keccak_r1024_driver Keccak_r1024_driver.c KeccakF1600.o Keccak_r1024.o


Keccak_r1024.o: Keccak_r1024.c Keccak_r1024.h
	$(CC) $(CFLAGS) -c Keccak_r1024.c $(LIBS)

KeccakF1600.o: KeccakF1600.c KeccakF1600.h
	$(CC) $(CFLAGS) -c KeccakF1600.c $(LIBS)

clean:
	$(rm) KeccakF1600.o Keccak_r1024.o Keccak_r1024_driver *.o  *~
