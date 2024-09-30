#ifndef UTIL_H
#define UTIL_H

#include <signal.h>
#include "keymap.h"

typedef void handler_t(int);

void input(char pind, int *x, int *y);
int toggle(int first, int second);
handler_t *Signal(int signum, handler_t *handler);
void sigint_handler(int sig);
void sigsegv_handler(int sig);
enum key readkey();
void *Malloc(size_t size);

#endif
