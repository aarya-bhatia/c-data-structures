#include "include/list.h"

size_t List_size(List *this) { return this->size; }

List *List_alloc(copy_type elem_copy, free_type elem_free) {
  List *this = calloc(1, sizeof *this);
  this->head = NULL;
  this->tail = NULL;
  this->size = 0;
  this->elem_copy = elem_copy ? elem_copy : shallow_copy;
  this->elem_free = elem_free ? elem_free : shallow_free;
  return this;
}

void List_free(List *this) {
  ListNode *tmp = this->head;

  while (tmp) {
    ListNode *next = tmp->next;
    this->elem_free(tmp->elem);
    tmp->elem = NULL;
    free(tmp);
    tmp = next;
  }

  memset(this, 0, sizeof *this);
  free(this);
}

void List_insert_after(List *this, ListNode *position, ListNode *insert) {
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

void List_insert_before(List *this, ListNode *position, ListNode *insert) {
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

void List_push_front(List *this, void *elem) {
  ListNode *node = calloc(1, sizeof *node);
  node->elem = this->elem_copy(elem);

  if (!this->size) {
    this->head = this->tail = node;
    this->size = 1;
  } else {
    List_insert_before(this, this->head, node);
  }
}

void List_push_back(List *this, void *elem) {
  ListNode *node = calloc(1, sizeof *node);
  node->elem = this->elem_copy(elem);

  if (!this->size) {
    this->head = this->tail = node;
    this->size = 1;
  } else {
    List_insert_after(this, this->tail, node);
  }
}

void List_remove_node(List *this, ListNode *node) {
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
  this->elem_free(node);
  free(node);
  this->size--;
}

bool List_pop_front(List *this) {
  if (this->size == 0) {
    return false;
  }

  List_remove_node(this, this->head);
  return true;
}

bool List_pop_back(List *this) {
  if (this->size == 0) {
    return false;
  }

  List_remove_node(this, this->tail);
  return true;
}

void *List_peek_front(List *this) {
  return this->size ? this->head->elem : NULL;
}

void *List_peek_back(List *this) {
  return this->size ? this->tail->elem : NULL;
}

void List_iter_init(ListIter *iter, List *list) {
  assert(iter);
  assert(list);

  iter->current = list->head;
}

bool List_iter_next(ListIter *iter, void **elem_ptr) {
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
