#include "list.h"

size_t list_size(List *this) { return this->size; }

ListNode *list_node_alloc(void *elem) {
  ListNode *node = calloc(1, sizeof *node);
  node->elem = elem;
  return node;
}

List *list_alloc() {
  List *this = calloc(1, sizeof *this);
  this->head = NULL;
  this->tail = NULL;
  this->size = 0;
  return this;
}

void list_clear(List *this) {
  ListNode *tmp = this->head;

  while (tmp) {
    ListNode *next = tmp->next;
    tmp->elem = NULL;
    free(tmp);
    tmp = next;
  }

  this->head = this->tail = NULL;
  this->size = 0;
}

void list_free(List *this) {
  list_clear(this);
  free(this);
}

void list_insert_after(List *this, ListNode *position, ListNode *insert) {
  assert(this);
  assert(position);
  assert(insert);

  if (position->next) {
    position->next->prev = insert;
  }

  insert->next = position->next;
  insert->prev = position;
  position->next = insert;

  if (this->tail == position) {
    this->tail = insert;
  }

  this->size++;
}

void list_insert_before(List *this, ListNode *position, ListNode *insert) {
  assert(this);
  assert(position);
  assert(insert);

  if (position->prev) {
    position->prev->next = insert;
  }

  insert->next = position;
  insert->prev = position->prev;
  position->prev = insert;

  if (this->head == position) {
    this->head = insert;
  }

  this->size++;
}

void list_push_front(List *this, void *elem) {
  ListNode *node = list_node_alloc(elem);

  if (!this->size) {
    this->head = this->tail = node;
    this->size = 1;
  } else {
    list_insert_before(this, this->head, node);
  }
}

void list_push_back(List *this, void *elem) {
  ListNode *node = list_node_alloc(elem);

  if (!this->size) {
    this->head = this->tail = node;
    this->size = 1;
  } else {
    list_insert_after(this, this->tail, node);
  }
}

void list_remove_node(List *this, ListNode *node) {
  if (this->head == node) {
    this->head = node->next;
  }

  if (this->tail == node) {
    this->tail = node->prev;
  }

  if (node->prev) {
    node->prev->next = node->next;
  }

  if (node->next) {
    node->next->prev = node->prev;
  }

  node->next = node->prev = NULL;
  node->elem = NULL;
  free(node);
  this->size--;
}

bool list_pop_front(List *this) {
  if (this->size == 0) {
    return false;
  }

  list_remove_node(this, this->head);
  return true;
}

bool list_pop_back(List *this) {
  if (this->size == 0) {
    return false;
  }

  list_remove_node(this, this->tail);
  return true;
}

void *list_peek_front(List *this) {
  return this->size ? this->head->elem : NULL;
}

void *list_peek_back(List *this) {
  return this->size ? this->tail->elem : NULL;
}

void list_iter_init(ListIter *iter, List *list) {
  assert(iter);
  assert(list);

  iter->current = list->head;
}

bool list_iter_next(ListIter *iter, void **elem_ptr) {
  assert(iter);

  if (!iter->current) {
    return false;
  }

  if (elem_ptr) {
    *elem_ptr = iter->current->elem;
  }

  iter->current = iter->current->next;

  return true;
}
