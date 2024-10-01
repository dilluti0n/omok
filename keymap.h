#ifndef KEYMAP_H
#define KEYMAP_H

#include "game.h"

enum key {
	KEY_UP = 0,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_W,
	KEY_S,
	KEY_A,
	KEY_D,
	KEY_1,
	KEY_RET,
	KEY_UNDEF,
};

typedef void (*key_func_t)(struct game_context *);

enum key keymap_keycode(const char *str);
int keymap_argc(enum key keycode);
char **keymap_argv(enum key keycode);
key_func_t keymap_func(enum key keycode);

#endif
