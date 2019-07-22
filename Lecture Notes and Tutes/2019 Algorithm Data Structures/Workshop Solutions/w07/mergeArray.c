/* merge.c */
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#define WINDOW 2

int *mergeSort(int *list, int size){
    /* FILL IN loop */
    int i, j, sortedIndex;
    int left, right;

    int width = 1;
    int *sortedList;

    sortedList = (int *)calloc(size, sizeof(int));
    assert(sortedList);

    /* While the width of sub-array is less than size of full array */
    while (width <= size) {
        left = 0;

        /* Sort from left side */
        while (left < size) {
            i = 0;
            j = 0;
            sortedIndex = 0;

            right = left + width;
            /* Sort until sub-array exahusted */

            /* 
            Think of the initial sub-array as list[0] vs list[0 + 1], then list[1] vs list[1 + 1], etc... 
            */

            /* While the left and right indicies are less than the size of the full array, and whilst the size of the sub-array is less than our width */
            while (left + i < size && right + j < size && i < width && j < width) {
                /* Tie-breaker to the left */
                if (list[left + i] <= list[right + j]) {
                    sortedList[sortedIndex] = list[left + i];
                    i++;
                }
                else {
                    sortedList[sortedIndex] = list[right + j];
                    j++;
                }
                sortedIndex++;
            }
            /* Sort left list */
            while (i < width && (left + i) < size) {
                sortedList[sortedIndex] = list[left + i];
                i++;
                sortedIndex++;
            }
            /* Sort right list */
            while (j < width && (right + j) < size) {
                sortedList[sortedIndex] = list[right + j];
                j++;
                sortedIndex++;
            }

            /* Now assign to initial array */
            for (i = 0; i < sortedIndex; i++) {
                list[left + i] = sortedList[i];
            }
            /* Reset index and move left index to next sub-array */
            sortedIndex = 0;
            left += WINDOW*width;
        }
        /* Size of sub-array is now doubled */
        width *= WINDOW; 
    }
    
    free(sortedList);
    sortedList = NULL;

    return list;
}