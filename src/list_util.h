#pragma once
#include "list.h"

void list_update_size(List *);
void list_split(List *first, ListNode *position, List *second);
void list_concat(List *first, List *second, List *result);
