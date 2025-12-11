#include "aoc.h"
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512
#define MEMO_SIZE 1024
#define INF 200000000L

typedef struct {
	int target_mask;
	int * masks;
	int * num_buttons_for_mask;
	size_t num_masks;
} Manual;

/**
 * remove the beginning and end characters
 */
char* trim_first_and_last(char *str) {
	str++;
	char * end = str + strlen(str) - 1;
	end--;
	end[1] = '\0';
	return str;
}

long fewest_presses(Manual * m, int mask, int * memo) {
	if (mask < 0 || mask >= MEMO_SIZE) {
		fprintf(stderr, "Need a larger memo size (mask=%d, memo_size=%d)\n", mask, MEMO_SIZE);
		exit(1);
	}

	if (mask == 0) {
		return 0;
	}

	if (memo[mask] != -1) {
		return memo[mask];
	}

	// don't go back down this mask route recursively as that would just cycle
	memo[mask] = INF;

	long best = INF;
	for (size_t i = 0; i < m->num_masks; i++) {
		int new_mask = mask ^ m->masks[i];
		long candidate = fewest_presses(m, new_mask, memo);
		if (candidate + 1 < best) {
			best = candidate + 1;
		}
	}
	memo[mask] = best;
	return best;
}

// ..##
// ##..
// becomes
// ####
// ..##
// ..##
// becomes
// ....
// so 1 1 becomes 0
// so 0 1 becomes 1
// so 0 0 becomes 0
// so 1 0 becomes 1

long day10_part1(FILE *fp) {
	char buffer[BUFFER_SIZE];
	int memo[MEMO_SIZE];

	long total_presses = 0;
	while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {
		char * outer_save;
		char * token = trim_first_and_last(strtok_r(buffer, " ", &outer_save));
		size_t len = strlen(token);
		int mask = 0;
		for (size_t i = 0 ; i < len ; i++) {
			int i_mask = 1 << i;
			if (token[i] == '#') {
				mask = mask | i_mask;
			}
		}
		Manual manual = {0};
		manual.target_mask = mask;
		int * masks = NULL;
		int * num_buttons_for_mask = NULL;
		size_t num_masks = 0;
		token = strtok_r(NULL, " ", &outer_save);
		while (token != NULL) {
			token = trim_first_and_last(token);
			char * inner_save;
			char * next_token = strtok_r(NULL, " ", &outer_save);
			char * inner_token = strtok_r(token, ",", &inner_save);
			if (next_token != NULL) {
				int * temp = realloc(masks, sizeof(int) * (num_masks + 1));
				int * temp2 = realloc(num_buttons_for_mask, sizeof(int) * (num_masks + 1));
				int mask = 0;
				while(inner_token != NULL) {
					int i = atoi(inner_token);
					mask |= 1 << i;
					inner_token = strtok_r(NULL, ",", &inner_save);
				}
				temp[num_masks] = mask;
				temp2[num_masks] = 1;
				masks = temp;
				num_buttons_for_mask = temp2;
				num_masks++;
			}
			token = next_token;
		}
		manual.masks = masks;
		manual.num_buttons_for_mask = num_buttons_for_mask;
		manual.num_masks = num_masks;
		for (int i = 0 ; i < MEMO_SIZE ; i++) {
			memo[i] = -1;
		}
		total_presses += fewest_presses(&manual, mask, memo);
		free(manual.masks);
		free(manual.num_buttons_for_mask);
	}
	return total_presses;
}

long day10_part2(FILE *fp) {
	return 0;
}

