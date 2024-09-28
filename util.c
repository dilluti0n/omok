#include <stdio.h>
#include "board.h"

void input(char pind, int *x, int *y) {
	for (;;) {
		printf("%c's turn\n", pind);
		printf("\t\tx :");
		scanf("%d", x);
		printf("\t\ty :");
		scanf("%d", y);
		int vx, vy;
		if ((vx = *x) < 0 || vx > MAXBOARD || (vy = *y) < 0 ||
		    vy > 9 || valueofboard(vx, vy) != '+') {
			fprintf(stderr, "cannot place to this location\n");
			continue;
		}
		break;
	}
}

int toggle(int first, int second) {
	static int t = 0;
	t = ~t;
	return t? first : second;
}
