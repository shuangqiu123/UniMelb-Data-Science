#include <stdio.h>
#include <stdlib.h>

#define I 10

int main(int argc, char **argv){

    int A[I];

    for (int i = 0; i < I; i++) {
        A[i] = rand();
    }

    printf("%d, %d, %d\n", A[0], A[2], A[5]);
    
    return 0;
}