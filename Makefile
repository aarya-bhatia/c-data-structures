CC=gcc
INCLUDES=-Isrc
CFLAGS=-std=c99 -Wall -Wextra -Wno-pointer-arith \
	   -pedantic -gdwarf-4 -MMD -MP -O0 -D_GNU_SOURCE -c $(INCLUDES)
LDFLAGS=-Llib -llog
FILES=$(shell find src -type f -name "*.c")
OBJ=$(FILES:src/%.c=obj/%.o)
TEST_OBJ=obj/test.o $(OBJ)

TEST_EXE=test

all: $(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ)
	@mkdir -p $(dir $@);
	$(CC) $^ $(LDFLAGS) -o $@

obj/%.o: src/%.c
	@mkdir -p $(dir $@);
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf obj $(TEST_EXE)

.PHONY: clean

-include $(OBJS_DIR)/*.d
