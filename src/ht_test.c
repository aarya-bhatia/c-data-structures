#include "include/common.h"
#include "include/hashtable.h"

void ht_test_string_to_int() {
	Hashtable *h = ht_alloc(string_copy, free, string_compare, string_hash,
							int_copy, free);
	int b = 1, a = 2, o = 3;

	log_info("Adding banana -> %d", b);
	ht_set(h, "Banana", &b);

	log_info("Adding apple -> %d", a);
	ht_set(h, "Apple", &a);

	log_info("Adding orange -> %d", o);
	ht_set(h, "Orange", &o);

	log_info("Adding orange -> %d", a);
	ht_set(h, "Orange", &a);

	assert(*(int *)ht_get(h, "Banana") == b);
	assert(*(int *)ht_get(h, "Apple") == a);
	assert(*(int *)ht_get(h, "Orange") == a);
	assert(!ht_get(h, "Pomegranate"));

	ht_free(h);
}

int main() {
	ht_test_string_to_int();
	return 0;
}
