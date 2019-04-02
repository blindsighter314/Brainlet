#ifndef BL_BF_H_
#define BL_BF_H_

extern unsigned char memory[5242880];
extern long blindex;
extern long memoryLimit;
extern unsigned char BFMode;

int loopCharStarts[255] = {0};
int loopParamStarts[255] = {0};
unsigned char loopDepth = 0; // Max amount of loops: 255
unsigned char ignoreCode = 0;

void bfInterpret(char line[50][200]) {
	int paramScope = 0;
	int charScope = 0;

	while(line[paramScope][0] != '\0') {
		while(line[paramScope][charScope] != '\0') {
			char command = line[paramScope][charScope];

			if (ignoreCode == 0) {
				if (command == '>') {
					blindex++;
					if (blindex > memoryLimit) {
						printf("Error: Index pointer out of range.\n");
						exit(0);
					}
				} else if (command == '<') {
					blindex--;
					if (blindex < 0) {
						printf("Error: Index pointer out of range.\n");
						exit(0);
					}
				} else if (command == '+') {
					memory[blindex]++;
				} else if (command == '-') {
					memory[blindex]--;
				}
			}

			if (command == '[') {
				if (memory[blindex] == 0 && ignoreCode == 0) {
					loopDepth++;
					ignoreCode = loopDepth;
				} else {
					loopDepth++;
					loopCharStarts[loopDepth] = charScope;
					loopParamStarts[loopDepth] = paramScope;
				}
			} else if (command == ']') {
				if (loopDepth == 0) {
					printf("Error: Mismatched BF Loop Brackets.\n");
					exit(0);
				}
				if (memory[blindex] != 0) {
					charScope = loopCharStarts[loopDepth];
					paramScope = loopParamStarts[loopDepth];
				} else {
					if (ignoreCode == loopDepth) {
						ignoreCode = 0;
					}
					loopDepth--;
				}
			}

			charScope++;
		}

		paramScope++;
		charScope = 0;
	}
}

#endif
