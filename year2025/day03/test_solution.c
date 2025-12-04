#include <stdio.h>
#include <string.h>
#include "aoc.h"
#include "solution.h"

int main() {
	char *sample_path = "year2025/day03/sample.txt";
	FILE *sample_fp = fopen(sample_path, "r");

	if (sample_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	long result = day03_part1(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 357);

	char *input_path = "year2025/day03/input.txt";
	FILE *input_fp = fopen(input_path, "r");
	if (input_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	result = day03_part1(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result == 16946);


	sample_fp = fopen(sample_path, "r");
	result = day03_part2(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 3121910778619);

	input_fp = fopen(input_path, "r");
	result = day03_part2(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result == 168627047606506);
	return 0;
}
