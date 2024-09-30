#include "game.h"
#include <linux/limits.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include "util.h"
#include "board.h"
#include "io.h"
#include "console.h"
#include "cursor.h"

#define MAXLINE 255

static struct termios oldterm;
static volatile sig_atomic_t lock = 0;

void game_init()
{
	struct termios term;
	tcgetattr(STDIN_FILENO, &oldterm);
	lock = 1;
	term = oldterm;
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	printf("\e[?25l");	/* hide cursor */
	Signal(SIGINT, sigint_handler);
	board_init();
}

void game_turn()
{
	struct game_context turn;

	turn.pind = toggle('O', 'X');

	char *occupied[] = {"Cannot place it there", NULL};

	cursor_init();
	for (;;) {
		char cmd[MAXLINE];

		cursor_update(&turn.x, &turn.y);
		turn.cannot_place = board_isoccupied(turn.x, turn.y);
		io_render_inputp(turn.pind, '#', turn.x, turn.y,
				 turn.cannot_place? occupied : NULL);
		enum key keycode;
		if ((keycode = io_readkey()) != KEY_UNDEF) {
			sprintf(cmd, "press %d", keycode);
			console_execline(cmd, &turn);
		}
		if (cursor_ismoved())
			break;
	}
	board_store(turn.pind, turn.x, turn.y);
	if (board_iswin(turn.pind, turn.x, turn.y))
		game_win(turn.pind);
}

void game_win(char pind)
{
	printf("\033[H\033[2J"); /* clear */
	printf("%c win\n", pind);
	board_print();
	game_finish(0);
}

/* should be signal-safe */
void game_finish(int exitcode)
{
	if (lock == 1)
		tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
	write(STDOUT_FILENO, "\e[?25h", sizeof("\e[?25h") - 1);
	_exit(exitcode);
}
