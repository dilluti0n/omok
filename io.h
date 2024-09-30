#ifndef IO_H
#define IO_H

#include "keymap.h"

enum key io_readkey();
void io_render_inputp(char pind, char cursor, int cx, int cy, char **msgs);

#endif
