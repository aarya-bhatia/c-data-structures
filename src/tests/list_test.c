#include "../list.h"
#include "../sorted_list.h"

void list_test() {
  List *queue = list_alloc();
  int data[1024];

  for (int i = 0; i < 1024; i++) {
    data[i] = i;
    if (i % 4 == 0) {
      list_push_back(queue, data + i);
    }
  }

  while (list_size(queue)) {
    void *elem = list_peek_front(queue);
    list_pop_front(queue);
    int i = *(int *)elem;
    assert(i >= 0);
    assert(i < 1024);
    assert(data[i] == i);
    data[i] = 0;
  }

  assert(list_size(queue) == 0);
  list_free(queue);

  for (int i = 0; i < 10; i++) {
    if (i % 4 == 0) {
      assert(data[i] == 0);
    } else {
      assert(data[i] == i);
    }
  }

  log_info("%s", "success");
}

void sorted_list_test() {
  SortedList *slist = sorted_list_alloc((compare_type)strcmp, true);
  sorted_list_push(slist, "a");
  sorted_list_push(slist, "b");
  sorted_list_push(slist, "c");
  assert(sorted_list_size(slist) == 3);
  assert(!strcmp(sorted_list_pop(slist), "a"));
  assert(!strcmp(sorted_list_pop(slist), "b"));
  assert(!strcmp(sorted_list_pop(slist), "c"));

  sorted_list_free(slist);

  slist = sorted_list_alloc((compare_type)strcmp, false);
  sorted_list_push(slist, "a");
  sorted_list_push(slist, "b");
  sorted_list_push(slist, "c");
  assert(sorted_list_size(slist) == 3);
  assert(!strcmp(sorted_list_pop(slist), "c"));
  assert(!strcmp(sorted_list_pop(slist), "b"));
  assert(!strcmp(sorted_list_pop(slist), "a"));

  sorted_list_free(slist);
}

int main() {
  list_test();
  sorted_list_test();
}
