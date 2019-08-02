#include <stdio.h>
#include <stdlib.h>
#include "../w05/hashT.c"

#define INPUTSIZE 14

/* Declare hash table data structure */
/* Recall we need a: size, used (or allocated), arbitrary data/hash function/insert/print */

struct hashTable {
    int size;
    int used;
	void **data;
    int *(*hash)(void *);
    void (*insert)(struct hashTable *, int *, void *); /* Function pointer to the insert function */
    void (*print)(void *);
};

/* Write insert function */

/* Write printTable function. */

/* Write freeTable function. */

int main(int argc, char **argv){
    
    int inputs[INPUTSIZE] = {2, 3, 97, 23, 15, 21, 4, 23, 29, 37, 5, 23, 28, 40};
    
    /* Declare table. */

    
    int i;
    
    /* Create empty table. */
    printf("Created hash table of size 13\n");
    printTable(/* table */);
    
    for(i = 0; i < INPUTSIZE; i++){
        printf("Inserting %d\n",inputs[i]);
        insert(/* table */, inputs[i]);
        printTable(/* table */);
    }
    printf("Finished inserting items into table\n");
    
    freeTable(/* Table */);
    
    return 0;
}