#include "callbacks.h"

void *int_copy(const void *intptr) {
  int *p = (int *)malloc(sizeof *p);
  memcpy(p, intptr, sizeof(int));
  return p;
}

void *shallow_copy(const void *ptr) { return (void *)ptr; }

void *string_copy(const void *ptr) { return strdup(ptr); }

void int_free(void *p) { free(p); }

void shallow_free(void *p) { (void)p; }

void string_free(void *p) { free(p); }

int int_compare(const void *p1, const void *p2) {
  return *(int *)p1 - *(int *)p2;
}

int shallow_compare(const void *p1, const void *p2) {
  if (p1 == p2) {
    return 0;
  }
  if (p1 < p2) {
    return -1;
  }
  return 1;
}

int string_compare(const void *p1, const void *p2) { return strcmp(p1, p2); }
