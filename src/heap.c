#include "heap.h"
#include "common.h"

#define PARENT(i) ((i)-1) / 2
#define LEFT(i) 2 * (i) + 1
#define RIGHT(i) 2 * (i) + 2

#define ELEMENT(heap, i) heap->elements[i]
#define KEY(heap, i) heap->elements[i]->key
#define VALUE(heap, i) heap->elements[i]->data

void _swap(Heap *heap, size_t i, size_t j) {
  HeapNode *tmp = heap->elements[i];
  heap->elements[i] = heap->elements[j];
  heap->elements[j] = tmp;
  heap->elements[i]->index = i;
  heap->elements[j]->index = j;
}

void _bubble_up(Heap *heap, size_t i) {
  if (i == 0) {
    return;
  }

  size_t parent = PARENT(i);
  if (KEY(heap, i) < KEY(heap, parent)) {
    _swap(heap, i, parent);
    _bubble_up(heap, parent);
  }
}

void _bubble_down(Heap *heap, size_t i) {
  assert(i < heap->size);

  if (LEFT(i) < heap->size) {
    size_t min_child = LEFT(i);
    if (RIGHT(i) < heap->size && KEY(heap, RIGHT(i)) < KEY(heap, LEFT(i))) {
      min_child = RIGHT(i);
    }

    if (min_child < heap->size && KEY(heap, min_child) < KEY(heap, i)) {
      _swap(heap, i, min_child);
      _bubble_down(heap, min_child);
    }
  }
}

void _bubble(Heap *heap, size_t i) {
  assert(i < heap->size);
  if (i > 0 && KEY(heap, i) < KEY(heap, PARENT(i))) {
    _bubble_up(heap, i);
  } else {
    _bubble_down(heap, i);
  }
}

Heap *heap_alloc(size_t capacity) {
  Heap *h = calloc(1, sizeof *h);
  h->capacity = MAX(capacity, DEFAULT_CAPACITY);
  h->elements = calloc(h->capacity, sizeof(HeapNode *));

  return h;
}

void heap_free(Heap *heap) {
  for (size_t i = 0; i < heap->size; i++) {
    free(heap->elements[i]);
    heap->elements[i] = NULL;
  }

  free(heap->elements);
  free(heap);
}

HeapNode *heap_push(Heap *heap, int key, void *data) {
  if (heap->size == heap->capacity) {
    heap->capacity *= 2;
    heap->elements =
        realloc(heap->elements, heap->capacity * sizeof(HeapNode *));
  }

  HeapNode *node = calloc(1, sizeof *node);
  node->key = key;
  node->index = heap->size;
  node->data = data;

  heap->elements[node->index] = node;
  heap->size++;

  _bubble_up(heap, node->index);
  return node;
}

size_t heap_size(Heap *heap) { return heap->size; }

void *heap_peek(Heap *heap) {
  assert(heap->size > 0);
  return VALUE(heap, 0);
}

void *heap_pop(Heap *heap) {
  assert(heap_size(heap) > 0);
  return heap_remove(heap, heap->elements[0]);
}

void *heap_remove(Heap *heap, HeapNode *node) {
  assert(node);
  assert(node->index < heap->size);

  size_t last = heap->size - 1;
  heap->size--;

  if (node->index < last) {
    size_t old = node->index;
    _swap(heap, node->index, last);
    _bubble(heap, old);
  }

  void *data = node->data;
  heap->elements[node->index] = NULL;
  free(node);
  return data;
}

void heap_update(Heap *heap, HeapNode *node, int key) {
  assert(node);
  assert(node->index < heap->size);

  node->key = key;
  _bubble(heap, node->index);
}
