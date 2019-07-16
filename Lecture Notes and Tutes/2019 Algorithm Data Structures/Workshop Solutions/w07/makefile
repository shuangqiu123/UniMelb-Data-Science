CC = gcc
CFLAGS = -Wall -Werror -I -g
HEADERS1 = ll.h queue.h mergeLinkedList.h
HEADERS2 = mergeArray.h

main1.o: main1.c $(HEADERS1)
	gcc -c main1.c -o main1.o

main2.o: main2.c $(HEADERS2)
	gcc -c main2.c -o main2.o

prog1: main1.o
	gcc main1.o mergeLinkedList.c queue.c ll.c -o mergeSortLinkedList

prog2: main2.o
	gcc main2.o mergeArray.c -o mergeSortArray

clean:
	-rm -f main1.o
	-rm -f main2.o
	-rm -f mergeSortLinkedList
	-rm -f mergeSortArray