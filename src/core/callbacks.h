#pragma once

#include "common.h"

typedef int (*compare_type)(const void *elem_ptr_1, const void *elem_ptr_2);
typedef void *(*copy_type)(const void *elem_ptr);
typedef size_t (*hash_type)(const void *elem_ptr);
typedef char *(*to_string_type)(const void *elem_ptr);
typedef bool (*filter_type)(const void *elem_ptr);
typedef void (*free_type)(void *elem_ptr);
typedef void (*callback_type)(void *elem_ptr);

void *int_copy(const void *);
void *shallow_copy(const void *);
void *cstring_copy(const void *);

void int_free(void *);
void shallow_free(void *);
void cstring_free(void *);

int int_compare(const void *, const void *);
int shallow_compare(const void *, const void *);
int cstring_compare(const void *, const void *);

const char *int_to_string(void *p);
const char *shallow_to_string(void *p);

