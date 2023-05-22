CFLAGS=-std=c99 -Wall -Wextra -Wno-pointer-arith \
	   -pedantic -gdwarf-4 -MMD -MP -O0 \
	   -Isrc -D_GNU_SOURCE -c

FILES=$(shell find src -type f -name "*.c")
OBJ=$(FILES:src/%.c=obj/%.o)

all: test

test: libaarya obj/test.o
	gcc obj/test.o -Llib -llog -laarya -o test

libaarya: $(OBJ)
	ar rcs lib/libaarya.a $^

obj/%.o: src/%.c
	mkdir -p obj;
	gcc $(CFLAGS) $< -o $@

clean:
	rm -rf obj test

.PHONY: clean libaarya

-include obj/*.d
