CC = gcc
AR = ar
CFLAGS = -c -Wall

all: prog

prog: main.o libinterfaz.a
	$(CC) -static -o prog main.o libinterfaz.a

libinterfaz.a: interfaz.o
	$(AR) rcs libinterfaz.a interfaz.o

main.o: main.c interfaz.h
	$(CC) $(CFLAGS) main.c

interfaz.o: interfaz.c interfaz.h
	$(CC) $(CFLAGS) interfaz.c

.PHONY: clean

clean: 
	rm -f *.o *.a prog