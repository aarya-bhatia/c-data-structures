#include "include/common.h"
#include "include/hashtable.h"
#include "include/list.h"
#include "include/queue.h"
#include "include/vector.h"

void print_string(void *s) { puts(s); }

void list_test() {
	List *queue = List_alloc(shallow_copy, shallow_free);
	int data[1024];

	for (int i = 0; i < 1024; i++) {
		data[i] = i;
		if (i % 4 == 0) {
			List_push_back(queue, data + i);
		}
	}

	while (List_size(queue)) {
		void *elem = List_peek_front(queue);
		List_pop_front(queue);
		int i = *(int *)elem;
		assert(i >= 0);
		assert(i < 1024);
		assert(data[i] == i);
		data[i] = 0;
	}

	assert(List_size(queue) == 0);
	List_free(queue);

	for (int i = 0; i < 10; i++) {
		if (i % 4 == 0) {
			assert(data[i] == 0);
		} else {
			assert(data[i] == i);
		}
	}

	log_info("%s", "success");
}

struct s {
	int x;
};

struct s *struct_copy(struct s *other) {
	struct s *this = calloc(1, sizeof *this);
	memcpy(this, other, sizeof *this);
	return this;
}

void struct_free(struct s *other) { free(other); }

void print(char *key, struct s *value) { printf("%s -> %d\n", key, value->x); }

void hashtable_iter_test() {
	Hashtable *this =
		ht_alloc(int_copy, free, int_compare, int_hash, string_copy, free);

	int n = 100;
	for (int i = 0; i < n; i++) {
		char some_string[16];
		for (int i = 0; i < 15; i++) {
			some_string[i] = 'a' + rand() % 26;
		}
		some_string[15] = 0;
		ht_set(this, (void *)&i, (void *)some_string);
	}

	HashtableIter itr;
	ht_iter_init(&itr, this);

	int count = 0;
	while (ht_iter_next(&itr, NULL, NULL) == true) {
		count++;
	}

	assert(count == n);

	int *i = NULL;
	int sum = 0;

	ht_iter_init(&itr, this);

	while (ht_iter_next(&itr, (void **)&i, NULL) == true) {
		sum += *i;
	}

	assert(sum == n * (n - 1) / 2);

	ht_print(this, (to_string_type)int_to_string, shallow_to_string);
	ht_free(this);
}

void hashtable_test() {
	Hashtable *this =
		ht_alloc(string_copy, free, string_compare, string_hash,
				 (copy_type)struct_copy, (free_type)struct_free);

	this->value_copy = (copy_type)struct_copy;
	this->value_free = (free_type)struct_free;

	{
		struct s s1;

		s1.x = 1;
		ht_set(this, "hello", &s1);

		s1.x = 2;
		ht_set(this, "world", &s1);
	}

	ht_foreach(this, (void (*)(void *, void *))print);

	ht_remove(this, "hello", NULL, NULL);

	assert(this->size == 1);

	struct s s1;

	s1.x = 1;
	ht_set(this, "hello", &s1);

	assert(this->size == 2);

	struct s *s2 = ht_get(this, "hello");
	assert(s2->x == s1.x);

	struct s s3;
	s3.x = -1;
	ht_set(this, "hello", &s3);

	s2 = ht_get(this, "hello");
	assert(s2->x == s3.x);

	s2 = ht_get(this, "world");
	assert(s2->x == 2);

	ht_free(this);
}

// bool check_mod_3(int *key, void *val, int *arg) { return *key % 3 == *arg; }

void hashtable_test1() {
	// stress test 1

	Hashtable *this = ht_alloc_int_to_shallow();

	// insert all
	for (int i = 0; i < 1000; i++) {
		assert(!ht_contains(this, &i));
		ht_set(this, &i, NULL);
		assert(ht_size(this) == (size_t)i + 1);
		assert(ht_contains(this, &i));
	}

	assert(ht_size(this) == 1000);
	assert(ht_capacity(this) > 1000);

	// remove all
	for (int i = 0; i < 1000; i++) {
		assert(ht_contains(this, &i));
		assert(ht_remove(this, &i, NULL, NULL));
		assert(!ht_contains(this, &i));
		assert(ht_size(this) == (size_t)(1000 - i - 1));
	}

	assert(ht_size(this) == 0);

	for (int i = 0; i < 5000; i++) {
		ht_set(this, &i, NULL);
	}

	assert(ht_size(this) == 5000);

	for (int i = 0; i < 1000; i++) {
		assert(ht_remove(this, &i, NULL, NULL));
	}

	assert(ht_size(this) == 4000);

	for (int i = 0; i < 1000; i++) {
		assert(!ht_remove(this, &i, NULL, NULL));
	}

	for (int i = 1000; i < 2000; i++) {
		ht_set(this, &i, NULL);
	}

	assert(ht_size(this) == 4000);

	for (int i = 1000; i < 5000; i += 2) {
		assert(ht_contains(this, &i));
		ht_set(this, &i, NULL);	 // update key
		assert(ht_size(this) == 4000);
	}

	ht_free(this);
}

// TODO
void hashtable_test2() {
	Hashtable *this = ht_alloc_int_to_shallow();

	int i;
	int n = 609;

	for (i = 0; i < n; i++) {
		ht_set(this, &i, NULL);
	}

	log_info("ht_size() = %zu", ht_size(this));
	log_info("ht_capacity() = %zu", ht_capacity(this));
	assert(ht_size(this) == (size_t)n);

	int arg;

	for (int i = 0; i < 3; i++) {
		arg = i;
		log_info("Removing elements which are congruent to %d mod 3", arg);
		// ht_remove_all_filter(this, (filter_type)check_mod_3, &arg);
		for (int j = 0; j < n; j++) {
			if (j % 3 == i) {
				ht_remove(this, &j, NULL, NULL);
			}
		}
		log_info("ht_size() = %zu", ht_size(this));
	}

	log_info("ht_size() = %zu", ht_size(this));
	assert(ht_size(this) == 0);

	ht_free(this);
}

void vector_test() {
	Vector *this = Vector_alloc(string_copy, free);

	Vector_push(this, "hello");
	Vector_push(this, "world");

	assert(this->size == 2);

	Vector_foreach(this, print_string);

	assert(Vector_contains(this, "hello", string_compare));
	assert(!Vector_contains(this, "hello1", string_compare));

	Vector_remove(this, 1, NULL);
	Vector_remove(this, 0, NULL);

	assert(this->size == 0);

	Vector_push(this, "a");
	Vector_push(this, "b");
	Vector_push(this, "c");

	Vector_remove(this, 1, NULL);

	assert(this->size == 2);

	Vector_free(this);
}

struct test_case_t {
	const char *name;
	void (*function)();
};

int main(int argc, char *argv[]) {
	if (argc == 2 && strcmp(argv[1], "help") == 0) {
		printf("Usage: %s [ test_name ]\n", *argv);
		return 0;
	}

	struct test_case_t test_cases[] = {
		{"vector_test", vector_test},
		{"hashtable_test", hashtable_test},
		{"list_test", list_test},
		{"hashtable_iter_test", hashtable_iter_test},
		{"hashtable_test1", hashtable_test1},
		{"hashtable_test2", hashtable_test2}};

	if (argc == 1) {
		for (size_t i = 0; i < sizeof test_cases / sizeof test_cases[0]; i++) {
			test_cases[i].function();
		}
	} else {
		for (char **arg = argv + 1; *arg; arg++) {
			log_debug("Test: %s", *arg);
			for (size_t i = 0; i < sizeof test_cases / sizeof test_cases[0];
				 i++) {
				if (strcmp(*arg, test_cases[i].name) == 0) {
					log_debug("Test matched: %s", test_cases[i].name);
					test_cases[i].function();
					break;
				}
			}
		}
	}

	return 0;
}
