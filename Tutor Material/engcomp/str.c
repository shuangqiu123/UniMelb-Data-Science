#include <stdio.h>
#include <stdlib.h>

void myStrCat(char *dst, char *src) {
    // we want *dst + *src
    // find length of dst with ndst, and src with nsrc
    int ndst = 0, nsrc = 0;

    // loop while not null byte for dsc
    while(dst[ndst] != '\0') {
        ndst++;
    }

    // now, while we can add src (assumption that dst has sufficient space according to question)
    while(src[nsrc] != '\0') {
        dst[ndst++] = src[nsrc++];
        // here, we let dst at index ndst (this is at the end of dst string since we found out how long it was in the previous while loop)
        // then, we assign this index the first char of src (since nsrc is declared as 0)
        // then we increment ndst and nsrc until the char is a null byte
    }
    // assign the final final char as null byte
    dst[ndst] = '\0';
}

// ignore
int main() {
    char *str1 = (char *)malloc(100 * sizeof(char));
    str1[0] = 'a';
    str1[1] = 'b';
    str1[2] = 'c';
    str1[3] = '\0'; 
    char *str2 = "def";

    myStrCat(str1, str2);

    printf("strcat string after function: %s\n", str1);

    return 1;
}