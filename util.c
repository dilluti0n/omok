#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "board.h"
#include "util.h"
#include "game.h"

static void render_input_prompt(char pind, char cursor, int cx, int cy,
				char **msgs);

void input(char pind, int *x, int *y)
{
	int cx = 0, cy = 0;
	for (;;) {
		int cannot_place = board_isoccupied(cx, cy);
		char *occupied[] = {"Cannot place it there", NULL};

		render_input_prompt(pind, '#', cx, cy,
				    cannot_place? occupied : NULL);

		switch (readkey()) {
		case KEY_W:
		case KEY_UP:
			if (--cx < 0)
				cx = 0;
			break;
		case KEY_S:
		case KEY_DOWN:
			if (++cx > MAXBOARD - 1)
				cx = MAXBOARD - 1;
			break;
		case KEY_D:
		case KEY_RIGHT:
			if (++cy > MAXBOARD - 1)
				cy = MAXBOARD - 1;
			break;
		case KEY_A:
		case KEY_LEFT:
			if (--cy < 0)
				cy = 0;
			break;
		case KEY_RET:
			if (!cannot_place) {
				*x = cx;
				*y = cy;
			}
			return;
		case UNDEF:
			break;
		}
	}
}

static void render_input_prompt(char pind, char cursor, int cx, int cy, char **msgs)
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

enum key readkey()
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
	game_finish(1);
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
