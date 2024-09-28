#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "board.h"
#include "game.h"

static char board[MAXBOARD][MAXBOARD];

void board_init()
{
	memset(board, '+', sizeof(board));
}

void board_print()
{
	for (int i = 0; i < MAXBOARD; i++) {
		for (int j = 0; j < MAXBOARD; j++)
			printf("%c ", board[i][j]);
		printf("\n");
	}
}

void board_render(int x, int y)
{
	for (int i = 0; i < MAXBOARD; i++) {
		for (int j = 0; j < MAXBOARD; j++)
			printf("%c ", (i == x && j == y)? '#' : board[i][j]);
		printf("\n");
	}
}

int board_value(int x, int y)
{
	return board[x][y];
}

void board_store(char pind, int x, int y)
{
	if (x > MAXBOARD - 1 || y > MAXBOARD - 1 || x < 0 || y < 0)
		return;

	board[x][y] = pind;
}

int board_iswin(char pind, int x, int y)
{
	int i, j, cnt = 0;
	for (i = y; i < MAXBOARD && board[x][i] == pind; i++)
		cnt++;
	for (i = y - 1; i >= 0 && board[x][i] == pind; i--)
		cnt++;
	if (cnt >= 5)
		return 1;
	cnt = 0;
	for (j = x; j < MAXBOARD && board[j][y] == pind; j++)
		cnt++;
	for (j = x - 1; j >= 0 && board[j][y] == pind; j--)
		cnt++;
	if (cnt >= 5)
		return 1;
	cnt = 0;
	for (i = x, j = y; j < MAXBOARD && i < MAXBOARD && board[i][j] == pind; i++, j++)
		cnt++;
	for (i = x - 1, j = y - 1; j >= 0 && i >= 0 && board[i][j] == pind; i--, j--)
		cnt++;
	if (cnt >= 5)
		return 1;
	cnt = 0;
	for (i = x, j = y; j < MAXBOARD && i >= 0 && board[i][j] == pind; i--, j++)
		cnt++;
	for (i = x - 1, j = y - 1; j >= 0 && i >= 0 && board[i][j] == pind; i++, j--)
		cnt++;
	if (cnt >= 5)
		return 1;
	return 0;
}
