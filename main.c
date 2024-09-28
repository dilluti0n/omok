#include "board.h"
#include "util.h"
#include "game.h"

int main()
{
	game_init();

	while (1) {
		int x, y;
		char pind = toggle('O', 'X');

		input(pind, &x, &y);
		board_store(pind, x, y);
		if (board_iswin(pind, x, y))
			game_win(pind);
	}
}
