#ifndef CURSOR_H
#define CURSOR_H

#include "game.h"

void cursor_init();
void cursor_diff_set(int dx, int dy);
int cursor_set(int x, int y);
void cursor_update(struct game_context *context);

#endif
