#include <stdio.h>
#include <string.h>
#include "aoc.h"
#include "solution.h"

int main(void) {
	char *sample_path = "year2025/day09/sample.txt";
	FILE *sample_fp = fopen(sample_path, "r");

	if (sample_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	long result = day09_part1(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 0);

	char *input_path = "year2025/day09/input.txt";
	FILE *input_fp = fopen(input_path, "r");
	if (input_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	result = day09_part1(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result == 0);


	sample_fp = fopen(sample_path, "r");
	result = day09_part2(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 0);

	input_fp = fopen(input_path, "r");
	result = day09_part2(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result == 0);
	return 0;
}
