#ifndef CURSOR_H
#define CURSOR_H

void cursor_init();
void cursor_diff_set(int dx, int dy);
int cursor_set(int x, int y);
void cursor_update(int *cx, int *cy);
void cursor_move();
int cursor_ismoved();

#endif
