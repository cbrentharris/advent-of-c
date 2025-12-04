#include <stdio.h>
#include <string.h>
#include "aoc.h"
#include "solution.h"

int main() {
	char *sample_path = "year2025/day02/sample.txt";
	FILE *sample_fp = fopen(sample_path, "r");

	if (sample_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	long result = day02_part1(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 1227775554);

	char *input_path = "year2025/day02/input.txt";
	FILE *input_fp = fopen(input_path, "r");
	if (input_fp == NULL) {
		perror("Error opening file.");
		return 1;
	}

	result = day02_part1(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result == 28844599675);


	sample_fp = fopen(sample_path, "r");
	result = day02_part2(sample_fp);
	fclose(sample_fp);
	AOC_ASSERT(result == 4174379265);

	input_fp = fopen(input_path, "r");
	result = day02_part2(input_fp);
	fclose(input_fp);
	AOC_ASSERT(result == 48778605167);
	return 0;
}
