#pragma once

#include "callbacks.h"
#include "common.h"

typedef struct Vector {
  void **elems;
  size_t size;
  size_t capacity;
} Vector;

Vector *vector_alloc();
void vector_free(Vector *);
void *vector_first(Vector *);
void *vector_last(Vector *);
void *vector_at(Vector *, size_t index);
size_t vector_size(Vector *);
size_t vector_capacity(Vector *);
void vector_reserve(Vector *, size_t capacity);
bool vector_contains(Vector *, const void *target, compare_type compare);
void vector_remove(Vector *, size_t index);
void vector_push(Vector *, void *elem);
void vector_foreach(Vector *, void (*callback)(void *elem_ptr));
void vector_clear(Vector *);

void vector_shuffle(Vector *);
char *vector_join(Vector *, const char *);
Vector *vector_split(const char *str, const char *delim);
