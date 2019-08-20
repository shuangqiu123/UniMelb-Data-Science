CC = gcc
CFLAGS = -Wall -Werror -I -g
HEADERS = pqueue.h

make: main.o $(HEADERS)
	$(CC) -c main.c -o main.o

prog1: main.o $(HEADERS)
	$(CC) -o pq main.o pqueue.c $(CFLAGS)