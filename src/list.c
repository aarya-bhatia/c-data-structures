#include "list.h"

/**
 * Returns size of list, assumes list nodes were not altered by user.
 */
size_t list_size(List *this) { return this->size; }

/**
 * list node constructor
 */
ListNode *list_node_alloc(void *elem) {
  ListNode *node = calloc(1, sizeof *node);
  node->elem = elem;
  return node;
}

/**
 * Initialise and returns a new list.
 */
List *list_alloc() {
  List *this = calloc(1, sizeof *this);
  list_init(this);
  return this;
}

/**
 * Initialise a list that may be allocated on the stack.
 */
void list_init(List *this) {
  this->head = NULL;
  this->tail = NULL;
  this->size = 0;
}

/**
 * Remove all nodes from the list. Does not "free" the list.
 * This function can be called to deallocate all memory of a
 * stack-allocated list as well.
 */
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

/**
 * Removes all nodes and also frees the list.
 * This function should be called only if the list was
 * allocated on the heap using list_alloc().
 */
void list_free(List *this) {
  list_clear(this);
  free(this);
}

/**
 * Inserts the node "insert" after the node "position" in the given list.
 * If "position" is NULL, "insert" is inserted at the back of the list.
 *
 * Nodes before or after "insert" are discarded.
 */
void list_insert_after(List *this, ListNode *position, ListNode *insert) {
  assert(this);
  assert(insert);

  insert->prev = insert->next = NULL;

  if (!position) {
    if (!this->head) {
      this->head = this->tail = insert;
    } else {
      list_insert_before(this, this->head, insert);
    }
  } else {
    if (position->next) {
      position->next->prev = insert;
    }

    insert->next = position->next;
    insert->prev = position;
    position->next = insert;

    if (this->tail == position) {
      this->tail = insert;
    }
  }

  this->size++;
}

/**
 * Inserts the node "insert" before the node "position" in the given list.
 * If "position" is NULL, "insert" is inserted at the front of the list.
 *
 * Nodes before or after "insert" are discarded.
 */
void list_insert_before(List *this, ListNode *position, ListNode *insert) {
  assert(this);
  assert(insert);

  insert->prev = insert->next = NULL;

  if (!position) {
    if (!this->tail) {
      this->head = this->tail = insert;
    } else {
      list_insert_after(this, this->tail, insert);
    }
  } else {
    if (position->prev) {
      position->prev->next = insert;
    }

    insert->next = position;
    insert->prev = position->prev;
    position->prev = insert;

    if (this->head == position) {
      this->head = insert;
    }
  }

  this->size++;
}

/**
 * Add element "elem" to the front of the list.
 */
void list_push_front(List *this, void *elem) {
  ListNode *node = list_node_alloc(elem);

  if (!this->size) {
    this->head = this->tail = node;
    this->size = 1;
  } else {
    list_insert_before(this, this->head, node);
  }
}

/**
 * Add element "elem" to the back of the list.
 */
void list_push_back(List *this, void *elem) {
  ListNode *node = list_node_alloc(elem);

  if (!this->size) {
    this->head = this->tail = node;
    this->size = 1;
  } else {
    list_insert_after(this, this->tail, node);
  }
}

/**
 * Remove and free the given node from the list.
 * Assumes given node is a member of the list.
 */
void list_remove_node(List *this, ListNode *node) {
  assert(this);
  assert(node);

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

/**
 * Remove the element at the front of the list.
 * Returns true if an element was removed.
 */
bool list_pop_front(List *this) {
  if (this->size == 0) {
    return false;
  }

  list_remove_node(this, this->head);
  return true;
}

/**
 * Remove the element at the back of the list.
 * Returns true if an element was removed.
 */
bool list_pop_back(List *this) {
  if (this->size == 0) {
    return false;
  }

  list_remove_node(this, this->tail);
  return true;
}

/**
 * Returns the element at the front of the list. Returns NULL if list is empty.
 */
void *list_peek_front(List *this) {
  return this->size ? this->head->elem : NULL;
}

/**
 * Returns the element at the back of the list. Returns NULL if list is empty.
 */
void *list_peek_back(List *this) {
  return this->size ? this->tail->elem : NULL;
}

/**
 * Initialise or reset the list iterator instance for the given list.
 * This function should be called before list_iter_next().
 */
void list_iter_init(ListIter *iter, List *list) {
  assert(iter);
  assert(list);

  iter->current = list->head;
}

/**
 * Advances the list iterator and provides a ptr to the next element in the
 * list. To ignore the value of the next node, set elem_ptr to NULL.
 *
 * This function should be called after list_iter_init().
 *
 * Returns true if there was an element at the iterator.
 */
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

/**
 * Returns the node at given index in the list.
 */
ListNode *list_seek(List *this, size_t index) {
  assert(index < list_size(this));

  ListNode *res = this->head;
  for (size_t i = 0; i < index; i++) {
    res = res->next;
  }

  return res;
}

/**
 * Returns the element at given index in the list.
 */
void *list_get(List *this, size_t index) {
  assert(index < list_size(this));
  return list_seek(this, index)->elem;
}

/**
 * Updates the element at given index in the list.
 */
void list_set(List *this, size_t index, void *elem) {
  assert(index < list_size(this));
  ListNode *node = list_seek(this, index);
  node->elem = elem;
}
