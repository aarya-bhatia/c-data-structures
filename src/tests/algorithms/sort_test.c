#include "../../algorithms/algorithms.h"

void print_int_list(List *l) {
  ListIter itr;
  list_iter_init(&itr, l);
  int *i;
  while (list_iter_next(&itr, (void **)&i)) {
    printf("%d ", *i);
  }
  printf("\n");
}

void print_int_vector(Vector *v) {
  for (size_t i = 0; i < v->size; i++) {
    printf("%d ", *(int *)v->elems[i]);
  }
  printf("\n");
}

void list_sort_test() {
  List l;
  list_init(&l);
  int n = 500;
  int nums[n];
  long sum = 0;
  for (int i = 0; i < n; i++) {
    nums[i] = rand() % 10;
    sum += nums[i];
    list_push_back(&l, nums + i);
  }

  assert(l.size == (size_t)n);

  list_sort(&l, (compare_type)int_compare);
  assert(l.size == (size_t)n);

  ListIter itr;
  list_iter_init(&itr, &l);
  int *i = NULL;
  int *j = NULL;
  long new_sum = 0;
  while (list_iter_next(&itr, (void **)&i)) {
    if (j) {
      assert(*j <= *i);
    }

    j = i;
    new_sum += *i;
  }

  assert(sum == new_sum);

  list_clear(&l);
}

void vector_sort_test() {
  Vector *v = vector_alloc();
  int nums[] = {1, 2, 3};
  vector_push(v, nums + 2);
  vector_push(v, nums + 0);
  vector_push(v, nums + 1);

  printf("before: ");
  print_int_vector(v);
  vector_sort(v, (compare_type)int_compare);
  printf("after: ");
  print_int_vector(v);

  vector_free(v);
}

int main() {
  list_sort_test();
  vector_sort_test();
  return 0;
}
