#ifndef BL_LIBS_H_
#define BL_LIBS_H_

extern unsigned char libraries[7];

void routeLibrary(char c[50][200]){
	if (strcmp(c[0], "INCLUDE") == 0) {
		if (strcmp(c[1], "MATH") == 0) {
			libraries[1] = 1;
		} else if (strcmp(c[1], "MEMORY") == 0) {
			libraries[2] = 1;
		} else if (strcmp(c[1], "IO") == 0) {
			libraries[3] = 1;
		} else if (strcmp(c[1], "LOGIC") == 0) {
			libraries[4] = 1;
		} else if (strcmp(c[1], "CLIPBOARD") == 0) {
			libraries[5] = 1;
		} else if (strcmp(c[1], "RANDOM") == 0) {
			libraries[6] = 1;
		} else if (strcmp(c[1], "ALL") == 0) {
			for (int i = 1; i <= 6; i++) {
				libraries[i] = 1;
			}
		}
	} else if (strcmp(c[0], "EXCLUDE") == 0) {
		if (strcmp(c[1], "MATH") == 0) {
			libraries[1] = 0;
		} else if (strcmp(c[1], "MEMORY") == 0) {
			libraries[2] = 0;
		} else if (strcmp(c[1], "IO") == 0) {
			libraries[3] = 0;
		} else if (strcmp(c[1], "LOGIC") == 0) {
			libraries[4] = 0;
		} else if (strcmp(c[1], "CLIPBOARD") == 0) {
			libraries[5] = 0;
		} else if (strcmp(c[1], "RANDOM") == 0) {
			libraries[6] = 0;
		} else if (strcmp(c[1], "ALL") == 0) {
			for (int i = 1; i <= 6; i++) {
				libraries[i] = 0;
			}
		}
	}
}

#endif
