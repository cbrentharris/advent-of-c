#include "solution.h"
#include "aoc.h"
#include <stdlib.h>

long day01_part1(FILE *fp) {
        char line[256];
        int dialPosition = 50;
        int dialLength = 100;
        int password = 0;
        while (fgets(line, sizeof(line), fp)) {
                char direction = line[0];
                int magnitude = atoi(line + 1);
                dialPosition = positive_mod(direction == 'R' ? dialPosition + magnitude : dialPosition - magnitude, dialLength);
		if (dialPosition == 0) {
			password++;
		}
        }
	return password;
}

long day01_part2(FILE *fp) {
        char line[256];
        int dialPosition = 50;
        int dialLength = 100;
        int password = 0;
        while (fgets(line, sizeof(line), fp)) {
                char direction = line[0];
                int magnitude = atoi(line + 1);
                int newDialPosition = direction == 'R' ? dialPosition + magnitude : dialPosition - magnitude;
                if (newDialPosition >= dialLength) {
                        password += newDialPosition / dialLength;
                } else if (newDialPosition <= 0 && dialPosition > 0) {
                        password += -1 * (newDialPosition / dialLength) + 1;
                } else if (newDialPosition <= -100) {
                        password += -1 * (newDialPosition / dialLength);
                }
                dialPosition = positive_mod(newDialPosition, dialLength);
        }
	return password;
}
