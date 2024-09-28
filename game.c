#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include "util.h"
#include "board.h"

struct termios oldterm;

void init_game()
{
	struct termios term;
	tcgetattr(STDIN_FILENO, &oldterm);
	term = oldterm;
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	printf("\e[?25l");	/* hide cursor */
	Signal(SIGINT, sigint_handler);
	init_board();
}

void finish_game(int exitcode)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
	write(STDOUT_FILENO, "\e[?25h", sizeof("\e[?25h") - 1);
	_exit(exitcode);
}
