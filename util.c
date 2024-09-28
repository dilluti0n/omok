#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "board.h"
#include "util.h"
#include "game.h"

void input(char pind, int *x, int *y)
{
	int vx = 0, vy = 0;
	for (;;) {
		int cannot_place = 0;
		printf("\033[H\033[2J"); /* clear */
		printf("\t\t%c's turn\n", pind);
		for (int i = 1; i < MAXBOARD; i++)
			printf("__");
		printf("_\n");
		renderboard(vx, vy);
		for (int i = 1; i < MAXBOARD; i++)
			printf("--");
		printf("- [");
		if (valueofboard(vx, vy) != '+') {
			cannot_place = 1;
			printf("Cannot place it there");
		}
		printf("]");
#ifdef DEBUG
		printf("vx: %d vy: %d\nvalueofboard: %c\n",
		       vx, vy, valueofboard(vx, vy));
#endif
		enum key pkey = readkey();
		switch (pkey) {
		case UP:
			if (vx == 0)
				continue;
			vx--;
			break;
		case DOWN:
			if (vx == MAXBOARD - 1)
				continue;
			vx++;
			break;
		case RIGHT:
			if (vy == MAXBOARD - 1)
				continue;
			vy++;
			break;
		case LEFT:
			if (vy == 0)
				continue;
			vy--;
			break;
		case RET:
			if (cannot_place)
				continue;
			*x = vx;
			*y = vy;
			return;
		}
	}
}

enum key readkey()
{
	char c;
	for (;;) {
		c = getchar();
		if (c == '\033') {
			getchar(); /* jump '[' */
			switch(getchar()) {
			case 'A':
				return UP;
			case 'B':
				return DOWN;
			case 'C':
				return RIGHT;
			case 'D':
				return LEFT;
			}
		} else if (c == '\n') {
			return RET;
		}
	}
}

int toggle(int first, int second)
{
	static int t = 0;
	t = ~t;
	return t? first : second;
}

void sigint_handler(int sig)
{
	write(STDOUT_FILENO, "\ninturrupt by user\n",
	      sizeof("\ninturrupt by user\n") - 1);
	finish_game(1);
}

/* wrapper for sigaction */
handler_t *Signal(int signum, handler_t *handler)
{
	struct sigaction action, old_action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask); /* block sigs of type being handled */
	action.sa_flags = SA_RESTART; /* restart syscalls if possible */

	if (sigaction(signum, &action, &old_action) < 0)
		perror("Signal error");
	return old_action.sa_handler;
}
