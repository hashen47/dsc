#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "assert.h"

#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    int front;
    size_t offset;
    size_t size;
    size_t capacity;
    size_t bufsize;
    size_t el_size;
    void *buf;
} Queue;


Queue *queue_init(size_t el_size, int capacity);
bool enqueue(Queue *q, void *value); 
bool queue_resize(Queue *q, size_t new_capacity);
void *dequeue(Queue *q); 
void *queue_peek(Queue *q); 
bool is_queue_empty(Queue *q);
bool is_queue_full(Queue *q);
size_t queue_size(Queue *q);
size_t queue_size(Queue *q);
size_t queue_capacity(Queue *q);
void queue_free(Queue *q);


#define QUEUE_INIT(type, capacity) queue_init(sizeof(type), capacity)
#define QUEUE_SIZE(q) queue_size(q)
#define QUEUE_CAPACITY(q) queue_capacity(q)
#define IS_QUEUE_EMPTY(q) is_queue_empty(q)
#define IS_QUEUE_FULL(q) is_queue_full(q)
#define ENQUEUE(q, value) enqueue(q, &value)
#define DEQUEUE(q, type) *((type*)dequeue(q))
#define QEUEUE_PEEK(q, type) *((type*)queue_peek(q))
#define QUEUE_RESIZE(q, new_capacity) queue_resize(q, new_capacity)
#define QUEUE_FREE(q) queue_free(q)


#endif
