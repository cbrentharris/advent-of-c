#include "aoc.h"
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define BUFFER_SIZE 512

typedef struct {
	long x;
	long y;
} Point;

typedef struct {
	Point * a;
	Point * b;
} Segment;

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

int compare_segments_area(const void *a, const void *b) {
	const Segment * ra = a;
	const Segment * rb = b;
	long a_area = calculate_area(ra->a, ra->b);
	long b_area = calculate_area(rb->a, rb->b);
	if (a_area > b_area) {
		return -1;
	} else if (a_area < b_area) {
		return 1;
	} else {
		return 0;
	}
}

int point_on_segment(Point *p, Segment *e) {
	long x1 = e->a->x, y1 = e->a->y;
	long x2 = e->b->x, y2 = e->b->y;

	long vx1 = x2 - x1;
	long vy1 = y2 - y1;
	long vx2 = p->x - x1;
	long vy2 = p->y - y1;

	long cross = vx1 * vy2 - vy1 * vx2;
	if (cross != 0) {
		return 0;
	}
	if (p->x < MIN(x1, x2) || p->x > MAX(x1, x2) ||
			p->y < MIN(y1, y2) || p->y > MAX(y1, y2)) {
		return 0;
	}
	return 1;
}

size_t cast_ray_count(Point *a, Segment *edges, size_t edge_count) {
	for (size_t i = 0; i < edge_count; i++) {
		if (point_on_segment(a, &edges[i])) {
			return 1;
		}
	}

	size_t a_count = 0;
	for (size_t i = 0 ; i < edge_count ; i++) {
		Segment edge = edges[i];
		long y1 = edge.a->y;
		long y2 = edge.b->y;
		long x1 = edge.a->x;
		long x2 = edge.b->x;

		int y_cross = (y1 > a->y) != (y2 > a->y);
		if (y_cross) {
			double t = (double)(a->y - y1) / (double)(y2 - y1);
			double x_intersect = x1 + t * (double)(x2 - x1);
			if (x_intersect > (double)a->x) {
				a_count++;
			}
		}
	}
	return a_count;
}

int point_inside_or_on(Point *p, Segment *edges, size_t edge_count) {
	size_t count = cast_ray_count(p, edges, edge_count);
	return count % 2 == 1;
}

long orient(Point *a, Point *b, Point *c) {
	long ux = b->x - a->x;
	long uy = b->y - a->y;
	long vx = c->x - a->x;
	long vy = c->y - a->y;
	long cross = ux * vy - uy * vx;
	if (cross > 0) {
		return 1;
	}
	if (cross < 0) {
		return -1;
	}
	return 0;
}

int on_segment_closed(Point *a, Point *b, Point *p) {
	return p->x >= MIN(a->x, b->x) && p->x <= MAX(a->x, b->x) &&
	p->y >= MIN(a->y, b->y) && p->y <= MAX(a->y, b->y);
}

int segments_intersect(Point *a, Point *b, Point *c, Point *d) {
	int o1 = orient(a, b, c);
	int o2 = orient(a, b, d);
	int o3 = orient(c, d, a);
	int o4 = orient(c, d, b);

	if (o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0 &&
		o1 != o2 && o3 != o4) {
		return 1;
	}
	return 0;
}

int segment_inside_polygon(Segment *s, Segment *edges, size_t edge_count) {
	Point *a = s->a;
	Point *b = s->b;

	if (!point_inside_or_on(a, edges, edge_count)) {
		// If the segment corner isn't within the polygon reject
		return 0;
	}
	if (!point_inside_or_on(b, edges, edge_count)) {
		return 0;
	}

	for (size_t i = 0; i < edge_count; i++) {
		Segment *e = &edges[i];

		if (e->a == a || e->a == b || e->b == a || e->b == b) {
			// if a segment is an edge, then we are good.
			continue;
		}

		if (segments_intersect(a, b, e->a, e->b)) {
			return 0;
		}
	}
	return 1;
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
	free(points);
	return area;
}

long day09_part2(FILE *fp) {
	char buffer[BUFFER_SIZE];

	Point * red_corners = NULL;
	size_t count = 0;
	while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
		char * delim = ",";
		long x = atol(strtok(buffer, delim));
		long y = atol(strtok(NULL, delim));
		Point * temp = realloc(red_corners, sizeof(Point) * (count + 1));
		Point p = {0};
		p.x = x;
		p.y= y;
		temp[count] = p;
		count++;
		red_corners = temp;
	}

	Segment * edges = malloc(sizeof(Segment) * count);
	size_t edge_count = count;

	for (size_t i = 0 ; i < count ; i++) {
		size_t j = i + 1;
		if (j == count) {
			j = 0;
		}
		Segment s = {0};
		s.a = &red_corners[i];
		s.b = &red_corners[j];
		edges[i] = s;
	}

	size_t total_pairs = (size_t)count * (count - 1) / 2;
	Segment * corners = malloc(sizeof(Segment) * total_pairs);
	size_t corner_count = 0;
	for (size_t i = 0 ; i < count ; i++) {
		for (size_t j = i + 1 ; j < count ; j++) {
			Segment s = {0};
			s.a = &red_corners[i];
			s.b = &red_corners[j];
			corners[corner_count] = s;
			corner_count++;
		}
	}

	qsort(corners, total_pairs, sizeof(*corners), compare_segments_area);

	for(size_t i = 0 ; i < total_pairs ; i++) {
		Segment s = corners[i];
		Point * p1 = s.a;
		Point * p2 = s.b;
		long x_min = MIN(p1->x, p2->x);
		long y_min = MIN(p1->y, p2->y);
		long x_max = MAX(p1->x, p2->x);
		long y_max = MAX(p1->y, p2->y);

		Point c1 = {0};
		Point c2 = {0};
		Point c3 = {0};
		Point c4 = {0};

		c1.x = x_min;
		c1.y = y_min;

		c2.x = x_min;
		c2.y = y_max;

		c3.x = x_max;
		c3.y = y_min;

		c4.x = x_max;
		c4.y = y_max;

		Segment s1 = {0};
		s1.a = &c1;
		s1.b = &c2;
		Segment s2 = {0};
		s2.a = &c1;
		s2.b = &c3;
		Segment s3 = {0};
		s3.a = &c2;
		s3.b = &c4;
		Segment s4 = {0};
		s4.a = &c3;
		s4.b = &c4;

		if (segment_inside_polygon(&s1, edges, edge_count) &&
			segment_inside_polygon(&s2, edges, edge_count) &&
			segment_inside_polygon(&s3, edges, edge_count) &&
			segment_inside_polygon(&s4, edges, edge_count)) {
			return calculate_area(p1, p2);
		}
	}
	free(edges);
	free(corners);
	free(red_corners);
	return 0;
}

