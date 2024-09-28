#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "board.h"
#include "util.h"

void input(char pind, int *x, int *y)
{
	for (;;) {
		printf("%c's turn\n", pind);
		printf("\t\tx :");
		scanf("%d", x);
		printf("\t\ty :");
		scanf("%d", y);
		int vx, vy;
		if ((vx = *x) < 0 || vx > MAXBOARD || (vy = *y) < 0 ||
		    vy > 9 || valueofboard(vx, vy) != '+') {
			fprintf(stderr, "cannot place to this location\n");
			continue;
		}
		break;
	}
}

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
	return finish_game(1);
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
