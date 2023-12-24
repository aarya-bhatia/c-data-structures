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
void *string_copy(const void *);

void int_free(void *);
void shallow_free(void *);
void string_free(void *);

int int_compare(const void *, const void *);
int shallow_compare(const void *, const void *);
int string_compare(const void *, const void *);
