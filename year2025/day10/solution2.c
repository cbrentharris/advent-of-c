#include "aoc.h"
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512

typedef struct {
	char * diagram;
	int ** buttons;
	size_t * button_dimensions;
	int * joltage_requirements;
	size_t joltage_length;
	size_t button_count;
} Manual;

long find_fewest_presses_helper(Manual * m, char * curr, int current_presses) {
	if (current_presses > 100) {
		return current_presses;
	}
	size_t len = strlen(curr);
	int all_match = 1;
	int distance = 0;
	for (size_t i = 0 ; i < len ; i++) {
		all_match = all_match && m->diagram[i] == curr[i];
		distance += m->diagram[i] != curr[i];
	}
	if (all_match) {
		return current_presses;
	}

	long fewest = 1000000000;
	for(size_t i = 0 ; i < m->button_count ; i++) {
		char * dup = strdup(curr);
		int * buttons = m->buttons[i];
		for (size_t j = 0  ; j < (m->button_dimensions[i]) ; j++) {
			if (dup[buttons[j]] == '.') {
				dup[buttons[j]] = '#';
			} else {
				dup[buttons[j]] = '.';
			}
		}
		int new_distance = 0;
		for (size_t i = 0 ; i < len ; i++) {
			new_distance += (m->diagram[i] != dup[i]);
		}
		if (new_distance <= distance) {
			fewest = MIN(fewest, find_fewest_presses_helper(m, dup, current_presses + 1)); 
		}
		free(dup);
	}
	return fewest;
}

long find_fewest_presses(Manual * m) {
	char * dup = strdup(m->diagram);
	size_t len = strlen(dup);
	for(size_t i = 0 ; i < len ; i++) {
		dup[i] = '.';
	}
	long fewest = find_fewest_presses_helper(m, dup, 0);
	free(dup);
	return fewest;
}


long day10_part1(FILE *fp) {
	char buffer[BUFFER_SIZE];

	Manual * manuals = NULL;
	long fewest_presses = 0;
	while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {
		Manual manual = {0};
		char * outer_save;
		char * token = strtok_r(buffer, " ", &outer_save);
		size_t len = strlen(token);
		memmove(token, token + 1, len - 2);
		token[len - 2] = '\0';
		manual.diagram = token;
		size_t button_count = 0;
		int ** buttons = NULL;
		size_t * button_dimensions = NULL;
		int * joltage_requirements = NULL;
		size_t joltage_length = 0;
		token = strtok_r(NULL, " ", &outer_save);
		while (token != NULL) {
			char * inner_save;
			char * next_token = strtok_r(NULL, " ", &outer_save);
			size_t len = strlen(token);
			memmove(token, token + 1, len - 2);
			token[len - 2] = '\0';
			char * inner_token = strtok_r(token, ",", &inner_save);
			if (next_token == NULL) {
				// parse joltage requirements
				while (inner_token != NULL) {
					int * temp = realloc(joltage_requirements, sizeof(int) * (joltage_length + 1));
					int joltage = atoi(inner_token);
					temp[joltage_length] = joltage;
					joltage_length++;
					joltage_requirements = temp;
					inner_token = strtok_r(NULL, ",", &inner_save);
				}
			} else {
				// parse button
				// strip parens
				int ** temp = realloc(buttons, sizeof(int *) * (button_count + 1));
				size_t * temp2 = realloc(button_dimensions, sizeof(size_t) * (button_count + 1));
				size_t local_count = 0;
				int * button_local = NULL;
				while(inner_token != NULL) {
					int b = atoi(inner_token);
					//printf("b: %d, inner: %s\n", b, inner_token);
					int * temp3 = realloc(button_local, sizeof(int) * (local_count + 1));
					temp3[local_count] = b;
					local_count++;
					button_local = temp3;
					inner_token = strtok_r(NULL, ",", &inner_save);
				}
				temp[button_count] = button_local;
				temp2[button_count] = local_count;
				buttons = temp;
				button_dimensions = temp2;
				button_count++;
			}
			token = next_token;
			//free(inner_token);
			//free(next_token);
		}
		manual.button_count = button_count;
		manual.buttons = buttons;
		manual.button_dimensions = button_dimensions;
		manual.joltage_requirements = joltage_requirements;
		manual.joltage_length = joltage_length;
		fewest_presses += find_fewest_presses(&manual);
		printf("Fewest: %ld\n", fewest_presses);
		for (size_t i = 0 ; i < button_count ; i++) {
			free(buttons[i]);
		}
		free(buttons);
		free(button_dimensions);
		free(joltage_requirements);
	}
	return fewest_presses;
}

long day10_part2(FILE *fp) {
	return 0;
}

