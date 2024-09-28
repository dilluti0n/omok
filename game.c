#include "game.h"
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include "util.h"
#include "board.h"

struct termios oldterm;

void game_init()
{
	struct termios term;
	tcgetattr(STDIN_FILENO, &oldterm);
	term = oldterm;
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	printf("\e[?25l");	/* hide cursor */
	Signal(SIGINT, sigint_handler);
	board_init();
}

void game_win(char pind)
{
	printf("\033[H\033[2J"); /* clear */
	printf("%c win\n", pind);
	board_print();
	game_finish(0);
}

void game_finish(int exitcode)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
	write(STDOUT_FILENO, "\e[?25h", sizeof("\e[?25h") - 1);
	_exit(exitcode);
}
