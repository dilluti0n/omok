#ifndef CONSOLE_H
#define CONSOLE_H

#include "game.h"

int console_exec(int argc, char **argv, struct game_context *context);
int console_execline(const char *line, struct game_context *context);

#endif
