#include "board.h"
#include "cursor.h"

#define X_MIN 0
#define Y_MIN 0
#define X_MAX (MAXBOARD - 1)
#define Y_MAX (MAXBOARD - 1)
#define X_DEFAULT 0
#define Y_DEFAULT 0

struct cursor {
	int x, y;
	int ismoved;
} static cursor;

void cursor_init()
{
	cursor.x = X_DEFAULT;
	cursor.y = Y_DEFAULT;
	cursor.ismoved = 0;
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

void cursor_update(int *x, int *y)
{
	*x = cursor.x;
	*y = cursor.y;
}

void cursor_move()
{
	cursor.ismoved = 1;
}

int cursor_ismoved()
{
	return cursor.ismoved;
}
