#pragma once

#include <stdbool.h>
#include <sys/types.h>

typedef struct ListNode {
	void *elem;
	struct ListNode *next;
	struct ListNode *prev;
} ListNode;

typedef struct List {
	ListNode *head;
	ListNode *tail;
	size_t size;
	void *(*elem_copy)(void *);
	void (*elem_free)(void *);
} List;

typedef struct ListIter {
	ListNode *current;
} ListIter;

List *List_alloc(void *(*elem_copy)(void *), void (*elem_free)(void *));
void List_free(List *);

void List_push_front(List *, void *elem);
void List_push_back(List *, void *elem);
bool List_pop_front(List *);
bool List_pop_back(List *);
void *List_peek_front(List *);
void *List_peek_back(List *);
size_t List_size(List *);

void List_remove_node(List *, ListNode *node);
void List_insert_after(List *, ListNode *position, ListNode *insert);
void List_insert_before(List *, ListNode *position, ListNode *insert);

void List_iter_init(ListIter *iter, List *list);
bool List_iter_next(ListIter *iter, void **elem_ptr);
