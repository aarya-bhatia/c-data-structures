/** Min-heap priority queue data structure */
#pragma once
#include <sys/types.h>

typedef struct HeapNode {
  int key;
  size_t index;
  void *data;
} HeapNode;

typedef struct Heap {
  HeapNode **elements;
  size_t capacity;
  size_t size;
} Heap;

Heap *heap_alloc(size_t capacity);
void heap_free(Heap *heap);

size_t heap_size(Heap *heap);
HeapNode *heap_push(Heap *heap, int key, void *data);
void *heap_peek(Heap *heap);
void *heap_pop(Heap *heap);

void *heap_remove(Heap *heap, HeapNode *node);
void heap_update(Heap *heap, HeapNode *node, int key);
