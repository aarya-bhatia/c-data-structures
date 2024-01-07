#include "common.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>

size_t _align_capacity(size_t capacity) {
  size_t i = 1;
  while (i < capacity) {
    i *= 2;
  }
  return i;
}

/**
 * Use this utility function to allocate a string with given format and args.
 * The purpose of this function is to check the size of the resultant string
 * after all substitutions and allocate only those many bytes.
 */
char *make_string(char *format, ...) {
  va_list args;

  // Find the length of the output string

  va_start(args, format);
  int n = vsnprintf(NULL, 0, format, args);
  va_end(args);

  // Create the output string

  char *s = calloc(1, n + 1);

  va_start(args, format);
  vsprintf(s, format, args);
  va_end(args);

  return s;
}

/**
 * Note: This function returns a pointer to a substring of the original string.
 * If the given string was allocated dynamically, the caller must not overwrite
 * that pointer with the returned value, since the original pointer must be
 * deallocated using the same allocator with which it was allocated.  The return
 * value must NOT be deallocated using free() etc.
 *
 */
char *trimwhitespace(char *str) {
  char *end;

  // Trim leading space
  while (isspace((unsigned char)*str))
    str++;

  if (*str == 0) // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

/**
 * Return a pointer to the last occurrence of substring "pattern" in
 * given string "string". Returns NULL if pattern not found.
 */
char *rstrstr(char *string, char *pattern) {
  char *next = strstr(string, pattern);
  char *prev = next;

  while (next) {
    next = strstr(prev + strlen(pattern), pattern);

    if (next) {
      prev = next;
    }
  }

  return prev;
}
