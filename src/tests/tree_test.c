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

void test3() {
  Tree *t = NULL;

  t = tree_insert(t, 10);
  t = tree_insert(t, 7);
  t = tree_insert(t, 4);
  t = tree_insert(t, 2);
  t = tree_insert(t, 12);
  t = tree_insert(t, 5);

  assert(tree_size(t) == 6);

  /*
   *         10
   *        /  \
   *       7   12
   *      /
   *     4
   *    / \
   *   2   5
   */

  t = tree_remove(t, 12);
  assert(tree_size(t) == 5);
  assert(tree_find(t, 12) == NULL);

  /*
   *         10
   *        /
   *       7
   *      /
   *     4
   *    / \
   *   2   5
   */

  t = tree_remove(t, 7);
  assert(tree_size(t) == 4);
  assert(tree_find(t, 7) == NULL);

  /*
   *         10
   *        /
   *       5
   *      /
   *     4
   *    /
   *   2
   */

  t = tree_remove(t, 4);
  assert(tree_size(t) == 3);
  assert(tree_find(t, 4) == NULL);

  /*
   *     10
   *    /
   *   5
   *  /
   * 2
   */

  tree_free(t);
}

void test2() {
  Tree *t = NULL;
  t = tree_insert(t, 2);
  t = tree_insert(t, 1);
  t = tree_remove(t, 2);

  assert(tree_size(t) == 1);
  assert(!tree_find(t, 2));
  tree_free(t);
  t = NULL;

  t = tree_insert(t, 2);
  t = tree_insert(t, 1);
  t = tree_insert(t, 3);
  t = tree_remove(t, 2);

  assert(tree_size(t) == 2);
  assert(!tree_find(t, 2));
  tree_free(t);
  t = NULL;

  t = tree_insert(t, 5);
  t = tree_insert(t, 3);
  t = tree_insert(t, 6);
  t = tree_insert(t, 4);
  t = tree_remove(t, 5);

  assert(tree_size(t) == 3);
  assert(!tree_find(t, 5));
  tree_free(t);
  t = NULL;
}

int main() {
  test1();
  test2();
  test3();
  return 0;
}
