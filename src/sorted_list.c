#include "sorted_list.h"

size_t sorted_list_size(SortedList *slist) { return slist->list.size; }

SortedList *sorted_list_alloc(compare_type compare, bool ascending) {
  assert(compare);
  SortedList *slist = calloc(1, sizeof *slist);
  slist->compare = compare;
  slist->ascending = ascending;
  return slist;
}

void sorted_list_free(SortedList *slist) {
  list_clear(&slist->list);
  free(slist);
}

void _helper(SortedList *slist, ListNode *itr, void *elem) {
  if ((slist->ascending && slist->compare(elem, itr->elem) <= 0) ||
      (!slist->ascending && slist->compare(elem, itr->elem) >= 0)) {
    list_insert_before(&slist->list, itr, list_node_alloc(elem));
  } else if (itr->next == NULL) {
    list_insert_after(&slist->list, itr, list_node_alloc(elem));
  } else {
    _helper(slist, itr->next, elem);
  }
}

void sorted_list_push(SortedList *slist, void *elem) {
  assert(slist);
  assert(elem);

  if (list_size(&slist->list) == 0) {
    list_push_back(&slist->list, elem);
  } else {
    _helper(slist, slist->list.head, elem);
  }
}

void *sorted_list_pop(SortedList *slist) {
  assert(slist);
  void *elem = list_peek_front(&slist->list);
  list_pop_front(&slist->list);
  return elem;
}
