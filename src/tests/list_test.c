#include "../list.h"
#include "../list_util.h"
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

void list_util_test() {
  List l;
  List l1;

  list_init(&l);
  list_init(&l1);

  list_push_back(&l, "a");
  list_push_back(&l, "b");
  list_push_back(&l, "c");
  list_push_back(&l, "d");

  assert(!strcmp(list_get(&l, 0), "a"));
  assert(!strcmp(list_get(&l, 1), "b"));
  assert(!strcmp(list_get(&l, 2), "c"));
  assert(!strcmp(list_get(&l, 3), "d"));

  list_split(&l, list_seek(&l, 2), &l1);

  assert(list_size(&l) == 2);
  assert(list_size(&l1) == 2);

  assert(!strcmp(list_get(&l, 0), "a"));
  assert(!strcmp(list_get(&l, 1), "b"));
  assert(!strcmp(list_get(&l1, 0), "c"));
  assert(!strcmp(list_get(&l1, 1), "d"));

  list_concat(&l, &l1, &l);

  assert(list_size(&l) == 4);
  assert(list_size(&l1) == 0);

  assert(!strcmp(list_get(&l, 0), "a"));
  assert(!strcmp(list_get(&l, 1), "b"));
  assert(!strcmp(list_get(&l, 2), "c"));
  assert(!strcmp(list_get(&l, 3), "d"));

  list_clear(&l);
  list_clear(&l1);
}

int main() {
  list_test();
  sorted_list_test();
  list_util_test();
}
