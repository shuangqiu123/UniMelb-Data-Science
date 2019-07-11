#include <stdio.h>
#include <stdlib.h>

/* You may have to make some changes to this program to make this work. */
/* Changes the value of x given to the integer 9. */
void changeX(int x);

int main(int argc, char **argv){
    int x = 5;
    printf("[main    before] x = %d\n",x);
    changeX(x);
    printf("[main    after ] x = %d\n",x);
    return 0;
}

void changeX(int x){
    printf("[changeX before] x = %d\n",x);
    x = 9;
    printf("[changeX after ] x = %d\n",x);
}