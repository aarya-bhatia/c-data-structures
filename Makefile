DIRS=$(shell find src/ -type d)
INCLUDES=$(addprefix -I,$(DIRS))

CFLAGS=-std=c99 -Wall -Wextra -Wno-pointer-arith \
	   -pedantic -gdwarf-4 -MMD -MP -O0 \
	   -D_GNU_SOURCE -c $(INCLUDES)

CORE_FILES=$(wildcard src/core/*.c)
CORE_OBJS=$(CORE_FILES:src/%.c=obj/%.o)

EXTRA_FILES=$(wildcard src/extra/*.c)
EXTRA_OBJS=$(EXTRA_FILES:src/%.c=obj/%.o)

all: bin/vector_test bin/list_test bin/string_test bin/files_test

tmp:
	echo $(CORE_OBJS)

bin/ht_test: obj/test/ht_test.o $(CORE_OBJS)
	mkdir -p $(dir $@);
	gcc $^ -o $@

bin/vector_test: obj/test/vector_test.o $(CORE_OBJS)
	mkdir -p $(dir $@);
	gcc $^ -o $@

bin/list_test: obj/test/list_test.o $(CORE_OBJS)
	mkdir -p $(dir $@);
	gcc $^ -o $@

bin/string_test: obj/test/string_test.o $(CORE_OBJS)
	mkdir -p $(dir $@);
	gcc $^ -o $@

bin/files_test: obj/test/files_test.o $(CORE_OBJS) $(EXTRA_OBJS)
	gcc $^ -o $@

lib: $(CORE_OBJS)
	ar rcs libaarya.a $^

obj/%.o: src/%.c
	mkdir -p $(dir $@);
	gcc $(CFLAGS) $< -o $@

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test

clean:
	rm -rf obj bin *.a

.PHONY: clean libaarya memcheck

-include obj/*.d
