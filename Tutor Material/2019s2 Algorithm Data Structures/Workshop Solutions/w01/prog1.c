#include <stdio.h>

/* Define an I, which will be the size of the array, A. */
#define I 10
#define MULTIPLE 12

int main(int argc, char **argv){
    /* Define an array, A, of integers */
    int A[I];
    /* write a loop which populates A with multiples of 12 */
    for (int i = 0; i < I; i++) {
        A[i] = i * MULTIPLE;
    }
    /* print out A[0], A[2] and A[5] */
    printf("%d, %d, %d\n", A[0], A[2], A[5]);
    
    return 0;
}