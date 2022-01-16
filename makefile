CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=calculate

all: $(EXEC)

calculate: calculate.o main.o
	$(CC) -o calculate calculate.o main.o $(LDFLAGS)

calculate.o: calculate.c
	$(CC) -o calculate.o -c calculate.c $(CFLAGS)

main.o: main.c calculate.h
	$(CC) -o main.o -c main.c $(CFLAGS)

clean: rm -r *.o