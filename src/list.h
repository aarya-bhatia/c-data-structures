#pragma once

#include "common.h"

typedef struct ListNode {
  void *elem;
  struct ListNode *next;
  struct ListNode *prev;
} ListNode;

typedef struct List {
  ListNode *head;
  ListNode *tail;
  size_t size;
} List;

typedef struct ListIter {
  ListNode *current;
} ListIter;

ListNode *list_node_alloc(void *elem);
List *list_alloc();
void list_init(List *);
void list_clear(List *);
void list_free(List *);
size_t list_size(List *);

void list_push_front(List *, void *elem);
void list_push_back(List *, void *elem);
bool list_pop_front(List *);
bool list_pop_back(List *);
void *list_peek_front(List *);
void *list_peek_back(List *);

void list_remove_node(List *, ListNode *node);
void list_insert_after(List *, ListNode *position, ListNode *insert);
void list_insert_before(List *, ListNode *position, ListNode *insert);

void list_iter_init(ListIter *iter, List *list);
bool list_iter_next(ListIter *iter, void **elem_ptr);

ListNode *list_seek(List *, size_t index);
void *list_get(List *, size_t index);
void list_set(List *, size_t index, void *elem);
