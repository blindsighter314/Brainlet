#ifndef BL_ROUTING_H_
#define BL_ROUTING_H_

#include "bl_libs.h"
#include "bl_math.h"
#include "bl_memory.h"
#include "bl_io.h"
#include "bl_logic.h"
#include "bl_clipboard.h"
#include "bl_rand.h"

extern unsigned char libraries[7];
extern unsigned char memory[5242880];
extern long blindex;

int ignoreBLCode = 0;

char lib_Libs[2][8] = {"INCLUDE", "EXCLUDE"};
char lib_Math[6][6] = {"ADD", "SUB", "PROD", "DIV", "MOD", "GRAZE"};
char lib_Memory[7][10] = {"PARTITION", "STEP", "JUMP", "SET", "RANGE", "TYPE", "TYPECAST"};
char lib_IO[7][15] = {"PRINT", "PRINTMEMORY", "PRINTDECMEMORY", "PRINTBINMEMORY", "PRINTHEXMEMORY", "INPUT", "NEWLINE"};
char lib_Logic[8][16] = {"IF", "END", "LOOP", "BREAKLOOP", "CONDITIONALJUMP", "ANCHOR", "JUMPANCHOR", "JUMPLINE"};
char lib_Clipboard[3][6] = {"CUT", "COPY", "PASTE"};

void routeCommand(char command[50][200]) {
	// c in this context is the command we're routing
	unsigned char found = 0;
	int paramScope = 0;

	char c[50][200]; // Ew
	memset(c, '\0', 10000);

	int i = 0;

	// All of this nonsense is to get variables ([CUR], [0]) Working.
	while (command[i][0] != '\0') {
		strcpy(c[i], command[i]);
		i++;
	}

	while (c[paramScope][0] != '\0') {
		if (c[paramScope][0] == '[') {
			memmove(c[paramScope], c[paramScope] + 1, strlen(c[paramScope]));
			c[paramScope][strlen(c[paramScope]) - 1] = '\0';
			
			char buffer[4];

			if (strcmp(c[paramScope], "CUR") == 0) {
//				strcpy(c[paramScope], itoa(memory[blindex], buffer, 10));
				sprintf(buffer, "%d", memory[blindex]);
				strcpy(c[paramScope], buffer);
			} else {
//				strcpy(c[paramScope], itoa(memory[atoi(c[paramScope])], buffer, 10));
				sprintf(buffer, "%d", memory[atoi(c[paramScope])]);
				strcpy(c[paramScope], buffer);
			}
		}
		paramScope++;
	}

	if (ignoreBLCode == 0) {
		for (int i = 0; i <= 1; i++) {
			if (strcmp(lib_Libs[i], c[0]) == 0) {
				found++;
				routeLibrary(c);
				break;
			}
		}
	}

	if (found == 0 && libraries[1] == 1 && ignoreBLCode == 0) {
		for (int i = 0; i <= 5; i++) {
			if (strcmp(lib_Math[i], c[0]) == 0) {
				found++;
				routeMath(c);
				break;
			}
		}
	}

	if (found == 0 && libraries[2] == 1 && ignoreBLCode == 0) {
		for (int i = 0; i <= 6; i++) {
			if (strcmp(lib_Memory[i], c[0]) == 0) {
				found++;
				routeMemory(c);
				break;
			}
		}
	}

	if (found == 0 && libraries[3] == 1 && ignoreBLCode == 0) {
		for (int i = 0; i <= 6; i++){
			if (strcmp(lib_IO[i], c[0]) == 0) {
				found++;
				routeIO(c);
				break;
			}
		}
	}

	if (found == 0 && libraries[4] == 1) {
		for (int i = 0; i <= 7; i++) {
			if (strcmp(lib_Logic[i], c[0]) == 0) {
				found++;
				routeLogic(c);
				break;
			}
		}
	}

	if (found == 0 && libraries[5] == 1 && ignoreBLCode == 0) {
		for (int i = 0; i <= 2; i++) {
			if (strcmp(lib_Clipboard[i], c[0]) == 0) {
				found++;
				routeClipboard(c);
				break;
			}
		}
	}

	if (found == 0 && libraries[6] == 1 && strcmp("RAND", c[0]) == 0 && ignoreBLCode == 0) {
		routeRand(c);
		found++;
	}

	if (found == 0 && c[0][0] != '#' && ignoreBLCode == 0) {
		printf("Warning: Command not found %s\n", c[0]);
	}
}

#endif
