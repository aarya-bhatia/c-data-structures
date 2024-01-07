#include "sstring.h"

size_t string_size(String *this) { return this->size; }
size_t string_capacity(String *this) { return this->capacity; }

String *string_alloc() {
  String *this = calloc(1, sizeof *this);
  this->capacity = INITIAL_CAPACITY;
  this->buffer = calloc(this->capacity, 1);
  return this;
}

String *string_alloc1(const char *cstr) {
  String *this = string_alloc();
  string_append_cstr(this, cstr);
  return this;
}

void string_append_char(String *this, char c) {
  string_reserve(this, this->size + 1);
  this->buffer[this->size++] = c;
}

void string_append_cstr(String *this, const char *cstr) {
  assert(this);
  assert(cstr);
  size_t length = strlen(cstr);
  string_reserve(this, this->size + length);
  memcpy(this->buffer + this->size, cstr, length);
  this->size += length;
}

void string_append_string(String *this, const String *other) {
  string_reserve(this, this->size + other->size);
  memcpy(this->buffer + this->size, other->buffer, other->size);
  this->size += other->size;
}

char *string_to_cstr(String *this) {
  char *cstr = malloc(this->size + 1);
  memcpy(cstr, this->buffer, this->size);
  cstr[this->size] = 0;
  return cstr;
}

void string_free(String *this) {
  if (!this) {
    return;
  }

  free(this->buffer);
  free(this);
}

/**
 * Returns a substring (C string) of given Stringin the range [start ... end)
 * Returns NULL if invalid range i.e. end < start
 */
char *string_slice(String *this, size_t start, size_t end) {
  if (end < start || start >= this->size || end > this->size) {
    return NULL;
  }

  size_t length = end - start;
  char *str = calloc(length + 1, 1);
  memcpy(str, this->buffer + start, length);
  return str;
}

/**
 * To change the size of given Stringto specified size.
 * - If new size > old size => This function will expand the string in size and
 * capacity and fill new bytes with 0.
 * - If new size < old size => Stringwill destroy the additional bytes and
 * shrink itself to given size and capacity.
 * - This function WILL change the SIZE and CAPACITY of the given String.
 * - The capacity of the string will be at least the minimum capacity, i.e.
 * capacity >= size.
 */
void string_resize(String *this, size_t size) {
  if (size == this->size) {
    return;
  }

  this->capacity = _align_capacity(size);
  this->buffer = realloc(this->buffer, this->capacity);

  if (size > this->size) {
    // zero out the new bytes
    memset(this->buffer + this->size, 0, size - this->size);
  } else {
    // zero out the extra bytes
    memset(this->buffer + size, 0, this->size - size);
  }

  this->size = size;
}

/**
 * - This function will do nothing if new capacity is smaller than old capacity.
 * - It will ensure that the string has space for at least 'capacity' no. of
 * bytes.
 * - It will NOT change the size of the string, but it MAY change its capacity.
 */
void string_reserve(String *this, size_t capacity) {
  if (capacity > this->capacity) {
    this->capacity = _align_capacity(capacity);
    this->buffer = realloc(this->buffer, this->capacity);
  }
}
