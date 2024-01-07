#pragma once
#include "common.h"

#define INITIAL_CAPACITY 16

typedef struct String {
  char *buffer;
  size_t size;
  size_t capacity;
} String;

String *string_alloc();
String *string_alloc1(const char *cstr);
void string_free(String *s);
size_t string_size(String *s);
size_t string_capacity(String *s);
void string_append_char(String *s, char c);
void string_append_string(String *s, const String *t);
void string_append_cstr(String *s, const char *c);
char *string_to_cstr(String *s);
void string_resize(String *s, size_t size);
void string_reserve(String *s, size_t capacity);
char *string_slice(String *s, size_t start, size_t end);
