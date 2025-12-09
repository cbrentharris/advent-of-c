#include "aoc.h"
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 512

typedef struct {
	long x;
	long y;
} Point;

long delta(long x, long y) {
	if (x > y) {
		return x - y;
	} else {
		return y - x;
	}
}

long calculate_area(Point * p1, Point * p2) {
	long x_diff = delta(p1->x, p2->x) + 1;
	long y_diff = delta(p1->y, p2->y) + 1;
	return x_diff * y_diff;
}

long day09_part1(FILE *fp) {
	char buffer[BUFFER_SIZE];

	Point * points = NULL;
	size_t count = 0;
	while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
		char * delim = ",";
		long x = atol(strtok(buffer, delim));
		long y = atol(strtok(NULL, delim));
		Point * temp = realloc(points, sizeof(Point) * (count + 1));
		Point p = {0};
		p.x = x;
		p.y = y;
		temp[count] = p;
		count++;
		points = temp;
	}
	long area = 0;
	for (size_t i = 0 ; i < count ; i++) {
		Point p1 = points[i];
		for (size_t j = i + 1 ; j < count ; j++) {
			Point p2 = points[j];
			area = MAX(area, calculate_area(&p1, &p2));
		}
	}
	return area;
}

long day09_part2(FILE *fp) {
	return 0;
}
