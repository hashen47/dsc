#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "assert.h"

#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array {
	void *buf;
	size_t offset;
	size_t bufsize;
	size_t el_size;
} Array;

// create a new array, if success return pointer to the array, else return NULL
Array *array_init(size_t element_size);

// grow the array->buf, if success return true, else return false
bool array_grow(Array *arr);

// append element to given array, if success return true, else return false
bool array_append(Array *arr, void *val);

// insert value to given index, if value insertion success return true, else (because of array_grow fail) return false
bool array_insert_at(Array *arr, int index, void *val);

// replace a given index's old value with new value
void array_replace_at(Array *arr, int index, void *val);

// return value according to given index
void *array_get_at(Array *arr, int index);

// return array size 
size_t array_size(Array *arr);

// remove element in given index 
void array_remove_at(Array *arr, int index);

// pop and return last element of the array
void *array_pop(Array *arr);

// clear the entire array, if success then return true, else return false
bool array_clear(Array *arr);

// free the array 
void array_free(Array *arr);

#define ARRAY_INIT(type) array_init(sizeof(type))
#define ARRAY_APPEND(arr, val) array_append((arr), &(val))
#define ARRAY_INSERT_AT(arr, index, val) array_insert_at((arr), (index), &(val))
#define ARRAY_REPLACE_AT(arr, index, val) array_replace_at((arr), (index), &(val))
#define ARRAY_GET_AT(arr, index, type) (*(type*)array_get_at((arr), (index)))
#define ARRAY_SIZE(arr) array_size((arr))
#define ARRAY_FREE(arr) array_free((arr))
#define ARRAY_REMOVE_AT(arr, index) array_remove_at((arr), (index))
#define ARRAY_POP(arr, type) (*(type*)array_pop((arr)))
#define ARRAY_CLEAR(arr) array_clear((arr))

#endif
