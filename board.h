#ifndef BOARD_H
#define BOARD_H

#define MAXBOARD 19

void board_init();
void board_print();
void board_render(int x, int y);
int board_value(int x, int y);
void board_store(char pind, int x, int y);
int board_iswin(char pind, int x, int y);

#endif
