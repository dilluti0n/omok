#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "console.h"
#include "keymap.h"
#include "game.h"


struct command {
	const char *name;
	int (*func)(int, char **, struct game_context *);
};

/* Should be in lexical order except unknown */
enum cmd {
	CMD_PRESS,
	CMD_SETCURSOR,
	CMD_UNKNOWN,
};

static const char *prompt = ">> ";

static int find_str_bsearch(const char **srclist, const char *str);
static int cmd_cmp(const void *a, const void *b);
static enum cmd findcmd(const char *cmd);
static int console_action(int argc, char **argv);
static int console_press(int argc, char **argv, struct game_context *context);
static int console_setcursor(int argc, char **argv,
			     struct game_context *context);

static const struct command cmdtable[] = {
	[CMD_PRESS] = {"press", &console_press},
	[CMD_SETCURSOR] = {"setcursor", &console_setcursor},
	[CMD_UNKNOWN] = NULL,
};

static int cmd_cmp(const void *a, const void *b)
{
	return strcmp((const char *)a, ((struct command *)b)->name);
}

static enum cmd findcmd(const char *cmd)
{
	/* const struct command *found = bsearch(cmd, cmdtable, sizeof(cmdtable) - 1, */
	/* 				      sizeof(struct command), */
	/* 				      &cmd_cmp); */
	/* if (found != NULL) */
	/* 	return (enum cmd) (found - cmdtable); */
	/* return CMD_UNKNOWN; */

	int i;
	for (i = 0; i < CMD_UNKNOWN && strcmp(cmdtable[i].name, cmd); i++)
		;
	return i;
}

int console_exec(int argc, char **argv, struct game_context *context)
{
	const char *command;
	if (argv == NULL || (command = argv[0]) == NULL)
		return 1;
	int cmdcode = findcmd(command);
	if (cmdcode == CMD_UNKNOWN)
		return 2;
	(*cmdtable[cmdcode].func)(argc, argv, context);
	return 0;
}

int console_execline(const char *line, struct game_context *context)
{
	int argc = 0, ret;
	char *token, *cline = strdup(line), **argv = NULL;

	token = strtok(cline, " ");
	while (token != NULL) {
		argv = realloc(argv, sizeof(char *) * (argc + 1));
		argv[argc++] = strdup(token);
		token = strtok(NULL, " ");
	}
	free(cline);
	ret = console_exec(argc, argv, context);
	free(argv);
	return ret;
}

static int console_press(int argc, char **argv, struct game_context *context)
{
	if (argc != 2) {
		fprintf(stderr, "press: wrong number of arguments\n");
		return 1;
	}
	int tmp = isdigit(argv[1][0])? atoi(argv[1]) : keymap_keycode(argv[1]);
	if (tmp < 0 || tmp >= KEY_UNDEF) {
		fprintf(stderr, "press: wrong argument\n");
		return 1;
	}

	keymap_func(tmp)(context);
	return 0;
}

static int console_setcursor(int argc, char **argv,
			     struct game_context *context)
{
	return 0;
}
