#include "keymap.h"
#include "cursor.h"
#include "game.h"
#include <stdlib.h>
#include <string.h>

void upfunc(struct game_context *);
void downfunc(struct game_context *);
void leftfunc(struct game_context *);
void rightfunc(struct game_context *);
void retfunc(struct game_context *);

struct keymap {
	const char *name;
	key_func_t func;
} static keytab[KEY_UNDEF + 1] = {
	[KEY_UP] = {"KEY_UP", upfunc},
	[KEY_DOWN] = {"KEY_DOWN", downfunc},
	[KEY_RIGHT] = {"KEY_RIGHT", rightfunc},
	[KEY_LEFT] = {"KEY_LEFT", leftfunc},
	[KEY_W] = {"KEY_W", upfunc},
	[KEY_S] = {"KEY_S", downfunc},
	[KEY_A] = {"KEY_A", leftfunc},
	[KEY_D] = {"KEY_D", rightfunc},
	[KEY_RET] = {"KEY_RET", retfunc},
	[KEY_UNDEF] = NULL,
};

void upfunc(struct game_context *context)
{
	cursor_diff_set(-1, 0);
}

void downfunc(struct game_context *context)
{
	cursor_diff_set(+1, 0);
}

void leftfunc(struct game_context *context)
{
	cursor_diff_set(0, -1);
}

void rightfunc(struct game_context *context)
{
	cursor_diff_set(0, +1);
}

void retfunc(struct game_context *context)
{
	if (!context->cannot_place)
		cursor_move();
}

static char *keyname[] = {
	[KEY_UP] = "KEY_UP",
	[KEY_DOWN] = "KEY_DOWN",
	[KEY_RIGHT] = "KEY_RIGHT",
	[KEY_LEFT] = "KEY_LEFT",
	[KEY_W] = "KEY_W",
	[KEY_S] = "KEY_S",
	[KEY_A] = "KEY_A",
	[KEY_D] = "KEY_D",
	[KEY_RET] = "KEY_RET",
	[KEY_UNDEF] = NULL,
};

enum key keymap_keycode(const char *str)
{
	int i;
	for (i = 0; i < KEY_UNDEF && strcmp(keyname[i], str); i++)
		;
	return i;
}

key_func_t keymap_func(enum key keycode)
{
	if (keycode != KEY_UNDEF)
		return keytab[keycode].func;
	return NULL;
}
