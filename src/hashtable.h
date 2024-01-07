#pragma once

#include "callbacks.h"
#include "common.h"
#include "vector.h"

#define HT_DENSITY 0.6
#define HT_INITIAL_CAPACITY 11

typedef struct HTNode {
  const void *key;
  void *value;
  struct HTNode *next;
} HTNode;

typedef struct Hashtable {
  HTNode **table;
  size_t size;
  size_t capacity;
  copy_type key_copy;
  free_type key_free;
  compare_type key_compare;
  hash_type hash;
} Hashtable;

typedef struct HashtableIter {
  Hashtable *hashtable;
  size_t index;
  HTNode *node;
  bool start;
} HashtableIter;

Hashtable *ht_alloc(copy_type key_copy, free_type key_free,
                    compare_type key_compare, hash_type key_hash);

void ht_free(Hashtable *);
size_t ht_size(Hashtable *);
size_t ht_capacity(Hashtable *);

void *ht_get(Hashtable *, const void *key);
void ht_set(Hashtable *, const void *key, void *value);
bool ht_remove(Hashtable *, const void *key);
bool ht_contains(Hashtable *, const void *key);
HTNode *ht_find(Hashtable *, const void *key);

void ht_iter_init(HashtableIter *itr, Hashtable *ht);
bool ht_iter_next(HashtableIter *itr, const void **key_save, void **value_save);
void ht_foreach(Hashtable *, void (*callback)(const void *key, void *value));
void ht_foreach_key(Hashtable *, void (*callback)(const void *key));
void ht_foreach_value(Hashtable *, void (*callback)(void *value));

void ht_print(Hashtable *, to_string_type key_to_string,
              to_string_type value_to_string);

Vector *ht_get_keys(Hashtable *);
Vector *ht_get_values(Hashtable *);

/* hash functions */
uint32_t jenkins_hash(const void *key, size_t len);
uint32_t fnv_hash(const void *key, size_t len);
size_t string_hash(const void *);
size_t int_hash(const void *);
size_t shallow_hash(const void *);
