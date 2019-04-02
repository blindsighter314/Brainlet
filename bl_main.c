#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bl_bf.h"
#include "bl_routing.h"

char commands[10000][50][200]; // Limits: 10000 lines; 50 params each; 200 chars each; 95.367 MB

unsigned char memory[5242880];
long blindex = 0;
long memoryLimit = 0;
long highestAllocation = 0;
unsigned char BFMode = 0;

unsigned char seed[100];
unsigned char seedLocation = 0;

int line = 0;

/*
0 = libraries; can't be disabled
1 = Math
2 = Memory
3 = IO
4 = Logic
5 = Clipboard
6 = Random
*/
unsigned char libraries[7] = {1, 1, 1, 1, 1, 1, 1};

void execute() {
	if (commands[0][0][0] == '\0') {
		printf("Error: No script to execute");
		exit(0);
	}

	while(commands[line][0][0] != '\0') {
		if (BFMode == 0) {
			if (strcmp(commands[line][0], "EXEC") == 0) {
				BFMode++;
			} else {
				routeCommand(commands[line]);
			}
		} else {
			if (strcmp(commands[line][0], "ENDEXEC") == 0) {
				BFMode--;
			} else {
				bfInterpret(commands[line]);
			}
		}

		line++;
	}
}

int main() {
	FILE *fp;
	char line[10000];
	long lineScope = 0;


	fp = fopen("test.bl", "r");
		while (fgets(line, 200, fp) != NULL) {
			if (line[0] != '\n') {
				int paramScope = 0;
				int paramLength = 0;
				int charScope = 0;
				char str[200];

				while(line[charScope]!= '\n'&& line[charScope]!= '#' && paramScope<= 50 && charScope<= 200) {
					if (line[charScope] != '\t') {
						char c = line[charScope];

						if (c == ' ') {
							if (paramLength != 0) {
								commands[lineScope][paramScope][paramLength] = '\0';
								paramLength = 0;
								paramScope++;
							}
						} else {
							commands[lineScope][paramScope][paramLength] = c;
							paramLength++;
						}
					}

					charScope++;
				}

				if (line[charScope] == '#' && commands[lineScope][0][0] == '\0') {
					commands[lineScope][0][0] = '#';
				}

				if (paramScope > 50) {
					printf("Warning: Too many paramaters on line %d (Max is 50)\n", (lineScope + 1));
				}

				if (charScope > 200) {
					printf("Warning: Too many characters on line %d, paramater %d (Max is 200)\n", (lineScope + 1), (paramScope + 1));
					printf("Be sure the last line in your script is empty!\n");
				}

				lineScope++;
			}
		}
	fclose(fp);
	execute();
	return 0;
}
