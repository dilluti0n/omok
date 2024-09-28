#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "board.h"
#include "game.h"

static char board[MAXBOARD][MAXBOARD];

static void win(char pind)
{
	printf("\033[H\033[2J"); /* clear */
	printf("%c win\n", pind);
	printboard();
	finish_game(0);
}

void init_board()
{
	memset(board, '+', sizeof(board));
}

void printboard()
{
	for (int i = 0; i < MAXBOARD; i++) {
		for (int j = 0; j < MAXBOARD; j++)
			printf("%c ", board[i][j]);
		printf("\n");
	}
}

void renderboard(int x, int y)
{
	for (int i = 0; i < MAXBOARD; i++) {
		for (int j = 0; j < MAXBOARD; j++)
			printf("%c ", (i == x && j == y)? '#' : board[i][j]);
		printf("\n");
	}
}

int valueofboard(int x, int y)
{
	return board[x][y];
}

void move_and_eval(char pind, int x, int y)
{
	if (x > MAXBOARD - 1 || y > MAXBOARD - 1 || x < 0 || y < 0)
		return;

	board[x][y] = pind;

	int i, j, cnt = 0;
	for (i = y; i < MAXBOARD && board[x][i] == pind; i++)
		cnt++;
	for (i = y - 1; i >= 0 && board[x][i] == pind; i--)
		cnt++;
	if (cnt >= 5)
		win(pind);
	cnt = 0;
	for (j = x; j < MAXBOARD && board[j][y] == pind; j++)
		cnt++;
	for (j = x - 1; j >= 0 && board[j][y] == pind; j--)
		cnt++;
	if (cnt >= 5)
		win(pind);
	cnt = 0;
	for (i = x, j = y; j < MAXBOARD && i < MAXBOARD && board[i][j] == pind; i++, j++)
		cnt++;
	for (i = x - 1, j = y - 1; j >= 0 && i >= 0 && board[i][j] == pind; i--, j--)
		cnt++;
	if (cnt >= 5)
		win(pind);
	cnt = 0;
	for (i = x, j = y; j < MAXBOARD && i >= 0 && board[i][j] == pind; i--, j++)
		cnt++;
	for (i = x - 1, j = y - 1; j >= 0 && i >= 0 && board[i][j] == pind; i++, j--)
		cnt++;
	if (cnt >= 5)
		win(pind);
}
