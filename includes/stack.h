#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "assert.h"

#ifndef STACK_H
#define STACK_H

typedef struct {
	int offset;
	int capacity;
	size_t el_size;
	size_t bufsize;
	void *buf;
} Stack;

// is success return pointer to stack, else (any memory allocation error occur) return NULL 
Stack *stack_init(size_t element_size, int capactiy);

// push given value to stack, if is success return true, else return false
bool stack_push(Stack *s, void *value);

// push value from the stack
void *stack_pop(Stack *s);

// return the top element of the stack (without poping) 
void *stack_top(Stack *s);

// is stack is grow return true, else (any memory allocation error occur) return false
bool stack_grow(Stack *s);

// return whether stack is full or not 
bool is_stack_full(Stack *s);

// return whether stack is empty or not 
bool is_stack_empty(Stack *s);

// return the stack size (currently fill element count)
size_t stack_size(Stack *s);

// return the stack capacity, if capacity is 0 mean unlimited
size_t stack_capacity(Stack *s);

// free the stack
void stack_free(Stack *s);


#define STACK_INIT(type, size) stack_init(sizeof(type), size)
#define STACK_PUSH(stack, value) stack_push(stack, (void*)&value)
#define STACK_POP(stack, type) (*(type*)stack_pop(stack))
#define STACK_TOP(stack, type) (*(type*)stack_top(stack))
#define IS_STACK_FULL(stack) is_stack_full(stack)
#define IS_STACK_EMPTY(stack) is_stack_empty(stack)
#define STACK_SIZE(stack) stack_size(stack)
#define STACK_CAPACITY(stack) stack_capacity(stack)
#define STACK_FREE(stack) stack_free(stack)


#endif
