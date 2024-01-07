#include "../common.h"

int main() {
  char *s = make_string("%d.%d.%d.%d", 192, 168, 0, 1);
  assert(!strcmp(s, "192.168.0.1"));
  free(s);
  s = make_string(" %s ", "hello");
  assert(!strcmp(s, " hello "));
  assert(!strcmp(trimwhitespace(s), "hello"));
  free(s);
  s = make_string("the_dark_side_of_the_moon");
  assert(!strcmp(rstrstr(s, "the"), "the_moon"));
  free(s);
  return 0;
}
