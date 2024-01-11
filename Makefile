INCLUDES=-Isrc

LIB_FILES=$(wildcard src/*.c)
LIB_OBJS=$(LIB_FILES:src/%.c=obj/%.lib.o)

ALG_LIB_FILES=$(wildcard src/algorithms/*.c)
ALG_LIB_OBJS=$(ALG_LIB_FILES:src/%.c=obj/%.lib.o)

TEST_FILES=$(wildcard src/tests/*.c)
TEST_TARGETS=$(TEST_FILES:src/tests/%.c=bin/%)

ALG_TEST_FILES=$(wildcard src/tests/algorithms/*.c)
ALG_TEST_TARGETS=$(ALG_TEST_FILES:src/tests/%.c=bin/%)

CFLAGS=-std=c99 -Wall -Wextra -Wno-pointer-arith \
	   -pedantic -gdwarf-4 -MMD -MP -O0 \
	   -D_GNU_SOURCE -c $(INCLUDES)

LDFLAGS=-pthread

all: $(TEST_TARGETS) $(ALG_TEST_TARGETS)

tmp:
	@echo $(TEST_TARGETS)
	@echo $(LIB_OBJS)
	@echo $(ALG_TEST_TARGETS)
	@echo $(ALG_LIB_OBJS)

bin/%: obj/%.test.o $(LIB_OBJS) $(ALG_LIB_OBJS)
	@mkdir -p $(dir $@);
	@gcc $^ -o $@ $(LDFLAGS)

obj/%.test.o: src/tests/%.c
	@mkdir -p $(dir $@);
	@gcc $(CFLAGS) $< -o $@

obj/%.lib.o: src/%.c
	@mkdir -p $(dir $@);
	@gcc $(CFLAGS) $< -o $@

clean:
	@rm -rf obj bin

.PHONY: clean

-include obj/*.d
