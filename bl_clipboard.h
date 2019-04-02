#ifndef BL_CLIPBOARD_H_
#define BL_CLIPBOARD_H_

extern unsigned char memory[5242880];
extern long blindex;
extern long memoryLimit;

void routeClipboard(char c[50][200]) {
	if (strcmp(c[0], "CUT") == 0) {
		memory[0] = memory[blindex];
		memory[blindex] = 0;
	} else if (strcmp(c[0], "COPY") == 0) {
		memory[0] = memory[blindex];
	} else if (strcmp(c[0], "PASTE") == 0) {
		memory[blindex] = memory[0];
	}
}

#endif
