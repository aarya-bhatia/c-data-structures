#pragma once
#include "../callbacks.h"
#include "../list.h"
#include "../list_util.h"
#include "../vector.h"

void list_sort(List *, compare_type compare);
void vector_sort(Vector *, compare_type compare);
bool list_search(List *, void *target, compare_type compare);
bool vector_binary_search(Vector *, void *target, compare_type compare);
bool vector_linear_search(Vector *, void *target, compare_type compare);
