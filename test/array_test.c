#include "../includes/array.h"
#include <string.h>
#include <time.h>

#define run_test(test_func_name) do { \
    test_func_name(); \
    printf("FILE: %s: (%s) is completed...\n", __FILE__, #test_func_name); \
} while(0)

// not added INIT and FREE (because those two are mandatory anyway)
typedef enum {
	APPEND,
	INSERT,
	REPLACE,
	REMOVE,
	POP
} Opt_Type;

void test_with_int() {
	typedef struct {
        Opt_Type type;
        int index;
        int value;
        int result[100];
        int result_length;
	} Testcase;

    Testcase testcases[] = {
        {
            .type=APPEND,
            .value=1,
            .result={1,},
            .result_length=1,
        },
        {
            .type=APPEND,
            .value=2,
            .result={1, 2},
            .result_length=2,
        },
        {
            .type=APPEND,
            .value=3,
            .result={1, 2, 3},
            .result_length=3,
        },
        {
            .type=APPEND,
            .value=4,
            .result={1, 2, 3, 4},
            .result_length=4,
        },
        {
            .type=APPEND,
            .value=5,
            .result={1, 2, 3, 4, 5},
            .result_length=5,
        },
        {
            .type=APPEND,
            .value=6,
            .result={1, 2, 3, 4, 5, 6},
            .result_length=6,
        },
        {
            .type=APPEND,
            .value=7,
            .result={1, 2, 3, 4, 5, 6, 7},
            .result_length=7,
        },
        {
            .type=APPEND,
            .value=8,
            .result={1, 2, 3, 4, 5, 6, 7, 8},
            .result_length=8,
        },
        {
            .type=APPEND,
            .value=9,
            .result={1, 2, 3, 4, 5, 6, 7, 8, 9},
            .result_length=9,
        },
        {
            .type=APPEND,
            .value=10,
            .result={1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            .result_length=10,
        },
        {
            .type=APPEND,
            .value=11,
            .result={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            .result_length=11,
        },
        {
            .type=INSERT,
            .index=4,
            .value=12,
            .result={1, 2, 3, 4, 12, 5, 6, 7, 8, 9, 10, 11},
            .result_length=12,
        },
        {
            .type=INSERT,
            .index=7,
            .value=13,
            .result={1, 2, 3, 4, 12, 5, 6, 13, 7, 8, 9, 10, 11},
            .result_length=13,
        },
        {
            .type=POP,
            .result={1, 2, 3, 4, 12, 5, 6, 13, 7, 8, 9, 10},
            .result_length=12,
        },
        {
            .type=POP,
            .result={1, 2, 3, 4, 12, 5, 6, 13, 7, 8, 9},
            .result_length=11,
        },
        {
            .type=REMOVE,
            .index=2,
            .result={1, 2, 4, 12, 5, 6, 13, 7, 8, 9},
            .result_length=10,
        },
        {
            .type=REPLACE,
            .index=9,
            .value=14,
            .result={1, 2, 4, 12, 5, 6, 13, 7, 8, 14},
            .result_length=10,
        },
        {
            .type=REPLACE,
            .index=8,
            .value=15,
            .result={1, 2, 4, 12, 5, 6, 13, 7, 15, 14},
            .result_length=10,
        },
        {
            .type=APPEND,
            .value=16,
            .result={1, 2, 4, 12, 5, 6, 13, 7, 15, 14, 16},
            .result_length=11,
        },
        {
            .type=APPEND,
            .value=17,
            .result={1, 2, 4, 12, 5, 6, 13, 7, 15, 14, 16, 17},
            .result_length=12,
        },
    };

	Array* arr1 = ARRAY_INIT(int);

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];
        switch (tc.type) {
            case APPEND:
                ARRAY_APPEND(arr1, tc.value);
                break;
            case INSERT:
                ARRAY_INSERT_AT(arr1, tc.index, tc.value);
                break;
            case REPLACE:
                ARRAY_REPLACE_AT(arr1, tc.index, tc.value);
                break;
            case REMOVE:
                ARRAY_REMOVE_AT(arr1, tc.index);
                break;
            case POP:
                (void)ARRAY_POP(arr1, int);
                break;
            default:
                ASSERT(1, "(switch statement) cannot reach here");
        }

        for (int j = 0; j < tc.result_length; j++) {
            int arr_val = ARRAY_GET_AT(arr1, j, int);
            if (arr_val != tc.result[j]) {
                char line[200];
                sprintf(line, "(test_with_int): TEST FAIL, TEST(%d): expected: %d, real: %d\n", i+1, tc.result[j], arr_val);
                ARRAY_FREE(arr1);
                ASSERT(arr_val == tc.result[i], line);
            }
        }
    }

	ARRAY_FREE(arr1);
}

void test_with_str() {
    typedef struct {
        Opt_Type type;
        int index;
        char *value;
        char *result_arr[100]; // NOTE: if result set length exceed 100 update result array length
        int result_length;
    } Testcase;

    Testcase testcases[] = {
        {
            .type=APPEND,
            .value="one",
            .result_arr={"one"},
            .result_length=1,
        },
    };

    Array *arr1 = ARRAY_INIT(char*);

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];

        switch (tc.type) {
            case APPEND:
                ARRAY_APPEND(arr1, tc.value);
                break;
            case INSERT:
                ARRAY_INSERT_AT(arr1, tc.index, tc.value);
                break;
            case REPLACE:
                ARRAY_REPLACE_AT(arr1, tc.index, tc.value);
                break;
            case REMOVE:
                ARRAY_REMOVE_AT(arr1, tc.index);
                break;
            case POP:
                (void)ARRAY_POP(arr1, char*);
                break;
            default:
                ASSERT(1, "(switch statement) cannot reach here");
        }

        for (int j = 0; j < tc.result_length; j++) {
            char *value = ARRAY_GET_AT(arr1, j, char*);
            if (strcmp(value, tc.result_arr[j]) != 0) {
                char line[200];
                sprintf(line, "(test_with_str): TEST FAIL, TEST(%d): expected: %s, real: %s\n", i+1, tc.result_arr[j], value);
                ARRAY_FREE(arr1);
                ASSERT(strcmp(value, tc.result_arr[j]) == 0, line);
            }
        }
    }

    ARRAY_FREE(arr1);
}

void test_with_people_ptr() {
    typedef struct {
        char *name;
        int age;
        double weight;
    } People;

    typedef struct {
        Opt_Type type;
        int index;
        People *p_ptr;
        People *p_arr[100];
        int p_arr_length;
    } Testcase;

    People p1 = {.name="test1"  , .age=24, .weight=64.34};
    People p2 = {.name="test2"  , .age=22, .weight=54.34};
    People p3 = {.name="test3"  , .age=21, .weight=44.34};
    People p4 = {.name="test4"  , .age=11, .weight=22.34};
    People p5 = {.name="test5"  , .age=22, .weight=52.34};
    People p6 = {.name="test6"  , .age=99, .weight=10.29};

    Testcase testcases[] = {
        {
            .type=APPEND,
            .p_ptr=&p1,
            .p_arr={&p1},
            .p_arr_length=1,
        },
        {
            .type=APPEND,
            .p_ptr=&p2,
            .p_arr={&p1, &p2},
            .p_arr_length=2,
        },
        {
            .type=APPEND,
            .p_ptr=&p3,
            .p_arr={&p1, &p2, &p3},
            .p_arr_length=3,
        },
        {
            .type=INSERT,
            .index=1,
            .p_ptr=&p4,
            .p_arr={&p1, &p4, &p2, &p3},
            .p_arr_length=4,
        },
        {
            .type=POP,
            .p_arr={&p1, &p4, &p2},
            .p_arr_length=3,
        },
        {
            .type=REPLACE,
            .index=2,
            .p_ptr=&p5,
            .p_arr={&p1, &p4, &p5},
            .p_arr_length=3,
        },
        {
            .type=REMOVE,
            .index=0,
            .p_arr={&p4, &p5},
            .p_arr_length=2,
        },
        {
            .type=APPEND,
            .p_ptr=&p6,
            .p_arr={&p4, &p5, &p6},
            .p_arr_length=3,
        },
    };

    Array *arr1 = ARRAY_INIT(People*);

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];

        switch (tc.type) {
            case APPEND:
                ARRAY_APPEND(arr1, tc.p_ptr);
                break;
            case INSERT:
                ARRAY_INSERT_AT(arr1, tc.index, tc.p_ptr);
                break;
            case REPLACE:
                ARRAY_REPLACE_AT(arr1, tc.index, tc.p_ptr);
                break;
            case REMOVE:
                ARRAY_REMOVE_AT(arr1, tc.index);
                break;
            case POP:
                (void)ARRAY_POP(arr1, People*);
                break;
            default:
                ASSERT(1, "(switch statement) cannot reach here");
        }

        if (ARRAY_SIZE(arr1) != tc.p_arr_length) {
            char line[200];
            sprintf(line, "(test_with_people_ptr): TEST FAIL, expected (array length): %d, real (array length): %zu\n", tc.p_arr_length, ARRAY_SIZE(arr1));
            ARRAY_FREE(arr1);
            ASSERT(tc.p_arr_length == ARRAY_SIZE(arr1), line);
        }

        for (int j = 0; j < tc.p_arr_length; j++) {
            People *people = ARRAY_GET_AT(arr1, j, People*);
            People *result = tc.p_arr[j];

            if (people->age != result->age) {
                char line[200];
                sprintf(line, "(test_with_people_ptr): TEST FAIL, TEST(%d): expected (age): %d, real (age): %d\n", i+1, result->age, people->age);
                ARRAY_FREE(arr1);
                ASSERT(people->age == result->age, line);
            }

            if (people->weight != result->weight) {
                char line[200];
                sprintf(line, "(test_with_people_ptr): TEST FAIL, TEST(%d): expected (weight): %lf, real (weight): %lf\n", i+1, result->weight, people->weight);
                ARRAY_FREE(arr1);
                ASSERT(people->weight == result->weight, line);
            }

            if (strcmp(people->name, result->name) != 0) {
                char line[200];
                sprintf(line, "(test_with_people_ptr): TEST FAIL, TEST(%d): expected (name): %s, real (name): %s\n", i+1, result->name, people->name);
                ARRAY_FREE(arr1);
                ASSERT(strcmp(people->name, result->name) == 0, line);
            }
        } 
    }

    ARRAY_FREE(arr1);
}

void test_with_people() {
    typedef struct {
        char *name;
        int age;
        double weight;
    } People;

    typedef struct {
        Opt_Type type;
        int index;
        People people;
        People people_arr[100];
        int people_arr_length;
    } Testcase;

    Testcase testcases[] = {
        {
            .type=APPEND,
            .people={.name="test1", .age=24, .weight=64.34},
            .people_arr={
                {.name="test1", .age=24, .weight=64.34},
            },
            .people_arr_length=1,
        },
        {
            .type=APPEND,
            .people={.name="test2", .age=22, .weight=54.34},
            .people_arr={
                {.name="test1", .age=24, .weight=64.34},
                {.name="test2", .age=22, .weight=54.34},
            },
            .people_arr_length=2,
        },
        {
            .type=APPEND,
            .people={.name="test3", .age=21, .weight=44.34},
            .people_arr={
                {.name="test1", .age=24, .weight=64.34},
                {.name="test2", .age=22, .weight=54.34},
                {.name="test3", .age=21, .weight=44.34},
            },
            .people_arr_length=3,
        },
        {
            .type=INSERT,
            .index=1,
            .people={.name="test4", .age=11, .weight=22.34},
            .people_arr={
                {.name="test1", .age=24, .weight=64.34},
                {.name="test4", .age=11, .weight=22.34},
                {.name="test2", .age=22, .weight=54.34},
                {.name="test3", .age=21, .weight=44.34},
            },
            .people_arr_length=4,
        },
        {
            .type=POP,
            .people_arr={
                {.name="test1", .age=24, .weight=64.34},
                {.name="test4", .age=11, .weight=22.34},
                {.name="test2", .age=22, .weight=54.34},
            },
            .people_arr_length=3,
        },
        {
            .type=REPLACE,
            .index=2,
            .people={.name="test5", .age=22, .weight=52.34},
            .people_arr={
                {.name="test1", .age=24, .weight=64.34},
                {.name="test4", .age=11, .weight=22.34},
                {.name="test5", .age=22, .weight=52.34},
            },
            .people_arr_length=3,
        },
        {
            .type=REMOVE,
            .index=0,
            .people_arr={
                {.name="test4", .age=11, .weight=22.34},
                {.name="test5", .age=22, .weight=52.34},
            },
            .people_arr_length=2,
        },
    };

    Array *arr1 = ARRAY_INIT(People);

    for (int i = 0; i < sizeof(testcases)/sizeof(Testcase); i++) {
        Testcase tc = testcases[i];

        switch (tc.type) {
            case APPEND:
                ARRAY_APPEND(arr1, tc.people);
                break;
            case INSERT:
                ARRAY_INSERT_AT(arr1, tc.index, tc.people);
                break;
            case REPLACE:
                ARRAY_REPLACE_AT(arr1, tc.index, tc.people);
                break;
            case REMOVE:
                ARRAY_REMOVE_AT(arr1, tc.index);
                break;
            case POP:
                (void)ARRAY_POP(arr1, People);
                break;
            default:
                ASSERT(1, "(switch statement) cannot reach here");
        }

        if (ARRAY_SIZE(arr1) != tc.people_arr_length) {
            char line[200];
            sprintf(line, "(test_with_people): TEST FAIL, expected (array length): %d, real (array length): %zu\n", tc.people_arr_length, ARRAY_SIZE(arr1));
            ARRAY_FREE(arr1);
            ASSERT(tc.people_arr_length == ARRAY_SIZE(arr1), line);
        }

        for (int j = 0; j < tc.people_arr_length; j++) {
            People people = ARRAY_GET_AT(arr1, j, People);
            People result = tc.people_arr[j];

            if (people.age != result.age) {
                char line[200];
                sprintf(line, "(test_with_people): TEST FAIL, TEST(%d): expected (age): %d, real (age): %d\n", i+1, result.age, people.age);
                ARRAY_FREE(arr1);
                ASSERT(people.age == result.age, line);
            }

            if (people.weight != result.weight) {
                char line[200];
                sprintf(line, "(test_with_people): TEST FAIL, TEST(%d): expected (weight): %lf, real (weight): %lf\n", i+1, result.weight, people.weight);
                ARRAY_FREE(arr1);
                ASSERT(people.weight == result.weight, line);
            }

            if (strcmp(people.name, result.name) != 0) {
                char line[200];
                sprintf(line, "(test_with_people): TEST FAIL, TEST(%d): expected (name): %s, real (name): %s\n", i+1, result.name, people.name);
                ARRAY_FREE(arr1);
                ASSERT(strcmp(people.name, result.name) == 0, line);
            }
        } 
    }

    ARRAY_FREE(arr1);
}

void test_array_copy_slice_reverse_comp(void) {
    // TODO: may be in the future test with other types also for now this is enough 
    Array *arr1 = ARRAY_INIT(int);
    Array *arr2 = ARRAY_INIT(int);

    size_t size = 20;
    srand(time(NULL));
    for (size_t i = 0; i < size; i++) {
        int val = rand() % 100;
        ARRAY_APPEND(arr1, val);
        ARRAY_APPEND(arr2, val);
    }

    Array *arr3 = ARRAY_SLICE(arr1, 0, 10);
    Array *arr4 = ARRAY_SLICE(arr2, 0, 10);
    Array *arr5 = ARRAY_COPY(arr1);

    ASSERT(ARRAY_COMP(arr1, arr2), "arr1 and arr2 are not the same");
    ASSERT(ARRAY_COMP(arr3, arr4), "arr3 and arr4 are not the same");

    ARRAY_REVERSE(arr5);

    for (size_t i = 0; i < ARRAY_SIZE(arr1); i++) {
        ASSERT(ARRAY_GET_AT(arr1, i, int) == ARRAY_GET_AT(arr5, ARRAY_SIZE(arr1)-1-i, int), "arr1 element and arr5 (reverse of arr5) are not equal in reverse order");
    }

    ARRAY_FREE(arr1);
    ARRAY_FREE(arr2);
    ARRAY_FREE(arr3);
    ARRAY_FREE(arr4);
    ARRAY_FREE(arr5);
}

int main(void) {
    run_test(test_with_int);
    run_test(test_with_str);
    run_test(test_with_people);
    run_test(test_with_people_ptr);
    run_test(test_array_copy_slice_reverse_comp);
}
