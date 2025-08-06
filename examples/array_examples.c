#include <stdio.h>
#include "../includes/array.h"                                            // include this headers file (use your relative path)

int main(void) {
    Array *arr1 = ARRAY_INIT(int);                                        // initialize a new array in 'int' type

    for (int i = 0; i < 10; i++) {
        ARRAY_APPEND(arr1, i);                                            // append values to the array
    }

    int val = 40;
    ARRAY_INSERT_AT(arr1, 0, val);                                        // insert 40 in '0' index to arr1 (first you have to assign value to variable, then pass it)

    val = 23;
    ARRAY_APPEND(arr1, val);                                              // append 23 to arr1 (first you have to assign value to variable, then pass it)

    val = 30;
    ARRAY_REPLACE_AT(arr1, 5, val);                                       // replace 5th index with 30 (first you have to assign value to variable, then pass it)

    // ARRAY_INSERT_AT(arr1, 0, 40);                                      // WRONG: don't to this, this is wrong, you cannot pass direct value
    // ARRAY_APPEND(arr1, 23)                                             // WRONG: don't do this, this is wrong, you cannot pass direct values
    // ARRAY_REPLACE_AT(arr1, 5, 30)                                      // WRONG: don't do this, this is wrong, you cannot pass direct values

    printf("size: %zu\n", ARRAY_SIZE(arr1));                              // can get the array size (current size)

    for (int i = 0; i < ARRAY_SIZE(arr1); i++) {    
        printf("index: %d, value: %d\n", i, ARRAY_GET_AT(arr1, i, int));  // get value from given index 
    }

    printf("value: %d\n", ARRAY_GET_AT(arr1, 0, int));                    // this is also fine

    for (int i = 0; i < ARRAY_SIZE(arr1); i++) {
        printf("value: %d\n", ARRAY_POP(arr1, int));                      // pop value from the array
    }

    printf("size: %zu\n", ARRAY_SIZE(arr1));

    ARRAY_FREE(arr1);                                                     // free up the memory
}
