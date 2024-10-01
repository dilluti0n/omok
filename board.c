#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "board.h"

#define BOARD_DEFAULT_INDICATOR '+'

static char board[MAXBOARD][MAXBOARD];

void board_init()
{
	memset(board, BOARD_DEFAULT_INDICATOR, sizeof(board));
}

void board_print()
{
	for (int i = 0; i < MAXBOARD; i++) {
		for (int j = 0; j < MAXBOARD; j++)
			printf("%c ", board[i][j]);
		printf("\n");
	}
}

void board_render(struct game_context *p, char cursor)
{
	for (int i = 0; i < MAXBOARD; i++) {
		for (int j = 0; j < MAXBOARD; j++)
			printf("%c ",
			       (i == p->xpos &&
				j == p->ypos)? cursor : board[i][j]);
		printf("\n");
	}
}

int board_isoccupied(struct game_context *p)
{
	return board[p->xpos][p->ypos] != BOARD_DEFAULT_INDICATOR;
}

void board_store(struct game_context *p)
{
	if (p->xpos > MAXBOARD - 1 || p->ypos > MAXBOARD - 1 || p->xpos < 0 || p->ypos < 0)
		return;

	board[p->xpos][p->ypos] = p->pind;
}

int board_count_continuous(struct game_context *p, enum direction direction)
{
	int cnt = 0;

	int i, j;

	switch (direction) {
	case HORIZONTAL:
		for (j = p->xpos; j < MAXBOARD && board[j][p->ypos] == p->pind; j++)
			cnt++;
		for (j = p->xpos - 1; j >= 0 && board[j][p->ypos] == p->pind; j--)
			cnt++;
		return cnt;
	case VERTICAL:
		for (i = p->ypos; i < MAXBOARD && board[p->xpos][i] == p->pind; i++)
			cnt++;
		for (i = p->ypos - 1; i >= 0 && board[p->xpos][i] == p->pind; i--)
			cnt++;
		return cnt;
	case SLASH:
		for (i = p->xpos, j = p->ypos;
		     j < MAXBOARD && i >= 0 && board[i][j] == p->pind;
		     i--, j++)
			cnt++;
		for (i = p->xpos + 1, j = p->ypos - 1;
		     j >= 0 && i >= 0 && board[i][j] == p->pind;
		     i++, j--)
			cnt++;
		return cnt;
	case BACKSLASH:
		for (i = p->xpos, j = p->ypos;
		     j < MAXBOARD && i < MAXBOARD && board[i][j] == p->pind;
		     i++, j++)
			cnt++;
		for (i = p->xpos - 1, j = p->ypos - 1;
		     j >= 0 && i >= 0 && board[i][j] == p->pind;
		     i--, j--)
			cnt++;
		return cnt;
	}
}
