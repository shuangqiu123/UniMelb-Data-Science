/* Add your stack implementation from Programming 4.1 
    and change the data type from integer to character */

/* Compresses all duplicate characters into character and
    count pairs in given input and prints the results. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_char.c"

void compress(char *input);

void compress(char *input){
    /* FILL IN HERE */
    struct stack *compStack = makeStack();

    int i, count, n;
    char prev, curr;

    n = strlen(input);

    for (i = 0; i < n; i++) {
        if (!empty(compStack) && prev != input[i]) { /* If stack not empty and prev char is not curr char */
            count = 0;
            while (!empty(compStack)) { /* While stack not empty, pop characters and add one to count */
                curr = pop(compStack);
                count++;
            }
            printf("%c%d", curr, count); /* Print final character */
        }
        push(compStack, input[i]); /* Push next char into stack and assign prev char */
        prev = input[i];
    }
    /* End of string. */
    if (!empty(compStack) && prev != input[i]) { 
        count = 0;
        while (!empty(compStack)) {
            curr = pop(compStack);
            count++;
        }
        printf("%c%d\n\n", curr, count);
    }
}

int main(int argc, char **argv){
    char *testInput = "Testting";
    printf("Test Input:\n");
    compress(testInput);

    char *input = "Aaaaaa, screamed the amateur magician as the aardvark ate the apple he'd prepared...";
    printf("Test Case 1:\n");
    compress(input);
    
    return 0;
}