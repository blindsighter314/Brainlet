#ifndef BL_MATH_H_
#define BL_MATH_H_

extern unsigned char memory[5242880];
extern long blindex;
extern long memoryLimit;

void mathAdd(int numb) {
	memory[blindex] = (memory[blindex] + numb);
}

void mathSub(int numb) {
	memory[blindex] = (memory[blindex] - numb);
}

void mathProd(int numb) {
	memory[blindex] = (memory[blindex] * numb);
}

void mathDiv(int numb) {
	if (numb == 0) {
		printf("Error: Attempted to divide by 0");
		exit(0);
	}

	memory[blindex] = (memory[blindex] / numb);
}

void mathMod(int numb) {
	memory[blindex] = (memory[blindex] % numb);
}

void mathGraze(long start, long finish, unsigned char mode, int number) {
	if (start > memoryLimit || finish > memoryLimit || start < 0) {
		printf("Error: Attempted to graze outside of memroy partition.");
		exit(0);
	}

	long location = blindex;
	blindex = start;

	while (blindex <= finish) {
		if (mode == 0) {
            mathAdd(number);
        } else if (mode == 1) {
            mathSub(number);
        } else if (mode == 2) {
            mathProd(number);
        } else if (mode == 3) {
            mathDiv(number);
        } else if (mode == 4) {
            mathMod(number);
        }
        blindex++;
	}

	blindex = location;
}

void routeMath(char c[50][200]) {
	if (strcmp(c[0], "ADD") == 0) {
		if (c[1][0] == '\0') {
			mathAdd(1);
		} else {
			mathAdd(atoi(c[1]));
		}
	} else if (strcmp(c[0], "SUB") == 0) {
		if (c[1][0] == '\0') {
			mathSub(1);
		} else {
			mathSub(atoi(c[1]));
		}
	} else if (strcmp(c[0], "PROD") == 0 && c[1][0] != '\0') {
		mathProd(atoi(c[1]));
	} else if (strcmp(c[0], "DIV") == 0 && c[1][0] != '\0') {
		mathDiv(atoi(c[1]));
	} else if (strcmp(c[0], "MOD") == 0 && c[1][0] != '\0') {
		mathMod(atoi(c[1]));
	} else if (strcmp(c[0], "GRAZE") == 0&&c[1][0]!='\0'&&c[2][0]!= '\0'&&c[3][0]!= '\0' && c[4][0]!= '\0') {
		unsigned char mode = 0;
		if (strcmp(c[3], "ADD") == 0) {
			mode = 0;
		} else if (strcmp(c[3], "SUB") == 0) {
			mode = 1;
		}  else if (strcmp(c[3], "PROD") == 0) {
			mode = 2;
		}  else if (strcmp(c[3], "DIV") == 0) {
			mode = 3;
		}  else if (strcmp(c[3], "MOD") == 0) {
			mode = 4;
		}

		mathGraze(atoi(c[1]), atoi(c[2]), mode, atoi(c[4]));
	}
}

#endif
