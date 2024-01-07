#include "tree.h"
#include <stdlib.h>

void tree_free(Tree *t) {
  if (!t) {
    return;
  }

  if (t->left) {
    tree_free(t->left);
  }

  if (t->right) {
    tree_free(t->right);
  }

  free(t);
}

size_t tree_size(Tree *t) {
  if (!t) {
    return 0;
  }

  return tree_size(t->left) + tree_size(t->right) + 1;
}

Tree *tree_insert(Tree *t, int key) {
  if (!t) {
    t = calloc(1, sizeof *t);
    t->key = key;
  } else if (key < t->key) {
    t->left = tree_insert(t->left, key);
  } else if (key > t->key) {
    t->right = tree_insert(t->right, key);
  }

  return t;
}

Tree *tree_find(Tree *t, int key) {
  if (!t) {
    return NULL;
  } else if (key < t->key) {
    return tree_find(t->left, key);
  } else if (key > t->key) {
    return tree_find(t->right, key);
  } else {
    return t;
  }
}
