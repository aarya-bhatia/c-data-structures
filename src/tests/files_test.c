#include "files.h"

int tests_passed = 0;
int tests_total = 0;

void test_resolve_path_helper(char *path, char *expected) {
  char *resolved = resolve_path(path);

  log_info("TEST: resolve_path(\"%s\")", path);

  if (strcmp(resolved, expected) != 0) {
    log_warn("FAIL: \"%s\" != \"%s\"", resolved, expected);
  } else {
    log_info("PASS: \"%s\" == \"%s\"", resolved, expected);
    tests_passed++;
  }

  tests_total++;
}

int test_resolve_path() {
  char *home_dir = "/home/aarya";
  char *cur_dir = "/home/aarya/repos/aarya-bhatia/c-data-structures";
  char *parent_dir = "/home/aarya/repos/aarya-bhatia";

  test_resolve_path_helper("/", "/");
  test_resolve_path_helper("~", home_dir);
  test_resolve_path_helper(".", cur_dir);
  test_resolve_path_helper("..", parent_dir);
  test_resolve_path_helper("./", cur_dir);

  char path[4096];

  sprintf(path, "%s/%s", cur_dir, "hello.pdf");
  test_resolve_path_helper("hello.pdf", path);

  sprintf(path, "%s/%s", parent_dir, "hello");
  test_resolve_path_helper("../hello", path);

  sprintf(path, "%s/%s", parent_dir, "hello.txt");
  test_resolve_path_helper("./../hello.txt", path);

  sprintf(path, "%s/test/hello", home_dir);
  test_resolve_path_helper("~/test/test1/../hello", path);

  sprintf(path, "%s/test/test1/hello", home_dir);
  test_resolve_path_helper("~/test/test1/hello", path);

  sprintf(path, "%s/data/a/b/hello", cur_dir);
  test_resolve_path_helper("data/a/b/hello", path);

  sprintf(path, "%s/file", home_dir);
  test_resolve_path_helper(path, path);

  sprintf(path, "%s/hello", home_dir);
  test_resolve_path_helper("~/hello", path);

  test_resolve_path_helper("/tmp/hello", "/tmp/hello");

  sprintf(path, "%s/.../hello", cur_dir);
  test_resolve_path_helper(".../hello", path);

  test_resolve_path_helper("///", "/");

  test_resolve_path_helper("./..//~/~/~//", home_dir);

  assert(tests_passed <= tests_total);
  if (tests_passed == tests_total) {
    log_info("%s", "Result: All tests passed!");
    return 0;
  } else {
    log_warn("Result: %d tests passed, %d tests failed", tests_passed,
             tests_total - tests_passed);
    return 1;
  }
}

int test_mkdirs() {
  mkdirs("/home/aarya/file1");
  mkdirs("data/test1/test2/test3");
  mkdirs("data/test2/test3/../test4");
  return 0;
}

int main(int argc, char *argv[]) {
  int done[32] = {0};
  int status = 0;
  for (int i = 1; i < argc; i++) {
    int test_num = atoi(argv[i]);
    switch (test_num) {
    case 1:
      if (!done[1]) {
        status |= test_resolve_path();
      }
      done[1] = 1;
      break;
    case 2:
      if (!done[2]) {
        status |= test_mkdirs();
      }
      done[2] = 1;
      break;
    }
  }

  return status;
}
