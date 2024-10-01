#ifndef IO_H
#define IO_H

#include "keymap.h"

#define ASCII_CLEAR "\033[H\033[2J"
#define ASCII_HIDE_CURSOR "\e[?25l"

enum key io_readkey();
void io_print_startup();
void io_render_inputp(struct game_context *p, char cursor, const char **msgs);

#endif
