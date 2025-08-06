#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../includes/stack.h"

#define run_test(test_func_name) do { \
    test_func_name(); \
    printf("FILE: %s: (%s) is completed...\n", __FILE__, #test_func_name); \
} while (0)

typedef enum {
    INIT,
    PUSH,
    POP,
    TOP,
} Opt;

void test_with_int_limited_size(void) {
    typedef struct {
        Opt operation;
        size_t size; 
        int push_value;
        size_t capacity;
        int pop_value;
        int top_value;
        bool is_empty;
        bool is_full;
    } Testcase;

    Testcase testcases[] = {
        {
            .capacity=6,
            .operation=INIT,
            .is_empty=true,
            .size=0,
        },
        {
            .capacity=6,
            .operation=PUSH,
            .size=1,
            .push_value=1,
        },
        {
            .capacity=6,
            .operation=PUSH,
            .size=2,
            .push_value=2,
        },
        {
            .capacity=6,
            .operation=TOP,
            .top_value=2,
            .size=2,
        },
        {
            .capacity=6,
            .operation=PUSH,
            .size=3,
            .push_value=3,
        },
        {
            .capacity=6,
            .operation=PUSH,
            .size=4,
            .push_value=4,
        },
        {
            .capacity=6,
            .operation=PUSH,
            .size=5,
            .push_value=5,
        },
        {
            .capacity=6,
            .operation=PUSH,
            .size=6,
            .push_value=6,
            .is_full=true,
        },
        {
            .capacity=6,
            .operation=POP,
            .size=5,
            .pop_value=6,
        },
        {
            .capacity=6,
            .operation=POP,
            .size=4,
            .pop_value=5,
        },
        {
            .capacity=6,
            .operation=POP,
            .size=3,
            .pop_value=4,
        },
        {
            .capacity=6,
            .operation=POP,
            .size=2,
            .pop_value=3,
        },
        {
            .capacity=6,
            .operation=POP,
            .size=1,
            .pop_value=2,
        },
        {
            .capacity=6,
            .operation=POP,
            .size=0,
            .pop_value=1,
            .is_empty=true,
        },
    };

    Stack *stack;

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];

        char line[100];
        switch (tc.operation) {
            case INIT:
                stack = STACK_INIT(int, tc.capacity);
                break;
            case PUSH:
                STACK_PUSH(stack, tc.push_value);
                break;
            case POP:
                int pop_value = STACK_POP(stack, int);
                sprintf(line, "FAIL: pop value is different: expected: %d, real: %d\n", tc.pop_value, pop_value);
                ASSERT(tc.pop_value == pop_value, line);
                break;
            case TOP:
                int top_value = STACK_TOP(stack, int);
                sprintf(line, "FAIL: top value is different: expected: %d, real: %d\n", tc.top_value, top_value);
                ASSERT(tc.top_value == top_value, line);
                break;
            default:
                ASSERT(false, "unrechable switch case");
        }

        sprintf(line, "FAIL: stack is empty: expected: %d, real: %d\n", tc.is_empty, IS_STACK_EMPTY(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_full == IS_STACK_FULL(stack), line);

        size_t capacity = STACK_CAPACITY(stack); 
        sprintf(line, "FAIL: capacity: expected: %zu, real: %zu\n", tc.capacity, capacity);
        ASSERT(tc.capacity == capacity, line);

        size_t size = STACK_SIZE(stack);
        sprintf(line, "FAIL: size: expected: %zu, real: %zu\n", tc.size, size);
        ASSERT(tc.size == size, line);
    }

    STACK_FREE(stack);
}

void test_with_int_unlimited_size(void) {
    typedef struct {
        Opt operation;
        size_t size; 
        int push_value;
        size_t capacity;
        int pop_value;
        int top_value;
        bool is_empty;
        bool is_full;
    } Testcase;

    Testcase testcases[] = {
        {
            .operation=INIT,
            .is_empty=true,
            .size=0,
        },
        {
            .operation=PUSH,
            .size=1,
            .push_value=1,
        },
        {
            .operation=PUSH,
            .size=2,
            .push_value=2,
        },
        {
            .operation=TOP,
            .top_value=2,
            .size=2,
        },
        {
            .operation=PUSH,
            .size=3,
            .push_value=3,
        },
        {
            .operation=PUSH,
            .size=4,
            .push_value=4,
        },
        {
            .operation=PUSH,
            .size=5,
            .push_value=5,
        },
        {
            .operation=PUSH,
            .size=6,
            .push_value=6,
        },
        {
            .operation=PUSH,
            .size=7,
            .push_value=7,
        },
        {
            .operation=POP,
            .size=6,
            .pop_value=7,
        },
        {
            .operation=PUSH,
            .size=7,
            .push_value=100,
        },
        {
            .operation=PUSH,
            .size=8,
            .push_value=200,
        },
        {
            .operation=POP,
            .size=7,
            .pop_value=200,
        },
        {
            .operation=POP,
            .size=6,
            .pop_value=100,
        },
        {
            .operation=POP,
            .size=5,
            .pop_value=6,
        },
        {
            .operation=POP,
            .size=4,
            .pop_value=5,
        },
        {
            .operation=POP,
            .size=3,
            .pop_value=4,
        },
        {
            .operation=POP,
            .size=2,
            .pop_value=3,
        },
        {
            .operation=POP,
            .size=1,
            .pop_value=2,
        },
        {
            .operation=POP,
            .is_empty=true,
            .size=0,
            .pop_value=1,
        },
    };

    Stack *stack;

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];

        char line[100];
        switch (tc.operation) {
            case INIT:
                stack = STACK_INIT(int, tc.capacity);
                break;
            case PUSH:
                STACK_PUSH(stack, tc.push_value);
                break;
            case POP:
                int pop_value = STACK_POP(stack, int);
                sprintf(line, "FAIL: pop value is different: expected: %d, real: %d\n", tc.pop_value, pop_value);
                ASSERT(tc.pop_value == pop_value, line);
                break;
            case TOP:
                int top_value = STACK_TOP(stack, int);
                sprintf(line, "FAIL: top value is different: expected: %d, real: %d\n", tc.top_value, top_value);
                ASSERT(tc.top_value == top_value, line);
                break;
            default:
                ASSERT(false, "unrechable switch case");
        }

        sprintf(line, "FAIL: stack is empty: expected: %d, real: %d\n", tc.is_empty, IS_STACK_EMPTY(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_full == IS_STACK_FULL(stack), line);

        size_t capacity = STACK_CAPACITY(stack);
        sprintf(line, "FAIL: capacity: expected: %zu, real: %zu\n", tc.capacity, capacity);
        ASSERT(tc.capacity == capacity, line);

        size_t size = STACK_SIZE(stack);
        sprintf(line, "FAIL: size: expected: %zu, real: %zu\n", tc.size, size);
        ASSERT(tc.size == size, line);
    }

    STACK_FREE(stack);
}

void test_with_str_limited_size(void) {
    typedef struct {
        Opt operation;
        size_t size; 
        size_t capacity;
        char *push_value;
        char *pop_value;
        char *top_value;
        bool is_empty;
        bool is_full;
    } Testcase;

    Testcase testcases[] = {
        {
            .operation=INIT,
            .capacity=6,
            .is_empty=true,
        },
        {
            .operation=PUSH,
            .capacity=6,
            .push_value="one",
            .size=1,
        },
        {
            .operation=PUSH,
            .capacity=6,
            .push_value="two",
            .size=2,
        },
        {
            .operation=PUSH,
            .capacity=6,
            .push_value="three",
            .size=3,
        },
        {
            .operation=PUSH,
            .capacity=6,
            .push_value="four",
            .size=4,
        },
        {
            .operation=PUSH,
            .capacity=6,
            .push_value="five",
            .size=5,
        },
        {
            .operation=PUSH,
            .capacity=6,
            .push_value="six",
            .is_full=true,
            .size=6,
        },
        {
            .operation=TOP,
            .capacity=6,
            .top_value="six",
            .is_full=true,
            .size=6,
        },
        {
            .operation=POP,
            .capacity=6,
            .pop_value="six",
            .size=5,
        },
        {
            .operation=POP,
            .capacity=6,
            .pop_value="five",
            .size=4,
        },
        {
            .operation=PUSH,
            .capacity=6,
            .push_value="seven",
            .size=5,
        },
        {
            .operation=TOP,
            .capacity=6,
            .top_value="seven",
            .size=5,
        },
        {
            .operation=POP,
            .capacity=6,
            .pop_value="seven",
            .size=4,
        },
        {
            .operation=POP,
            .capacity=6,
            .pop_value="four",
            .size=3,
        },
        {
            .operation=POP,
            .capacity=6,
            .pop_value="three",
            .size=2,
        },
        {
            .operation=POP,
            .capacity=6,
            .pop_value="two",
            .size=1,
        },
        {
            .operation=POP,
            .capacity=6,
            .pop_value="one",
            .is_empty=true,
            .size=0,
        },
    };

    Stack *stack;

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];

        char line[100];
        switch (tc.operation) {
            case INIT:
                stack = STACK_INIT(char*, tc.capacity);
                break;
            case PUSH:
                STACK_PUSH(stack, tc.push_value);
                break;
            case POP:
                char *pop_value = STACK_POP(stack, char*);
                sprintf(line, "FAIL: pop value is different: expected: %s, real: %s\n", tc.pop_value, pop_value);
                ASSERT(strcmp(tc.pop_value, pop_value) == 0, line);
                break;
            case TOP:
                char *top_value = STACK_TOP(stack, char*);
                sprintf(line, "FAIL: top value is different: expected: %s, real: %s\n", tc.top_value, top_value);
                ASSERT(strcmp(tc.top_value, top_value) == 0, line);
                break;
            default:
                ASSERT(false, "unrechable switch case");
        }

        sprintf(line, "FAIL: stack is empty: expected: %d, real: %d\n", tc.is_empty, IS_STACK_EMPTY(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_full == IS_STACK_FULL(stack), line);

        size_t capacity = STACK_CAPACITY(stack);
        sprintf(line, "FAIL: capacity: expected: %zu, real: %zu\n", tc.capacity, capacity);
        ASSERT(tc.capacity == capacity, line);

        size_t size = STACK_SIZE(stack);
        sprintf(line, "FAIL: size: expected: %zu, real: %zu\n", tc.size, size);
        ASSERT(tc.size == size, line);
    }

    STACK_FREE(stack);
}

void test_with_str_unlimited_size(void) {
    typedef struct {
        Opt operation;
        size_t size; 
        size_t capacity;
        char *push_value;
        char *pop_value;
        char *top_value;
        bool is_empty;
        bool is_full;
    } Testcase;

    Testcase testcases[] = {
        {
            .operation=INIT,
            .is_empty=true,
        },
        {
            .operation=PUSH,
            .push_value="one",
            .size=1,
        },
        {
            .operation=PUSH,
            .push_value="two",
            .size=2,
        },
        {
            .operation=PUSH,
            .push_value="three",
            .size=3,
        },
        {
            .operation=PUSH,
            .push_value="four",
            .size=4,
        },
        {
            .operation=PUSH,
            .push_value="five",
            .size=5,
        },
        {
            .operation=PUSH,
            .push_value="six",
            .size=6,
        },
        {
            .operation=TOP,
            .top_value="six",
            .size=6,
        },
        {
            .operation=POP,
            .pop_value="six",
            .size=5,
        },
        {
            .operation=POP,
            .pop_value="five",
            .size=4,
        },
        {
            .operation=PUSH,
            .push_value="seven",
            .size=5,
        },
        {
            .operation=TOP,
            .top_value="seven",
            .size=5,
        },
        {
            .operation=POP,
            .pop_value="seven",
            .size=4,
        },
        {
            .operation=POP,
            .pop_value="four",
            .size=3,
        },
        {
            .operation=POP,
            .pop_value="three",
            .size=2,
        },
        {
            .operation=POP,
            .pop_value="two",
            .size=1,
        },
        {
            .operation=POP,
            .pop_value="one",
            .is_empty=true,
            .size=0,
        },
    };

    Stack *stack;

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];

        char line[100];
        switch (tc.operation) {
            case INIT:
                stack = STACK_INIT(char*, tc.capacity);
                break;
            case PUSH:
                STACK_PUSH(stack, tc.push_value);
                break;
            case POP:
                char *pop_value = STACK_POP(stack, char*);
                sprintf(line, "FAIL: pop value is different: expected: %s, real: %s\n", tc.pop_value, pop_value);
                ASSERT(strcmp(tc.pop_value, pop_value) == 0, line);
                break;
            case TOP:
                char *top_value = STACK_TOP(stack, char*);
                sprintf(line, "FAIL: top value is different: expected: %s, real: %s\n", tc.top_value, top_value);
                ASSERT(strcmp(tc.top_value, top_value) == 0, line);
                break;
            default:
                ASSERT(false, "unrechable switch case");
        }

        sprintf(line, "FAIL: stack is empty: expected: %d, real: %d\n", tc.is_empty, IS_STACK_EMPTY(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_full == IS_STACK_FULL(stack), line);

        size_t capacity = STACK_CAPACITY(stack);
        sprintf(line, "FAIL: capacity: expected: %zu, real: %zu\n", tc.capacity, capacity);
        ASSERT(tc.capacity == capacity, line);

        size_t size = STACK_SIZE(stack);
        sprintf(line, "FAIL: size: expected: %zu, real: %zu\n", tc.size, size);
        ASSERT(tc.size == size, line);
    }

    STACK_FREE(stack);
}

void test_with_people_limited_size(void) {
    typedef struct {
        char *name;
        int age;
        double weight;
    } People;

    typedef struct {
        Opt operation;
        People push_value;
        People pop_value;
        People top_value;
        size_t capacity;
        size_t size;
        bool is_empty;
        bool is_full;
    } Testcase;

    Testcase testcases[] = {
        {
            .operation=INIT,
            .capacity=10,
            .is_empty=true,
        },
        {
            .operation=PUSH,
            .capacity=10,
            .size=1,
            .push_value={.name="user1", .age=24, .weight=61.30},
        },
        {
            .operation=PUSH,
            .capacity=10,
            .size=2,
            .push_value={.name="user2", .age=22, .weight=51.30},
        },
        {
            .operation=PUSH,
            .capacity=10,
            .size=3,
            .push_value={.name="user3", .age=24, .weight=58.30},
        },
        {
            .operation=TOP,
            .capacity=10,
            .size=3,
            .top_value={.name="user3", .age=24, .weight=58.30},
        },
        {
            .operation=PUSH,
            .capacity=10,
            .size=4,
            .push_value={.name="user4", .age=24, .weight=48.28},
        },
        {
            .operation=PUSH,
            .capacity=10,
            .size=5,
            .push_value={.name="user5", .age=24, .weight=48.99},
        },
        {
            .operation=PUSH,
            .capacity=10,
            .size=6,
            .push_value={.name="user6", .age=24, .weight=33.21},
        },
        {
            .operation=TOP,
            .capacity=10,
            .size=6,
            .top_value={.name="user6", .age=24, .weight=33.21},
        },
        {
            .operation=PUSH,
            .capacity=10,
            .size=7,
            .push_value={.name="user7", .age=24, .weight=100.55},
        },
        {
            .operation=PUSH,
            .capacity=10,
            .size=8,
            .push_value={.name="user8", .age=29, .weight=99.55},
        },
        {
            .operation=PUSH,
            .capacity=10,
            .size=9,
            .push_value={.name="user9", .age=30, .weight=85.95},
        },
        {
            .operation=PUSH,
            .capacity=10,
            .size=10,
            .is_full=true,
            .push_value={.name="user10", .age=20, .weight=65.01},
        },
        {
            .operation=POP,
            .capacity=10,
            .size=9,
            .pop_value={.name="user10", .age=20, .weight=65.01},
        },
        {
            .operation=POP,
            .capacity=10,
            .size=8,
            .pop_value={.name="user9", .age=30, .weight=85.95},
        },
        {
            .operation=POP,
            .capacity=10,
            .size=7,
            .pop_value={.name="user8", .age=29, .weight=99.55},
        },
        {
            .operation=POP,
            .capacity=10,
            .size=6,
            .pop_value={.name="user7", .age=24, .weight=100.55},
        },
        {
            .operation=TOP,
            .capacity=10,
            .size=6,
            .top_value={.name="user6", .age=24, .weight=33.21},
        },
        {
            .operation=POP,
            .capacity=10,
            .size=5,
            .pop_value={.name="user6", .age=24, .weight=33.21},
        },
        {
            .operation=POP,
            .capacity=10,
            .size=4,
            .pop_value={.name="user5", .age=24, .weight=48.99},
        },
        {
            .operation=POP,
            .capacity=10,
            .size=3,
            .pop_value={.name="user4", .age=24, .weight=48.28},
        },
        {
            .operation=POP,
            .capacity=10,
            .size=2,
            .pop_value={.name="user3", .age=24, .weight=58.30},
        },
        {
            .operation=POP,
            .capacity=10,
            .size=1,
            .pop_value={.name="user2", .age=22, .weight=51.30},
        },
        {
            .operation=POP,
            .capacity=10,
            .size=0,
            .is_empty=true,
            .pop_value={.name="user1", .age=24, .weight=61.30},
        },
    };

    Stack *stack;

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];

        char line[100];
        switch (tc.operation) {
            case INIT:
                stack = STACK_INIT(People, tc.capacity);
                break;
            case PUSH:
                STACK_PUSH(stack, tc.push_value);
                break;
            case POP:
                People pop_value = STACK_POP(stack, People);

                sprintf(line, "FAIL: pop value is different (name): expected: %s, real: %s\n", tc.pop_value.name, pop_value.name);
                ASSERT(strcmp(tc.pop_value.name, pop_value.name) == 0, line);

                sprintf(line, "FAIL: pop value is different (age): expected: %d, real: %d\n", tc.pop_value.age, pop_value.age);
                ASSERT(tc.pop_value.age == pop_value.age, line);

                sprintf(line, "FAIL: pop value is different (weight): expected: %lf, real: %lf\n", tc.pop_value.weight, pop_value.weight);
                ASSERT(tc.pop_value.weight == pop_value.weight, line);
                break;
            case TOP:
                People top_value = STACK_TOP(stack, People);

                sprintf(line, "FAIL: top value is different (name): expected: %s, real: %s\n", tc.top_value.name, top_value.name);
                ASSERT(strcmp(tc.top_value.name, top_value.name) == 0, line);

                sprintf(line, "FAIL: top value is different (age): expected: %d, real: %d\n", tc.top_value.age, top_value.age);
                ASSERT(tc.top_value.age == top_value.age, line);

                sprintf(line, "FAIL: top value is different (weight): expected: %lf, real: %lf\n", tc.top_value.weight, top_value.weight);
                ASSERT(tc.top_value.weight == top_value.weight, line);
                break;
            default:
                ASSERT(false, "unrechable switch case");
        }

        sprintf(line, "FAIL: stack is empty: expected: %d, real: %d\n", tc.is_empty, IS_STACK_EMPTY(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_full == IS_STACK_FULL(stack), line);

        size_t capacity = STACK_CAPACITY(stack);
        sprintf(line, "FAIL: capacity: expected: %zu, real: %zu\n", tc.capacity, capacity);
        ASSERT(tc.capacity == capacity, line);

        size_t size = STACK_SIZE(stack);
        sprintf(line, "FAIL: size: expected: %zu, real: %zu\n", tc.size, size);
        ASSERT(tc.size == size, line);
    }

    STACK_FREE(stack);
}

void test_with_people_unlimited_size(void) {
    typedef struct {
        char *name;
        int age;
        double weight;
    } People;

    typedef struct {
        Opt operation;
        People push_value;
        People pop_value;
        People top_value;
        size_t capacity;
        size_t size;
        bool is_empty;
        bool is_full;
    } Testcase;

    Testcase testcases[] = {
        {
            .operation=INIT,
            .is_empty=true,
        },
        {
            .operation=PUSH,
            .size=1,
            .push_value={.name="user1", .age=24, .weight=61.30},
        },
        {
            .operation=PUSH,
            .size=2,
            .push_value={.name="user2", .age=22, .weight=51.30},
        },
        {
            .operation=PUSH,
            .size=3,
            .push_value={.name="user3", .age=24, .weight=58.30},
        },
        {
            .operation=TOP,
            .size=3,
            .top_value={.name="user3", .age=24, .weight=58.30},
        },
        {
            .operation=PUSH,
            .size=4,
            .push_value={.name="user4", .age=24, .weight=48.28},
        },
        {
            .operation=PUSH,
            .size=5,
            .push_value={.name="user5", .age=24, .weight=48.99},
        },
        {
            .operation=PUSH,
            .size=6,
            .push_value={.name="user6", .age=24, .weight=33.21},
        },
        {
            .operation=TOP,
            .size=6,
            .top_value={.name="user6", .age=24, .weight=33.21},
        },
        {
            .operation=PUSH,
            .size=7,
            .push_value={.name="user7", .age=24, .weight=100.55},
        },
        {
            .operation=PUSH,
            .size=8,
            .push_value={.name="user8", .age=29, .weight=99.55},
        },
        {
            .operation=PUSH,
            .size=9,
            .push_value={.name="user9", .age=30, .weight=85.95},
        },
        {
            .operation=PUSH,
            .size=10,
            .push_value={.name="user10", .age=20, .weight=65.01},
        },
        {
            .operation=POP,
            .size=9,
            .pop_value={.name="user10", .age=20, .weight=65.01},
        },
        {
            .operation=POP,
            .size=8,
            .pop_value={.name="user9", .age=30, .weight=85.95},
        },
        {
            .operation=POP,
            .size=7,
            .pop_value={.name="user8", .age=29, .weight=99.55},
        },
        {
            .operation=POP,
            .size=6,
            .pop_value={.name="user7", .age=24, .weight=100.55},
        },
        {
            .operation=TOP,
            .size=6,
            .top_value={.name="user6", .age=24, .weight=33.21},
        },
        {
            .operation=POP,
            .size=5,
            .pop_value={.name="user6", .age=24, .weight=33.21},
        },
        {
            .operation=POP,
            .size=4,
            .pop_value={.name="user5", .age=24, .weight=48.99},
        },
        {
            .operation=POP,
            .size=3,
            .pop_value={.name="user4", .age=24, .weight=48.28},
        },
        {
            .operation=POP,
            .size=2,
            .pop_value={.name="user3", .age=24, .weight=58.30},
        },
        {
            .operation=POP,
            .size=1,
            .pop_value={.name="user2", .age=22, .weight=51.30},
        },
        {
            .operation=POP,
            .size=0,
            .is_empty=true,
            .pop_value={.name="user1", .age=24, .weight=61.30},
        },
    };

    Stack *stack;

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];

        char line[100];
        switch (tc.operation) {
            case INIT:
                stack = STACK_INIT(People, tc.capacity);
                break;
            case PUSH:
                STACK_PUSH(stack, tc.push_value);
                break;
            case POP:
                People pop_value = STACK_POP(stack, People);

                sprintf(line, "FAIL: pop value is different (name): expected: %s, real: %s\n", tc.pop_value.name, pop_value.name);
                ASSERT(strcmp(tc.pop_value.name, pop_value.name) == 0, line);

                sprintf(line, "FAIL: pop value is different (age): expected: %d, real: %d\n", tc.pop_value.age, pop_value.age);
                ASSERT(tc.pop_value.age == pop_value.age, line);

                sprintf(line, "FAIL: pop value is different (weight): expected: %lf, real: %lf\n", tc.pop_value.weight, pop_value.weight);
                ASSERT(tc.pop_value.weight == pop_value.weight, line);
                break;
            case TOP:
                People top_value = STACK_TOP(stack, People);

                sprintf(line, "FAIL: top value is different (name): expected: %s, real: %s\n", tc.top_value.name, top_value.name);
                ASSERT(strcmp(tc.top_value.name, top_value.name) == 0, line);

                sprintf(line, "FAIL: top value is different (age): expected: %d, real: %d\n", tc.top_value.age, top_value.age);
                ASSERT(tc.top_value.age == top_value.age, line);

                sprintf(line, "FAIL: top value is different (weight): expected: %lf, real: %lf\n", tc.top_value.weight, top_value.weight);
                ASSERT(tc.top_value.weight == top_value.weight, line);
                break;
            default:
                ASSERT(false, "unrechable switch case");
        }

        sprintf(line, "FAIL: stack is empty: expected: %d, real: %d\n", tc.is_empty, IS_STACK_EMPTY(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_empty == IS_STACK_EMPTY(stack), line);

        sprintf(line, "FAIL: stack is full: expected: %d, real: %d\n", tc.is_full, IS_STACK_FULL(stack));
        ASSERT(tc.is_full == IS_STACK_FULL(stack), line);

        size_t capacity = STACK_CAPACITY(stack);
        sprintf(line, "FAIL: capacity: expected: %zu, real: %zu\n", tc.capacity, capacity);
        ASSERT(tc.capacity == capacity, line);

        size_t size = STACK_SIZE(stack);
        sprintf(line, "FAIL: size: expected: %zu, real: %zu\n", tc.size, size);
        ASSERT(tc.size == size, line);
    }

    STACK_FREE(stack);
}

int main(void) {
    run_test(test_with_int_limited_size);
    run_test(test_with_int_unlimited_size);
    run_test(test_with_str_limited_size);
    run_test(test_with_str_unlimited_size);
    run_test(test_with_people_limited_size);
    run_test(test_with_people_unlimited_size);
}
