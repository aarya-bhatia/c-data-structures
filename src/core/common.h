#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "log.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

char *make_string(char *format, ...);
char *rstrstr(char *string, char *pattern);
char *trimwhitespace(char *str);
size_t _align_capacity(size_t capacity);

