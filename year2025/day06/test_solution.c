#include <stdio.h>
#include <string.h>
#include "aoc.h"
#include "solution.h"

int main(void) {
	char *sample_path = "year2025/day06/sample.txt";
	FILE *sample_fp = fopen(sample_path, "r");

	if (sample_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	long result = day06_part1(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 4277556);

	char *input_path = "year2025/day06/input.txt";
	FILE *input_fp = fopen(input_path, "r");
	if (input_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	result = day06_part1(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result == 6172481852142);


	sample_fp = fopen(sample_path, "r");
	result = day06_part2(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 3263827);

	input_fp = fopen(input_path, "r");
	result = day06_part2(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result == 10188206723429);
	return 0;
}
