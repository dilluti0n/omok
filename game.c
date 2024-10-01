#include "game.h"
#include <linux/limits.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include "keymap.h"
#include "util.h"
#include "board.h"
#include "io.h"
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
	printf(ASCII_HIDE_CURSOR);
	Signal(SIGINT, sigint_handler);
	Signal(SIGSEGV, sigsegv_handler);
	board_init();
}

void game_start()
{
	io_print_startup();
	while (io_readkey() != KEY_1)
		;
}

void game_turn()
{
	struct game_context turn;
	const char *msg_occupied = "Cannot place it there";
	const char *msg[] = {msg_occupied, NULL};

	turn.pind = toggle('O', 'X');
	cursor_init();
	for (;;) {
		turn.flag = 0;
		cursor_update(&turn);
		if (board_isoccupied(&turn))
			turn.flag |= GC_FLAG_CANNOT_PLACE;
		io_render_inputp(&turn, '#',
				 GC_CANNOT_PLACE(turn.flag)? msg : NULL);
		enum key keycode;
		if ((keycode = io_readkey()) != KEY_UNDEF)
			keymap_func(keycode)(&turn);
		if (GC_ISMOVED(turn.flag))
			break;
	}

	board_store(&turn);

	if (game_iswin(&turn))
		game_win(&turn);
}

int game_iswin(struct game_context *context)
{
	if (board_count_continuous(context, VERTICAL) >= 5 ||
	    board_count_continuous(context, HORIZONTAL) >= 5 ||
	    board_count_continuous(context, SLASH) >= 5 ||
	    board_count_continuous(context, BACKSLASH) >= 5)
		return 1;
	return 0;
}

void game_win(struct game_context *context)
{
	printf(ASCII_CLEAR);
	printf("%c win\n", context->pind);
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
