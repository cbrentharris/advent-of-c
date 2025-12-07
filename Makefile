CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -std=c17 -D_POSIX_C_SOURCE=200809L -Iinclude
LDFLAGS = -lm

COMMON_SRC = src/aoc.c
COMMON_OBJ = $(COMMON_SRC:.c=.o)

# List the binaries you want to build.
# For now you have just 2025 day 01.
BINARIES = bin/2025_01 bin/2025_02 bin/2025_03 bin/2025_04 bin/2025_05 bin/2025_06
TESTS    = bin/test_2025_01_solution bin/test_2025_02_solution bin/test_2025_03_solution bin/test_2025_04_solution bin/test_2025_05_solution bin/test_2025_06_solution

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

bin/2025_03: year2025/day03/main.c year2025/day03/solution.c $(COMMON_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/test_2025_03_solution: year2025/day03/test_solution.c year2025/day03/solution.c $(COMMON_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/2025_04: year2025/day04/main.c year2025/day04/solution.c $(COMMON_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/test_2025_04_solution: year2025/day04/test_solution.c year2025/day04/solution.c $(COMMON_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/2025_05: year2025/day05/main.c year2025/day05/solution.c $(COMMON_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/test_2025_05_solution: year2025/day05/test_solution.c year2025/day05/solution.c $(COMMON_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/2025_06: year2025/day06/main.c year2025/day06/solution.c $(COMMON_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/test_2025_06_solution: year2025/day06/test_solution.c year2025/day06/solution.c $(COMMON_OBJ)
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

