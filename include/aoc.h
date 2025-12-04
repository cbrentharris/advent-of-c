#ifndef AOC_H
#define AOC_H

#include <stddef.h>

int positive_mod(int a, int m);

int num_digits(long n);

/* Simple assert macro that shows file:line. */
#define AOC_ASSERT(cond) do {                             \
    if (!(cond)) {                                        \
        fprintf(stderr, "Assertion failed: %s (%s:%d)\n", \
                #cond, __FILE__, __LINE__);               \
        return 1;                                         \
    }                                                     \
} while (0)

#endif
