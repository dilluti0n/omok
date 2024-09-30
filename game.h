#ifndef GAME_H
#define GAME_H

struct game_context {
	int x, y, cannot_place, pind;
};

void game_init();
void game_turn();
void game_win(struct game_context *context);
void game_finish(int exitcode);

#endif
