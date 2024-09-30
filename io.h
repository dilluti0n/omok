#ifndef IO_H
#define IO_H

#include "keymap.h"

enum key io_readkey();
void io_render_inputp(struct game_context *p, char cursor, char **msgs);

#endif
