#include "vector.h"

size_t vector_size(Vector *this) { return this->size; }
size_t vector_capacity(Vector *this) { return this->capacity; }

void *vector_first(Vector *this) {
  assert(this->size > 0);
  return vector_at(this, 0);
}

void *vector_last(Vector *this) {
  assert(this->size > 0);
  return vector_at(this, vector_size(this) - 1);
}

void *vector_at(Vector *this, size_t index) {
  assert(this);
  assert(index < this->size);
  return this->elems[index];
}

Vector *vector_alloc() {
  Vector *this = calloc(1, sizeof *this);
  this->elems = calloc(DEFAULT_CAPACITY, sizeof *this->elems);
  this->size = 0;
  this->capacity = DEFAULT_CAPACITY;
  return this;
}

void vector_free(Vector *this) {
  assert(this);
  for (size_t i = 0; i < this->size; i++) {
    this->elems[i] = NULL;
  }
  free(this->elems);
  free(this);
}

void vector_reserve(Vector *this, size_t capacity) {
  assert(this);
  if (capacity <= this->capacity) {
    return;
  }
  this->capacity = _align_capacity(capacity);
  this->elems = realloc(this->elems, this->capacity * sizeof *this->elems);
  memset(this->elems + this->size, 0,
         (this->capacity - this->size) * sizeof *this->elems);
}

bool vector_contains(Vector *this, const void *target, compare_type compare) {
  assert(this);
  assert(compare);

  for (size_t i = 0; i < this->size; i++) {
    if (compare(this->elems[i], target) == 0) {
      return true;
    }
  }

  return false;
}

void vector_remove(Vector *this, size_t index) {
  assert(this);
  if (index >= this->size) {
    return;
  }

  this->elems[index] = NULL;

  if (index < this->size - 1) {
    memmove(this->elems + index, this->elems + index + 1,
            (this->size - index - 1) * sizeof *this->elems);
  }

  this->size--;
}

void vector_push(Vector *this, void *elem) {
  assert(this);
  vector_reserve(this, this->size + 1);
  this->elems[this->size++] = elem;
}

void vector_foreach(Vector *this, void (*callback)(void *elem_ptr)) {
  assert(this);
  assert(callback);

  for (size_t i = 0; i < this->size; i++) {
    callback(this->elems[i]);
  }
}
void vector_clear(Vector *this) {
  for (size_t i = 0; i < this->size; i++) {
    this->elems[i] = NULL;
  }
  this->size = 0;
}
