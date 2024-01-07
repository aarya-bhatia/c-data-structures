#include "../hashtable.h"

void print_key(const void *key, void *value) { puts(key); }

Hashtable *ht_alloc_int_key() {
  return ht_alloc(int_copy, free, int_compare, int_hash);
}

Hashtable *ht_alloc_string_key() {
  return ht_alloc(cstring_copy, cstring_free, cstring_compare, string_hash);
}

void hashtable_iter_test() {
  Hashtable *this = ht_alloc_int_key();

  int n = 100;
  for (int i = 0; i < n; i++) {
    char *string = calloc(16, 1);
    for (int i = 0; i < 15; i++) {
      string[i] = 'a' + rand() % 26;
    }
    ht_set(this, &i, string);
  }

  HashtableIter itr;
  ht_iter_init(&itr, this);

  int count = 0;
  while (ht_iter_next(&itr, NULL, NULL) == true) {
    count++;
  }

  assert(count == n);

  int *i = NULL;
  int sum = 0;

  ht_iter_init(&itr, this);
  while (ht_iter_next(&itr, (const void **)&i, NULL) == true) {
    sum += *i;
  }

  assert(sum == n * (n - 1) / 2);

  ht_print(this, (to_string_type)int_to_string,
           (to_string_type)shallow_to_string);
  ht_foreach_value(this, free);
  ht_free(this);
}

void hashtable_test() {
  Hashtable *this = ht_alloc_string_key();

  int i = 1;
  ht_set(this, "hello", &i);

  i++;
  ht_set(this, "world", &i);

  assert(ht_get(this, "hello") == ht_get(this, "world"));

  assert(ht_size(this) == 2);
  ht_remove(this, "hello");
  assert(ht_size(this) == 1);

  i = 1;
  ht_set(this, "hello", &i);
  assert(this->size == 2);

  int *j = ht_get(this, "hello");
  assert(*j == i);

  ht_free(this);
}

void hashtable_test1() {
  // stress test 1

  Hashtable *this = ht_alloc(int_copy, free, int_compare, int_hash);

  // insert all
  for (int i = 0; i < 1000; i++) {
    assert(!ht_contains(this, &i));
    ht_set(this, &i, NULL);
    assert(ht_size(this) == (size_t)i + 1);
    assert(ht_contains(this, &i));
  }

  assert(ht_size(this) == 1000);
  assert(ht_capacity(this) > 1000);

  // remove all
  for (int i = 0; i < 1000; i++) {
    assert(ht_contains(this, &i));
    assert(ht_remove(this, &i));
    assert(!ht_contains(this, &i));
    assert(ht_size(this) == (size_t)(1000 - i - 1));
  }

  assert(ht_size(this) == 0);

  for (int i = 0; i < 5000; i++) {
    ht_set(this, &i, NULL);
  }

  assert(ht_size(this) == 5000);

  for (int i = 0; i < 1000; i++) {
    assert(ht_remove(this, &i));
  }

  assert(ht_size(this) == 4000);

  for (int i = 0; i < 1000; i++) {
    assert(!ht_remove(this, &i));
  }

  for (int i = 1000; i < 2000; i++) {
    ht_set(this, &i, NULL);
  }

  assert(ht_size(this) == 4000);

  for (int i = 1000; i < 5000; i += 2) {
    assert(ht_contains(this, &i));
    ht_set(this, &i, NULL); // update key
    assert(ht_size(this) == 4000);
  }

  ht_free(this);
}

void hashtable_test2() {
  Hashtable *h = ht_alloc_string_key();
  int b = 1, a = 2, o = 3;

  log_info("Adding banana -> %d", b);
  ht_set(h, "Banana", &b);

  log_info("Adding apple -> %d", a);
  ht_set(h, "Apple", &a);

  log_info("Adding orange -> %d", o);
  ht_set(h, "Orange", &o);

  log_info("Adding orange -> %d", a);
  ht_set(h, "Orange", &a);

  assert(*(int *)ht_get(h, "Banana") == b);
  assert(*(int *)ht_get(h, "Apple") == a);
  assert(*(int *)ht_get(h, "Orange") == a);
  assert(!ht_get(h, "Pomegranate"));

  ht_free(h);
}

struct test_case_t {
  const char *name;
  void (*function)();
};

int main(int argc, char *argv[]) {
  if (argc == 2 && strcmp(argv[1], "help") == 0) {
    printf("Usage: %s [ test_name ]\n", *argv);
    return 0;
  }

  struct test_case_t test_cases[] = {
      {"hashtable_test", hashtable_test},
      {"hashtable_iter_test", hashtable_iter_test},
      {"hashtable_test1", hashtable_test1},
      {"hashtable_test2", hashtable_test2}};

  if (argc == 1) {
    for (size_t i = 0; i < sizeof test_cases / sizeof test_cases[0]; i++) {
      test_cases[i].function();
    }
  } else {
    for (char **arg = argv + 1; *arg; arg++) {
      log_debug("Test: %s", *arg);
      for (size_t i = 0; i < sizeof test_cases / sizeof test_cases[0]; i++) {
        if (strcmp(*arg, test_cases[i].name) == 0) {
          log_debug("Test matched: %s", test_cases[i].name);
          test_cases[i].function();
          break;
        }
      }
    }
  }

  return 0;
}
