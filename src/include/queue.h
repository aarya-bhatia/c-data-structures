#pragma once

#include <pthread.h>

#include "common.h"
#include "list.h"

typedef struct queue_t {
	List *l;
	pthread_mutex_t m;
	pthread_cond_t cv;
} queue_t;

queue_t *queue_alloc(elem_copy_type elem_copy, elem_free_type elem_free);
void queue_free(queue_t *q);
void queue_enqueue(queue_t *q, void *data);
void *queue_dequeue(queue_t *q);
