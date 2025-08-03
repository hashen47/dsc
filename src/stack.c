#include "../includes/stack.h"

Stack *stack_init(size_t element_size, int capacity) {
	ASSERT(element_size > 0, "(stack_init): element_size cannot be zero");
	ASSERT(capacity >= 0, "(stack_init): capacity cannot be negative");

	Stack *s = malloc(sizeof(Stack));
	if (s == NULL) return NULL;

	s->capacity = capacity;
	s->el_size = element_size;
	s->offset = 0;
	s->bufsize = s->capacity == 0 ? 2 : capacity;

	void *buf = malloc(s->el_size * s->bufsize);
	if (buf == NULL) {
		free(s);
		return NULL;
	}
	s->buf = buf;

	return s;
}

bool stack_grow(Stack *s) {
	ASSERT(s != NULL, "(stack_grow): stack pointer is NULL");
	if (s->offset >= s->bufsize-1) {
		s->bufsize *= 2;
		void *new_buf = realloc(s->buf, s->el_size * s->bufsize);
		if (new_buf == NULL) return false;
		s->buf = new_buf;
	}
	return true;
}

bool stack_push(Stack *s, void *value) {
	ASSERT(s != NULL, "(stack_push): stack pointer is NULL");
	ASSERT(value != NULL, "(stack_push): value is NULL");
	ASSERT(s->buf != NULL, "(stack_push): stack->buf is NULL");
	if (s->capacity != 0) {
		ASSERT(s->offset < s->capacity, "(stack_push): stack is full");
	}

	if (s->capacity == 0) {
		if (! stack_grow(s)) return false;
	}

	int start_index = s->offset++ * s->el_size;
	for (int i = 0; i < s->el_size; i++) {
		*((unsigned char*)s->buf + start_index + i) = *((unsigned char*)value + i);
	}

	return true;
}

size_t stack_size(Stack *s) {
	ASSERT(s != NULL, "(stack_size): stack pointer is NULL");
	return s->offset;
}

size_t stack_capacity(Stack *s) {
	ASSERT(s != NULL, "(stack_capacity): stack pointer is NULL");
	return s->capacity;
}

bool is_stack_full(Stack *s) {
	ASSERT(s != NULL, "(is_stack_full): stack pointer is NULL");
	return s->capacity != 0 && stack_size(s) == s->capacity;
}

void *stack_pop(Stack *s) {
	ASSERT(s != NULL, "(stack_pop): stack pointer is NULL");
	ASSERT(!is_stack_empty(s), "(stack_pop): stack is empty");
	return (unsigned char*)s->buf + (--s->offset * s->el_size);
}

void *stack_top(Stack *s) {
	ASSERT(s != NULL, "(stack_top): stack pointer is NULL");
	ASSERT(!is_stack_empty(s), "(stack_top): stack is empty");
	return (unsigned char*)s->buf + ((s->offset-1) * s->el_size);
}

bool is_stack_empty(Stack *s) {
	return stack_size(s) == 0;
}

void stack_free(Stack *s) {
	if (s == NULL) return;
	if (s->buf != NULL) {
		free(s->buf);
	}
	free(s);
}
