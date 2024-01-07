#include "files.h"

char *join(Vector *vector);
void resolve_path_helper(Vector *vector, char *name);

char *resolve_path(char *path) {
  assert(path);
  if (strlen(path) == 0) {
    return NULL;
  }

  Vector *vector = vector_alloc(NULL, free);
  assert(vector);

  if (path[0] != '/') {
    vector_push(vector, getcwd(NULL, 0));
  } else {
    vector_push(vector, strdup("/"));
  }

  char *s = strstr(path, "/");
  char *t = path;

  while (s) {
    if (s != t) {
      char *tmp = strndup(t, s - t);
      assert(tmp);
      resolve_path_helper(vector, tmp);
    }

    t = s + 1;
    s = strstr(t, "/");
  }

  assert(t);
  if (*t != 0) {
    assert(*t != '/');
    if (strcmp(t, ".") == 0 && vector_size(vector) == 0) {
      vector_push(vector, strdup(getenv("HOME")));
    } else {
      resolve_path_helper(vector, t);
    }
  }

  char *result = join(vector);
  vector_free(vector);

  assert(result[0] == '/');
  assert(strcmp(result, "~") != 0);
  assert(strcmp(result, ".") != 0);
  assert(strcmp(result, "..") != 0);

  return result;
}

void mkdirs(char *filepath) {
  assert(filepath);
  char *resolved = resolve_path(filepath);
  assert(resolved);
  assert(*resolved == '/');

  if (strcmp(resolved, "/") == 0) {
    return;
  }

  char *s = strstr(resolved + 1, "/");
  char *t = resolved;

  struct stat st = {0};
  while (s) {
    *s = 0;
    memset(&st, 0, sizeof st);
    if (stat(resolved, &st) == -1) {
      log_debug("mkdir(\"%s\")", resolved);
      mkdir(resolved, 0750);
    }
    *s = '/';

    t = s;
    s = strstr(t + 1, "/");
  }

  log_debug("%s", resolved);
  free(resolved);
}

char *join(Vector *vector) {
  assert(vector);
  assert(vector_size(vector) > 0);

  String *s = string_alloc();
  for (size_t i = 0; i < vector_size(vector); i++) {
    char *name = vector_at(vector, i);

    assert(name);
    assert(strlen(name) > 0);

    if (strcmp(name, "/") == 0) {
      if (string_size(s) == 0) {
        string_append_cstr(s, "/");
        continue;
      }
    }

    if (name[0] == '/') {
      size_t n = strlen(name);

      if (name[n - 1] == '/') {
        name[n - 1] = 0;
      }

      if (string_size(s) == 0) {
        string_append_cstr(s, name);
      } else {
        assert(strlen(name + 1) > 0);
        string_append_cstr(s, name + 1);
      }
    } else {
      string_append_cstr(s, name);
    }

    if (i + 1 < vector_size(vector)) {
      string_append_cstr(s, "/");
    }
  }

  char *joined = string_to_cstr(s);
  string_free(s);
  return joined;
}

void resolve_path_helper(Vector *vector, char *name) {
  if (strcmp(name, "..") == 0) {
    if (vector_size(vector) >= 1) {
      char *prev = vector_at(vector, vector_size(vector) - 1);
      char *ptr = rstrstr(prev, "/");
      if (!ptr) {
        vector_remove(vector, vector_size(vector) - 1);
      } else {
        *ptr = 0;
      }
    } else {
      log_error("Invalid path");
    }
  } else if (strcmp(name, "~") == 0) {
    vector_clear(vector);
    vector_push(vector, strdup(getenv("HOME")));
  } else if (strcmp(name, ".") != 0) {
    vector_push(vector, strdup(name));
  }
}
