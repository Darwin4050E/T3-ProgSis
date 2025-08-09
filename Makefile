CC = gcc
CFLAGS = -c -Wall

all: program

program: main.o interfaz.o
	$(CC) main.o interfaz.o -o program

main.o: main.c interfaz.h
	$(CC) $(CFLAGS) main.c

interfaz.o: interfaz.c interfaz.h
	$(CC) $(CFLAGS) interfaz.c

.PHONY: clean

clean: 
	rm -f *.o program
