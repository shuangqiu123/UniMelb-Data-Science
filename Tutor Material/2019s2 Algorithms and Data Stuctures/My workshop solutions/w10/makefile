CC = gcc
CFLAGS = -Wall -Werror -I -g
HEADERS = ../w09/pqueue.h dijkstra.h digraph.h

make: main.o $(HEADERS)
	$(CC) -c main.c -o main.o

prog1: main.o $(HEADERS)
	$(CC) -o pq main.o ../w09/pqueue.c dijkstra.c digraph.c $(CFLAGS)