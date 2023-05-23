#pragma once

#include "include/common.h"
#include "include/hashtable.h"
#include "include/list.h"
#include "include/vector.h"

typedef struct Vertex {
	void *key;
	void *data;
	List *adj; /* List of vertices */
} Vertex;

typedef struct Graph {
	elem_compare_type key_compare;
	elem_hash_type key_hash;
	elem_copy_type key_copy;
	elem_free_type key_free;
	elem_copy_type value_copy;
	elem_free_type value_free;
	Hashtable *nodes; /* Map key to vertex */
} Graph;
