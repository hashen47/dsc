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
