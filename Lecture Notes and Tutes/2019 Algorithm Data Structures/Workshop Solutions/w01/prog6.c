/* Run using valgrind!!! */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 

#define I 7
#define NULLBYTE 1

/* Define node struct */
typedef struct node node_t;

struct node {
	node_t *next;
	char *str;
};

/* Func */
int main(int argc, char **argv){
    char *A[I];
    int i, j, len;

    node_t *head = NULL;
	node_t *curr = NULL;

    for (i = 0; i < I; i++) {
        /* malloc the first node */
        curr = (node_t*)malloc(sizeof(node_t));
        assert(curr);

        scanf("%d", &len);
        
        /* calloc the string array */
        curr->str = (char*)calloc(len + NULLBYTE, sizeof(char));
        assert(curr->str);

        curr->next = head;
        head = curr;

        for (j = 0; j < len; j++) {
            scanf("%c", &curr->str[j]);
        }

        curr->str[len] = '\0';
    }

    printf("%s, %s, %s\n", curr->str, curr->next->str, curr->next->next->str);

    curr = head;
    while (curr != NULL) {
        head = curr;
        free(curr->str);
        curr = curr->next;
        free(head);
    }

    return 0;
}