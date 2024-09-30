#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "util.h"
#include "game.h"

int toggle(int first, int second)
{
	static int t = 0;
	t = ~t;
	return t? first : second;
}

void sigint_handler(int sig)
{
	write(STDOUT_FILENO, "\ninturrupt by user\n",
	      sizeof("\ninturrupt by user\n") - 1);
	game_finish(1);
}

void sigsegv_handler(int sig)
{
	write(STDOUT_FILENO, "\nSegment fault\n",
	      sizeof("\nSegment fault\n") - 1);
	game_finish(2);
}

/* wrapper for sigaction */
handler_t *Signal(int signum, handler_t *handler)
{
	struct sigaction action, old_action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask); /* block sigs of type being handled */
	action.sa_flags = SA_RESTART; /* restart syscalls if possible */

	if (sigaction(signum, &action, &old_action) < 0)
		perror("Signal error");
	return old_action.sa_handler;
}

void *Malloc(size_t size)
{
	void *ret;
	if ((ret = malloc(size)) == NULL) {
		perror("malloc:");
		exit(2);
	}
	return ret;
}
