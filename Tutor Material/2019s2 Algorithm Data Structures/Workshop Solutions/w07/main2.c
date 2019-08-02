/* main.c */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mergeArray.h"

/* 8 is a power of 2, so should be the least trouble. */
/* Try 7 to have to deal with an empty list */
#define SIZE 8

int main(int argc, char **argv){
    int list[SIZE];
    int *sortedList;
    int i;
    
    /* Initialise random number generator. */
    time_t t;
    srand((unsigned) time(&t));
    
    printf("Original Array: ");
    for(i = 0; i < SIZE; i++){
        /* values between 0 and 99 are easier to read. */
        list[i] = rand() % 100;
        printf("%d ",list[i]);
    }
    
    printf("\n");
    
    printf("Mergesorting.\n");
    sortedList = mergeSort(list, SIZE);
    printf("MergeSorted list: ");
    for(i = 0; i < SIZE; i++){
        printf("%d ",sortedList[i]);
    }
    printf("\n");
    
    return 0;
}