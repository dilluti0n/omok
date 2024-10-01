#include "game.h"

int main()
{
	game_init();
	game_start();

	for (;;)
		game_turn();
}
