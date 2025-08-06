#include <stdio.h>
#include "../includes/queue.h"

int main(void) {
    Queue *q = QUEUE_INIT(int, 10);                           // size cannot be zero or negative here
    // Queue *q = QUEUE_INIT(int, 0);                         // WRONG: you have to give positive capacity to the queue, if you want to resize it later, use QUEUE_RESIZE function

    printf("queue capacity: %zu\n", QUEUE_CAPACITY(q));       // get the queue capacity
    printf("queue size: %zu\n", QUEUE_SIZE(q));               // get how many elements fill in the queue
    printf("is queue full: %d\n", IS_QUEUE_FULL(q));          // get whether queue is full or not
    printf("is queue empty: %d\n", IS_QUEUE_EMPTY(q));        // get whether queue is empty or not

    // ENQUEUE(q, 1);                                         // WRONG: you cannot pass values directly, first assign value to a variable and then pass the variable

    for (int i = 0; i < QUEUE_CAPACITY(q); i++) {
        ENQUEUE(q, i);                                        // enqueue values to the queue 
    }

    printf("queue capacity: %zu\n", QUEUE_CAPACITY(q));
    printf("queue size: %zu\n", QUEUE_SIZE(q));
    printf("is queue full: %d\n", IS_QUEUE_FULL(q));
    printf("is queue empty: %d\n", IS_QUEUE_EMPTY(q));

    for (int i = 0; i < QUEUE_CAPACITY(q)-2; i++) {
        int value = DEQUEUE(q, int);                          // enqueue values to the queue 
        printf("(BEFORE RESIZE); value: %d\n", value);
    }

    if (!QUEUE_RESIZE(q, 20)) {                               // we can resize queue if we want, new capacity should be greater than previous capacity, return false mean error, true mean success 
        printf("QUEUE RESIZE FAIL\n");
        return 1;
    }

    printf("queue capacity: %zu\n", QUEUE_CAPACITY(q));
    printf("queue size: %zu\n", QUEUE_SIZE(q));
    printf("is queue full: %d\n", IS_QUEUE_FULL(q));
    printf("is queue empty: %d\n", IS_QUEUE_EMPTY(q));

    int i = 0;
    while (!IS_QUEUE_FULL(q)) {
        // ENQUEUE(q, i++);                                   // WRONG: cannot do any operations here, only pass the variable only
        ENQUEUE(q, i);
        i++;
    }

    printf("queue capacity: %zu\n", QUEUE_CAPACITY(q));
    printf("queue size: %zu\n", QUEUE_SIZE(q));
    printf("is queue full: %d\n", IS_QUEUE_FULL(q));
    printf("is queue empty: %d\n", IS_QUEUE_EMPTY(q));

    for (int i = 0; i < QUEUE_CAPACITY(q); i++) {
        int value = DEQUEUE(q, int);
        printf("(AFTER RESIZE): value: %d\n", value);
    }

    QUEUE_FREE(q);
}
