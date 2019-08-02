CC=gcc
CFLAGS=-Wall -Werror -I -g
HEADERS=hashT.h

main.o: main.c $(HEADERS)
	gcc -c main.c -o main.o

main: main.o
	gcc main.o hashT.c -o hash $(CFLAGS)

clean:
	-rm -f main.o
	-rm -f hash