#include "../sstring.h"

void check_string(String *s, char *value, size_t size) {
  log_info("check %s, %zu", value, size);

  assert(s);
  assert(!memcmp(s->buffer, value, size));
  assert(string_size(s) == size);
  assert(string_capacity(s) >= string_size(s));
}

void check_string_append(char *s1, char *s2) {
  log_info("check append %s, %s", s1, s2);

  String *t1 = string_alloc1(s1);
  String *t2 = string_alloc1(s2);

  assert(t1);
  assert(t2);

  size_t l1 = strlen(s1), l2 = strlen(s2);

  assert(t1->size == l1);
  assert(t2->size == l2);

  string_append_string(t1, t2);

  assert(!memcmp(t1->buffer, s1, l1));
  assert(!memcmp(t2->buffer, s2, l2));
  assert(!memcmp(t1->buffer + l1, s2, l2));

  assert(t1->size == l1 + l2);

  assert(t1->capacity >= t1->size);
  assert(t2->capacity >= t2->size);

  string_free(t1);
  string_free(t2);
}

int main() {
  String *s = string_alloc();
  check_string(s, "", 0);
  assert(s->capacity == INITIAL_CAPACITY);

  String *s1 = string_alloc1("aarya");
  check_string(s1, "aarya", 5);

  char *c2 = string_slice(s1, 1, 3);
  String *s2 = string_alloc1(c2);
  free(c2);
  check_string(s2, "ar", 2);

  assert(!string_slice(s1, 1, 0));
  assert(!string_slice(s1, 6, 7));

  char *c3 = string_slice(s1, 0, 0);
  String *s3 = string_alloc1(c3);
  free(c3);
  check_string(s3, "", 0);

  check_string_append("", "aarya");
  check_string_append("aarya", "");
  check_string_append("aarya", " bhatia");
  check_string_append("", "");

  string_free(s);
  string_free(s1);
  string_free(s2);
  string_free(s3);

  return 0;
}
