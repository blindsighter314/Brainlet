#ifndef BL_RAND_H_
#define BL_RAND_H_

extern unsigned char memory[5242880];
extern long blindex;

// https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand

void routeRand(char c[50][200]) {
	if (strcmp(c[0], "RAND") == 0) {
		srand(time(NULL));
		if (c[1][0] == '\0') {
			memory[blindex] = (0 + rand() / (RAND_MAX / 256) + 1);
		} else {
			memory[blindex] = (atoi(c[1]) + rand() / (RAND_MAX / (atoi(c[2]) - atoi(c[1]) + 1) + 1));
		}
	}
}

#endif
