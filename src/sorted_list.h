#pragma once
#include "list.h"
#include "callbacks.h"

typedef struct SortedList {
  List list;
  compare_type compare;
  bool ascending;
} SortedList;

SortedList *sorted_list_alloc(compare_type compare, bool ascending);
void sorted_list_free(SortedList *);
void sorted_list_push(SortedList *, void *);
void *sorted_list_pop(SortedList *);
size_t sorted_list_size(SortedList *);
