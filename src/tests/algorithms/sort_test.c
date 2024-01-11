#include "../../algorithms/sort.h"

void print_int_list(List *l) {
  ListIter itr;
  list_iter_init(&itr, l);
  int *i;
  while (list_iter_next(&itr, (void **)&i)) {
    printf("%d ", *i);
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

  assert(l.size == n);
  // puts("before sort:");
  // print_int_list(&l);

  list_sort(&l, (compare_type)int_compare);
  assert(l.size == n);
  // puts("after sort:");
  // print_int_list(&l);

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

int main() {
  list_sort_test();
  return 0;
}
