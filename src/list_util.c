#include "list_util.h"

/**
 * Scans the list to update its size.
 */
void list_update_size(List *this) {
  this->size = 0;
  for (ListNode *itr = this->head; itr; itr = itr->next) {
    this->size++;
  }
}

/**
 * Split "first" list at "position" and store new list into "second".
 * After splitting, the first list will contain nodes up to and excluding
 * "position".
 */
void list_split(List *first, ListNode *position, List *second) {
  assert(first != second);
  assert(position);

  if (position->prev == NULL) {
    first->head = first->tail = NULL;
  } else {
    first->tail = position->prev;
    first->tail->next = NULL;
  }

  second->head = position;
  second->tail = first->tail;
  second->head->prev = NULL;

  list_update_size(second);
  first->size -= second->size;
}

/**
 * Transfers and concats the nodes from first and second into result list and
 * empties the input lists. Output list may be the same as one of the input
 * lists. Does not reallocate any of the nodes in the output list.
 */
void list_concat(List *first, List *second, List *result) {
  assert(first);
  assert(second);
  assert(result);
  assert(first != second);

  first->tail->next = second->head;
  second->head->prev = first->tail;

  ListNode *new_head = first->head;
  ListNode *new_tail = second->tail;
  size_t new_size = first->size + second->size;

  memset(first, 0, sizeof(List));
  memset(second, 0, sizeof(List));

  result->head = new_head;
  result->tail = new_tail;
  result->size = new_size;
}
