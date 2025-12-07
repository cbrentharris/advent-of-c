#include <stdio.h>
#include <string.h>
#include "aoc.h"
#include "solution.h"

int main(void) {
	char *sample_path = "year2025/day07/sample.txt";
	FILE *sample_fp = fopen(sample_path, "r");

	if (sample_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	long result = day07_part1(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 21);

	char *input_path = "year2025/day07/input.txt";
	FILE *input_fp = fopen(input_path, "r");
	if (input_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	result = day07_part1(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result == 1590);


	sample_fp = fopen(sample_path, "r");
	result = day07_part2(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 40);

	input_fp = fopen(input_path, "r");
	result = day07_part2(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result > 3661729930);
	AOC_ASSERT(result == 20571740188555);
	return 0;
}
