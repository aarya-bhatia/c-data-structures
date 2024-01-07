#include "../vector.h"

void vector_test() {
  Vector *this = vector_alloc();

  vector_push(this, "hello");
  vector_push(this, "world");

  assert(this->size == 2);

  vector_foreach(this, (callback_type)puts);

  assert(vector_contains(this, "hello", cstring_compare));
  assert(!vector_contains(this, "hello1", cstring_compare));

  vector_remove(this, 1);
  vector_remove(this, 0);

  assert(this->size == 0);

  vector_push(this, "a");
  vector_push(this, "b");
  vector_push(this, "c");

  vector_remove(this, 1);

  assert(this->size == 2);

  vector_free(this);
}

int main() { vector_test(); }
