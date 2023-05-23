CFLAGS=-std=c99 -Wall -Wextra -Wno-pointer-arith \
	   -pedantic -gdwarf-4 -MMD -MP -O0 \
	   -Isrc -D_GNU_SOURCE -c

FILES=$(shell find src -type f -name "*.c")
OBJ=$(FILES:src/%.c=obj/%.o)

all: test string_test

string_test: libaarya obj/string_test.o
	gcc obj/string_test.o -Llib -llog -laarya -o $@

test: libaarya obj/test.o
	gcc obj/test.o -Llib -llog -laarya -o $@

libaarya: $(OBJ)
	ar rcs lib/libaarya.a $^

obj/%.o: src/%.c
	mkdir -p obj;
	gcc $(CFLAGS) $< -o $@

clean:
	rm -rf obj test string_test

.PHONY: clean libaarya

-include obj/*.d
