#include "aoc.h"

int positive_mod(int a, int m) {
	int r = a % m;
	if (r < 0) {
		r += m;
	}
	return r;
}
