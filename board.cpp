#include <iostream>
#include <cstring>
#include <cstdlib>
#include "board.h"

#define MAXBOARD 10

static char board[MAXBOARD][MAXBOARD];

using namespace std;

static void win(char pind) {
	printboard();
	cout << pind << " win" << endl;
	exit(0);
}

void init_game() {
	memset(board, '+', sizeof(board));
}

void printboard() {
	cout << "\033[H\033[2J";
	cout << ' ';
	int i;
	for (i = 0; i < MAXBOARD; i++)
		cout << ' ' << i;
	cout << endl;
	for (i = 0; i < MAXBOARD; i++) {
		int j;
		cout << i << ' ';
		for (j = 0; j < MAXBOARD; j++)
			cout << board[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

int valueofboard(int x, int y) { return board[y][x]; }

void move_and_eval(char pind, int x, int y) {
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
