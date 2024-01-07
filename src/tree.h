#pragma once
#include <stdbool.h>
#include <sys/types.h>

typedef struct Tree {
  int key;
  void *value;
  struct Tree *left;
  struct Tree *right;
} Tree;

Tree *tree_alloc();
Tree *tree_insert(Tree *t, int key);
Tree *tree_find(Tree *t, int key);
void tree_free(Tree *t);
size_t tree_size(Tree *t);
Tree *tree_remove(Tree *tree, int key);
