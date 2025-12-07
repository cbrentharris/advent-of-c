#include "aoc.h"
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 512

long day07_part1(FILE *fp) {
	char buffer[BUFFER_SIZE];

	size_t len = 0;

	int *rays = NULL;

	long splits = 0;
	while(fgets(buffer, sizeof(buffer), fp) != NULL) {
		buffer[strcspn(buffer, "\n")] = '\0';
		len = strlen(buffer);
		int *next_rays = malloc(sizeof(int) * len);

		for (size_t col = 0 ; col < len ; col++) {
			next_rays[col] = 0;
		}

		if (rays == NULL) {
			rays = malloc(sizeof(int) * len);
			for (size_t col = 0 ; col < len ; col++) {
				rays[col] = 0;
			}
		}
		for (size_t column = 0 ; column < len ; column++) {
			if (buffer[column] == 'S') {
				next_rays[column] = 1;
			} else if (buffer[column] == '^' && rays[column] == 1) {
				splits++;
				next_rays[column] = 0;
				int previous = column - 1;
				size_t next = column + 1;
				if (previous >= 0 && buffer[previous] == '.') {
					next_rays[previous] = 1;
				}
				if (next < len && buffer[next] == '.') {
					next_rays[next] = 1;
				}
			} else {
				if (next_rays[column] != 1) {
					next_rays[column] = rays[column];
				}
			}
		}
		free(rays);
		rays = next_rays;
	}
	free(rays);
	return splits;
}

long day07_part2(FILE *fp) {
	char buffer[BUFFER_SIZE];

	size_t len = 0;

	long *rays = NULL;

	while(fgets(buffer, sizeof(buffer), fp) != NULL) {
		buffer[strcspn(buffer, "\n")] = '\0';
		len = strlen(buffer);
		long *next_rays = malloc(sizeof(long) * len);

		for (size_t col = 0 ; col < len ; col++) {
			next_rays[col] = 0;
		}

		if (rays == NULL) {
			rays = malloc(sizeof(long) * len);
			for (size_t col = 0 ; col < len ; col++) {
				rays[col] = 0;
			}
		}
		for (size_t column = 0 ; column < len ; column++) {
			if (buffer[column] == 'S') {
				next_rays[column] = 1;
			} else if (buffer[column] == '^' && rays[column] > 0) {
				next_rays[column] = 0;
				int previous = column - 1;
				size_t next = column + 1;
				if (previous >= 0 && buffer[previous] == '.') {
					next_rays[previous] += rays[column];
				}
				if (next < len && buffer[next] == '.') {
					next_rays[next] += rays[column];
				}
			} else {
				next_rays[column] += rays[column];
			}
		}
		free(rays);
		rays = next_rays;
	}
	long timelines = 0;
	for (size_t col = 0; col < len ; col++) {
		timelines += rays[col];
	}
	free(rays);
	return timelines;
}
