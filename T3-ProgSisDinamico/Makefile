CC = gcc

all: prog_dyn

prog_dyn: main.c libinterfaz.so
	$(CC) -o prog_dyn main.c ./libinterfaz.so

libinterfaz.so: interfaz.c interfaz.h
	$(CC) -shared -fPIC -o libinterfaz.so interfaz.c

.PHONY: clean

clean:
	rm -f *.so prog_dyn