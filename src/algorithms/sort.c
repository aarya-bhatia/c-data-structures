#include "sort.h"

void list_push_back_node(List *list, ListNode *node) {
  if (list->head == NULL && list->tail == NULL) {
    list->head = list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
}

/**
 * Merge sort
 */
void list_sort(List *list, compare_type compare) {
  if (list->size <= 1) {
    return;
  }

  size_t left_size = list->size / 2;
  size_t right_size = list->size - left_size;

  ListNode *mid = list_seek(list, left_size);

  List right;
  list_init(&right);
  list_split(list, mid, &right);

  assert(list->size == left_size);
  assert(right.size == right_size);

  list_sort(list, compare);   // sort left list recursively
  list_sort(&right, compare); // sort right list recursively

  ListNode *first_itr = list->head;
  ListNode *second_itr = right.head;

  // Merge left and right list in sorted order to a temporary list
  List sorted;
  list_init(&sorted);

  while (first_itr && second_itr) {
    if (compare(first_itr->elem, second_itr->elem) < 0) {
      list_push_back_node(&sorted, first_itr);
      first_itr = first_itr->next;
    } else {
      list_push_back_node(&sorted, second_itr);
      second_itr = second_itr->next;
    }
  }

  for (; first_itr; first_itr = first_itr->next) {
    list_push_back_node(&sorted, first_itr);
  }

  for (; second_itr; second_itr = second_itr->next) {
    list_push_back_node(&sorted, second_itr);
  }

  sorted.tail->next = NULL;
  list_update_size(&sorted);

  // copy the temporary back to the original list
  memcpy(list, &sorted, sizeof(List));
  memset(&sorted, 0, sizeof(List));

  assert(list->size == left_size + right_size);
}

/**
 * Quick sort TODO
 */
void vector_sort(Vector *v, compare_type compare) {}
