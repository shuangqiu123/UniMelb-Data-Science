#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 

#define I 7
#define NULLBYTE 1

int main(int argc, char **argv){
    char *A[I];
    int i, j, len;

    for (i = 0; i < I; i++) {
        scanf("%d", &len);
        
        A[i] = (char*)calloc(len + NULLBYTE, sizeof(char));
        assert(A[i]);

        for (j = 0; j < len; j++) {
            scanf("%c", &A[i][j]);
        }

        A[i][len] = '\0';
    }

	printf("%s, %s, %s\n", A[0], A[2], A[5]);

    for (i = 0; i < I; i++) {
        free(A[i]);
    }

    return 0;
}