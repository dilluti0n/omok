#include "util.h"
#include "keymap.h"
#include <stdio.h>
#include "board.h"

enum key io_readkey()
{
	char c;
	for (;;) {
		c = getchar();
		if (c == '\033') {
			getchar(); /* jump '[' */
			switch(getchar()) {
			case 'A':
				return KEY_UP;
			case 'B':
				return KEY_DOWN;
			case 'C':
				return KEY_RIGHT;
			case 'D':
				return KEY_LEFT;
			}
		} else {
			switch (c) {
			case 'w':
			case 'W':
				return KEY_W;
			case 'a':
			case 'A':
				return KEY_A;
			case 'd':
			case 'D':
				return KEY_D;
			case 's':
			case 'S':
				return KEY_S;
			case '\n':
				return KEY_RET;
			}
		}
	}
}

void io_render_inputp(char pind, char cursor, int cx, int cy, char **msgs)
{
	printf("\033[H\033[2J"); /* clear */
	printf("\t\t%c's turn\n", pind);
	for (int i = 1; i < MAXBOARD; i++)
		printf("__");
	printf("_\n");
	board_render(cursor, cx, cy);
	for (int i = 1; i < MAXBOARD; i++)
		printf("--");
	printf("-\n[");
	while (msgs != NULL && *msgs != NULL)
		printf("%s\n", *msgs++);
	printf("]");
#ifdef DEBUG
	printf("vx: %d vy: %d\nvalueofboard: %c\n",
	       vx, vy, valueofboard(vx, vy));
#endif
}
