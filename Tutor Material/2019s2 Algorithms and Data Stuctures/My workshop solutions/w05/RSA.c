#include <stdio.h>
#include <stdlib.h>

#define N 133
#define E 5
#define D 11

/* Returns an int representing the given
    value encrypted using RSA using the
    given parameters. */
unsigned int encrypt(unsigned int n, 
    unsigned int e, unsigned int value);

/* Returns an int representing the given
    value decrypted using RSA using the
    given parameters.
*/
unsigned int decrypt(unsigned int n,
    unsigned int d, unsigned int value);

unsigned int encrypt(unsigned int n, 
    unsigned int e, unsigned int value){
    /* Do (value^e) mod n */
    /*
    NOTE:
    >> is the Binary Right Shift Operator. The left operands value is moved right by the number of bits specified by the right operand.
    */
    int i;
    unsigned int n_bits = 0;
    unsigned int encryption = 1;

    /* 
    This finds the number of bits to shift to the right such that e becomes false (i.e 0).
    For example, if e = 60, then shifting e by 1 bit will make e = 30, then 15, then 7, etc... 
    */

    while (e >> n_bits) {
        n_bits++;
    }

    for (i = 0; i < n_bits; i++) {
        encryption = (encryption * encryption) % n;
        if (e >> (n_bits - 1 - i)) {
            encryption = (encryption * value) % n;
        }
    }
    
    return encryption;
}

unsigned int decrypt(unsigned int n,
    unsigned int d, unsigned int value){
    /* Do (value^d) mod n. */
    return encrypt(n, d, value);
}

int main(int argc, char **argv){
	unsigned int toEncrypt[] = {72, 63, 14, 72, 72, 131, 95, 107, 92, 104, 51, 
		24, 54, 14, 92, 72, 10, 95, 131, 96, 21, 104, 47, 25, 131, 95, 24};
	unsigned int toDecrypt[] = {96, 51, 13, 51, 129, 96, 73, 7, 41, 7, 80, 6, 
		109, 80, 2, 8, 2, 6, 56, 7, 41, 41, 124, 8, 57, 7};


	int i;
    
    for(i = 0; i < sizeof(toEncrypt)/sizeof(toEncrypt[0]); i++){
        printf("%c",(char) encrypt(N, E, toEncrypt[i]));
    }

    printf("\n");

    for(i = 0; i < sizeof(toDecrypt)/sizeof(toDecrypt[0]); i++){
        printf("%c",(char) decrypt(N, D, toDecrypt[i]));
    }
    printf("\n");
    
    return 0;
}