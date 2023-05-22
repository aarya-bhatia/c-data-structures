#include "include/queue.h"

queue_t *queue_alloc(elem_copy_type elem_copy, elem_free_type elem_free) {
	queue_t *this = calloc(1, sizeof *this);
	this->l = List_alloc(elem_copy, elem_free);
	pthread_mutex_init(&this->m, NULL);
	pthread_cond_init(&this->cv, NULL);
	return this;
}

void queue_free(queue_t *q) {
	List_free(q->l);
	pthread_mutex_destroy(&q->m);
	pthread_cond_destroy(&q->cv);
	free(q);
}

void queue_enqueue(queue_t *q, void *data) {
	pthread_mutex_lock(&q->m);
	List_push_back(q->l, data);
	pthread_cond_signal(&q->cv);
	pthread_mutex_unlock(&q->m);
}

void *queue_dequeue(queue_t *q) {
	pthread_mutex_lock(&q->m);
	while (List_size(q->l) == 0) {
		pthread_cond_wait(&q->cv, &q->m);
	}
	void *data = List_peek_front(q->l);
	List_pop_front(q->l);
	pthread_cond_signal(&q->cv);
	pthread_mutex_unlock(&q->m);
	return data;
}
