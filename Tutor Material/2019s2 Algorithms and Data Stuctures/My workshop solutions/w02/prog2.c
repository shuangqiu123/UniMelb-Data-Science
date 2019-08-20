#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv){
    int numStrings;
    int nextStringLength;
    int i, j;
    char **strings;
    
    /* Read number of strings to store. */
    scanf("%d", &numStrings);
    
    /* Allocate space for the array of strings. */
    strings = (char**)calloc(numStrings, sizeof(char*));
    /*
    Dynamic array which holds a dynamic string -> Use (char**).
    Then we want the array to have numStrings blocks of size dynamic string -> Use (char*)
    */
    assert(strings);
    
    /* For each string, get its length, allocate space for it
        and read all the characters into the string.
        Note: Remember, these are standard strings. */
    for (i = 0; i < numStrings; i++) {
        scanf("%d ", &nextStringLength); /* Note that you need to specify the space in scanf */

        strings[i] = (char*)calloc(nextStringLength + 1, sizeof(char));
        assert(strings[i]);

        for (j = 0; j < nextStringLength; j++) {
            scanf("%c", &strings[i][j]);
        }
        strings[i][nextStringLength] = '\0';
    }
    
    
    /* The below prints all words in the array with spaces between them. */
    if(numStrings > 0){
        printf("%s",strings[0]);
    }
    
    for(i = 1; i < numStrings; i++){
        printf(" %s",strings[i]);
    }
    printf("\n");

    for (i = 0; i < numStrings; i++) {
        free(strings[i]);
    }
    free(strings);
    
    return 0;
}