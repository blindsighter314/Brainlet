#ifndef BL_LOGIC_H_
#define BL_LOGIC_H_

extern int ignoreBLCode;

int logicDepth = 0;
int logicStarts[256];
int loopCounter[256];
int loopCounterInverse[256];
int loopDeepest = 0;

long anchors[256];

extern int line;

void routeLogic(char c[50][200]) {
	if (strcmp(c[0], "IF") == 0) {
        logicDepth++;

		if (ignoreBLCode == 0) {
			if (strcmp(c[2], "=") == 0) {
				if (atoi(c[1]) != atoi(c[3])) {
					ignoreBLCode = (logicDepth + 2);
				}
			} else if (strcmp(c[2], "!=") == 0 || strcmp(c[2], "~=") == 0) {
				if (atoi(c[1]) == atoi(c[3])) {
					ignoreBLCode = (logicDepth + 2);
				}
			} else if (strcmp(c[2], "<") == 0) {
                if (atoi(c[1]) >= atoi(c[3])) {
                    ignoreBLCode = (logicDepth + 2);
                }
            } else if (strcmp(c[2], ">") == 0) {
                if (atoi(c[1]) <= atoi(c[3])) {
                    ignoreBLCode = (logicDepth + 2);
                }
            } else if (strcmp(c[2], "<=") == 0) {
                if (atoi(c[1]) > atoi(c[3])) {
                    ignoreBLCode = (logicDepth + 2);
                }
            } else if (strcmp(c[2], ">=") == 0) {
                if (atoi(c[1]) < atoi(c[3])) {
                    ignoreBLCode = (logicDepth + 2);
                }
            }
		}
	} else if (strcmp(c[0], "END") == 0) {
        if (loopCounter[logicDepth] >= 1) {
            line = logicStarts[logicDepth];
            loopCounter[logicDepth]--;
            loopCounterInverse[logicDepth]++;

            if (loopCounter[logicDepth] == 0) {
                logicDepth--;
            }
        } else if (ignoreBLCode == (logicDepth + 2)) {
            ignoreBLCode = 0;
            logicDepth--;
        } else {
            if (loopCounter[logicDepth] == 0) {
                logicDepth--;
            }
        }
    } else if (strcmp(c[0], "LOOP") == 0) {
        logicDepth++;

        if (logicDepth > loopDeepest) {
            loopDeepest = logicDepth;
        }

        if (ignoreBLCode == 0) {
            loopCounter[logicDepth] = atoi(c[1]) - 1;
            loopCounterInverse[logicDepth] = 1;
            logicStarts[logicDepth] = line;
        }
    } else if (strcmp(c[0], "BREAKLOOP") == 0 && ignoreBLCode == 0) {
        ignoreBLCode = (loopDeepest + 2);
        loopCounter[loopDeepest] = 0;
    } else if (strcmp(c[0], "CONDITIONALJUMP") == 0 && ignoreBLCode == 0) {
        if (strcmp(c[2], "=") == 0) {
            if (atoi(c[1]) == atoi(c[3])) {
                line = (atoi(c[4]) - 2);
            }
        } else if (strcmp(c[2], "!=") == 0 || strcmp(c[2], "~=") == 0) {
            if (atoi(c[1]) != atoi(c[3])) {
                line = (atoi(c[4]) - 2);
            }
        } else if (strcmp(c[2], "<") == 0) {
            if (atoi(c[1]) < atoi(c[3])) {
                line = (atoi(c[4]) - 2);
            }
        } else if (strcmp(c[2], ">") == 0) {
            if (atoi(c[1]) > atoi(c[3])) {
                line = (atoi(c[4]) - 2);
            }
        } else if (strcmp(c[2], "<=") == 0) {
            if (atoi(c[1]) <= atoi(c[3])) {
                line = (atoi(c[4]) - 2);
            }
        } else if (strcmp(c[2], ">=") == 0) {
            if (atoi(c[1]) >= atoi(c[3])) {
                line = (atoi(c[4]) - 2);
            }
        }
    } else if (strcmp(c[0], "ANCHOR") == 0 && ignoreBLCode == 0) {
        if (c[1][0] != '\0' && c[2][0] != '\0') {
            anchors[atoi(c[1])] = (atoi(c[2]) - 2);
        }
    } else if (strcmp(c[0], "JUMPANCHOR") == 0 && ignoreBLCode == 0 && c[1][0] != '\0') {
        line = anchors[atoi(c[1])];
    } else if (strcmp(c[0], "JUMPLINE") == 0 && ignoreBLCode == 0 && c[1][0] != '\0') {
        line = atoi(c[1]) - 2;
    }
}

#endif
