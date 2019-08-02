#include <stdio.h>
#include <stdlib.h>
#define PRIMECOUNT 1000

/* functions */
int reverse_check(int n);

int main(int argc, char **argv){
    /* The primes 1 - 1000, if n is prime, 
        primes[n - 1] == 1 and 0 otherwise. */
    int primes[PRIMECOUNT];
    int i, j;
    
    for(i = 0; i < PRIMECOUNT; i++){
        primes[i] = 1;
    }
    
    /* Write a prime checking algorithm here. */
    for (i = 1; i < PRIMECOUNT; i++) {
        for (j = i + 1; j < PRIMECOUNT; j++) {
            if (primes[j] && ((j + 1) % (i + 1) == 0)) {
                primes[j] = 0;
            }
        }
    }
    /* -------------------------------------- */
    
    printf("All emirp primes found from 1 - 1000:\n");
    for(i = 0; i < PRIMECOUNT; i++){
        if(primes[i] && primes[reverse_check(i + 1) - 1]){
            printf("%d ", i + 1);
        }
    }
    printf("\n");
    
    return 0;
}

int reverse_check(int n) {
    int digits = 0, reverse = 0;
    int temp = 0;
    
    /* Find number of digits */
    temp = n;
    while (temp > 0) {
        digits++;
        temp /= 10;
    }

    /* Reverse the number */
    temp = n;
    while (digits > 0) {
        reverse *= 10;
        reverse += temp % 10;
        temp /= 10;
        digits--;
    }

    return reverse;
}