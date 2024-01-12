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
 * Sorts the elements in vector v from index l to index r using comparsion
 * function "compare".
 */
void vector_sort_helper(Vector *v, size_t l, size_t r, compare_type compare) {
  size_t size = r - l + 1;
  if (size <= 1) {
    return;
  }

  size_t mid = l + (size >> 1);

  vector_sort_helper(v, l, mid - 1, compare);
  vector_sort_helper(v, mid, r, compare);

  void *sorted[size];
  int i = l;
  int j = mid;
  int k = 0;

  while (i <= mid - 1 && j <= r) {
    if (compare(v->elems[i], v->elems[j]) < 0) {
      sorted[k++] = v->elems[i++];
    } else {
      sorted[k++] = v->elems[j++];
    }
  }

  while (i <= mid - 1) {
    sorted[k++] = v->elems[i++];
  }

  while (j <= r) {
    sorted[k++] = v->elems[j++];
  }

  assert(i == mid);
  assert(j == r + 1);
  assert(k == size);

  for (int vi = l; vi <= r; vi++) {
    v->elems[vi] = sorted[vi - l];
  }
}

/**
 * Merge sort
 */
void vector_sort(Vector *v, compare_type compare) {
  vector_sort_helper(v, 0, v->size - 1, compare);
}
