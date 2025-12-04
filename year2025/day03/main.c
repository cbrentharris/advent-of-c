#include <stdio.h>
#include <stdlib.h>
#include "aoc.h"
#include "solution.h"

int main(int argc, char **argv) {
	const char *path = (argc > 1) ? argv[1] : "input.txt";
	FILE *fp = fopen(path, "rb");
	if (fp == NULL) {
		perror("Error opening file");
		return 1;
	}

	long p1 = day03_part1(fp);
	fclose(fp);

	fp = fopen(path, "rb");
	long p2 = day03_part2(fp);
	fclose(fp);

	printf("Part 1: %ld, Part 2: %ld\n", p1, p2);
	return 0;
}
