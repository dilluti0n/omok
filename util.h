#ifndef UTIL_H
#define UTIL_H

#include <signal.h>

typedef void handler_t(int);

enum key {
	UNDEF = 0,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	RET,
};

void input(char pind, int *x, int *y);
int toggle(int first, int second);
handler_t *Signal(int signum, handler_t *handler);
void sigint_handler(int sig);
enum key readkey();

#endif
