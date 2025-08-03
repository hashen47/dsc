#include <stdio.h>
#include <stdbool.h>
#include "../includes/assert.h"

int main(void) {
    int id = 0;

    switch (id) {
        case 0:
            ASSERT(false, "this is simple assertion example");
            break;
        case 1:
            int a = 0;
            int b = 1;
            ASSERT(a == b, "a is not equal to b");
            break;
        case 2:
            int age = -11;
            ASSERT(age > 0, "age is zero or negative");  // if given statement is false, then ASSERTION occur
            break;
        default:
            ASSERT(false, "unrechable switch case");
            break;
    }

}
