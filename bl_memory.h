#ifndef BL_MEMORY_H_
#define BL_MEMORY_H_

extern unsigned char memory[5242880];
extern long blindex;
extern long memoryLimit;
extern long highestAllocation;

void memoryPartition(long numb) {
	if (numb > 5242880) {
		printf("Error: Memory allocated has exceeded the hard limit of 5242880 cells.");
		exit(0);
	}

	if (numb < 0) {
		printf("Error: Memory allocated is below 0.");
		exit(0);
	}

	memoryLimit = numb;

	if (memoryLimit > highestAllocation) {
		highestAllocation = memoryLimit;
	}

	if (memoryLimit < highestAllocation) {
		for (int i = (memoryLimit + 1); i <= highestAllocation; i++) {
			memory[i] = 0;
		}
	}

	if (blindex > memoryLimit) {
		blindex = memoryLimit;
	}
}

void memoryPartitionUp(long numb) {
	memoryLimit = (memoryLimit + numb);

	if (memoryLimit > 5242880) {
		printf("Error: Memory allocated has exceeded the hard limit of 5242880 cells.");
		exit(0);
	}

	if (memoryLimit > highestAllocation) {
		highestAllocation = memoryLimit;
	}
}

void memoryPartitionDown(long numb) {
	memoryLimit = (memoryLimit - numb);

	if (memoryLimit < 0) {
		printf("Error: Memory allocated is below 0.");
		exit(0);
	}

	for (int i = (memoryLimit + 1); i <= highestAllocation; i++) {
		memory[i] = 0;
	}

	if (memoryLimit < highestAllocation) {
		highestAllocation = memoryLimit;
	}

	if (blindex > memoryLimit) {
		blindex = memoryLimit;
	}
}

void memoryStep(long numb) {
	blindex = (blindex + numb);

	if (blindex < 0 || blindex > memoryLimit) {
		printf("Error: Attempted to step out of memory index.");
		exit(0);
	}
}

void memoryJump(long numb) {
	if (numb < 0 || numb > memoryLimit) {
		printf("Error: Attempted to jump out of memory index.");
		exit(0);
	}

	blindex = numb;
}

void memoryRange(long upper, unsigned char mode) {
	if (blindex + upper - 1 > memoryLimit) {
		printf("Error: Attempted to erect range exceeding memory limit.");
		exit(0);
	}

	long scope = 1;

	if (mode != 0) {
		scope = upper;
	}

	for (long i = blindex; i <= (blindex + (upper - 1)); i++) {
		memory[i] = (unsigned char) scope;

		if (mode == 0) {
			scope++;
		} else {
			scope--;
		}
	}
}

void routeMemory(char c[50][200]) {
	if (strcmp(c[0], "PARTITION") == 0) {
		if (c[1][0] != '\0') {
			if (strcmp(c[1], "UP") == 0) {
				if (c[2][0] == '\0') {
					memoryPartitionUp(1);
				} else {
					memoryPartitionUp(atol(c[2]));
				}
			} else if (strcmp(c[1], "DOWN") == 0) {
				if (c[2][0] == '\0') {
					memoryPartitionDown(1);
				} else {
					memoryPartitionDown(atol(c[2]));
				}
			} else {
				memoryPartition(atol(c[1]) - 1);
			}
		} else {
			memoryPartition(0);
		}
	} else if (strcmp(c[0], "STEP") == 0) {
		long amount = 1;

		if (c[1][0] != '\0') {
			if (c[2][0] != '\0') {
				amount = atol(c[2]);
			}

			if (strcmp(c[1], "LEFT") == 0) {
				amount = (amount * -1);
			}
		}

		memoryStep(amount);
	} else if (strcmp(c[0], "JUMP") == 0) {
		if (c[1][0] != '\0') {
			memoryJump(atol(c[1]));
		} else {
			memoryJump(0);
		}
	} else if (strcmp(c[0], "SET") == 0) {
		if (c[1][0] != '\0') {
			memory[blindex] = ((unsigned char) atoi(c[1]));
		} else {
			memory[blindex] = 0;
		}
	} else if (strcmp(c[0], "RANGE") == 0) {
		long amount = 1;

		if (c[2][0] != '\0') {
			amount = atol(c[2]);
		}

		if (strcmp(c[1], "ASC") == 0) {
			memoryRange(amount, 0);
		} else {
			memoryRange(amount, 1);
		}
	} else if (strcmp(c[0], "TYPE") == 0 && c[1][0] != '\0') {
		if (c[2][0] == '\0') {
			memory[blindex] = (unsigned char)c[1][0];
		} else {
			memory[atol(c[1])] = (unsigned char)c[2][0];
		}
	} else if (strcmp(c[0], "TYPECAST") == 0 && c[1][0] != '\0') {
		int word = 1;
		int letter = 0;
		long header = blindex;

		while (c[word][0] != '\0') {
			int letter = 0;

			while (c[word][letter] != '\0') {
				if (blindex > memoryLimit) {
					printf("Error: Attempted to erect typecast exceeding memory limit.");
					exit(0);
				}

				memory[header] = ((unsigned char) c[word][letter]);
				header++;
				letter++;
			}

			word++;

			if (c[word][0] != '\0') {
				memory[header] = ' ';
				header++;
			}
		}
	}
}

#endif
