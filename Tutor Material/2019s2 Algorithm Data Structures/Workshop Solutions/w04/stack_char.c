/* stack_char.c */
/* Same as stack.c apart from the changes from int to char */
#include <stdlib.h>
#include <assert.h>

#define MIN_SIZE 2

struct stack {
    /* FILL IN: Define stack struct here. */
    char *stack; /* array */
    int used; /* count of occupied elements (assigned values) */
    int allocated; /* count of allocations */
};

struct stack *makeStack(){
    /* FILL IN */
    struct stack *newStack = (struct stack*)calloc(1, sizeof(struct stack));
    /* Initialise the new stack and assign default values. */
    assert(newStack);

    newStack->stack = NULL;
    newStack->used = 0;
    newStack->allocated = 0;

    return newStack;
}

void push(struct stack *stack, int item){
    /* FILL IN */
    if (stack->allocated == 0) { /* If not allocated, we need to make a new stack of min size 2. */
        stack->allocated = MIN_SIZE;
        stack->stack = (char*)calloc(stack->allocated, sizeof(char));
        assert(stack->stack);
    }
    else if (stack->allocated <= stack->used + 1) { /* Else if the number currently allocated stacks is leq number of used, increase size. */
        stack->allocated *= MIN_SIZE; /* Double the current size. */
        stack->stack = (char*)realloc(stack->stack, sizeof(char)*(stack->allocated));
        assert(stack->stack);
    }
    /* Now we can assign the item to the stack and add 1 to the count. */
    stack->stack[stack->used] = item;    /* Really it should be value not item since we're working with integers but oh well... */
    stack->used++;
}

int pop(struct stack *stack){
    /* FILL IN */
    /* All we really need to do here is to return the value and decrease the count */
    stack->used--;
    return stack->stack[stack->used];
}

int empty(struct stack *stack){
    /* FILL IN */
    if (!stack || stack->used == 0) {
        return 1;
    }
    else return 0;
}
void freeStack(struct stack **stack){
    /* FILL IN */
    /* The logic here is:
        1) Not do anything if the stack does not exist
        2) Free the stacks 
        3) Free the stack structure
        4) Dereference the pointer (good practice after freeing)
    */
    if (!*stack || !stack) return;
    else if ((*stack)->stack) {
        free((*stack)->stack);
    }
    free(*stack);
    *stack = NULL;
}

