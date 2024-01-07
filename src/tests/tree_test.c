#include "../tree.h"
#include <assert.h>
#include <stdlib.h>

void test1() {
  Tree *t = NULL;
  assert(tree_size(t) == 0);

  t = tree_insert(t, 3);
  t = tree_insert(t, 1);
  t = tree_insert(t, 2);

  assert(tree_size(t) == 3);

  assert(tree_find(t, 1));
  assert(tree_find(t, 2));
  assert(tree_find(t, 3));

  assert(tree_find(t, 0) == NULL);
  assert(tree_find(t, 4) == NULL);

  t = tree_insert(t, 3);
  assert(tree_size(t) == 3);

  tree_free(t);
}

int main() {
  test1();
  return 0;
}
