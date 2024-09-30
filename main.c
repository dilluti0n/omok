#include "game.h"

int main()
{
	game_init();

	for (;;)
		game_turn();
}
