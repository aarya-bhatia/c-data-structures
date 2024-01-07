#include "hashtable.h"

#include "vector.h"

size_t ht_size(Hashtable *this) { return this->size; }
size_t ht_capacity(Hashtable *this) { return this->capacity; }

Hashtable *ht_alloc(copy_type key_copy, free_type key_free,
                    compare_type key_compare, hash_type key_hash) {
  Hashtable *this = calloc(1, sizeof *this);
  this->capacity = HT_INITIAL_CAPACITY;
  this->table = calloc(HT_INITIAL_CAPACITY, sizeof(HTNode *));
  this->size = 0;
  this->key_copy = key_copy ? key_copy : shallow_copy;
  this->key_free = key_free ? key_free : shallow_free;
  this->key_compare = key_compare ? key_compare : shallow_compare;
  this->hash = key_hash ? key_hash : shallow_hash;

  return this;
}

HTNode *ht_find(Hashtable *this, const void *key) {
  assert(this);
  assert(this->key_compare);
  assert(key);

  size_t hash = this->hash((void *)key) % this->capacity;
  HTNode *node = this->table[hash];

  while (node) {
    if (this->key_compare(node->key, key) == 0) {
      return node;
    }
    node = node->next;
  }

  return NULL;
}

void ht_set(Hashtable *this, const void *key, void *value) {
  assert(this);
  assert(key);

  HTNode *found = ht_find(this, key);

  if (found) { // Update existing node value
    found->value = value;
  } else { // Create new node and add to bucket
    size_t hash = this->hash(key) % this->capacity;
    HTNode *new_node = calloc(1, sizeof *new_node);
    new_node->key = this->key_copy(key);
    new_node->value = value;
    new_node->next = this->table[hash];
    this->table[hash] = new_node;
    this->size++;
  }

  /* Rehashing */
  if (this->size > this->capacity * HT_DENSITY) {
    size_t new_capacity = (this->capacity * 2) + 1;
    HTNode **new_table = calloc(new_capacity, sizeof(HTNode *));

    for (size_t i = 0; i < this->capacity; i++) {
      HTNode *node = this->table[i];

      while (node) {
        HTNode *tmp = node->next;
        size_t new_hash = this->hash(node->key) % new_capacity;
        node->next = new_table[new_hash];
        new_table[new_hash] = node;
        node = tmp;
      }
    }

    free(this->table);
    this->table = new_table;
    this->capacity = new_capacity;
  }
}

void *ht_get(Hashtable *this, const void *key) {
  assert(this);
  assert(key);

  HTNode *found = ht_find(this, key);
  return found ? found->value : NULL;
}

void ht_node_free(Hashtable *this, HTNode *node) {
  assert(this);
  assert(this->key_free);
  if (!node) {
    return;
  }

  this->key_free((void *)node->key);
  free(node);
}

void ht_free(Hashtable *this) {
  if (!this) {
    return;
  }

  for (size_t i = 0; i < this->capacity; i++) {
    if (this->table[i]) {
      HTNode *itr = this->table[i];

      while (itr) {
        HTNode *tmp = itr->next;
        ht_node_free(this, itr);
        itr = tmp;
      }
    }

    this->table[i] = NULL;
  }

  free(this->table);
  this->table = NULL;

  free(this);
}

void ht_foreach(Hashtable *this,
                void (*callback)(const void *key, void *value)) {
  for (size_t i = 0; i < this->capacity; i++) {
    if (this->table[i]) {
      HTNode *itr = this->table[i];
      while (itr) {
        callback(itr->key, itr->value);
        itr = itr->next;
      }
    }
  }
}

void ht_foreach_key(Hashtable *this, void (*callback)(const void *key)) {
  for (size_t i = 0; i < this->capacity; i++) {
    if (this->table[i]) {
      HTNode *itr = this->table[i];
      while (itr) {
        callback(itr->key);
        itr = itr->next;
      }
    }
  }
}

void ht_foreach_value(Hashtable *this, void (*callback)(void *value)) {
  for (size_t i = 0; i < this->capacity; i++) {
    if (this->table[i]) {
      HTNode *itr = this->table[i];
      while (itr) {
        callback(itr->value);
        itr = itr->next;
      }
    }
  }
}

bool ht_contains(Hashtable *this, const void *key) {
  return ht_find(this, key) != NULL;
}

/**
 * Removes an element from the hashtable if an element with matching key exists.
 *
 * @param this the hashtable to remove element from
 * @param key the key for the element to remove
 * @param key_out If key_out is non null, the node key is not freed and stored
 * into the given pointer.
 * @param value_out If value_out is non null, the node value is not freed and
 * stored into the given pointer.
 *
 * NOTE: In all other cases, the key or value of the node is freed automatically
 * based on the given callback function key_free and value_free.
 *
 * WARNING: If the callback function is not provided, the key and value are not
 * freed. This could cause a memory leak, if the pointers to the node key or
 * node value are not accessible by the callee.
 *
 * @return Returs true if deletion was success. Returns false if no element was
 * deleted i.e key does not exist.
 */
bool ht_remove(Hashtable *this, const void *key) {
  for (size_t i = 0; i < this->capacity; i++) {
    if (this->table[i]) {
      HTNode *curr = this->table[i];
      HTNode *prev = NULL;

      while (curr) {
        if (this->key_compare(curr->key, key) == 0) {
          if (!prev) {
            this->table[i] = curr->next;
          } else {
            prev->next = curr->next;
          }

          ht_node_free(this, curr);
          this->size--;

          return true;
        }

        prev = curr;
        curr = curr->next;
      }
    }
  }

  return false;
}

void ht_iter_init(HashtableIter *itr, Hashtable *ht) {
  itr->hashtable = ht;
  itr->node = NULL;
  itr->index = 0;
  itr->start = false;
}

bool ht_iter_next(HashtableIter *itr, const void **key_save,
                  void **value_save) {
  // End of table
  if (itr->index >= itr->hashtable->capacity) {
    return false;
  }
  // Get next node in bucket
  if (itr->node) {
    itr->node = itr->node->next;
  }
  // No more nodes in bucket
  if (!itr->node) {
    if (!itr->start) {
      itr->start = true;
      itr->index = 0;
    } else {
      itr->index++;
    }

    // Find next available bucket
    for (; itr->index < itr->hashtable->capacity; itr->index++) {
      if (itr->hashtable->table[itr->index]) {
        itr->node = itr->hashtable->table[itr->index];
        break;
      }
    }

    // End of table
    if (!itr->node || itr->index >= itr->hashtable->capacity) {
      return false;
    }
  }

  assert(itr->node);

  // Save key and value pointer in given pointers

  if (key_save) {
    *key_save = itr->node->key;
  }

  if (value_save) {
    *value_save = itr->node->value;
  }

  return true;
}

uint32_t jenkins_hash(const void *key, size_t len) {
  uint32_t hash, i;
  const uint8_t *data = (const uint8_t *)key;

  for (hash = i = 0; i < len; ++i) {
    hash += data[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}

uint32_t fnv_hash(const void *key, size_t len) {
  const uint32_t FNV_PRIME = 16777619;
  const uint32_t FNV_OFFSET = 2166136261;
  uint32_t hash = FNV_OFFSET;
  const uint8_t *data = (const uint8_t *)key;

  for (size_t i = 0; i < len; ++i) {
    hash = hash ^ data[i];
    hash = hash * FNV_PRIME;
  }

  return hash;
}

size_t string_hash(const void *data) {
  // djb2 hash function
  char *str = (char *)data;
  unsigned long hash = 5381;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }

  return hash;
}

size_t int_hash(const void *data) { return jenkins_hash(data, sizeof(int)); }
size_t shallow_hash(const void *data) { return (size_t)data; }

void ht_print(Hashtable *this, to_string_type key_to_string,
              to_string_type value_to_string) {
  HTNode *itr = NULL;
  for (size_t i = 0; i < this->capacity; i++) {
    itr = this->table[i];
    while (itr) {
      log_info("bucket: %zu, key: %s, value: %s", i, key_to_string(itr->key),
               value_to_string(itr->value));
      itr = itr->next;
    }
  }
}

Vector *ht_get_keys(Hashtable *this) {
  Vector *res = vector_alloc();
  HashtableIter itr;
  const void *key = NULL;
  ht_iter_init(&itr, this);
  while (ht_iter_next(&itr, &key, NULL)) {
    vector_push(res, this->key_copy(key));
  }
  return res;
}

Vector *ht_get_values(Hashtable *this) {
  Vector *res = vector_alloc();
  HashtableIter itr;
  void *value = NULL;
  ht_iter_init(&itr, this);
  while (ht_iter_next(&itr, NULL, &value)) {
    vector_push(res, value);
  }

  return res;
}
