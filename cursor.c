#include "board.h"
#include "game.h"
#include "cursor.h"

#define X_MIN 0
#define Y_MIN 0
#define X_MAX (MAXBOARD - 1)
#define Y_MAX (MAXBOARD - 1)
#define X_DEFAULT 0
#define Y_DEFAULT 0

struct cursor {
	int x, y;
} static cursor;

void cursor_init()
{
	cursor.x = X_DEFAULT;
	cursor.y = Y_DEFAULT;
}

void cursor_diff_set(int dx, int dy)
{
	cursor_set(cursor.x + dx, cursor.y + dy);
}

int cursor_set(int x, int y)
{
	if (x < X_MIN || x > X_MAX || y < Y_MIN || y > Y_MAX)
		return 1;
	cursor.x = x;
	cursor.y = y;
	return 0;
}

void cursor_update(struct game_context *context)
{
	context->xpos = cursor.x;
	context->ypos = cursor.y;
}
