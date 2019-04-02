#ifndef BL_IO_H_
#define BL_IO_H_

extern unsigned char memory[5242880];
extern long blindex;
extern long memoryLimit;

void ioPrint(unsigned char mode, unsigned char single) {
	// 0: ASCII, 1: DECIMAL, 2: BINARY
	if (single == 1) {
		if (mode == 0) {
			printf("%c", memory[blindex]);
		} else if (mode == 1) {
			printf("%d", memory[blindex]);
		} else if (mode == 2) {
			unsigned char bin[8] = {0, 0, 0, 0, 0, 0, 0, 0};
			unsigned char copier = memory[blindex];
			unsigned char i = 0;

			while (copier > 0) {
				bin[i] = (copier % 2);
				copier = (copier / 2);
				i++;
			}

			for (int b = 0; b <= 7; b++) {
				printf("%d", bin[b]);
			}
		} else if (mode == 3) {
			printf("%X", memory[blindex]);
		}
	} else {
		for (int i = 0; i <= memoryLimit; i++) {
			if (mode == 0) {
				printf("%c", memory[i]);
			} else if (mode == 1) {
				if (i == blindex) {
					printf("[%d]", memory[i]);
				} else {
					printf(" %d ", memory[i]);
				}
			} else if (mode == 2) {
				unsigned char bin[8] = {0, 0, 0, 0, 0, 0, 0, 0};
				unsigned char copier = memory[i];
				unsigned char binIndex = 0;

				while (copier > 0) {
					bin[binIndex] = (copier % 2);
					copier = (copier / 2);
					binIndex++;
				}

				if (i == blindex) {
					printf("[");
				} else {
					printf(" ");
				}

				for (int b = 0; b <= 7; b++) {
					printf("%d", bin[b]);
				}

				if (i == blindex) {
					printf("]");
				} else {
					printf(" ");
				}

			} else if (mode == 3) {
				if (i == blindex) {
					printf("[%X]", memory[i]);
				} else {
					printf(" %X ", memory[i]);
				}
			}
		}

		printf("\n");
	}
}

void ioInput(unsigned char mode) {
	if (mode == 0) {
		char ch;
		ch = getchar();
		memory[blindex] = (unsigned char)ch;
	} else if (mode == 1) {
		int ch;
		scanf("%d", &ch);
		memory[blindex] = (unsigned char)ch;
	}
}

void routeIO(char c[50][200]) {
	if (strcmp(c[0], "PRINT") == 0) {
		if (c[1][0] != '\0') {
			if (strcmp(c[1], "CHAR") == 0) {
				ioPrint(0, 1);
			} else if (strcmp(c[1], "DEC") == 0) {
				ioPrint(1, 1);
			} else if (strcmp(c[1], "BIN") == 0) {
				ioPrint(2, 1);
			} else if (strcmp(c[1], "HEX") == 0) {
				ioPrint(3, 1);
			}
		} else {
			ioPrint(0, 1);
		}
	} else if (strcmp(c[0], "PRINTMEMORY") == 0) {
		ioPrint(0, 0);
	} else if (strcmp(c[0], "PRINTDECMEMORY") == 0) {
		ioPrint(1, 0);
	} else if (strcmp(c[0], "PRINTBINMEMORY") == 0) {
		ioPrint(2, 0);
	} else if (strcmp(c[0], "PRINTHEXMEMORY") == 0) {
		ioPrint(3, 0);
	} else if (strcmp(c[0], "INPUT") == 0) {
		if (c[1][0] != '\0') {
			if (strcmp(c[1], "ASCII") == 0) {
				ioInput(0);
			} else if (strcmp(c[1], "DECIMAL") == 0 || strcmp(c[1], "DEC") == 0) {
				ioInput(1);
			}
		} else {
			ioInput(0);
		}
	} else if (strcmp(c[0], "NEWLINE") == 0) {
		printf("\n");
	}
}

#endif
