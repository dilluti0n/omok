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
			printf("%c ", (i == p->x && j == p->y)? cursor : board[i][j]);
		printf("\n");
	}
}

int board_isoccupied(struct game_context *p)
{
	return board[p->x][p->y] != BOARD_DEFAULT_INDICATOR;
}

void board_store(struct game_context *p)
{
	if (p->x > MAXBOARD - 1 || p->y > MAXBOARD - 1 || p->x < 0 || p->y < 0)
		return;

	board[p->x][p->y] = p->pind;
}

int board_iswin(struct game_context *p)
{
	int i, j, cnt = 0;
	for (i = p->y; i < MAXBOARD && board[p->x][i] == p->pind; i++)
		cnt++;
	for (i = p->y - 1; i >= 0 && board[p->x][i] == p->pind; i--)
		cnt++;
	if (cnt >= 5)
		return 1;
	cnt = 0;
	for (j = p->x; j < MAXBOARD && board[j][p->y] == p->pind; j++)
		cnt++;
	for (j = p->x - 1; j >= 0 && board[j][p->y] == p->pind; j--)
		cnt++;
	if (cnt >= 5)
		return 1;
	cnt = 0;
	for (i = p->x, j = p->y; j < MAXBOARD && i < MAXBOARD && board[i][j] == p->pind; i++, j++)
		cnt++;
	for (i = p->x - 1, j = p->y - 1; j >= 0 && i >= 0 && board[i][j] == p->pind; i--, j--)
		cnt++;
	if (cnt >= 5)
		return 1;
	cnt = 0;
	for (i = p->x, j = p->y; j < MAXBOARD && i >= 0 && board[i][j] == p->pind; i--, j++)
		cnt++;
	for (i = p->x - 1, j = p->y - 1; j >= 0 && i >= 0 && board[i][j] == p->pind; i++, j--)
		cnt++;
	if (cnt >= 5)
		return 1;
	return 0;
}
