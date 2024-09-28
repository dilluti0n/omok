#include "board.h"
#include "util.h"
#include "game.h"

int main()
{
	init_game();

	while (1) {
		int x, y;
		char pind = toggle('O', 'X');

		printboard();
		input(pind, &x, &y);
		move_and_eval(pind, x, y);
	}
}
