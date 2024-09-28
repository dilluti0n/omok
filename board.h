#ifndef BOARD_H
#define BOARD_H

#define MAXBOARD 19

void init_board();
void printboard();
void renderboard(int x, int y);
int valueofboard(int x, int y);
void move_and_eval(char pind, int x, int y);

#endif
