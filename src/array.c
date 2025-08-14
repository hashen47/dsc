#include <string.h>
#include "../includes/array.h"

Array *array_init(size_t element_size) {
	ASSERT(element_size > 0, "(array_init): element size cannot be zero");

	Array *arr = malloc(sizeof(Array));
	arr->offset = 0;
	arr->bufsize = 2;
	arr->el_size = element_size;

	void *buf = malloc(sizeof(arr->el_size) * arr->bufsize);
	if (buf == NULL) return NULL;

	arr->buf = buf;
	return arr;
}

bool array_grow(Array *arr) {
	ASSERT(arr != NULL, "(array_grow): array pointer is NULL");
	if (arr->offset >= arr->bufsize-1) {
		arr->bufsize *= 2;
		void *new_buf = realloc(arr->buf, arr->bufsize * arr->el_size);
		if (new_buf == NULL) {
			return false;
		}
		arr->buf = new_buf;
	}
	return true;
}

bool array_append(Array *arr, void *val) {
	ASSERT(arr != NULL, "(array_append): array pointer is NULL");
	if (! array_grow(arr)) return false;
	int start_index = (arr->offset++ * arr->el_size);
	for (int i = 0; i < arr->el_size; i++) {
		*((unsigned char*)arr->buf + (start_index+i)) = *((unsigned char*)val + i);
	}
	return true;
}

Array *array_slice(Array *src_arr, int start_i, int end_i) {
	ASSERT(src_arr != NULL, "(array_slice): src array pointer is NULL");
	ASSERT(start_i >= 0, "(array_slice): start_i cannot be negative");
	ASSERT(end_i <= src_arr->offset, "(array_slice): end_i cannot exceed the src array size");

    Array *dst_arr = malloc(sizeof(Array));
    if (dst_arr == NULL) return NULL;

    dst_arr->el_size = src_arr->el_size;
    dst_arr->offset = end_i - start_i;
    dst_arr->bufsize = src_arr->bufsize;

    dst_arr->buf = malloc(sizeof(dst_arr->el_size) * dst_arr->bufsize);
    if (dst_arr->buf == NULL) return NULL;

    int buf_len = (end_i - start_i) * dst_arr->el_size;
    for (size_t i = 0; i < buf_len; i++) {
        *((unsigned char*)dst_arr->buf + i) = *((unsigned char*)src_arr->buf + start_i + i);
    }

    return dst_arr;
}

Array *array_copy(Array *src_arr) {
	ASSERT(src_arr != NULL, "(array_copy): src array pointer is NULL");
    return array_slice(src_arr, 0, src_arr->offset);
}

bool array_comp(Array *arr1, Array *arr2) {
	ASSERT(arr1 != NULL, "(array_comp): arr1 pointer is NULL");
	ASSERT(arr2 != NULL, "(array_comp): arr2 pointer is NULL");
	ASSERT(arr1->buf != NULL, "(array_comp): arr1->buf pointer is NULL");
	ASSERT(arr2->buf != NULL, "(array_comp): arr2->buf pointer is NULL");

    if (arr1->offset != arr2->offset) return false;

    for (size_t i = 0; i < arr1->offset * arr1->el_size; i++) {
        if (*((unsigned char*)arr1->buf + i) != *((unsigned char*)arr2->buf + i)) return false;
    }

    return true;
}

void array_reverse(Array *arr) {
	ASSERT(arr != NULL, "(array_reverse): arr pointer is NULL");
	ASSERT(arr->buf != NULL, "(array_reverse): arr->buf pointer is NULL");

    for (size_t i = 0; i < arr->offset; i++) {
        if (i >= arr->offset-1-i) break;
        for (size_t j = 0; j < arr->el_size; j++) {
            unsigned char temp = *((unsigned char*)arr->buf + (i*arr->el_size) + j);
            *((unsigned char*)arr->buf + (i*arr->el_size) + j) = *((unsigned char*)arr->buf + ((arr->offset-1-i) * arr->el_size) + j);
            *((unsigned char*)arr->buf + ((arr->offset-1-i) * arr->el_size) + j) = temp;
        }
    }
}

bool array_insert_at(Array *arr, int index, void *val) {
	ASSERT(arr != NULL, "(array_insert_at): array pointer is NULL");
	ASSERT(index >= 0, "(array_insert_at): index cannot be negative");
	ASSERT(index < arr->offset, "(array_insert_at): index out of bound");

	void *pointer_to_last_element = array_get_at(arr, array_size(arr)-1);
	if (! array_append(arr, pointer_to_last_element)) return false;

	int byte_count_to_one_before_last_element = (arr->offset-1) * arr->el_size;
	for (int i = byte_count_to_one_before_last_element; i >= (index+1)*arr->el_size; i--) {
		*((unsigned char*)arr->buf + i) = *((unsigned char*)arr->buf + (i - arr->el_size));
	}

	for (int i = 0; i < arr->el_size; i++) {
		*((unsigned char*)arr->buf + (index * arr->el_size + i)) = *((unsigned char*)val + i);
	}

	return true;
}

void array_replace_at(Array *arr, int index, void *val) {
	ASSERT(arr != NULL, "(array_replace_at): array pointer is NULL");
	ASSERT(index >= 0, "(array_replace_at): index cannot be negative");
	ASSERT(index < arr->offset, "(array_replace_at): index out of bound");

	int start_index = index * arr->el_size;
    for (int i = 0; i < arr->el_size; i++) {
        *((unsigned char*)arr->buf + start_index + i) = *((unsigned char*)val + i);
    }
}

void *array_get_at(Array *arr, int index) {
	ASSERT(arr != NULL, "(array_get_at): array pointer is NULL");
	ASSERT(index < arr->offset, "(array_get_at): index out of bound");
	return (void*)((unsigned char*)arr->buf + (index * arr->el_size));
}

size_t array_size(Array *arr) {
	ASSERT(arr != NULL, "(array_size): array pointer is NULL");
	return arr->offset;
}

void array_free(Array *arr) {
	if (arr == NULL) return;
	if (arr->buf != NULL) {
		free(arr->buf);
	}
	free(arr);
}

void array_remove_at(Array *arr, int index) {
	ASSERT(arr != NULL, "(array_remove_at): array pointer is NULL");
	ASSERT(index < arr->offset, "(array_remove_at): index out of bound");

	if (index != arr->offset-1) {
		for (int i = (index+1)*arr->el_size; i <= (arr->offset)*arr->el_size; i++) {
			*((unsigned char*)arr->buf + i - arr->el_size) = *((unsigned char*)arr->buf + i);
		}
	}

	arr->offset--;
}

void *array_pop(Array *arr) {
	ASSERT(arr != NULL, "(array_pop): array pointer is NULL");
	ASSERT(arr->offset != 0, "(array_pop): array don't have any elements");
	void *val = array_get_at(arr, arr->offset-1);
	arr->offset--;
	return val;
}

bool array_clear(Array *arr) {
	ASSERT(arr != NULL, "(array_clear): array pointer is NULL");

	void *buf = malloc(2 * arr->el_size);
	if (buf == NULL) return false;
	if (arr->buf != NULL) free(arr->buf);

	arr->buf = buf;
	arr->offset = 0;
	arr->bufsize = 2;

	return true;
}
