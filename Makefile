CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -std=c17 -Iinclude
LDFLAGS =

COMMON_SRC = src/aoc.c
COMMON_OBJ = $(COMMON_SRC:.c=.o)

# List the binaries you want to build.
# For now you have just 2025 day 01.
BINARIES = bin/2025_01 bin/2025_02
TESTS    = bin/test_2025_01_solution bin/test_2025_02_solution

.PHONY: all clean tests

all: $(BINARIES)

# ----- Day 2025-01 -----

bin/2025_01: year2025/day01/main.c year2025/day01/solution.c $(COMMON_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/test_2025_01_solution: year2025/day01/test_solution.c year2025/day01/solution.c $(COMMON_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/2025_02: year2025/day02/main.c year2025/day02/solution.c $(COMMON_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/test_2025_02_solution: year2025/day02/test_solution.c year2025/day02/solution.c $(COMMON_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

tests: $(TESTS)
	@echo "Running tests..."
	@for t in $(TESTS); do \
		echo "  $$t"; \
		./$$t || exit 1; \
	done
	@echo "All tests passed."

clean:
	rm -rf $(COMMON_OBJ) bin

