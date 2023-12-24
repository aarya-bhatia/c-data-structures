#include "queue.h"
#include "list.h"

Queue *queue_alloc() {
  Queue *this = calloc(1, sizeof *this);
  this->l = list_alloc();
  pthread_mutex_init(&this->m, NULL);
  pthread_cond_init(&this->cv, NULL);
  return this;
}

void queue_free(Queue *q) {
  list_free(q->l);
  pthread_mutex_destroy(&q->m);
  pthread_cond_destroy(&q->cv);
  free(q);
}

void queue_push(Queue *q, void *elem) {
  pthread_mutex_lock(&q->m);
  list_push_back(q->l, elem);
  pthread_cond_signal(&q->cv);
  pthread_mutex_unlock(&q->m);
}

void *queue_pop(Queue *q) {
  pthread_mutex_lock(&q->m);
  while (list_size(q->l) == 0) {
    pthread_cond_wait(&q->cv, &q->m);
  }
  void *data = list_peek_front(q->l);
  list_pop_front(q->l);
  pthread_cond_signal(&q->cv);
  pthread_mutex_unlock(&q->m);
  return data;
}
