#include "../../algorithms/algorithms.h"

static int nums[] = {1, 2, 3, 4};

void list_search_test() {
  List l;
  list_init(&l);

  for (int i = 0; i <= 2; i++) {
    list_push_back(&l, nums + i);
  }

  assert(list_search(&l, nums + 0, (compare_type)int_compare));
  assert(list_search(&l, nums + 1, (compare_type)int_compare));
  assert(list_search(&l, nums + 2, (compare_type)int_compare));
  assert(!list_search(&l, nums + 3, (compare_type)int_compare));

  list_clear(&l);
}

void vector_search_test() {
  Vector *v = vector_alloc();

  for (int i = 0; i <= 2; i++) {
    vector_push(v, nums + i);
  }

  assert(vector_linear_search(v, nums + 0, (compare_type)int_compare));
  assert(vector_linear_search(v, nums + 1, (compare_type)int_compare));
  assert(vector_linear_search(v, nums + 2, (compare_type)int_compare));
  assert(!vector_linear_search(v, nums + 3, (compare_type)int_compare));

  assert(vector_binary_search(v, nums + 0, (compare_type)int_compare));
  assert(vector_binary_search(v, nums + 1, (compare_type)int_compare));
  assert(vector_binary_search(v, nums + 2, (compare_type)int_compare));
  assert(!vector_binary_search(v, nums + 3, (compare_type)int_compare));

  vector_free(v);
}

int main() {
  list_search_test();
  vector_search_test();
  return 0;
}
