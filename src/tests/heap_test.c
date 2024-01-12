#include "../common.h"
#include "../heap.h"

void test1() {
  Heap *heap = heap_alloc(0);

  assert(heap->capacity == DEFAULT_CAPACITY);
  assert(heap->size == 0);
  assert(heap->elements);

  HeapNode *n1 = heap_push(heap, 1, (void *)1);
  assert((size_t)heap_remove(heap, n1) == 1);

  heap_free(heap);
}

void test2() {
  Heap *heap = heap_alloc(0);

  assert(heap_push(heap, 3, (void *)3));
  assert(heap_push(heap, 1, (void *)1));
  assert(heap_push(heap, 2, (void *)2));

  assert((size_t)heap_pop(heap) == 1);
  assert((size_t)heap_pop(heap) == 2);
  assert((size_t)heap_pop(heap) == 3);

  heap_free(heap);
}

void test3() {
  Heap *heap = heap_alloc(0);

  HeapNode *n1 = heap_push(heap, 10, (void *)10);
  heap_push(heap, 8, (void *)8);

  assert(heap_size(heap) == 2);
  assert((size_t)heap_peek(heap) == 8);

  heap_update(heap, n1, 1);

  assert((size_t)heap_pop(heap) == 10);
  assert((size_t)heap_pop(heap) == 8);

  heap_free(heap);
}

int main() {
  test1();
  test2();
  test3();
  return 0;
}
