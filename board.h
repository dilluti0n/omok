#ifndef BOARD_H
#define BOARD_H

#include "game.h"

#define MAXBOARD 19

enum direction {
	HORIZONTAL,
	VERTICAL,
	SLASH,
	BACKSLASH,
};

void board_init();
void board_print();
void board_render(struct game_context *p, char cursor);
int board_isoccupied(struct game_context *p);
void board_store(struct game_context *p);
int board_count_continuous(struct game_context *p, enum direction direction);
int board_iswin(struct game_context *p);

#endif
