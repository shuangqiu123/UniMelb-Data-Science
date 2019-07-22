/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"
#define SIZE 10
#define ARBITRARYTAKE 3

int main(int argc, char **argv){
    int inputs[SIZE] = {7, 1, 3, 5, 6, 8, 4, 2, 9, 11};
    int i;
    
    struct pqueue *queue = makeQueue();
    
    printf("Adding all items to priority queue\n");
    for(i = 0; i < SIZE; i++){
        printf("%d ",inputs[i]);
        enqueue(queue, inputs[i], &(inputs[i]));
    }
    printf("\n");
    if(empty(queue)){
        printf("ERROR: Queue empty after all items added\n");
    }
    
    printf("Removing first three items from priority queue\n");
    for(i = 0; i < ARBITRARYTAKE; i++){
        printf("%d ",*(int *) (dequeue(queue)));
    }
    printf("\n");
    
    printf("Updating priority 11 item to 1\n");
    inputs[SIZE - 1] = 1;
    /* Normally you'd find this information from somewhere that
        the priority queue will update, but as the update function
        doesn't do anything anything with this information, that
        doesn't really matter. */
    update(queue, SIZE - ARBITRARYTAKE - 1);
    printf("Taking rest of items from priority queue.\n");
    for(i = 0; i < SIZE - ARBITRARYTAKE; i++){
        if(!empty(queue)){
            printf("%d ",*(int *) (dequeue(queue)));
        }
    }
    printf("\n");
    
    if(! empty(queue)){
        printf("ERROR: Queue not empty after all items dequeued\n");
    }
    
    freeQueue(queue);
    
    return 0;
}