#include <stdio.h>
#include <stdlib.h>

#define I 7

int main(int argc, char **argv){
    int A[I];
    int i = 0;

    while (i < I) {
        scanf("%d", &A[i]);
        i++;
    }
    
    printf("%d, %d, %d\n", A[0], A[2], A[5]);
    
    return 0;
}