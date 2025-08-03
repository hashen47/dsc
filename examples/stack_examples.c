#include <stdio.h>
#include <stdlib.h>
#include "../includes/stack.h"                                   // include this headers file (use your relative path)

int main(void) {
    // fixed-size stack example
    Stack *s1 = STACK_INIT(int, 10);                             // initialize the stack (first param type, second param size) if size is 0 that stack can dynamically grow, if size is more than zero then it is fixed size

    printf("is stack empty: %d\n", IS_STACK_EMPTY(s1));          // can know that is stack empty
    printf("is stack full: %d\n", IS_STACK_FULL(s1));            // can know that is stack full
    printf("capacity of the stack: %zu\n", STACK_CAPACITY(s1));  // zero mean un-fixed stack, positive value mean fixed-size stack and also the max size that can contains
    printf("size of the stack: %zu\n", STACK_SIZE(s1));          // give that how many elements are currently contains the stack 

    for (int i = 0; i < STACK_CAPACITY(s1); i++) {
        // STACK_PUSH(s1, rand() % 100);                         // WRONG: don't do this cannot pass values directly 
        int value = rand() % 100;
        STACK_PUSH(s1, value);                                   // push values to the stack
    }

    printf("capacity of the stack: %zu\n", STACK_CAPACITY(s1));
    printf("size of the stack: %zu\n", STACK_SIZE(s1));

    for (int i = 0; i < STACK_CAPACITY(s1); i++) {
        printf("pop value: %d\n", STACK_POP(s1, int));           // pop values from the stack
    }

    printf("capacity of the stack: %zu\n", STACK_CAPACITY(s1));
    printf("size of the stack: %zu\n", STACK_SIZE(s1));

    STACK_FREE(s1);                                              // free the stack memory


    // dynamically grow stack example
    Stack *s2 = STACK_INIT(int, 0);                              // '0' mean no fix sized, can grow dynamically

    printf("is stack empty: %d\n", IS_STACK_EMPTY(s2));          // can know that is stack empty
    printf("is stack full: %d\n", IS_STACK_FULL(s2));            // can know that is stack full
    printf("capacity of the stack: %zu\n", STACK_CAPACITY(s2));  // zero mean un-fixed stack, positive value mean fixed-size stack and also the max size that can contains
    printf("size of the stack: %zu\n", STACK_SIZE(s2));          // give that how many elements are currently contains the stack 

    /*
    for (int i = 0; i < STACK_CAPACITY(s2); i++) {               // WRONG: don't do this, for dynamically growing stack capacity is '0' ('0' indicates dynamically grow stack)
        STACK_PUSH(s2, rand() % 100);                            
    }
    */

    for (int i = 0; i < 20; i++) {
        // STACK_PUSH(s2, rand() % 100);                         // WRONG: cannot pass values directly 
        int value = rand() % 100;
        STACK_PUSH(s2, value);                                   // push some random values to the stack
    }

    printf("capacity of the stack: %zu\n", STACK_CAPACITY(s2));
    printf("size of the stack: %zu\n", STACK_SIZE(s2));

    while (STACK_SIZE(s2) != 0) {
        printf("pop value: %d\n", STACK_POP(s2, int));           // pop values from the stack
    }

    printf("capacity of the stack: %zu\n", STACK_CAPACITY(s2));
    printf("size of the stack: %zu\n", STACK_SIZE(s2));

    STACK_FREE(s2);                                              // free the stack memory
}
