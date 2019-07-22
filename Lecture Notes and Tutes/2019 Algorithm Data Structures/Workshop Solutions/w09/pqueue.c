/* pqueue.c */
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "pqueue.h"

#define DEFAULTSIZE 2

struct pqueue {
    /* FILL IN THIS PART */
    /* A priority queue requires a priority, data, and used/allocated */
    int *priority;
    void **dataArray;
    int used;
    int allocated;

};

struct pqueue *makeQueue(){
    /* Write this */
    struct pqueue *initialPQ = (struct pqueue *)calloc(1, sizeof(struct pqueue));
    assert(initialPQ);

    initialPQ->priority = NULL;
    initialPQ->dataArray = NULL;

    initialPQ->used = 0;
    initialPQ->allocated = 0;

    return initialPQ;
}

void enqueue(struct pqueue *queue, int priority, void *data){
    /* Write this */
    /* Initialise queue if it has not */
    if (!queue->priority) {
        queue->priority = (int *)calloc(DEFAULTSIZE, sizeof(int));
        assert(queue->priority);

        queue->dataArray = (void **)calloc(DEFAULTSIZE, sizeof(void *));
        assert(queue->dataArray);

        queue->allocated = DEFAULTSIZE;
    }
    /* Condition if the queue becomes full (i.e we need more space) */
    else if (queue->used + 1 >= queue->allocated) {
        queue->allocated *= DEFAULTSIZE;

        queue->priority = (int *)realloc(queue->priority, sizeof(int) * queue->allocated);
        assert(queue->priority);

        queue->dataArray = (void **)realloc(queue->dataArray, sizeof (void *) * queue->allocated);
        assert(queue->dataArray);
    }
    /* Assign data and priority of item to be enqueued */
    queue->priority[queue->used] = priority;
    queue->dataArray[queue->used] = data;
    queue->used++;
}

void *dequeue(struct pqueue *queue){
    /* Write this */
    int i;
    int priorityIndex = 0;

    void *value;

    for (i = 0; i < queue->used; i++) {
        /* Find the index of the max priority since our array is NOT sorted */
        /* An alternative to the step is to sort the dataArray by priority, then take the first element */
        if(queue->priority[i] < queue->priority[priorityIndex]){
            priorityIndex = i;
        }
    }

    /* Retrieve highest priority value */
    value = queue->dataArray[priorityIndex];
    /* We subtract one since we have dequeued the element */
    queue->priority[priorityIndex] = queue->priority[queue->used - 1]; 
    queue->dataArray[priorityIndex] = queue->dataArray[queue->used - 1];
    queue->used--;
    
    return value;
}

/* REDUNDANT */
void update(struct pqueue *queue, int index){
    int i;

	for(i = 0; i < queue->used; i++){
        /* 
        Recall dataArray is of type void **, so we are now trying to access
        the pointer to dataArray assigned as an integer type (int *)
        */
		if(*(int *)queue->dataArray[i] != queue->priority[i]){
			queue->priority[i] = *(int *)queue->dataArray[i];
		}
	}
}

int empty(struct pqueue *queue){
    /* Write this. */
    if (queue->used == 0) return 1;

    return 0;
}

void freeQueue(struct pqueue *queue){
    /* We just need to free all the allocated memory */
    free(queue->priority);
    free(queue->dataArray);
    free(queue);
}