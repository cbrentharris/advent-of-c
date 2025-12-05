#include "aoc.h"
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long day05_part1(FILE *fp) {
	char buffer[256];

	long **ranges = NULL;
	size_t range_count = 0;
	int parsing_ranges = 1;
	int fresh_count = 0;
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		int len = strlen(buffer);
		parsing_ranges = strcspn(buffer, "-") != strlen(buffer);
		
		if (parsing_ranges) {
			long **temp = realloc(ranges, (range_count + 1) * sizeof(long *));
			if (temp == NULL) {
				perror("Error allocating memory for ranges.");
				return 1;
			}
			char *token = strtok(buffer, "-");
			long lhs = atol(token);
			token = strtok(NULL, "-");
			long rhs = atol(token);
			temp[range_count] = malloc(sizeof(long) * 2);
			temp[range_count][0] = lhs;
			temp[range_count][1] = rhs;
			range_count++;
			ranges = temp;
		} else if (len > 1) { // skip empty line
			long id = atol(buffer);
			for (size_t i = 0 ; i < range_count ; i++) {
				long *range = ranges[i];
				long lhs = range[0];
				long rhs = range[1];
				if (lhs <= id && rhs >= id) {
					fresh_count++;
					break;
				}
			}
		}
	}
	for (size_t i = 0 ; i < range_count ; i++) {
		free(ranges[i]);
	}
	free(ranges);
	return fresh_count;
}

int compare_range(const void *a, const void *b) {
    long * const *ra = a;
    long * const *rb = b;

    if ((*ra)[0] < (*rb)[0]) return -1;
    if ((*ra)[0] > (*rb)[0]) return 1;
    if ((*ra)[1] < (*rb)[1]) return -1;
    if ((*ra)[1] > (*rb)[1]) return 1;
    return 0;
}

int overlaps(long *a, long *b) { 
	long a_lhs = a[0];
	long b_lhs = b[0];

	long a_rhs = a[1];
	long b_rhs = b[1];
	
	// let's do the following cases:
	// 1, 3 -- 2, 4
	// 1, 5 -- 2, 3
	// then flip
	return (a_lhs <= b_lhs && a_rhs >= b_lhs)
		|| (b_lhs <= a_lhs && b_rhs >= a_lhs);
}

void merge(long *src, long *dst) {
	long src_lhs = src[0];
	long dst_lhs = dst[0];

	long src_rhs = src[1];
	long dst_rhs = dst[1];

	dst[0] = MIN(src_lhs, dst_lhs);
	dst[1] = MAX(src_rhs, dst_rhs);
}

long day05_part2(FILE *fp) {
	char buffer[256];

	long **ranges = NULL;
	size_t range_count = 0;
	int parsing_ranges = 1;
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		parsing_ranges = strcspn(buffer, "-") != strlen(buffer);
		
		if (parsing_ranges) {
			long **temp = realloc(ranges, (range_count + 1) * sizeof(long *));
			if (temp == NULL) {
				perror("Error allocating memory.");
				return 0;
			}
			char *token = strtok(buffer, "-");
			long lhs = atol(token);
			token = strtok(NULL, "-");
			long rhs = atol(token);
			temp[range_count] = malloc(sizeof(long) * 2);
			temp[range_count][0] = lhs;
			temp[range_count][1] = rhs;
			range_count++;
			ranges = temp;
		}
	}
	// sort ranges
	qsort(ranges, range_count, sizeof(long*), compare_range);
	// merge ranges
	long **merged_ranges = malloc(sizeof(long *));
	merged_ranges[0] = malloc(sizeof(long) * 2);
	merged_ranges[0][0] = ranges[0][0];
	merged_ranges[0][1] = ranges[0][1];
	size_t merged_range_count = 1;
	for (size_t i = 1 ; i < range_count; i++) {
		long *range = ranges[i];
		long *merge_range = merged_ranges[merged_range_count - 1];
		if (overlaps(range, merge_range)) {
			merge(range, merge_range);
		} else {
			long **temp = realloc(merged_ranges, sizeof(long *) * (merged_range_count + 1));
			if (temp == NULL) {
				perror("Error allocating memory.");
				return 0;
			}
			temp[merged_range_count] = malloc(sizeof(long) * 2);
			temp[merged_range_count][0] = range[0];
			temp[merged_range_count][1] = range[1];
			merged_range_count++;
			merged_ranges = temp;
		}
	}

	for (size_t i = 0; i < range_count ; i++) {
		long *range = ranges[i];
		free(range);
	}
	free(ranges);


	long fresh_ids = 0;
	// iterate and sum ranges
	for (size_t i = 0 ; i < merged_range_count; i++) {
		long *range = merged_ranges[i];
		fresh_ids += (range[1] - range[0] + 1);
	}
	for (size_t i = 0 ; i < merged_range_count ; i++) {
		long *range = merged_ranges[i];
		free(range);
	}
	free(merged_ranges);
	return fresh_ids;
}
