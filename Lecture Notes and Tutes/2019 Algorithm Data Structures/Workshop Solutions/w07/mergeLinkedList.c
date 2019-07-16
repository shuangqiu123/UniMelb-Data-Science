/* merge.c */
#include <stddef.h>
#include "queue.h"

struct linkedList *mergeSort(struct linkedList *list){
    /* FILL IN SETUP FOR Linked List BOTTOM-UP mergesort */
    /* We need a queue for the ll nodes, a pointer to the curr and head nodes, and a new list for the sorted list (since it is not in-place) */
    /* Note this is bottom-up mergesort, hence it is NOT recursive */
    struct llq *queue = NULL;
	struct llq *nextQ = NULL;
    
	struct linkedList *curr = list; /* Current element from input ll */
	struct linkedList *nextNode = NULL; /* Next element from current */

	struct linkedList *sortedList;
	struct linkedList *sortedListRear;

    /* While linked list, add to queue */
	while(curr){
		nextNode = curr->next;
		curr->next = NULL;

		queue = add(queue, curr);
		curr = nextNode;
	}
	
    /* FILL IN loop */
    while (queue) {
        curr = dequeue(&queue);

        /* End condition */
        if (!queue) {
            /* If the queue is now empty and the next queue is empty, we only have a single element */
            if (!nextQ) {
                return curr;
            }
            else {
                /* Otherwise we add the current element to the next queue and dereference the pointer */
                nextQ = add(nextQ, curr);
                queue = nextQ;
                nextQ = NULL;
            }
        }
        /* Merge sort */
        else {
			nextNode = dequeue(&queue);

			sortedList = NULL;
			sortedListRear = NULL;

            /* While there are nodes to compare */
			while(curr && nextNode){
                /* Tie breaker to the left element, hence it preserves ordering and is stable */
				if(curr->item <= nextNode->item){
                    /* Initialize sorted list if it is empty */
					if(!sortedList) {
						sortedList = curr;
						sortedListRear = curr;
					} 
                    /* Sort two elements */
                    else {
						sortedListRear->next = curr;
						sortedListRear = sortedListRear->next;
					}

					curr = curr->next;
				} 
                else {
					if(!sortedList) {
						sortedList = nextNode;
						sortedListRear = nextNode;
					} 
                    else {
						sortedListRear->next = nextNode;
						sortedListRear = sortedListRear->next;
					}

					nextNode = nextNode->next;
				}
			}
            /* Empty array condition */
			if(!curr){
				if (!sortedList){
					sortedList = nextNode;
				} 
                /* Add tail of next list to end of list */
                else sortedListRear->next = nextNode;
			} 
            else {
				if (!sortedList){
					sortedList = curr;
				} 
                /* Add tail of curr list to end of next list */
                else sortedListRear->next = curr;
			}
			/* Add to next processing queue. */
			nextQ = add(nextQ, sortedList);

			/* Condition to reverse queue */
			if(!queue){
				queue = nextQ;
				nextQ = NULL;
			}
		}
	}

	return sortedList;
}