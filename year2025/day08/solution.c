#include "aoc.h"
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 512
#define DIMENSIONS 3

typedef struct {
	int id;
	long x;
	long y;
	long z;
} JunctionBox;

typedef struct {
	int count;
	int counted;
} Circuit;

typedef struct {
	JunctionBox *a;
	JunctionBox *b;
	double distance;
} Distance;

double euclidean_distance(const JunctionBox *a, const JunctionBox *b) {
	return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + pow(a->z - b->z, 2)); 
}

int compare_distances(const void *a, const void *b) {
	const Distance * ra = a;
	const Distance * rb = b;
	if (ra->distance < rb->distance) {
		return -1;
	} else if (ra->distance > rb->distance) {
		return 1;
	} else {
		return 0;
	}
}

void merge(Circuit ** circuits, Circuit * a, Circuit * b, size_t circuit_count) {
	a->count = b->count + a->count;
	for (size_t i = 0; i < circuit_count ; i++) {
		if(circuits[i] == b) {
			circuits[i] = a;
		}
	}
	free(b);
}

int compare_circuits(const void *a, const void *b) {
	Circuit * const *ra = a;
	Circuit * const *rb = b;
	if (*ra == *rb) {
		return 0;
	}

	if (*ra == NULL) {
		return 1;
	}
	if (*rb == NULL) {
		return -1;
	}

	if ((*ra)->count > (*rb)->count) {
		return -1;
	} else if ((*ra)->count < (*rb)->count) {
		return 1;
	} else {
		return 0; }
}

/**
 * d(p, q) = sqrt((p1 - q1)^2 + (p2 - q2)^2 + ... + (pn - qn)^2)
 */
long day08_part1(FILE *fp, int connections_to_make) {
	char buffer[BUFFER_SIZE];
	char *delim = ",";
	size_t num_boxes = 0;
	JunctionBox * boxes = NULL;
	while(fgets(buffer, sizeof(buffer), fp) != NULL) {
		JunctionBox *temp = realloc(boxes, (num_boxes + 1) * sizeof(JunctionBox));
		if (!temp) {
			perror("Error allocating memory to create junction box array.");
			exit(1);
		}
		JunctionBox box = {0};
		box.x = atoi(strtok(buffer, delim));
		box.y = atoi(strtok(NULL, delim));
		box.z = atoi(strtok(NULL, delim));
		box.id = num_boxes;
		temp[num_boxes] = box;
		boxes = temp;
		num_boxes++;
	}
	Distance * distances = NULL;
	size_t pairs = 0;
	for (size_t i = 0 ; i < num_boxes ; i++) {
		for (size_t j = i + 1 ; j < num_boxes ; j++) {
			Distance * temp = realloc(distances, (pairs + 1) * sizeof(Distance));
			Distance distance = {0};
			distance.a = &boxes[i];
			distance.b = &boxes[j];
			distance.distance = euclidean_distance(distance.a, distance.b); temp[pairs] = distance;
			distances = temp;
			pairs++;
		}
	}


	Circuit **circuits = malloc(sizeof(Circuit *) * num_boxes);
	for (size_t i = 0 ; i < num_boxes ; i++) {
		circuits[i] = NULL;
	}

	qsort(distances, pairs, sizeof(*distances), compare_distances);
	size_t pair_index = 0;
	int connections_made = 0;
	while (connections_made < connections_to_make) {
		Distance d = distances[pair_index];
		Circuit *a = circuits[d.a->id];
		Circuit *b = circuits[d.b->id];
		if (a == NULL && b == NULL) {
			Circuit *c = malloc(sizeof(Circuit));
			c->counted = 0;
			c->count = 2;
			circuits[d.a->id] = c;
			circuits[d.b->id] = c;
		} else if (a == NULL) {
			Circuit * c = circuits[d.b->id];
			c->count = c->count + 1;
			circuits[d.a->id] = c;
		} else if (b == NULL) {
			Circuit * c = circuits[d.a->id];
			c->count = c->count + 1;
			circuits[d.b->id] = c;
		} else if (a != b) {
			merge(circuits, a, b, num_boxes);
		}
		pair_index++;
		connections_made++;
	}


	qsort(circuits, num_boxes, sizeof(*circuits), compare_circuits);
	int multiplications = 0;
	int target_multiplications = 3;
	long result = 1;
	Circuit * previous = NULL;
	for (size_t i = 0; i < num_boxes ; i++) {
		if (multiplications == target_multiplications) {
			break;
		}
		Circuit * c = circuits[i];
		if (c == previous) {
			continue;
		}
		result *= c->count;
		multiplications++;
		previous = c;
	}
	free(distances);
	free(boxes);
	return result;
}

long day08_part2(FILE *fp) {
	char buffer[BUFFER_SIZE];
	char *delim = ",";
	size_t num_boxes = 0;
	JunctionBox * boxes = NULL;
	while(fgets(buffer, sizeof(buffer), fp) != NULL) {
		JunctionBox *temp = realloc(boxes, (num_boxes + 1) * sizeof(JunctionBox));
		if (!temp) {
			perror("Error allocating memory to create junction box array.");
			exit(1);
		}
		JunctionBox box = {0};
		box.x = atoi(strtok(buffer, delim));
		box.y = atoi(strtok(NULL, delim));
		box.z = atoi(strtok(NULL, delim));
		box.id = num_boxes;
		temp[num_boxes] = box;
		boxes = temp;
		num_boxes++;
	}
	Distance * distances = NULL;
	size_t pairs = 0;
	for (size_t i = 0 ; i < num_boxes ; i++) {
		for (size_t j = i + 1 ; j < num_boxes ; j++) {
			Distance * temp = realloc(distances, (pairs + 1) * sizeof(Distance));
			Distance distance = {0};
			distance.a = &boxes[i];
			distance.b = &boxes[j];
			distance.distance = euclidean_distance(distance.a, distance.b);
			temp[pairs] = distance;
			distances = temp;
			pairs++;
		}
	}


	Circuit **circuits = malloc(sizeof(Circuit *) * num_boxes);
	for (size_t i = 0 ; i < num_boxes ; i++) {
		circuits[i] = NULL;
	}

	qsort(distances, pairs, sizeof(*distances), compare_distances);
	size_t pair_index = 0;
	size_t num_circuits = num_boxes;
	while (num_circuits > 1) {
		Distance d = distances[pair_index];
		Circuit *a = circuits[d.a->id];
		Circuit *b = circuits[d.b->id];
		if (a == NULL && b == NULL) {
			Circuit *c = malloc(sizeof(Circuit));
			c->counted = 0;
			c->count = 2;
			circuits[d.a->id] = c;
			circuits[d.b->id] = c;
			num_circuits--;
		} else if (a == NULL) {
			Circuit * c = circuits[d.b->id];
			c->count = c->count + 1;
			circuits[d.a->id] = c;
			num_circuits--;
		} else if (b == NULL) {
			Circuit * c = circuits[d.a->id];
			c->count = c->count + 1;
			circuits[d.b->id] = c;
			num_circuits--;
		} else 	if (a != b) {
			merge(circuits, a, b, num_boxes);
			num_circuits--;
		}
		pair_index++;
	}
	Distance d = distances[pair_index - 1];
	return d.a->x * d.b->x;
}
