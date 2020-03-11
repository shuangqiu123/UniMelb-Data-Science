#include <stdio.h>
#include <stdlib.h>

int randomisedSubsetSum(int items[], int n, int k) {
    // n is given to be in range (0, 100) and represents number of elements in items
    // k is the required sum
    // num is a random int in range (0, n] and determines number of items to get
    int num; 
    int currSum;

    for (int i = 0; i < 10000; i++) {
        // required to be between 1 to n, so we add 1 if num % n = 0 to get num = 1
        // you would use num = rand() % n + 1; but ive fixed it to about 40 to give it a chance
        num = rand() % 40 + 1; 
        // we need to ensure that we do not select the same item twice when randomly choosing.

        // create a subset of size num
        int subset[num];
        int j = 0;

        while (j < num) {
            // get the value in items at index rand() % num
            int itemVal = items[rand() % num];
            
            // for every value in subset up to the j'th index (because the subset array is filled with j elements)
            // create a flag to determine if a value is a duplicate
            int duplicate = 0;
            for (int v = 0; v < j; v++) {
                // if duplicate found, break and flag it
                if (itemVal == subset[v]) {
                    duplicate = 1;
                    break;
                }
            }

            // if there are no duplicates
            if (!duplicate) {
                subset[j++] = itemVal;
                // notice how we only increment j if there are no duplicates, otherwise j does not change and it goes back to the top
            }
        }

        // now calculate the sum and see if its equal to k
        for (int u = 0; u < num; u++) {
            currSum += subset[u];
        }

        printf("Iteration %d: num = %d, sum = %d against k = %d\n", i, num, currSum, k);

        if (currSum == k) {
            return 1;
        }
    }

    // no sum found
    return 0;
}

// ignore
int main() {
    // test case with random cases
    int n = rand() % 100 + 1;
    int items[n];
    int k = rand() % 220000000;

    for (int i = 0; i < n; i++) {
        items[i] = rand() % 1000;
    }

    printf("Finding sum with k=%d and n=%d\n",k,n);

    int result = randomisedSubsetSum(items, n, k);
    if (result) {
        printf("Matching sum found\n");
    }
    else {
        printf("No sum found\n");
    }

    return 1;
}