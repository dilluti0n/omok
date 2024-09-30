#ifndef GAME_H
#define GAME_H

struct game_context {
	int pind;
	int x, y;
	int cannot_place;
	int ismoved;
};

void game_init();
void game_turn();
void game_win(struct game_context *context);
void game_finish(int exitcode);

#endif
