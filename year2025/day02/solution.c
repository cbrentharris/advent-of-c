#include "solution.h"
#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long day02_part1(FILE *fp) {
	char line[512];
	// we only have a single line input
	fgets(line, sizeof(line), fp);

	char *outer_saveptr;
	char *inner_saveptr;

	char *token = strtok_r(line, ",", &outer_saveptr);
	long invalid_ids_sum = 0;
	while (token != NULL) {
		long lhs = atol(strtok_r(token, "-", &inner_saveptr));
		long rhs = atol(strtok_r(NULL, "-", &inner_saveptr)); for (long i = lhs ; i <= rhs ; i++) {
			int digits = num_digits(i);
			if (digits % 2 == 1) {
				continue;
			}
			long i_rhs = i % ((long) pow(10, digits / 2));
			long i_lhs = i;
			while (i_lhs > i_rhs) {
				i_lhs = i_lhs / 10;
			}
			if (i_rhs == i_lhs && num_digits(i_rhs) == digits / 2) {
				invalid_ids_sum += i;
			}
		}
		token = strtok_r(NULL, ",", &outer_saveptr);
	}
	return invalid_ids_sum;
}

int repeats(long n) {
	int digits = num_digits(n);
	int repeat_length = digits / 2;
	while (repeat_length > 0) {
		if (digits % repeat_length != 0) {
			repeat_length--;
			continue;
		}

		long local_n = n;
		int local_digits = digits;
		int possible_repeats = local_digits / repeat_length;

		long previous_repeat = n / (long) pow(10, local_digits - repeat_length);
		local_n = local_n % (long) pow(10, local_digits - repeat_length);
		local_digits -= repeat_length;
		int all_match = 1;
		for (int i = 1 ; i < possible_repeats ; i++) {
			long current_repeat = local_n / (long) pow(10, local_digits - repeat_length);
			local_n = local_n % (long) pow(10, local_digits - repeat_length);
			local_digits -= repeat_length;
			all_match = current_repeat == previous_repeat;
			
			if (!all_match) {
				break;
			}
			previous_repeat = current_repeat;
		}

		if (all_match) {
			return 1;
		}
		repeat_length--;
	}
	return 0;
}

long day02_part2(FILE *fp) {
	char line[512];
	fgets(line, sizeof(line), fp);

	char *outer_saveptr;
	char *inner_saveptr;

	char *token = strtok_r(line, ",", &outer_saveptr);
	long invalid_ids_sum = 0;

	while (token != NULL) {
		long lhs = atol(strtok_r(token, "-", &inner_saveptr));
		long rhs = atol(strtok_r(NULL, "-", &inner_saveptr));
		for (long i = lhs ; i <= rhs ; i++) {
			if (repeats(i)) {
				invalid_ids_sum += i;
			}
		}
		token = strtok_r(NULL, ",", &outer_saveptr);
	}
	return invalid_ids_sum;
}
