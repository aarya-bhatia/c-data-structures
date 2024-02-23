#include "string_util.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void test_string_reverse() {
	char s1[] = "hello";
	string_reverse(s1);
	assert(strcmp(s1, "olleh") == 0);

	char *r1 = const_string_reverse("olleh");
	assert(strcmp(r1, "hello") == 0);
	free(r1);
}

int main(){
	test_string_reverse();
	return 0;
}
