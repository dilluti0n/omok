#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "board.h"
#include "util.h"

static char board[MAXBOARD][MAXBOARD];

static void win(char pind)
{
	printboard();
	printf("%c win", pind);
	finish_game(0);
}

void init_board()
{
	memset(board, '+', sizeof(board));
}

void printboard()
{
	printf("\033[H\033[2J"); /* clear */
	printf(" ");
	int i;
	for (i = 0; i < MAXBOARD; i++)
		printf(" %d", i);
	printf("\n");
	for (i = 0; i < MAXBOARD; i++) {
		int j;
		printf("%d ", i);
		for (j = 0; j < MAXBOARD; j++)
			printf("%c ", board[i][j]);
		printf("\n");
	}
	printf("\n");
}

int valueofboard(int x, int y)
{
	return board[y][x];
}

void move_and_eval(char pind, int x, int y)
{
	if (x > MAXBOARD - 1 || y > MAXBOARD - 1 || x < 0 || y < 0)
		return;

	board[y][x] = pind;

	int i, j, cnt = 0;
	for (i = x; i < MAXBOARD && board[y][i] == pind; i++)
		cnt++;
	for (i = x - 1; i >= 0 && board[y][i] == pind; i--)
		cnt++;
	if (cnt >= 5)
		win(pind);
	cnt = 0;
	for (j = y; j < MAXBOARD && board[j][x] == pind; j++)
		cnt++;
	for (j = y - 1; j >= 0 && board[j][x] == pind; j--)
		cnt++;
	if (cnt >= 5)
		win(pind);
	cnt = 0;
	for (i = x, j = y; j < MAXBOARD && i < MAXBOARD && board[j][i] == pind; i++, j++)
		cnt++;
	for (i = x - 1, j = y - 1; j >= 0 && i >= 0 && board[j][i] == pind; i--, j--)
		cnt++;
	if (cnt >= 5)
		win(pind);
	cnt = 0;
	for (i = x, j = y; j < MAXBOARD && i >= 0 && board[j][i] == pind; i++, j--)
		cnt++;
	for (i = x - 1, j = y - 1; j >= 0 && i >= 0 && board[j][i] == pind; i--, j++)
		cnt++;
	if (cnt >= 5)
		win(pind);
}
