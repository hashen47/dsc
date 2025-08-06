#include "../includes/queue.h"

Queue *queue_init(size_t el_size, int capacity) {
    ASSERT(el_size > 0, "(queue_init): el_size cannot be zero or negative");
    ASSERT(capacity > 0, "(queue_init): capacity cannot be zero or negative");

    Queue *q = malloc(sizeof(Queue));
    if (q == NULL) return NULL;

    q->offset = 0;
    q->front = 0;
    q->capacity = capacity;
    q->el_size = el_size;
    q->bufsize = 2;
    q->bufsize = capacity; 

    void *buf = malloc(q->bufsize * q->el_size);
    if (buf == NULL) return NULL;
    q->buf = buf;

    return q;
}

bool queue_resize(Queue *q, size_t new_capacity) {
    ASSERT(q != NULL, "(queue_resize): queue cannot be NULL");
    ASSERT(q->buf != NULL, "(queue_resize): queue->buf cannot be NULL");
    ASSERT(q->capacity <= new_capacity, "(queue_resize): new capacity should greater than previous capacity");

    void *new_buf = malloc(new_capacity * q->el_size);
    if (new_buf == NULL) return false;

    int j = 0;
    for (int i = q->front * q->el_size; i < q->offset * q->el_size; i++) {
        *((unsigned char*)new_buf + j++) = *((unsigned char*)q->buf + i);
    }

    q->capacity = new_capacity;
    q->offset -= q->front;
    q->front = 0;
    q->buf = new_buf;

    return true;
}

size_t queue_size(Queue *q) {
    ASSERT(q != NULL, "(queue_size): queue cannot be NULL");
    return q->size;
}

size_t queue_capacity(Queue *q) {
    ASSERT(q != NULL, "(queue_capacity): queue cannot be NULL");
    return q->capacity;
}

bool is_queue_empty(Queue *q) {
    ASSERT(q != NULL, "(is_queue_empty): queue cannot be NULL");
    return q->size == 0;
}

bool is_queue_full(Queue *q) {
    ASSERT(q != NULL, "(is_queue_empty): queue cannot be NULL");
    return q->size == q->capacity;
}

bool enqueue(Queue *q, void *value) {
    ASSERT(q != NULL, "(enqueue): queue cannot be NULL");
    ASSERT(q->buf != NULL, "(enqueue): queue->buf cannot be NULL");
    ASSERT(!is_queue_full(q), "(enqueue): queue is full");

    if (q->offset == q->bufsize) {
        if (! queue_resize(q, q->capacity)) return false;
    }

    int start_index = q->offset++ * q->el_size;
    for (int i = 0; i < q->el_size; i++) {
        *((unsigned char*)q->buf + start_index + i) = *((unsigned char*)value + i);
    }

    q->size++;

    return true;
}

void *dequeue(Queue *q) {
    ASSERT(q != NULL, "(dequeue): queue cannot be NULL");
    ASSERT(q->buf != NULL, "(dequeue): queue->buf cannot be NULL");
    ASSERT(!is_queue_empty(q), "(dequeue): queue is empty");
    q->size--;
    return (void*)((unsigned char*)q->buf + q->front++ * q->el_size);
}

void *queue_peek(Queue *q) {
    ASSERT(q != NULL, "(queue_peek): queue cannot be NULL");
    ASSERT(q->buf != NULL, "(queue_peek): queue->buf cannot be NULL");
    ASSERT(!is_queue_empty(q), "(queue_peek): queue is empty");
    return (void*)((unsigned char*)q->buf + q->front * q->el_size);
}

void queue_free(Queue *q) {
    if (q == NULL) return;
    if (q->buf != NULL) free(q->buf);
    free(q);
}
