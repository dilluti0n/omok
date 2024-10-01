#include "io.h"
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
			case '1':
				return KEY_1;
			case '\n':
				return KEY_RET;
			}
		}
	}
}

void io_print_startup()
{
	printf(ASCII_CLEAR);
	printf("                       __    \n"
	       " ____   _____   ____ |  | __\n"
	       " /  _ \\ /     \\ /  _ \\|  |/ /\n"
	       "(  <_> )  Y Y  (  <_> )    < \n"
	       " \\____/|__|_|  /\\____/|__|_ \\\n"
	       "             \\/            \\/\n");
	printf("\n");
	printf("\n");
	printf("Press 1 to start...\n");
}

void io_render_inputp(struct game_context *p, char cursor, const char **msgs)
{
	printf(ASCII_CLEAR);
	printf("\t\t%c's turn\n", p->pind);
	for (int i = 1; i < MAXBOARD; i++)
		printf("__");
	printf("_\n");
	board_render(p, cursor);
	for (int i = 1; i < MAXBOARD; i++)
		printf("--");
	printf("-\n\n");
	while (msgs != NULL && *msgs != NULL)
		printf("%s\n", *msgs++);
#ifdef DEBUG
	printf("x: %d y: %d\nvalueofboard: %c\n",
	       p->x, p->y, valueofboard(p->x, p->y));
#endif
}
