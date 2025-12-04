#include "aoc.h"
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long day04_part1(FILE *fp) {
	char *buffer = NULL;
	size_t buffer_len = 0;
	char **grid = NULL;
	size_t num_rows = 0;

	while(getline(&buffer, &buffer_len, fp) != -1) {
		char **temp = realloc(grid, (num_rows + 1) * sizeof(char *));
		if (!temp) {
			perror("Reallocation failed for increasing grid size.");
			break;
		}
		buffer[strcspn(buffer, "\n")] = '\0';
		grid = temp;
		grid[num_rows] = strdup(buffer);
		num_rows++;
	}
	size_t num_cols = strlen(grid[0]);

	free(buffer);
	int reachable_rolls_of_paper = 0;
	for (int i = 0 ; i < (int) num_rows ; i++) {
		for (int j = 0 ; j < (int) num_cols ; j++) {
			if (grid[i][j] != '@') {
				continue;
			}
			int rolls_of_paper_adjacent = 0;

			int down = i + 1;
			int up = i - 1;
			int left = j - 1;
			int right = j + 1;

			if (up >= 0) {
				if (grid[up][j] == '@') {
					rolls_of_paper_adjacent++;
				}
				if (right < (int) num_cols) {
					if (grid[up][right] == '@') {
						rolls_of_paper_adjacent++;
					}
				}
				if (left >= 0) {
					if (grid[up][left] == '@') {
						rolls_of_paper_adjacent++;
					}
				}
			}
			if (down < (int) num_rows) {
				if (grid[down][j] == '@') {
					rolls_of_paper_adjacent++;
				}
				if (right < (int) num_cols) {
					if (grid[down][right] == '@') {
						rolls_of_paper_adjacent++;
					}
				}
				if (left >= 0) {
					if (grid[down][left] == '@') {
						rolls_of_paper_adjacent++;
					}
				}
			}
			if (right < (int) num_cols) {
				if (grid[i][right] == '@') {
					rolls_of_paper_adjacent++;
				}
			}
			if (left >= 0) {
				if (grid[i][left] == '@') {
					rolls_of_paper_adjacent++;
				}
			}
			if (rolls_of_paper_adjacent < 4) {
				reachable_rolls_of_paper++;
			}
		}

	}
	return reachable_rolls_of_paper;
}

long day04_part2(FILE *fp) {
	char *buffer = NULL;
	size_t buffer_len = 0;
	char **grid = NULL;
	size_t num_rows = 0;

	while(getline(&buffer, &buffer_len, fp) != -1) {
		char **temp = realloc(grid, (num_rows + 1) * sizeof(char *));
		if (!temp) {
			perror("Reallocation failed for increasing grid size.");
			break;
		}
		buffer[strcspn(buffer, "\n")] = '\0';
		grid = temp;
		grid[num_rows] = strdup(buffer);
		num_rows++;
	}
	size_t num_cols = strlen(grid[0]);

	free(buffer);
	int reachable_rolls_of_paper_total = 0;
	int reachable_rolls_of_paper = 0;
	do {
		reachable_rolls_of_paper = 0;
		for (int i = 0 ; i < (int) num_rows ; i++) {
			for (int j = 0 ; j < (int) num_cols ; j++) {
				if (grid[i][j] != '@') {
					continue;
				}
				int rolls_of_paper_adjacent = 0;

				int down = i + 1;
				int up = i - 1;
				int left = j - 1;
				int right = j + 1;

				if (up >= 0) {
					if (grid[up][j] == '@') {
						rolls_of_paper_adjacent++;
					}
					if (right < (int) num_cols) {
						if (grid[up][right] == '@') {
							rolls_of_paper_adjacent++;
						}
					}
					if (left >= 0) {
						if (grid[up][left] == '@') {
							rolls_of_paper_adjacent++;
						}
					}
				}
				if (down < (int) num_rows) {
					if (grid[down][j] == '@') {
						rolls_of_paper_adjacent++;
					}
					if (right < (int) num_cols) {
						if (grid[down][right] == '@') {
							rolls_of_paper_adjacent++;
						}
					}
					if (left >= 0) {
						if (grid[down][left] == '@') {
							rolls_of_paper_adjacent++;
						}
					}
				}
				if (right < (int) num_cols) {
					if (grid[i][right] == '@') {
						rolls_of_paper_adjacent++;
					}
				}
				if (left >= 0) {
					if (grid[i][left] == '@') {
						rolls_of_paper_adjacent++;
					}
				}
				if (rolls_of_paper_adjacent < 4) {
					reachable_rolls_of_paper++;
					grid[i][j] = '.';
				}
			}

		}
		reachable_rolls_of_paper_total += reachable_rolls_of_paper;
	} while (reachable_rolls_of_paper > 0);
	return reachable_rolls_of_paper_total;
}
