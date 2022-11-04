TINYC := $(shell which tcc 2>/dev/null)
CLANG := $(shell which clang 2>/dev/null)
GCC := $(shell which gcc 2>/dev/null)
CC := $(or $(TINYC),$(CLANG),$(GCC))

.DELETE_ON_ERROR:
all: test

test:
	${CC} morse_test.c -o test && ./test && rm -rf test
