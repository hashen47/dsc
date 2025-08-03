#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../includes/queue.h"

#define run_test(test_func_name) do { \
    test_func_name(); \
    printf("FILE: %s: (%s) is completed...\n", __FILE__, #test_func_name); \
} while (0)

typedef enum {
    INIT,
    DQ,
    ENQ,
    RESIZE,
} Opt;

void test_with_int() {
    typedef struct {
        Opt operation;
        size_t size;
        size_t capacity;
        bool is_full;
        bool is_empty;
        int enq_value;
        int dq_value;
    } Testcase;

    Testcase testcases[] = {
        {
            .operation=INIT,
            .capacity=10,
            .is_empty=true,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=1,
            .enq_value=1,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=2,
            .enq_value=2,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=3,
            .enq_value=3,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=4,
            .enq_value=4,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=5,
            .enq_value=5,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=6,
            .enq_value=6,
        },
        {
            .operation=DQ,
            .capacity=10,
            .size=5,
            .dq_value=1,
        },
        {
            .operation=DQ,
            .capacity=10,
            .size=4,
            .dq_value=2,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=5,
            .enq_value=7,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=6,
            .enq_value=8,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=7,
            .enq_value=9,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=8,
            .enq_value=10,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=9,
            .enq_value=11,
        },
        {
            .operation=ENQ,
            .is_full=true,
            .capacity=10,
            .size=10,
            .enq_value=12,
        },
        {
            .operation=RESIZE,
            .capacity=15,
            .size=10,
        },
        {
            .operation=ENQ,
            .capacity=15,
            .size=11,
            .enq_value=13,
        },
        {
            .operation=ENQ,
            .capacity=15,
            .size=12,
            .enq_value=14,
        },
        {
            .operation=ENQ,
            .capacity=15,
            .size=13,
            .enq_value=15,
        },
        {
            .operation=ENQ,
            .capacity=15,
            .size=14,
            .enq_value=16,
        },
        {
            .operation=ENQ,
            .capacity=15,
            .is_full=true,
            .size=15,
            .enq_value=17,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=14,
            .dq_value=3,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=13,
            .dq_value=4,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=12,
            .dq_value=5,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=11,
            .dq_value=6,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=10,
            .dq_value=7,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=9,
            .dq_value=8,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=8,
            .dq_value=9,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=7,
            .dq_value=10,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=6,
            .dq_value=11,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=5,
            .dq_value=12,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=4,
            .dq_value=13,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=3,
            .dq_value=14,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=2,
            .dq_value=15,
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=1,
            .dq_value=16,
        },
        {
            .operation=DQ,
            .capacity=15,
            .is_empty=true,
            .size=0,
            .dq_value=17,
        },
    };

    Queue* q;
    char line[100];

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];

        switch (tc.operation) {
            case INIT:
                q = QUEUE_INIT(int, tc.capacity);
                ASSERT(q != NULL, "(test_with_int): q is NULL");
                break;
            case ENQ:
                ENQUEUE(q, tc.enq_value);
                break;
            case DQ:
                int val = DEQUEUE(q, int);
                sprintf(line, "FAIL: dequeue is fail: expected: %d, real: %d\n", tc.dq_value, val);
                ASSERT(val == tc.dq_value, line);
                break;
            case RESIZE:
                bool is_ok = QUEUE_RESIZE(q, tc.capacity);
                ASSERT(is_ok, "(test_with_int): q resize is FAIL"); 
                break;
            default:
                ASSERT(false, "un-rechable switch case");
        }

        sprintf(line, "FAIL: queue is empty: expected: %d, real: %d\n", tc.is_empty, IS_QUEUE_EMPTY(q));
        ASSERT(tc.is_empty == IS_QUEUE_EMPTY(q), line);

        sprintf(line, "FAIL: queue is full: expected: %d, real: %d\n", tc.is_full, IS_QUEUE_FULL(q));
        ASSERT(tc.is_empty == IS_QUEUE_EMPTY(q), line);

        sprintf(line, "FAIL: queue is full: expected: %d, real: %d\n", tc.is_full, IS_QUEUE_FULL(q));
        ASSERT(tc.is_full == IS_QUEUE_FULL(q), line);

        size_t capacity = QUEUE_CAPACITY(q);
        sprintf(line, "FAIL: capacity: expected: %zu, real: %zu\n", tc.capacity, capacity);
        ASSERT(tc.capacity == capacity, line);

        size_t size = QUEUE_SIZE(q);
        sprintf(line, "FAIL: size: expected: %zu, real: %zu\n", tc.size, size);
        ASSERT(tc.size == size, line);
    }

    QUEUE_FREE(q);
}

void test_with_str() {
    typedef struct {
        Opt operation;
        size_t size;
        size_t capacity;
        bool is_full;
        bool is_empty;
        char *enq_value;
        char *dq_value;
    } Testcase;

    Testcase testcases[] = {
        {
            .operation=INIT,
            .capacity=10,
            .is_empty=true,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=1,
            .enq_value="one",
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=2,
            .enq_value="two",
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=3,
            .enq_value="three",
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=4,
            .enq_value="four",
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=5,
            .enq_value="five",
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=6,
            .enq_value="six",
        },
        {
            .operation=DQ,
            .capacity=10,
            .size=5,
            .dq_value="one",
        },
        {
            .operation=DQ,
            .capacity=10,
            .size=4,
            .dq_value="two",
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=5,
            .enq_value="seven",
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=6,
            .enq_value="eight",
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=7,
            .enq_value="nine",
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=8,
            .enq_value="ten",
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=9,
            .enq_value="eleven",
        },
        {
            .operation=ENQ,
            .is_full=true,
            .capacity=10,
            .size=10,
            .enq_value="twelve",
        },
        {
            .operation=RESIZE,
            .capacity=15,
            .size=10,
        },
        {
            .operation=ENQ,
            .capacity=15,
            .size=11,
            .enq_value="thirteen",
        },
        {
            .operation=ENQ,
            .capacity=15,
            .size=12,
            .enq_value="forteen",
        },
        {
            .operation=ENQ,
            .capacity=15,
            .size=13,
            .enq_value="fifteen",
        },
        {
            .operation=ENQ,
            .capacity=15,
            .size=14,
            .enq_value="sixteen",
        },
        {
            .operation=ENQ,
            .capacity=15,
            .is_full=true,
            .size=15,
            .enq_value="seventeen",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=14,
            .dq_value="three",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=13,
            .dq_value="four",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=12,
            .dq_value="five",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=11,
            .dq_value="six",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=10,
            .dq_value="seven",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=9,
            .dq_value="eight",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=8,
            .dq_value="nine",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=7,
            .dq_value="ten",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=6,
            .dq_value="eleven",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=5,
            .dq_value="twelve",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=4,
            .dq_value="thirteen",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=3,
            .dq_value="forteen",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=2,
            .dq_value="fifteen",
        },
        {
            .operation=DQ,
            .capacity=15,
            .size=1,
            .dq_value="sixteen",
        },
        {
            .operation=DQ,
            .capacity=15,
            .is_empty=true,
            .size=0,
            .dq_value="seventeen",
        },
    };

    Queue* q;
    char line[100];

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];

        switch (tc.operation) {
            case INIT:
                q = QUEUE_INIT(char*, tc.capacity);
                ASSERT(q != NULL, "(test_with_str): q is NULL");
                break;
            case ENQ:
                ENQUEUE(q, tc.enq_value);
                break;
            case DQ:
                char *val = DEQUEUE(q, char*);
                sprintf(line, "(test_with_str): dequeue is fail: expected: %s, real: %s\n", tc.dq_value, val);
                ASSERT(strcmp(val, tc.dq_value) == 0, line);
                break;
            case RESIZE:
                bool is_ok = QUEUE_RESIZE(q, tc.capacity);
                ASSERT(is_ok, "(test_with_str): q resize is fail"); 
                break;
            default:
                ASSERT(false, "un-rechable switch case");
        }

        sprintf(line, "(test_with_str): queue is empty: expected: %d, real: %d\n", tc.is_empty, IS_QUEUE_EMPTY(q));
        ASSERT(tc.is_empty == IS_QUEUE_EMPTY(q), line);

        sprintf(line, "(test_with_str): queue is full: expected: %d, real: %d\n", tc.is_full, IS_QUEUE_FULL(q));
        ASSERT(tc.is_full == IS_QUEUE_FULL(q), line);

        size_t capacity = QUEUE_CAPACITY(q);
        sprintf(line, "(test_with_str): capacity: expected: %zu, real: %zu\n", tc.capacity, capacity);
        ASSERT(tc.capacity == capacity, line);

        size_t size = QUEUE_SIZE(q);
        sprintf(line, "(test_with_str): size: expected: %zu, real: %zu\n", tc.size, size);
        ASSERT(tc.size == size, line);
    }

    QUEUE_FREE(q);
}

void test_with_people(void) {
    typedef struct {
        char *name;
        int age;
        double weight;
    } People;

    typedef struct {
        Opt operation;
        size_t size;
        size_t capacity;
        bool is_full;
        bool is_empty;
        People enq_value;
        People dq_value;
    } Testcase;

    Testcase testcases[] = {
        {
            .operation=INIT,
            .capacity=10,
            .is_empty=true,
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=1,
            .enq_value={.name="one", .age=1, .weight=1.1},
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=2,
            .enq_value={.name="two", .age=2, .weight=2.1},
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=3,
            .enq_value={.name="three", .age=3, .weight=3.1},
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=4,
            .enq_value={.name="four", .age=4, .weight=4.1},
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=5,
            .enq_value={.name="five", .age=5, .weight=5.1},
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=6,
            .enq_value={.name="six", .age=6, .weight=6.1},
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=7,
            .enq_value={.name="seven", .age=7, .weight=7.1},
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=8,
            .enq_value={.name="eight", .age=8, .weight=8.1},
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=9,
            .enq_value={.name="nine", .age=9, .weight=9.1},
        },
        {
            .operation=ENQ,
            .is_full=true,
            .capacity=10,
            .size=10,
            .enq_value={.name="ten", .age=10, .weight=10.1},
        },
        {
            .operation=DQ,
            .capacity=10,
            .size=9,
            .dq_value={.name="one", .age=1, .weight=1.1},
        },
        {
            .operation=DQ,
            .capacity=10,
            .size=8,
            .dq_value={.name="two", .age=2, .weight=2.1},
        },
        {
            .operation=ENQ,
            .capacity=10,
            .size=9,
            .enq_value={.name="eleven", .age=11, .weight=11.1},
        },
        {
            .operation=ENQ,
            .is_full=true,
            .capacity=10,
            .size=10,
            .enq_value={.name="twelve", .age=12, .weight=12.1},
        },
        {
            .operation=RESIZE,
            .capacity=20,
            .size=10,
        },
        {
            .operation=ENQ,
            .capacity=20,
            .size=11,
            .enq_value={.name="thirteen", .age=13, .weight=13.1},
        },
        {
            .operation=ENQ,
            .capacity=20,
            .size=12,
            .enq_value={.name="forteen", .age=14, .weight=14.1},
        },
        {
            .operation=ENQ,
            .capacity=20,
            .size=13,
            .enq_value={.name="fifteen", .age=15, .weight=15.1},
        },
        {
            .operation=ENQ,
            .capacity=20,
            .size=14,
            .enq_value={.name="sixteen", .age=16, .weight=16.1},
        },
        {
            .operation=ENQ,
            .capacity=20,
            .size=15,
            .enq_value={.name="seventeen", .age=17, .weight=17.1},
        },
        {
            .operation=ENQ,
            .capacity=20,
            .size=16,
            .enq_value={.name="eighteen", .age=18, .weight=18.1},
        },
        {
            .operation=ENQ,
            .capacity=20,
            .size=17,
            .enq_value={.name="nineteen", .age=19, .weight=19.1},
        },
        {
            .operation=ENQ,
            .capacity=20,
            .size=18,
            .enq_value={.name="twenty", .age=20, .weight=20.1},
        },
        {
            .operation=ENQ,
            .capacity=20,
            .size=19,
            .enq_value={.name="twenty one", .age=21, .weight=21.1},
        },
        {
            .operation=ENQ,
            .is_full=true,
            .capacity=20,
            .size=20,
            .enq_value={.name="twenty two", .age=22, .weight=22.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=19,
            .dq_value={.name="three", .age=3, .weight=3.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=18,
            .dq_value={.name="four", .age=4, .weight=4.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=17,
            .dq_value={.name="five", .age=5, .weight=5.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=16,
            .dq_value={.name="six", .age=6, .weight=6.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=15,
            .dq_value={.name="seven", .age=7, .weight=7.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=14,
            .dq_value={.name="eight", .age=8, .weight=8.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=13,
            .dq_value={.name="nine", .age=9, .weight=9.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=12,
            .dq_value={.name="ten", .age=10, .weight=10.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=11,
            .dq_value={.name="eleven", .age=11, .weight=11.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=10,
            .dq_value={.name="twelve", .age=12, .weight=12.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=9,
            .dq_value={.name="thirteen", .age=13, .weight=13.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=8,
            .dq_value={.name="forteen", .age=14, .weight=14.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=7,
            .dq_value={.name="fifteen", .age=15, .weight=15.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=6,
            .dq_value={.name="sixteen", .age=16, .weight=16.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=5,
            .dq_value={.name="seventeen", .age=17, .weight=17.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=4,
            .dq_value={.name="eighteen", .age=18, .weight=18.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=3,
            .dq_value={.name="nineteen", .age=19, .weight=19.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=2,
            .dq_value={.name="twenty", .age=20, .weight=20.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .size=1,
            .dq_value={.name="twenty one", .age=21, .weight=21.1},
        },
        {
            .operation=DQ,
            .capacity=20,
            .is_empty=true,
            .size=0,
            .dq_value={.name="twenty two", .age=22, .weight=22.1},
        },
    };

    Queue *q;
    Testcase tc;
    char line[100];

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        tc = testcases[i];

        switch (tc.operation) {
            case INIT:
                q = QUEUE_INIT(People, tc.capacity);
                ASSERT(q != NULL, "(test_with_people): q is NULL");
                break;
            case ENQ:
                ENQUEUE(q, tc.enq_value);
                break;
            case DQ:
                People val = DEQUEUE(q, People);

                sprintf(line, "(test_with_people): dequeue name is wrong: expected: %s, real: %s\n", tc.dq_value.name, val.name);
                ASSERT(strcmp(val.name, tc.dq_value.name) == 0, line);

                sprintf(line, "(test_with_people): dequeue age is wrong: expected: %d, real: %d\n", tc.dq_value.age, val.age);
                ASSERT(val.age == tc.dq_value.age, line);

                sprintf(line, "(test_with_people): dequeue weight is wrong: expected: %lf, real: %lf\n", tc.dq_value.weight, val.weight);
                ASSERT(val.weight == tc.dq_value.weight, line);

                break;
            case RESIZE:
                bool is_ok = QUEUE_RESIZE(q, tc.capacity);
                ASSERT(is_ok, "(test_with_people): q resize is fail"); 
                break;
            default:
                ASSERT(false, "un-rechable switch case");
        }
    }

    sprintf(line, "(test_with_people): queue is empty: expected: %d, real: %d\n", tc.is_empty, IS_QUEUE_EMPTY(q));
    ASSERT(tc.is_empty == IS_QUEUE_EMPTY(q), line);

    sprintf(line, "(test_with_people): queue is full: expected: %d, real: %d\n", tc.is_full, IS_QUEUE_FULL(q));
    ASSERT(tc.is_full == IS_QUEUE_FULL(q), line);

    size_t capacity = QUEUE_CAPACITY(q);
    sprintf(line, "(test_with_people): capacity: expected: %zu, real: %zu\n", tc.capacity, capacity);
    ASSERT(tc.capacity == capacity, line);

    size_t size = QUEUE_SIZE(q);
    sprintf(line, "(test_with_people): size: expected: %zu, real: %zu\n", tc.size, size);
    ASSERT(tc.size == size, line);

    QUEUE_FREE(q);
}

int main(void) {
    run_test(test_with_int);
    run_test(test_with_str);
    run_test(test_with_people);
}
