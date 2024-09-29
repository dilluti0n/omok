#ifndef UTIL_H
#define UTIL_H

#include <signal.h>

typedef void handler_t(int);

enum key {
	UNDEF = 0,
	KEY_UP,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_W,
	KEY_S,
	KEY_A,
	KEY_D,
	KEY_RET,
};

void input(char pind, int *x, int *y);
int toggle(int first, int second);
handler_t *Signal(int signum, handler_t *handler);
void sigint_handler(int sig);
enum key readkey();

#endif
