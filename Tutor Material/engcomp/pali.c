#include <string.h>
#include <stdio.h>

int isPalindrome(char *str, int n) {
    // char *str represents the string, int n represents length of str + null byte, so we need to subtract 1
    n--;
    // base case (only 1 character for odd, or 0 characters for even number of characters)
    if (n == 1 || n == 0) {
        return 1;
    }

    // the first and last characters do not match
    if (str[0] != str[n]) {
        return 0;
    }
    
    // otherwise recurse by returning the function without the first character and n-1 from the total number of characters
    return isPalindrome(str + 1, n - 1);

    return 0;
}

// ignore this
int main() {
    char *str = "rats live on no evil star\0";
    printf("First test case: rats live on no evil star\n");
    if (isPalindrome(str, strlen(str))) {
        printf("First test case is palindrome\n");
    }
    else {
        printf("First test case is not palindrome (WRONG)\n");
    }

    char *str2 = "abab\0";
    printf("\nSecond test case: abab\n");
    if (isPalindrome(str2, strlen(str2))) {
        printf("Second test case is palindrome (WRONG)\n");
    }
    else {
        printf("Second test case is not palindrome\n");
    }
    return 1;
}