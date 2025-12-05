#include <stdio.h>
#include <string.h>
#include "aoc.h"
#include "solution.h"

int main(void) {
	char *sample_path = "year2025/day05/sample.txt";
	FILE *sample_fp = fopen(sample_path, "r");

	if (sample_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	long result = day05_part1(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 3);

	char *input_path = "year2025/day05/input.txt";
	FILE *input_fp = fopen(input_path, "r");
	if (input_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	result = day05_part1(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result == 525);


	sample_fp = fopen(sample_path, "r");
	result = day05_part2(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 14);

	input_fp = fopen(input_path, "r");
	result = day05_part2(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result == 333892124923577);
	return 0;
}
