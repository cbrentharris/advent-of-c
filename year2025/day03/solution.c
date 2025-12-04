#include "aoc.h"
#include "solution.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

long day03_part1(FILE *fp) {
	char buffer[256];

	int sum = 0;
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		int len = strlen(buffer) - 1; // ignore \n
		int a = -1;
		int b = -1;
		for (int i = 0 ; i < len ; i++) {
			int digit = buffer[i] - '0';
			if (digit > a && i < len - 1) {
				a = digit;
				b = buffer[i + 1] - '0';
			} else if (digit > b) {
				b = digit;
			}
		}
		sum += (10 * a + b);
	}
	return sum;
}

long day03_part2(FILE *fp) {
	char buffer[256];
	long sum = 0;

	while(fgets(buffer, sizeof(buffer), fp) != NULL) {
		int len = strlen(buffer) - 1; // ignore  \n
		int joltage_length = 12;
		char joltage[joltage_length];
		int joltage_index[joltage_length];
		for (int i = 0 ; i < joltage_length ; i++) {
			joltage[i] = buffer[i];
			joltage_index[i] = i;
		}

		for (int i = 0 ; i < len ; i++) {
			char digit = buffer[i];

			int joltage_remaining = MIN(joltage_length, len - i - 1);
			int start = MAX(joltage_length - joltage_remaining - 1, 0);
			for (int j = start ; j < joltage_length ; j++) {
				if (digit > joltage[j]) {
					int ok = 1;
					for (int k = 0; k < j; k++) {
						if (joltage_index[k] >= i) {
							ok = 0;
							break;
						}
					}
					if (!ok) {
						break;
					}
					joltage[j] = digit;
					joltage_index[j] = i;

					int i_offset = 1;

					for (int k = j + 1 ; k < joltage_length ; k++) {
						joltage[k] = buffer[i + i_offset++];
						joltage_index[k] = i + i_offset;
					}
					break;
				}
			}
		}

		long joltage_sum = 0;

		for (int i = 0 ; i < joltage_length ; i++) {
			joltage_sum += ((long) pow(10, i)) * (joltage[joltage_length - i - 1] - '0');
		}
		sum += joltage_sum;
	}
	return sum;
}
