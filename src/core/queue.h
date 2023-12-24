#pragma once

#include <pthread.h>

#include "common.h"
#include "list.h"

/**
 * A thread-safe blocking queue
 */
typedef struct Queue {
  List *l;
  pthread_mutex_t m;
  pthread_cond_t cv;
} Queue;

Queue *queue_alloc();
void queue_free(Queue *);
void queue_push(Queue *, void *);
void *queue_pop(Queue *);
