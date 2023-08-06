CFLAGS=-std=c99 -Wall -Wextra -Wno-pointer-arith \
	   -pedantic -gdwarf-4 -MMD -MP -O0 \
	   -Isrc -D_GNU_SOURCE -c

FILES=src/common.c src/astring.c src/queue.c\
	  src/hashtable.c src/list.c src/vector.c

OBJ=$(FILES:src/%.c=obj/%.o)

all: test string_test ht_test

ht_test: obj/ht_test.o $(OBJ)
	gcc $^ -o $@

string_test: obj/string_test.o $(OBJ)
	gcc $^ -o $@

test: obj/test.o $(OBJ)
	gcc $^ -o $@

libaarya: $(OBJ)
	ar rcs libaarya.a $^

obj/%.o: src/%.c
	mkdir -p obj;
	gcc $(CFLAGS) $< -o $@

clean:
	rm -rf obj test string_test ht_test libaarya.a

.PHONY: clean libaarya

-include obj/*.d
