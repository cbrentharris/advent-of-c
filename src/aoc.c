#include "aoc.h"
#include <math.h>

int positive_mod(int a, int m) {
	int r = a % m;
	if (r < 0) {
		r += m;
	}
	return r;
}

int num_digits(long n) {
	return (int) log10(n) + 1;
}
