#include "aoc.h"
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_LENGTH 4192

long day06_part1(FILE *fp) {
	char buffer[BUFFER_LENGTH];
	char *** input = NULL;
	size_t rows = 0;
	size_t columns = 0;

	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		buffer[strcspn(buffer, "\n")] = '\0';
		char *delim = " ";
		char *token = strtok(buffer, delim);

		char *** temp = realloc(input, sizeof(char **) * (rows + 1));
		columns = 0;
		char ** row = NULL;
		while (token != NULL) {
			char ** temp = realloc(row, sizeof(char *) * (columns + 1));
			temp[columns] = strdup(token);
			columns++;
			token = strtok(NULL, delim);
			row = temp;
		}
		temp[rows] = row;
		input = temp;
		rows++;
	}

	long result = 0;
	for (size_t col = 0; col < columns ; col++) {
		char operator = input[rows - 1][col][0];
		long intermediate_result = 0;
		if (operator == '*') {
			intermediate_result = 1;
		}
		for (size_t row = 0 ; row < rows - 1; row++) {
			if (operator == '*') {
				intermediate_result *= atol(input[row][col]);
			} else {
				intermediate_result += atol(input[row][col]);
			}
		}
		result += intermediate_result;
	}
	for (size_t row = 0; row < rows ; row++) {
		for (size_t col = 0 ; col < columns ; col++) {
			free(input[row][col]);
		}
		free(input[row]);
	}
	free(input);
	return result;
}

long day06_part2(FILE *fp) {
	char buffer[BUFFER_LENGTH];
	char ** input = NULL;
	size_t rows = 0;

	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		buffer[strcspn(buffer, "\n")] = '\0';
		char ** temp = realloc(input, sizeof(char *) * (rows + 1));
		temp[rows] = strdup(buffer);
		input = temp;
		rows++;
	}

	size_t len = strlen(input[rows - 1]);
	long result = 0;
	size_t operator_index = 0;
	while(operator_index < len) {
		size_t next_operator_index = operator_index + 1;
		size_t len = strlen(input[rows - 1]);
		while (next_operator_index < len && input[rows - 1][next_operator_index] == ' ') {
			next_operator_index++;
		}
		char operator = input[rows - 1][operator_index];
		long intermediate_result = 0;
		if (operator == '*') {
			intermediate_result = 1;
		}
		size_t max_size = next_operator_index - operator_index - 1;
		if (next_operator_index == len) {
			max_size++;
		}
		char ** numbers = malloc(sizeof(char *) * max_size);
		for (size_t num_col = 0 ; num_col < max_size; num_col++) {
			numbers[num_col] = "";
		}
		for (size_t num_col = 0; num_col < max_size ; num_col++) {
			for (size_t row = 0; row < rows - 1; row++) {
				char * num = numbers[num_col];
				size_t len = strlen(num);
				char * new_num = malloc(sizeof(char) * (len + 1));
				strcpy(new_num, num);
				char digit = input[row][operator_index + num_col];
				new_num[len] = digit;
				new_num[len + 1] = '\0';
				numbers[num_col] = new_num;
			}
			long num = atol(numbers[num_col]);
			free(numbers[num_col]);
			if (operator == '*') {
				intermediate_result *= num;
			} else {
				intermediate_result += num;
			}
		}
		free(numbers);
		result += intermediate_result;
		operator_index = next_operator_index;
	}
	for (size_t row = 0 ; row < rows ; row++) {
		free(input[row]);
	}
	free(input);
	return result;
}
