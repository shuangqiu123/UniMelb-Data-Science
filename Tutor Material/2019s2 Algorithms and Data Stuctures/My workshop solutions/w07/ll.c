/* ll.c */
#include <stdlib.h>
#include <assert.h>
#include "ll.h"

struct linkedList *prepend(struct linkedList *head, int item){
    /* FILL IN if using. */
    struct linkedList *newHead = (struct linkedList *)malloc(sizeof(struct linkedList));
    assert(newHead);

    newHead->next = head;
    newHead->item = item;

    return newHead;
}

/* Add a linked list item to the end of the list, traversing all items. */
struct linkedList *append(struct linkedList *head, int item){
    /* FILL IN if using. */
    struct linkedList **curr = &head;

    /* Traverse to the end of the linked list from initial address (head) */
    while (*curr) {
        curr = &((*curr)->next);
    }

    /* Add a new element to the linked list */
    *curr = (struct linkedList *)malloc(sizeof(struct linkedList));
    assert(curr);
    
    (*curr)->next = NULL;
    (*curr)->item = item;

    return head;
}