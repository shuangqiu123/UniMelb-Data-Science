CC = gcc
CFLAGS = -Wall -Werror -I -g
HEADERS = merge.h ../w07/queue.h ../w07/ll.h

main.o: main.o $(HEADERS)
	$(CC) -c main.c -o main.o

prog1: main.o ../w07/ll.c ../w07/queue.c merge.c $(HEADERS)
	$(CC) -o adaptiveMergeSort main.o ../w07/ll.c ../w07/queue.c merge.c $(CFLAGS)